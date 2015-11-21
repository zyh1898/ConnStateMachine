//
//  main.cpp
//  ConnStateMachine
//
//  Created by yuhaozhang on 15/11/8.
//  Copyright © 2015 yuhaozhang. All rights reserved.
//

#include <iostream>
#include <string>
#include <boost/msm/back/state_machine.hpp>
#include "ConnMachine.hpp"


int main(int argc, const char * argv[]) {
  // insert code here...
  typedef boost::msm::back::state_machine<ConnMachine_> ConnMachine;
  ConnMachine conn1;
  conn1.start();
  
  conn1.process_event(Connect("127.0.0.1"));
  conn1.process_event(Disconnect());
  
  std::string msg;
  cin>>msg;
  
  
  
  return 0;
}
