/*************************************************************************
OnlyTimer: NonblockingDelay Example
Luan Tran - 2024/08/01

This example shows how to use OnlyTimer for delay purpose without callback
function. 
It's how delay is typically implemented in state machines.

*IMPORTANT
callback function should not be too complex or time-consuming to execute.
Usually to setup a flag or checking conditions. 
In this case, The Serial.Print function takes tens of milliseconds 
to complete depends on the string length, and should be taken into account.

*************************************************************************/
#include <OnlyTimer.h>

OnlyTimer delayTimer;

void setup(){
  Serial.begin(115200);
}

void My_StateMachine_Task(){
  static uint32_t state = 0;
  switch(state){
    case 0:  
      Serial.println("State 1 done, delay 2 seconds");
      delayTimer.SetTimeout(2000);
      state = 1;
      break;
    case 1:
      if(delayTimer.IsRunning() == false){//timer expired    
        Serial.println("State 2 done, delay 5 seconds"); 
        delayTimer.SetTimeout(5000);
        state = 2;
      }
    case 2:
      if(delayTimer.IsRunning() == false){//timer expired  
        state = 0;//just go back to run state 1
      }
  default:
      break;
  }
}

void loop() {
  My_StateMachine_Task();
  OnlyTimer_Task();//THIS TASK MUST BE PUT IN MAIN LOOP IN A NON-BLOCKING WAY, if you want delay, see examples
}
