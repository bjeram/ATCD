// $Id$
//
// ****              Code generated by the                 ****
// ****  Component Integrated ACE ORB (CIAO) CIDL Compiler ****
// CIAO has been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// CIDL Compiler has been developed by:
//       Institute for Software Integrated Systems
//       Vanderbilt University
//       Nashville, TN
//       USA
//       http://www.isis.vanderbilt.edu/
//
// Information about CIAO is available at:
//    http://www.dre.vanderbilt.edu/CIAO

#include "Messenger_exec_i.h"

// MY CODE
#include "ace/OS_NS_unistd.h"
#include "History_exec_i.h"
#include "Runnable_exec_i.h"
#include "Publication_exec_i.h"

namespace CIAO_Messenger_Impl
{
  //==================================================================
  // Component Executor Implementation Class:   Messenger_exec_i
  //==================================================================

  Messenger_exec_i::Messenger_exec_i ()
    : subject_( "Test Subject" ),
      user_( "ciao_user" )
  {
    this->control_ = new Runnable_exec_i();
    this->history_ = new History_exec_i();
    this->content_ = new Publication_exec_i(
      "The quick brown fox jumped over the lazy dog",
      2 );
  }

  Messenger_exec_i::~Messenger_exec_i (void)
  {
    this->control_->_remove_ref();
    this->history_->_remove_ref();
    this->content_->_remove_ref();
  }

  // MY CODE
  int Messenger_exec_i::svc() {

    ACE_DEBUG((LM_INFO, ACE_TEXT("svc()\n")));

    while (1)
    {
      ACE_OS::sleep( this->content_->period() );

      // get the run_lock from the Runnable executor; we have an
      // agreement with the Runnable executor that we must posess the
      // run_lock to publish
      ACE_GUARD_RETURN (TAO_SYNCH_MUTEX, ace_mon, this->control_->get_run_lock(), 0);

      // create a message to publish
      ::Message_var msg = new ::OBV_Message();
      msg->subject( this->subject() );
      msg->text( this->content_->text() );
      msg->user( CORBA::string_dup( this->user_.c_str() ) );

      // add the message to the message history
      this->history_->add( msg.in() );

      ACE_DEBUG((LM_INFO, ACE_TEXT("Messenger_exec_i::svc: publishing message\n") ));

      // publish to all interested consumers
      this->context_->push_message_publisher( msg.in() );

      ACE_DEBUG((LM_INFO,
        ACE_TEXT("Published Message on subject %s\n   User %s\n   Text %s\n"),
        msg->subject(),
        msg->user(),
        msg->text() ));
    }

    ACE_DEBUG((LM_INFO, ACE_TEXT("svc():  Gracefully stopping publication\n")));
    return 0;
  }

  // Supported or inherited operations.

  // Attribute operations.

  char*
  Messenger_exec_i::subject ()
  {
    return CORBA::string_dup( this->subject_.c_str() );
  }

  void
  Messenger_exec_i::subject (const char* subject)
  {
    this->subject_ = subject;
  }

  // Port operations.

  ::CCM_Runnable_ptr
  Messenger_exec_i::get_control ()
  {
    // Your code here.

    // MY CODE

    // bump up ref count because we give up ownership when we return this
    this->control_->_add_ref();
    return this->control_;
  }

  ::CCM_Publication_ptr
  Messenger_exec_i::get_content ()
  {
    return ::CCM_Publication::_duplicate (this->content_);
  }

  ::CCM_History_ptr
  Messenger_exec_i::get_message_history ()
  {
    return ::CCM_History::_duplicate (this->history_);
  }

  // Operations from Components::SessionComponent

  void
  Messenger_exec_i::set_session_context (
    ::Components::SessionContext_ptr ctx)
  {
    this->context_ =
      ::CCM_Messenger_Context::_narrow (ctx);

    if (CORBA::is_nil (this->context_.in ()))
    {
      throw ::CORBA::INTERNAL ();
    }
  }

  void
  Messenger_exec_i::configuration_complete ()
  {
    /* Your code here. */
  }

  void
  Messenger_exec_i::ccm_activate ()
  {
    /* Your code here. */
    ACE_DEBUG((LM_INFO, ACE_TEXT("Messenger_exec_i::ccm_activate\n")));
    this->activate();
  }

  void
  Messenger_exec_i::ccm_passivate ()
  {
    /* Your code here. */
    ACE_DEBUG((LM_INFO, ACE_TEXT("Messenger_exec_i::ccm_passivate\n")));
  }

  void
  Messenger_exec_i::ccm_remove ()
  {
    /* Your code here. */
    ACE_DEBUG((LM_INFO, ACE_TEXT("Messenger_exec_i::ccm_remove\n")));
  }


  extern "C" MESSENGER_EXEC_Export ::Components::EnterpriseComponent_ptr
  create_Messenger_Impl (void)
  {
    ::Components::EnterpriseComponent_ptr retval =
      ::Components::EnterpriseComponent::_nil ();

    ACE_NEW_RETURN (retval,
                    Messenger_exec_i,
                    ::Components::EnterpriseComponent::_nil ());

    return retval;
  }

  //==================================================================
  // Home Executor Implementation Class:   MessengerHome_exec_i
  //==================================================================

  MessengerHome_exec_i::MessengerHome_exec_i (void)
  {
  }

  MessengerHome_exec_i::~MessengerHome_exec_i (void)
  {
  }

  // Supported or inherited operations.

  // Home operations.

  // Factory and finder operations.

  // Attribute operations.

  // Implicit operations.

  ::Components::EnterpriseComponent_ptr
  MessengerHome_exec_i::create ()
  {
    ::Components::EnterpriseComponent_ptr retval =
      ::Components::EnterpriseComponent::_nil ();

    ACE_NEW_THROW_EX (
      retval,
      Messenger_exec_i,
      ::CORBA::NO_MEMORY ());

    return retval;
  }

  extern "C" MESSENGER_EXEC_Export ::Components::HomeExecutorBase_ptr
  create_MessengerHome_Impl (void)
  {
    ::Components::HomeExecutorBase_ptr retval =
      ::Components::HomeExecutorBase::_nil ();

    ACE_NEW_RETURN (
      retval,
      MessengerHome_exec_i,
      ::Components::HomeExecutorBase::_nil ());

    return retval;
  }
}

