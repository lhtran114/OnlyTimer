/*************************************************************************
OnlyTimer: PeriodicTimer Example
Luan Tran - 2024/08/01

This example demonstates the simple way to setup a periodic timer.
It will print to serial port everytim the timer fires.

*IMPORTANT
callback function should not be too complex or time-consuming to execute.
Usually to setup a flag or checking conditions. 
In this case, The Serial.Print function takes tens of milliseconds 
to complete depends on the string length, and should be taken into account.

*************************************************************************/
#include <OnlyTimer.h>

OnlyTimer periodicTimer;

void Periodic_Print_Func(void *paramPtr){
  Serial.printf("millis: %u\n", millis());
}

void setup(){
  Serial.begin(115200);
  Serial.println("-----Starting a periodic timer-----");
  periodicTimer.PeriodicCallbackEvery(1000, Periodic_Print_Func);//set timer to callback every 1 second
}

void loop() {
  OnlyTimer_Task();//THIS TASK MUST BE PUT IN MAIN LOOP IN A NON-BLOCKING WAY, if you want delay, see examples
}
