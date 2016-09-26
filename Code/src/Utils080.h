/*
 * Utils080.h
 *
 *  Created on: Sep 26, 2016
 *      Author: Tinotenda Chemvura
 */

#ifndef UTILS080_H_
#define UTILS080_H_

// other stuff
#include <stdbool.h>

// FreeRTOS stuff
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

// STM32f4 stuff
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

// Just constants
#define COMPOSER 1
#define PLAYBACK 2
#define FREESTYLE 3

// ==========================================================================================
// ============================ FreeRTOS stuff ==============================================
// ==========================================================================================

uint64_t tickTime = 0;        // Counts OS ticks (default = 1000Hz).
uint64_t u64IdleTicks = 0;   // Value of u64IdleTicksCnt is copied once per sec.
uint64_t u64IdleTicksCnt = 0; // Counts when the OS has no task to execute.
uint16_t u16PWM1 = 0;

// This FreeRTOS callback function gets called once per tick (default = 1000Hz).
// ----------------------------------------------------------------------------
void vApplicationTickHook(void) {
	++tickTime;
}

// This FreeRTOS call-back function gets when no other task is ready to execute.
// On a completely unloaded system this is getting called at over 2.5MHz!
// ----------------------------------------------------------------------------
void vApplicationIdleHook(void) {
	++u64IdleTicksCnt;
}

// A required FreeRTOS function.
// ----------------------------------------------------------------------------
void vApplicationMallocFailedHook(void) {
	configASSERT(0);  // Latch on any failure / error.
}

// +++++++++++++++ function declerations ++++++++++++++++++

void startUpConfigs(void); // TODO implements this function

// ==========================================================================================
// ============================ Global Variables ============================================
// ==========================================================================================

uint8_t MODE = COMPOSER;
bool status = true;
uint8_t current_sample = 0;
uint8_t channelRack[16][4][16]; // 16 channel racks with 4 instruments each with 16 beat channel
uint16_t ComposerBuffer[16000];

#endif /* UTILS080_H_ */
