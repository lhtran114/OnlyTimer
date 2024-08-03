/*************************************************************************
OnlyTimer: OneShotTimer Example
Luan Tran - 2024/08/01

This example demonstates a complete fault-checking setup a 1-shot timer.
It also demonstrate how to pass parameter into callback function.

It will print to serial port only 1-time after the timer fires.


callback function should not be too complex or time-consuming to execute.
Usually to setup a flag or checking conditions. 
In this example, we do it the correct way by setting a flag then process
the information in a custom task.
*************************************************************************/
#include <OnlyTimer.h>

OnlyTimer oneShotTimer;

bool tmrFiredFlag = false;

//-----------------------------------------
//callback function when timer fires
//-----------------------------------------
void Timer_Fired_Func(void *paramPtr){
  uint32_t* currentMSPtr = (uint32_t*)paramPtr;//because the parameter passed into CB func was an uint32_t type, we should convert it to the correct type
  *currentMSPtr = millis();//change the value of currentMS
  tmrFiredFlag = true;//callback func should be shot. This will set a flag saying timer was fired.
}

//-----------------------------------------
//setup
//-----------------------------------------
uint32_t currentMS;
void setup(){
  bool setupSuccess = false;
  Serial.begin(115200);  
  Serial.println("-----------OnlyTimer: 1-shot Timer----------------");
  currentMS = millis();
  setupSuccess = oneShotTimer.SingleCallbackIn(3000, Timer_Fired_Func, &currentMS);//pass in the address of the currentMS variable
  if(setupSuccess)
    Serial.printf("1-shot timer started at: %u\n", currentMS);
  else
    Serial.println("Timer setup failed!");
}

//-----------------------------------------
//my custom print task
//-----------------------------------------
void My_Custom_Print_Task(){
  if(tmrFiredFlag){
    tmrFiredFlag = false;//reset the flag
    Serial.printf("Timer fired at: %u\n", currentMS);
    //if you want to restart timer, you can do it here by setup the same 1-shot timer
    //However, Onlytimer has a periodic timer for this purpose. Check out the other example
  }
}

//-----------------------------------------
//MAIN loop
//-----------------------------------------
void loop() {
  My_Custom_Print_Task();
  OnlyTimer_Task();//THIS TASK MUST BE PUT IN MAIN LOOP IN A NON-BLOCKING WAY, if you want delay, see examples
}
