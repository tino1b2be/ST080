/*
* composer.h
*
*  Created on: Aug 28, 2016
*      Author: Tinotenda Chemvura
*/

#ifndef COMPOSER_H_
#define COMPOSER_H_

//#include "FreeRTOS.h"
//#include "task.h"
//#include "queue.h"

xQueueHandle delayQueue;

// Task priorities: Higher numbers are higher priority.
uint64_t tickTime=0;        // Counts OS ticks (default = 1000Hz).
uint64_t u64IdleTicks=0;    // Value of u64IdleTicksCnt is copied once per sec.
uint64_t u64IdleTicksCnt=0; // Counts when the OS has no task to execute.
uint16_t u16PWM1=0;
uint32_t tempo = 120;		/* in bpm */
uint32_t averageTime = 600;	/* in ms */

// function definitions
void configStuff();
void vLEDTask( void *pvparameters );
void vButtonTask( void *pvparameters );

#endif /* COMPOSER_H_ */
