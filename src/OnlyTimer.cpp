/*******************************************************************************
- File Name:
    OnlyTimer.cpp    
    Created: 2024/07/28 by Luan Tran 

- Release notes:
	See OnlyTimer.h file

 *******************************************************************************/
#include "OnlyTimer.h"

uint32_t nTmrClients = 0;
OnlyTimer *tmrObjArr[MAX_TIMER_CLIENTS];

/*
Timer Object Constructor
After a timer object is created, it will be added to the timer object pointer array 
and the number of client will be keep track of.
*/
OnlyTimer::OnlyTimer(){	
	this->startMillis = 0;
	this->interval = 0;
	this->periodic = false;
	this->isRunning = false;
	this->CallbackFunc = NULL;
	this->cbParameter = NULL;	
	if(nTmrClients < MAX_TIMER_CLIENTS){
		tmrObjArr[nTmrClients] = this;
		nTmrClients++;	
		this->available = true;
	}
	else{
		this->available = false;
	}
}

/*
This function will call callbackFunc ONLY 1 time after milliInterval(ms) has passed.
a parameter pointer can also be passed into the callbackFunc

- milliInterval: 1-time time in ms
- callbackFunc: callback fuction pointer
- paramPtr: callback function parameter pointer

Return:
- true: if timer has been set successfully
- false: if timer is busy or not available
*/
bool OnlyTimer::SingleCallbackIn(uint32_t milliInterval, void(*callbackFunc)(void*), void* paramPtr){
  if(this->isRunning || !(this->available))
    return false;
	this->interval = milliInterval;
	this->periodic = false;
	this->CallbackFunc = callbackFunc;
	this->cbParameter = paramPtr;
	this->startMillis = millis(); 
	this->isRunning = true;
  return true;
}

  
/*
*This function will periodically call callbackFunc every milliInterval(ms). A parameter 
*pointer can also be passed into the callbackFunc

- milliInterval: periodic time in ms
- callbackFunc: callback fuction pointer
- paramPtr: callback function parameter pointer

Return:
- true: if timer has been set successfully
- false: if timer is busy or not available
*/
bool OnlyTimer::PeriodicCallbackEvery(uint32_t milliInterval, void(*callbackFunc)(void*), void* paramPtr){  
  if(this->isRunning || !(this->available))
    return false;
	this->interval = milliInterval;
	this->periodic = true;
	this->CallbackFunc = callbackFunc;
	this->cbParameter = paramPtr;
	this->startMillis = millis(); 
	this->isRunning = true;
  return true;
}

/*
*This function start timer for milliInterval(ms). This is a simple non-blocking way to
*do "delay" or simply check if a certain time has passed by pooling "IsRunning" after
*"SetTimeout"

Return:
- true: if timer has been set successfully
- false: if timer is busy or not available
*/
bool OnlyTimer::SetTimeout(uint32_t milliInterval){
  return this->SingleCallbackIn(milliInterval, NULL);
}


	
/*
*This function reset the timer counter ONLY if it's still running. 
*If the timer is stopped, it won't start the timmer.

Return:
- true: if timer has been reset successfully
- false: if timer is not running
*/
bool OnlyTimer::Reset(void){
  if(this->isRunning){		
		if(millis() - this->startMillis < this->interval){//still not timed out yet
			this->startMillis = millis();
			return true;
		}
  }
  return false;
}

/*
*This function will stop the timer.
*/
void OnlyTimer::Stop(){
	this->isRunning = false;
	this->startMillis = 0;
	this->interval = 0;
	this->periodic = false;
}

/*
*This function will be checked by the timer task in the main loop.
*Calling this won't affect timer functionalities, but it is not recommended.
*/
void OnlyTimer::SelfCheck(){
  uint32_t currentMillis;
  if(this->isRunning){//timer is running, must check
    currentMillis = millis();
    if(currentMillis - this->startMillis >= this->interval){//timeout
      if(this->periodic == false)//single callback, stop timer
        this->Stop();
      else//periodic callback, update start time and continue
        this->startMillis = currentMillis;
      if(CallbackFunc)//callback
        CallbackFunc(cbParameter);       
    }
  }
}

/*
 * This function will continuously loop through all the timer objects and check if any timer has fired
 */
void OnlyTimer_Task(void){
  uint32_t i;  
  for(i = 0; i < nTmrClients; i++){
    tmrObjArr[i]->SelfCheck();    
  }
}

/*******************************************************************************
 End of File
*/
