/* -*- C++ -*- */

//=============================================================================
/**
 *  @file    RTCosScheduling_PCP_Manager.cpp
 *
 *  $Id$
 *
 *  @author Matt Murphy <murphym@cs.uri.edu>
 */
//=============================================================================

#include "RTCosScheduling_PCP_Manager.h"

#if !defined (__ACE_INLINE__)
#include "RTCosScheduling_PCP_Manager.i"
#endif /* __ACE_INLINE__ */



namespace TAO {

struct
CosSchedulingLockNode *CosSchedulingLockNode::next()
{
  /// INT_MAX is a special value indicating the end of a list
  if (this->next_offset_ == INT_MAX)
    {
      return 0;
    }
  else
    {
      return ACE_reinterpret_cast(CosSchedulingLockNode *,
               (ACE_reinterpret_cast(int, this) + this->next_offset_)
             );
    }
}

void
CosSchedulingLockNode::next(struct CosSchedulingLockNode *next_lock)
{
  /// INT_MAX is a special value indicating the end of a list
  if (next_lock == 0)
    {
      this->next_offset_ = INT_MAX;
    }
  else
    {
      this->next_offset_ =
        (ACE_reinterpret_cast(int, next_lock) -
         ACE_reinterpret_cast(int, this));
    }
}

const CosSchedulingLockNode& CosSchedulingLockNode::operator=(const CosSchedulingLockNode& L)
{
  this->threadID_           = L.threadID_;
  this->priority_ceiling_   = L.priority_ceiling_;
  this->priority_           = L.priority_;
  this->elevated_priority_  = L.elevated_priority_;

  return *this;
}

CosSchedulingLockList::CosSchedulingLockList(CosSchedulingLockNode *lock_array,
  int size,
  ACE_SYNCH_MUTEX *mutex)
{
  ACE_TRY_NEW_ENV
    {
          /*
       *  The pointers to the beginnings of the lists must be globally visible,
       *  so I have chosen to use the first three locks in the array.
       *  lock_array[0].next() (== free_->next()   ) -> start of free list
       *  lock_array[1].next() (== granted_->next()) -> start of granted list
       *  lock_array[2].next() (== pending_->next()) -> start of pending list
       */

      /// start of the free list
      lock_array[0].next(&lock_array[3]);

      /// start with an empty granted list
      lock_array[1].next(0);

      /// start with an empty pending list
      lock_array[2].next(0);

      /// initialize the free list (link together the elements in the array)
      for (int i = 3; i < (size - 1); ++i)
        {
          lock_array[i].next(&lock_array[i + 1]);
           ACE_NEW_THROW_EX(lock_array[i].condition_,
                           ACE_Thread_Condition<ACE_Thread_Mutex>(*mutex),
                           CORBA::NO_MEMORY());
        }
      ACE_TRY_CHECK;
      lock_array[size - 1].next(0); /// terminate the free list


      /// Update the positions
      this->free_ = &lock_array[0];
      this->granted_ = &lock_array[1];
      this->pending_ = &lock_array[2];
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION(ACE_ANY_EXCEPTION,
                         "Error in generating Locklist on ServerScheduler\n");
    }
  ACE_ENDTRY;
}

void
CosSchedulingLockList::destroy(int size)
{
  for (int i = 3; i < size; ++i)
    {
      this->free_[i].condition_->remove();
      delete &free_[i].condition_;
    }
}

int
CosSchedulingLockList::grant_lock(const CosSchedulingLockNode& L)
{
  if (this->free_->next() == 0)
    {
      return 0; /// no free nodes left
    }
  /// take a node from the free list
  CosSchedulingLockNode *new_lock = this->free_->next();
  this->free_->next(this->free_->next()->next());
  *new_lock = L;

  if ((this->granted_->next() == 0)
    || (this->granted_->next()->priority_ceiling_ <= L.priority_ceiling_))
    {
      /// insert at the head of the list
      new_lock->next(this->granted_->next());
      this->granted_->next(new_lock);
    }
  else
    {
      /// find the proper location to insert
      /// the new lock (ordered by priority ceiling)
      CosSchedulingLockNode *current_lock = granted_->next();
      while ((current_lock->next() != 0)
        && (current_lock->next()->priority_ceiling_ > L.priority_ceiling_))
        {
         current_lock = current_lock->next();
        }
      new_lock->next(current_lock->next());
      current_lock->next(new_lock);
    }

  return 1;
}

int
CosSchedulingLockList::defer_lock(const CosSchedulingLockNode& L,
  ACE_SYNCH_MUTEX & mutex)
{
  if (this->free_->next() == 0)
    {
      return 0; /// no free nodes left
    }
  CosSchedulingLockNode *new_lock = free_->next();
  this->free_->next(free_->next()->next());
  *new_lock = L;

  if ((this->pending_->next() == 0)
    ||(this->pending_->next()->priority_ <= L.priority_))
    {
      /// insert at the head of the list
      new_lock->next(this->pending_->next());
      this->pending_->next(new_lock);
    }
  else
    {
      /// find the proper location to insert the new lock
      CosSchedulingLockNode *current_lock = pending_->next();
      while ((current_lock->next() != 0)
        && (current_lock->next()->priority_ceiling_ > L.priority_ceiling_))
        {
          current_lock = current_lock->next();
        }
      new_lock->next(current_lock->next());
      current_lock->next(new_lock);
    }


  if (new_lock->condition_)
    {
      new_lock->condition_->wait(mutex);
      return 1;
    }
  else
    {
    return 0;
    }
}


int
CosSchedulingLockList::release_lock(CosSchedulingLockNode& L)
{
  if (this->granted_->next() == 0)
    {
      return 0;  /// empty list of granted locks
    }

  if (this->granted_->next()->threadID_ == L.threadID_)
    {
      /// remove the lock at the head of the list and put it on the free list

      /// Set the Lock to the next one in the granted list
      L = *(this->granted_->next());

      /// (sets next offset from previous statement)
      L.next(this->granted_->next()->next());

      /// set the next granted's next one to be the next free one
      this->granted_->next()->next(this->free_->next());

      /// Set the next free one to be the next granted one
      this->free_->next(this->granted_->next());

      /// Set the next granted on to be the Lock's next one
      this->granted_->next(L.next());

      /// Set the Locks next on to NULL
      L.next(0);

      return 1;
    }

  /// find the lock to remove
  CosSchedulingLockNode *current_lock = granted_->next();
  while ((current_lock->next() != 0)
    && (current_lock->next()->threadID_ != L.threadID_))
    {
      current_lock = current_lock->next();
    }
  if (current_lock->next() != 0)
    {
      /// removes lock and prepends to the free list, as above
      L = *(current_lock->next());
      L.next(current_lock->next()->next());
      current_lock->next()->next(this->free_->next());
      this->free_->next(current_lock->next());
      current_lock->next(L.next());
      L.next(0);
      return 1;
    }

  return 0;
}

int
CosSchedulingLockList::remove_deferred_lock(CosSchedulingLockNode& L)
{
  if (this->pending_->next() == 0)
    {
      return 0; /// empty list of pending locks
    }

  /// take pending lock off the head of the list
  /// (highest priority request) and add to the free list
  L = *(this->pending_->next());
  L.next(this->pending_->next()->next());
  this->pending_->next()->next(free_->next());
  this->free_->next(this->pending_->next());
  this->pending_->next(L.next());
  L.next(0);
  return 1;
}

PCP_Manager::PCP_Manager(CosSchedulingLockList *locks,
  ACE_SYNCH_MUTEX *mutex,
  RTCORBA::Current_var current)
: locks_(locks),
  mutex_(mutex),
  current_(current)
{
  /// Get the thread ID
  this->threadID_ = (ACE_OS::getpid() << 16) + ACE_Thread::self();
}

void
PCP_Manager::lock(int priority_ceiling, int priority)
{
  ACE_TRY_NEW_ENV
    {

      /// we do not want the thread to be pre-empted inside
      /// this critical section, so we
      /// will set its priority to the highest possible
      //  This is not completely necessary since the server should be running
      //  at RTCORBA::maxPriority
      this->current_->the_priority(RTCORBA::maxPriority);
      this->mutex_->acquire();
      ACE_TRY_CHECK;

      /// create a structure to store my own lock request
      CosSchedulingLockNode MyLock;
      MyLock.threadID_ = this->threadID_;
      MyLock.priority_ceiling_ = MyLock.elevated_priority_ = priority_ceiling;
      MyLock.priority_ = priority;
      /// Start by assuming we don't have the lock then go look for it
      int HaveLock = 0;
      while (!HaveLock)
        {
          /// retrieve the highest priority ceiling from the list
          CosSchedulingLockNode *highest_lock = this->locks_->highest_ceiling();
          int prio_ceiling;
          /// check to see if are at the highest priority,
          /// if so set the priority ceiling
          if (highest_lock)
            {
               prio_ceiling = highest_lock->priority_ceiling_;
            }
          else
            {
              prio_ceiling = -1;
            }

          /// if I hold the highest ceiling or my priority is higher than the
          /// highest ceiling, just get the lock
          if ((highest_lock == 0) ||
              (highest_lock->threadID_ == this->threadID_) ||
              (highest_lock->priority_ceiling_ < priority))
            {
              /// Try and grant the lock, if it is not granted,
              /// then there are unfortunately no more lock nodes
              if (!this->locks_->grant_lock (MyLock))
                {
                  ACE_ERROR ((LM_ERROR,
                              "Fatal error--out of lock nodes!!!"));
                }
                /// Lock obtained from grant_lock, don't loop again
                HaveLock = 1;
            }
          else
            {
              /// There is another lock out there active, put this one
              /// in the list of pending locks
              if (this->locks_->defer_lock(MyLock, *this->mutex_))
                {
                  /// done waiting for it, remove it from the pending
                  /// lock list, will try again to grant on next loop
                  /// iteration
                  this->locks_->remove_deferred_lock (MyLock);
                }
              else
                {
                  ACE_ERROR((LM_ERROR,
                             "Error in deferring lock\n"));
                }
              ACE_TRY_CHECK;
            }
        }

      /// remove mutex on the lock list
      this->mutex_->release();
      ACE_TRY_CHECK;

      /// at this point we have the right to set the OS priority
      /// Do so at the priority ceiline.
      this->current_->the_priority(priority_ceiling);

      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION(ACE_ANY_EXCEPTION,
                          "Error in locking the node for ServerScheduler\n");
    }
  ACE_ENDTRY;
}

void PCP_Manager::release_lock()
{
  ACE_TRY_NEW_ENV
    {
      /// To prevent pre-emption in the critical section,
      /// which could lead to unbounded blocking
      this->current_->the_priority(RTCORBA::maxPriority);

      /// set up the mutex
      this->mutex_->acquire();
      ACE_TRY_CHECK;

      /// remove the lock node from the list of locks
      CosSchedulingLockNode L;
      L.threadID_ = this->threadID_;
      this->locks_->release_lock(L);

      /// Done with the list, release the mutex
      this->mutex_->release();
      ACE_TRY_CHECK;

      /// Let the highest priority lock signal the condition variable
      CosSchedulingLockNode *waiter = this->locks_->highest_priority();
      if (waiter)
        {
          waiter->condition_->signal();
        }
      ACE_TRY_CHECK;

      /// We do not need to restore priority because we have already set this
      // thread to wait at RTCORBA::maxPriority at the start of this method
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION(ACE_ANY_EXCEPTION,
                         "Error in unlocking the node for ServerScheduler\n");
    }
  ACE_ENDTRY;
}


PCP_Manager_Factory::PCP_Manager_Factory(char *shared_file)
{
  ACE_TRY_NEW_ENV
    {
#if !defined (ACE_LACKS_MMAP)
      char temp_file[MAXPATHLEN + 1];

      /// Get the temporary directory
      if (ACE::get_temp_dir (temp_file,
                             MAXPATHLEN - ACE_OS_String::strlen(shared_file))
          == -1)
        ACE_ERROR ((LM_ERROR,
                    "Temporary path too long\n"));
      ACE_TRY_CHECK;

      /// Add the filename to the end
      ACE_OS_String::strcat (temp_file, shared_file);

      /// Store in the global variable.
      this->shm_key_ = temp_file;

#ifndef ACE_LACKS_MKSTEMP
      if (ACE_OS::mkstemp (this->shm_key_) == 0
#else
      char *new_key = ACE_OS::mktemp (this->shm_key_);
      if (ACE_OS::fopen(new_key, "w") != NULL
#endif /* ACE_LACKS_MKSTEMP */
          || (ACE_OS::unlink (this->shm_key_) == -1
#ifndef ACE_HAS_WINCE
             && errno == EPERM
#endif /* ACE_HAS_WINCE */
              ))
        ACE_ERROR ((LM_ERROR,
                    "(%P|%t) %p\n",
                    this->shm_key_));
        ACE_TRY_CHECK;

#else /* !ACE_LACKS_MMAP */
      ACE_ERROR ((LM_INFO,
                  "mmap is not supported on this platform\n"));
#endif /* !ACE_LACKS_MMAP */

      /// determine space requirements for the lock list
      u_int CosSchedulingLockList_space =
        LOCK_ARRAY_SIZE * sizeof (CosSchedulingLockNode);

      /// allocate space in shared memory for size of the lock list
      int result =
        this->mem_.open(this->shm_key_, CosSchedulingLockList_space);

      /// Make sure shared memory CosSchedulingLockList is ok, scheduling
      /// service cannot run without it.
      if (result == -1)
        {
          ACE_ERROR((LM_ERROR,
                     "Error in creating the shared memory segment to hold "
                     "Lock information, aborting ServerScheduler.\n"));
          ACE_OS::exit(1);
        }

      ACE_CHECK;

      /// Make the shared memory a place for a lock list
      this->lock_array_ = ACE_static_cast(CosSchedulingLockNode *,
                                          this->mem_.malloc(CosSchedulingLockList_space));
      if (this->lock_array_ == 0)
        {
          ACE_ERROR((LM_ERROR,
                     "Error in creating Lock Array, locking impossible.\n"));
        }
      ACE_TRY_CHECK;

      /// get the pointer to the list of locks and
      /// construct a lock list manager object
      if (this->lock_array_ == 0)
        {
          ACE_ERROR((LM_ERROR,
                     "No Pointer for LockArray, aborting\n"));
          ACE_OS::exit(1);
        }
      else
        {
          /// construct the new lock list in shared memory
          ACE_NEW_THROW_EX(this->locks_,
                           CosSchedulingLockList(this->lock_array_,
                             LOCK_ARRAY_SIZE,
                             &this->mutex_),
                           CORBA::NO_MEMORY()
                          );
          ACE_TRY_CHECK;
        }
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION(ACE_ANY_EXCEPTION,
                         "Error in Setting lock factory for ServerScheduler\n");
    }
  ACE_ENDTRY;
}

PCP_Manager_Factory::~PCP_Manager_Factory()
{
  /// throw out all the old Locks
  this->locks_->destroy(LOCK_ARRAY_SIZE);
  /// and delete the shared memory
  this->mem_.remove();
  delete this->locks_;
}

}
