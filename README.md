# OnlyTimer
Simple yet powerful timer library based on Arduino millis.
With OnlyTimer you can:
- Setup a 1-shot timer with callback function with parameter pointer
- Setup a periodic timer with callback function with parameter pointer
- Setup a timer and poll for its expiration (non-blocking delay)
- Reset, stop a timer or check if it is available/running

A simple LED blink example using periodic callback timer:
//---------------------------------------------------------
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
  OnlyTimer_Task();
}
