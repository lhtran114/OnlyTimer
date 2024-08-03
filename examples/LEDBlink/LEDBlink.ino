/*************************************************************************
OnlyTimer: LEDBlink Example
Luan Tran - 2024/08/01

This example simply blinks a LED.

*IMPORTANT
callback function should not be too complex or time-consuming to execute.
Usually to setup a flag or checking conditions. 

*************************************************************************/
#include <OnlyTimer.h>

#define LED_PIN 2

OnlyTimer blinkTimer;

void Blink(void *paramPtr){
  static uint8_t ledState = LOW;
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
}

void setup(){
  Serial.begin(115200);  
  pinMode(LED_PIN, OUTPUT); 
  Serial.println("-----Blink Blink-----");
  blinkTimer.PeriodicCallbackEvery(200, Blink);//toggle led every 200ms
}

void loop() {
  OnlyTimer_Task();//THIS TASK MUST BE PUT IN MAIN LOOP IN A NON-BLOCKING WAY, if you want delay, see examples
}
