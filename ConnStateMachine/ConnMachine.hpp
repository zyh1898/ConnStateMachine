//
//  ConnMachine.hpp
//  ConnStateMachine
//
//  Created by yuhaozhang on 15/11/8.
//  Copyright © 2015 yuhaozhang. All rights reserved.
//

#ifndef ConnMachine_hpp
#define ConnMachine_hpp



#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/euml/euml.hpp>

#include <string>
#include <iostream>
using namespace std;
using namespace boost::msm::front::euml;
namespace msm = boost::msm;

/*
 states
 */
BOOST_MSM_EUML_STATE((), WaitForConnect)
BOOST_MSM_EUML_STATE((), Connected)

/*
 events
 */
BOOST_MSM_EUML_EVENT(Disconnect)
BOOST_MSM_EUML_DECLARE_ATTRIBUTE(std::string, ip);
BOOST_MSM_EUML_ATTRIBUTES((attributes_<<ip), targetIP_attributes)
BOOST_MSM_EUML_EVENT_WITH_ATTRIBUTES(Connect, targetIP_attributes)

/*
 action
 */
BOOST_MSM_EUML_ACTION(doConnect)
{
  template<typename EVT,typename FSM,
  typename SourceState,typename TargetState>
  void operator()(EVT const& evt,FSM & fsm,SourceState &,TargetState&)
  {
    std::string tar_ip=evt.get_attribute(ip);

    
    cout<<"doConnect to target:"<<tar_ip<<endl;
  }
};

BOOST_MSM_EUML_ACTION(doDisconnect)
{
  template<typename EVT,typename FSM,
  typename SourceState,typename TargetState>
  void operator()(EVT const& evt,FSM & fsm,SourceState &,TargetState&)
  {
	  std::string tarip;
	  tarip=fsm.get_attribute(ip);
	  cout<<"Disconnect from target"<<tarip<<endl;
  }
};

BOOST_MSM_EUML_ACTION(Log_No_Transition)
{
  template <class FSM,class Event>
  void operator()(Event const& e,FSM&,int state)
  {
    std::cout << "no transition from state " << state
    << " on event " << typeid(e).name() << std::endl;
  }
};

/*
 transition table
 */

BOOST_MSM_EUML_TRANSITION_TABLE((
      WaitForConnect+Connect/doConnect==Connected,
      Connected+Disconnect/doDisconnect==WaitForConnect
                                 
                                 ), transition_table);

BOOST_MSM_EUML_DECLARE_STATE_MACHINE((
                                     transition_table,
                                      init_<<WaitForConnect,
                                      no_action, // Entry
                                      no_action, // Exit
                                  attributes_ << ip, // Attributes
                                      configure_ << no_configure_, // configuration
                                      Log_No_Transition // no_transition handler
                                      ), ConnMachine_);




#endif /* ConnMachine_hpp */
