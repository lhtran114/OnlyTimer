/*************************************************************************
OnlyTimer: OneShotTimer Example
Luan Tran - 2024/07/31

This example demonstates the simple way to setup a 1-shot timer.
It will print to serial port only 1-time after the timer fires.

*IMPORTANT
callback function should not be too complex or time-consuming to execute.
Usually to setup a flag or checking conditions. 
In this case, The Serial.Print function takes tens of milliseconds 
to complete depends on the string length, and should be taken into account.

*************************************************************************/
#include <OnlyTimer.h>

OnlyTimer oneShotTimer;

/*
callback function when timer fires
- void *paramPtr must present. It isn't used in this case but look for
other example on how to use it.
*/
void One_Shot_Print_Func(void *paramPtr){
  Serial.printf("Timer fired!\n");
}

void setup(){
  Serial.begin(115200);
  Serial.println("Starting a 1-shot timer!");
  oneShotTimer.SingleCallbackIn(3000, One_Shot_Print_Func);//set timer to 1-shot callback in 3 seconds
}

void loop() {
  OnlyTimer_Task();//THIS TASK MUST BE PUT IN MAIN LOOP IN A NON-BLOCKING WAY, if you want delay, see examples
}
