// -*- C++ -*-
// $Id$

#include "StockBroker_exec.h"

namespace CIAO_Stock_StockBroker_Impl
{
  //============================================================
  // Component Executor Implementation Class: StockBroker_exec_i
  //============================================================
  StockBroker_exec_i::StockBroker_exec_i (void)
  {
  }

  StockBroker_exec_i::~StockBroker_exec_i (void)
  {
  }

  // Supported operations and attributes.
  void
  StockBroker_exec_i::stock_subscribe (
    const char * stock_name)
  {
    if ((ACE_OS::strcmp (stock_name, "MSFT") == 0) ||
        (ACE_OS::strcmp (stock_name, "IBM") == 0))
      {
        std::set<std::string>::iterator iter =
          this->subscribed_stock_list_.find (stock_name);

        if (iter == this->subscribed_stock_list_.end ())
          {
            ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("StockBroker_exec_i::stock_subscribe - ")
                ACE_TEXT ("subscribe to <%C>\n"),
                stock_name));
            this->subscribed_stock_list_.insert (stock_name);
          }
      }
    else
      {
        ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("StockBroker_exec_i::stock_subscribe - ")
            ACE_TEXT ("<%C> not found. Throw Invalid_Stock exception.\n"),
            stock_name));
        throw Stock::Invalid_Stock ();
      }
  }

  void
  StockBroker_exec_i::stock_unsubscribe (
    const char * stock_name)
  {
    if ((ACE_OS::strcmp (stock_name, "MSFT") == 0) ||
        (ACE_OS::strcmp (stock_name, "IBM") == 0))
      {
        std::set<std::string>::iterator iter =
          this->subscribed_stock_list_.find (stock_name);
        if (iter != this->subscribed_stock_list_.end ())
          {
            ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("StockBroker_exec_i::stock_unsubscribe - ")
                ACE_TEXT ("unsubscribe <%C>\n"),
                stock_name));
            this->subscribed_stock_list_.erase (iter);
          }
      }
    else
      {
        ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("StockBroker_exec_i::stock_unsubscribe - ")
            ACE_TEXT ("<%C> not found. Throw Invalid_Stock exception.\n"),
            stock_name));
        throw Stock::Invalid_Stock ();
      }
  }

  // Component attributes and port operations.

  void
  StockBroker_exec_i::push_notify_in (
    Stock::StockName *ev)
  {
    CORBA::String_var stock_name = CORBA::string_dup (ev->name ());

    // Retrieve stock information if the stock name is in the
    // subscribed_stock_list
    if (this->subscribed_stock_list_.find (stock_name.in ()) !=
        this->subscribed_stock_list_.end ())
      {
        Stock::StockQuoter_var quoter_obj =
          this->context_->get_connection_read_quoter ();

        if (CORBA::is_nil (quoter_obj.in ()))
          {
            throw CORBA::BAD_PARAM ();
          }

        Stock::StockInfo_var info =
          quoter_obj->get_stock_info (stock_name.in ());

        ACE_DEBUG ((LM_DEBUG, "Quoter - Current value of %s is %d\n",
                              stock_name.in (),
                              info->last));
      }
  }

  // Operations from Components::SessionComponent.

  void
  StockBroker_exec_i::set_session_context (
    ::Components::SessionContext_ptr ctx)
  {
    this->context_ =
      ::Stock::CCM_StockBroker_Context::_narrow (ctx);

    if ( ::CORBA::is_nil (this->context_.in ()))
      {
        throw ::CORBA::INTERNAL ();
      }
  }

  void
  StockBroker_exec_i::configuration_complete (void)
  {
    /* Your code here. */
  }

  void
  StockBroker_exec_i::ccm_activate (void)
  {
    /* Your code here. */
  }

  void
  StockBroker_exec_i::ccm_passivate (void)
  {
    /* Your code here. */
  }

  void
  StockBroker_exec_i::ccm_remove (void)
  {
    /* Your code here. */
  }

  extern "C" STOCKBROKER_EXEC_Export ::Components::EnterpriseComponent_ptr
  create_Stock_StockBroker_Impl (void)
  {
    ::Components::EnterpriseComponent_ptr retval =
      ::Components::EnterpriseComponent::_nil ();

    ACE_NEW_NORETURN (
      retval,
      StockBroker_exec_i);

    return retval;
  }
}

namespace CIAO_Stock_StockBroker_Impl
{
  //============================================================
  // Home Executor Implementation Class: StockBrokerHome_exec_i
  //============================================================

  StockBrokerHome_exec_i::StockBrokerHome_exec_i (void)
  {
  }

  StockBrokerHome_exec_i::~StockBrokerHome_exec_i (void)
  {
  }

  // All operations and attributes.

  // Factory operations.

  // Finder operations.

  // Implicit operations.

  ::Components::EnterpriseComponent_ptr
  StockBrokerHome_exec_i::create (void)
  {
    ::Components::EnterpriseComponent_ptr retval =
      ::Components::EnterpriseComponent::_nil ();

    ACE_NEW_THROW_EX (
      retval,
      StockBroker_exec_i,
      ::CORBA::NO_MEMORY ());

    return retval;
  }

  extern "C" STOCKBROKER_EXEC_Export ::Components::HomeExecutorBase_ptr
  create_Stock_StockBrokerHome_Impl (void)
  {
    ::Components::HomeExecutorBase_ptr retval =
      ::Components::HomeExecutorBase::_nil ();

    ACE_NEW_NORETURN (
      retval,
      StockBrokerHome_exec_i);

    return retval;
  }
}
