/*************************************************************************
OnlyTimer: OneShotAndPeriodic Example
Luan Tran - 2024/08/01

This example has 2 timers
- periodic timer keeps printing every 1 second.
- 1-shot timer will stop periodic timer after 8 seconds.

*IMPORTANT
callback function should not be too complex or time-consuming to execute.
Usually to setup a flag or checking conditions. 
In this case, The Serial.Print function takes tens of milliseconds 
to complete depends on the string length, and should be taken into account.
*************************************************************************/
#include <OnlyTimer.h>

OnlyTimer periodicTimer;
OnlyTimer oneShotTimer;

void Periodic_Print_Func(void *paramPtr){
  Serial.printf("millis: %u\n", millis());
}

void One_Shot_Stop_Func(void *paramPtr){
  periodicTimer.Stop();
  Serial.println("---All timers stopped---");
}

void setup(){
  Serial.begin(115200);
  Serial.println("-----Starting both timers-----");
  periodicTimer.PeriodicCallbackEvery(1000, Periodic_Print_Func);//set timer to callback every 1 second
  oneShotTimer.SingleCallbackIn(8000, One_Shot_Stop_Func);//set 1-shot timer to callback in 8 seconds
}

void loop() {
  OnlyTimer_Task();//THIS TASK MUST BE PUT IN MAIN LOOP IN A NON-BLOCKING WAY, if you want delay, see examples
}
