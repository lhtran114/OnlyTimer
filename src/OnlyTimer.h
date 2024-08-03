/*******************************************************************************
- File Name:
    OnlyTimer.h    
    Created: 2024/07/28 by Luan Tran 

- Release notes:
	version 1.0 - 2024/07/28: 
	Files first created. It is named "OnlyTimer" because all common names were
	taken. And I hope this timer is simple yet capable enough so that it is the
	only timer you need for your applications.
	

 *******************************************************************************/ 
#ifndef _ONLYTIMER_H
#define _ONLYTIMER_H

#include "Arduino.h"

#define MAX_TIMER_CLIENTS	86

class OnlyTimer{
  public:
  	/*
  	*Constructor
  	*/
  	OnlyTimer();
  	
  	/*
  	*This function will call callbackFunc ONLY 1 time after milliInterval(ms) has passed.
		*a parameter pointer can also be passed into the callbackFunc
  	*/
  	bool SingleCallbackIn(uint32_t milliInterval, void(*callbackFunc)(void*), void* paramPtr=NULL);
  	
  	/*
  	*This function will periodically call callbackFunc every milliInterval(ms). A parameter 
		*pointer can also be passed into the callbackFunc
  	*/
  	bool PeriodicCallbackEvery(uint32_t milliInterval, void(*callbackFunc)(void*), void* paramPtr=NULL);
  	
  	/*
  	*This function start timer for milliInterval(ms). This is a simple non-blocking way to
		*do "delay" or simply check if a certain time has passed by pooling "IsRunning" after
		*"SetTimeout"
  	*/
  	bool SetTimeout(uint32_t milliInterval);
  	
  	/*
  	*This function will stop the timer.
  	*/
  	void Stop(void);
	
  	/*
  	*This function reset the timer counter ONLY if it's still running. 
		*If the timer is stopped, it won't start the timmer.
  	*/
  	bool Reset(void);
	
		/*
  	*This function will return:
		*- true: if timer is running
		*- false: if timer NOT running
  	*/
    bool IsRunning(void) {return isRunning;};
	
		/*
  	*This function will return:
		*- true: if timer is availabe
		*- false: if timer NOT available
		*THIS LIBRARY does not use dynamic memory allocation, and maximum timers supported
		*is 68. You don't have to worry about memory leak, if it compiles, it'll work correctly
		*/
    bool IsAvailable(void) {return available;};
  
		/*
		*This function will be checked by the timer task in the main loop.
		*Calling this won't affect timer functionalities, but it is not recommended.
		*/
    void SelfCheck(void);
  
  private:
  	uint32_t startMillis;
  	uint32_t interval;
  	bool periodic;
  	bool isRunning;
    bool available;
  	void (*CallbackFunc)(void*);
	void *cbParameter;
};


void OnlyTimer_Task(void);
#endif /* _ONLYTIMER_H */

/*******************************************************************************
 End of File
*/
