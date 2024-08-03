/*************************************************************************
OnlyTimer: TimerReset Example
Luan Tran - 2024/08/01

- This example will setup a 1-shot timer that should be expired in 3 seconds.
- There is a custom task that keep reseting the timer, preventing it from 
getting fired.
- However, The custom task executing time will be increasing, and when it
surpassed 3 seconds, the timer fired and stop the task.

*IMPORTANT
callback function should not be too complex or time-consuming to execute.
Usually to setup a flag or checking conditions. 
In this case, The Serial.Print function takes tens of milliseconds 
to complete depends on the string length, and should be taken into account.

*************************************************************************/
#include <OnlyTimer.h>

OnlyTimer oneShotTimer;
bool customTaskOkToRun = true;

void One_Shot_Timer_Func(void *paramPtr){
  customTaskOkToRun = false;
  Serial.println("----Timer fired--Stop custom task----");
}

void setup(){
  Serial.begin(115200);
  Serial.println("----Starting 1-shot timer----");
  oneShotTimer.SingleCallbackIn(3000, One_Shot_Timer_Func);//set timer to callback in 3 seconds
}

void Custom_Task(){
  static uint32_t runTime = 2500;
  uint32_t startMS;
  if(customTaskOkToRun){
    startMS = millis();
    Serial.printf("Running task for %u(ms)!\n", runTime);
    while(millis() - startMS < runTime);
    if(oneShotTimer.Reset())//reset timer
      Serial.println("Timer has not been fired, reset success!\n");
    else
      Serial.println("Timer reset FAILED!\n");
    runTime += 200;
  }
}

void loop() {
  Custom_Task();
  OnlyTimer_Task();//THIS TASK MUST BE PUT IN MAIN LOOP IN A NON-BLOCKING WAY, if you want delay, see examples
}
