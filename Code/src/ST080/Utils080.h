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

// Library 38 (interrupts library)
#include "TM38/defines.h"
#include "TM38/tm_stm32f4_disco.h"
#include "TM38/tm_stm32f4_exti.h"

// FreeRTOS stuff
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

// STM32f4 stuff
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

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
	configASSERT(0);  				// Latch on any failure / error.
}

// ==========================================================================================
// ============================ Global Variables ============================================
// ==========================================================================================

// Modes used by the ST080
#define COMPOSER 1
#define PLAYBACK 2
#define FREESTYLE 3

// Instrument Macros
#define INSTR_1 0
#define INSTR_2 1
#define INSTR_3 2
#define INSTR_4 3

#define SAMPLE_SIZE 2048
#define DEFAULT_COMPOSER_BUFFERSIZE 16000
#define DEFAULT_TEMPO 0 // define proper tempos

uint8_t MODE = COMPOSER; 			// Global variable to e used to identify which mode the ST080 is currently in
bool status = true;					// Variable used by Composer to check if there has been an update on the channel rack configs.
uint64_t current = 0, previous = 0;	// Variables to be used by IRQ Handler for debouncing
uint8_t current_sample = INSTR_1;	// variable used by the composer mode to check which instrument sample is on the channel rack
bool channelRack[16][4][16]; 		// 16 channel racks with 4 instruments each with 16 beat channel
uint8_t currentBeat = 0;			// Variable to indicate the current beat/instrumental being edited on the beat rack.
bool resetLEDs = false;			// flag used to fresh the LEDs when switching modes. This flag will be checked by the UI_Task to check whether it should reset the LEDs or not
uint16_t ComposerBuffer[DEFAULT_COMPOSER_BUFFERSIZE];		// Buffer used by the composer mode to push to the audio output interface
uint16_t tempo = DEFAULT_TEMPO;
uint16_t drumKit1 [4][SAMPLE_SIZE] = {
		{0},
		{0},
		{0},
		{0}
};
//struct DrumKit {
//
//	// samples size for the instruments
//	uint16_t one_size;	// size of first sample
//	uint16_t two_size;	// size of second sample
//	uint16_t three_size;	// size of third sample
//	uint16_t four_size;	// size of forth sample
//
//	// samples for the 4 instruments
//	uint16_t one[];
//	uint16_t two[];
//	uint16_t three[];
//	uint16_t four[];
//
//} drumKit1;

// ==========================================================================================
// ============================ Function Declarations =======================================
// ==========================================================================================

void startUpConfigs(void); 			// Function to run the start up configurations.

// ==========================================================================================
// ============================ Function Implementations =====================================
// ==========================================================================================

/**
 * Run start up configurations for the STM080. These include
 * > Interrupt configurations
 * > GPIO inputs and outputs
 * > DMA and ADC and other audio stuff TODO Othniel
 * > EPROM and On-Board audio interface configutations
 * > TODO Add more stuff??
 */
void startUpConfigs(){
	// +++++++++++++++++ configure output pins ++++++++++++++++++++++++

	// B0-4, A8-10,13-15, C1-3,6,8,9,13-15, E0-4

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	/* Enable the clock for all ports*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	/* Configure Button pin as output*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	// Pins for port B0-4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// pins A8-10,13-15
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// pins C1-3,6,8,9,13-15
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_8 | GPIO_Pin_6 | GPIO_Pin_9 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	// pins E0-3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	// +++++++++++++++++ configure input pins ++++++++++++++++++++++++
	// A0-3, A5-7, E8-15, C0

	/* Configure Button pin as input */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;		// Input mode
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		// Push - Pull
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;		// To detect a logic high

	// Pins A0-3, A5-7
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// E8-15
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	// C0
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_0;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	// +++++++++++++++++ configure interrupt pins ++++++++++++++++++++++++

	// D0-3, E4-7
	bool fail = false;
	if (TM_EXTI_Attach(GPIOD, GPIO_Pin_0, TM_EXTI_Trigger_Rising) != TM_EXTI_Result_Ok){
		// PD0
		fail = true;
	} else if (TM_EXTI_Attach(GPIOD, GPIO_Pin_1, TM_EXTI_Trigger_Rising) != TM_EXTI_Result_Ok){
		// PD1
		fail = true;
	} else if (TM_EXTI_Attach(GPIOD, GPIO_Pin_2, TM_EXTI_Trigger_Rising) != TM_EXTI_Result_Ok){
		// PD2
		fail = true;
	} else if (TM_EXTI_Attach(GPIOD, GPIO_Pin_3, TM_EXTI_Trigger_Rising) != TM_EXTI_Result_Ok){
		// PD3
		fail = true;
	} else if (TM_EXTI_Attach(GPIOE, GPIO_Pin_4, TM_EXTI_Trigger_Rising) != TM_EXTI_Result_Ok){
		// PE4
		fail = true;
	} else if (TM_EXTI_Attach(GPIOE, GPIO_Pin_5, TM_EXTI_Trigger_Rising) != TM_EXTI_Result_Ok){
		// PE5
		fail = true;
	} else if (TM_EXTI_Attach(GPIOE, GPIO_Pin_6, TM_EXTI_Trigger_Rising) != TM_EXTI_Result_Ok){
		// PE6
		fail = true;
	} else if (TM_EXTI_Attach(GPIOE, GPIO_Pin_7, TM_EXTI_Trigger_Rising) != TM_EXTI_Result_Ok){
		// PA7
		fail = true;
	}

	if (fail){
		// TODO failed configuring interrupts. (FLASH LEDs or something)
	}
}

/**
 * IRQ for the channel rack buttons.
 */
void TM_EXTI_Handler(uint16_t GPIO_Pin) {

	// +++ debouncing logic (30 milliseconds) +++
	current = tickTime;
	if ((previous - current) < 30) {
		previous = current;
		return;
	}

	/* Handle external line 0 interrupts */
	// first pad for the instruments
	if (GPIO_Pin == GPIO_Pin_0) {
		if (MODE == COMPOSER){
			// change the instrument on the channel rack to the first one
			current_sample = INSTR_1;
			resetLEDs = true;
		}
	}

	/* Handle external line 1 interrupts */
	// second pad for the instruments
	else if (GPIO_Pin == GPIO_Pin_1) {
		if (MODE == COMPOSER){
			// change the instrument on the channel rack to the second one
			current_sample = INSTR_2;
			resetLEDs = true;
		}
		else if (MODE == FREESTYLE) {
			// TODO play the instrument
		}
	}

	/* Handle external line 2 interrupts */
	// third pad for the instruments
	else if (GPIO_Pin == GPIO_Pin_2) {
		if (MODE == COMPOSER){
			// change the instrument on the channel rack to the third one
			current_sample = INSTR_3;
			resetLEDs = true;
		}
		else if (MODE == FREESTYLE) {
			// TODO play the instrument
		}
	}

	/* Handle external line 3 interrupts */
	// forth pad for the instruments
	else if (GPIO_Pin == GPIO_Pin_3) {
		if (MODE == COMPOSER){
			// change the instrument on the channel rack to the forth one
			current_sample = INSTR_4;
			resetLEDs = true;
		}
		else if (MODE == FREESTYLE) {
			// TODO play the instrument
		}
	}

	/* Handle external line 4 interrupts */
	// switch to COMPOSER MODE
	else if (GPIO_Pin == GPIO_Pin_4) {
		MODE = COMPOSER;
	}

	/* Handle external line 5 interrupts */
	// switch to PLAYBACK MODE
	else if (GPIO_Pin == GPIO_Pin_5) {
		MODE = PLAYBACK;
	}

	/* Handle external line 6 interrupts */
	// switch to FREESTYLE MODE
	else if (GPIO_Pin == GPIO_Pin_6) {
		MODE = FREESTYLE;
	}

	/* Handle external line 7 interrupts */
	// Save pin
	else if (GPIO_Pin == GPIO_Pin_7) {
		// TODO implement save logic
		// Save the channelRack Array to the EPROM
	}

	previous = current; // for debouncing
}

	// +++++++++++++++++ TODO configure on-board amplifier ++++++++++++++++++++++++

	// +++++++++++++++++ TODO configure EPROM pins ++++++++++++++++++++++++

	// +++++++++++++++++ TODO configure Audio stuff (DMA, ADC, etc...) ++++++++++++++++++++++++

#endif /* UTILS080_H_ */
