/*
 * freestyle.h
 *
 *  Created on: Sep 11, 2016
 *      Author: John Odetokun
 */

#ifndef FREESTYLE_H_
#define FREESTYLE_H_

#include "defines.h"
#include "tm38/tm_stm32f4_disco.h"
#include "tm_stm32f4_exti.h"

#include "ST080Utils.h"

// Constants declarations
#define SAMPLE_SIZE 100 // Adapted from Tino's Code (Assuming all samples have equal length
#define NUM_INSTR 9 // Number of instruments

#define CHECKINSTR_STACK_SIZE 128 	// may be smaller than this
#define CHECKINSTR_PRIORITY 3		// must be higher than the priority of main task??

// variable declarations
uint16_t samples[NUM_INSTR][SAMPLE_SIZE]; // 2D array of the samples to be used (current drumkit)
uint16_t DAC_Buffer[16 * SAMPLE_SIZE];	// The DAC buffer to be used for output

// function declarations
static void initVariables(); //function that initializes the variables used in the Freestyle mode.
static uint16_t** loadDrumKit(); // function to load the default drumkit (returns a drumkit)
void configInterrupts(void);// function to configure the GPIO interrupts to be used in the mode to send selected sample (to audio)
void IRQHandler();
void vFreestyleTask(void *pvparameters);	// task to perform the main computations for the freestyle component

// Function Implementation
void vFreestyleTask(void *pvparameters){
	// Initialisations
	initVariables();
	configInterrupts();

}

static void initVariables(){
	// TODO initialise "instance" variables

	loadDrumKit(); // load samples from drumkit

	uint16_t samples[NUM_INSTR][SAMPLE_SIZE]; 	// load samples
	uint16_t DAC_Buffer[16 * SAMPLE_SIZE];		// initialise the DAC buffer

}

uint16_t** loadDrumKit(void)
{
	//TODO
	return 0;
}

void configureInterrupts(void){
	// Pins being used for Freestyle mode
	// PB0 PB1 PB2 PB3 PB4 PB5 PB6 PB7 PB8
	bool fail = false;
	if (TM_EXTI_Attach(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2\
    		GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_PIN_6,\
    		TM_EXTI_Trigger_Rising) != TM)


}
