/*
 * composer.h
 *
 *  Created on: Aug 28, 2016
 *      Author: Tinotenda Chemvura
 */

#ifndef COMPOSER_H_
#define COMPOSER_H_

#include "TM38/defines.h"
#include "TM38/tm_stm32f4_disco.h"
#include "TM38/tm_stm32f4_exti.h"
 
#include "ST080Utils.h"

// constansts declarations
#define SAMPLE_SIZE 100
#define NUM_INSTR 9

#define CHECKINSTR_STACK_SIZE 128 	// may be smaller than this
#define CHECKINSTR_PRIORITY 3		// must be higher than the priority of main task??

// variable declarations
uint16_t samples[NUM_INSTR][SAMPLE_SIZE]; // 2D array of the samples to be used (current drumkit)
uint16_t DAC_Buffer[16 * SAMPLE_SIZE];	// The DAC buffer to be used for output
bool rackPins[NUM_INSTR][16];// array representing the scores on the channel rack for each instrument
bool status;// This variable is set everytime the sample changes (or a score is chaged)
uint8_t sample;		// This variable is set the task vCheckCurrentSample()

// function declarations
static void initVariables(); // function to initialise the variables used in the composer mode.
static uint16_t** loadDrumKit(); // function to load the default drumkit (returns a drumkit)
void configInterrupts(void);// function to configure the GPIO interrupts to be used in the mode
void configInstrPins(void);	// function to configure the 9 buttons from the freestyle mode to select the instr to be modified in the channel rack.
int getInstrID(void);// Function to obtain the instrument being edited on the rack
void addSamples(int s);
void refreshUI(int sample);
void IRQHandler();
void vComposerTask(void *pvparameters);	// task to perform the main computations for the rhythm composer
void vCheckCurrentSample(void *pvparameters);// task to cycle through the 9-GPIO pins to check which instrument is supposed to be on the channel rack

// function implementations
void vComposerTask(void * pvparameters) {
	// initialise the variables
	initVariables();
	configInterrupts();
	configInstrPins();

	// start the task to read the instrument select pins
	xTaskCreate(vCheckCurrentSample, (signed char *) "Check Instr Select Pins", CHECKINSTR_STACK_SIZE, NULL, CHECKINSTR_PRIORITY, NULL);

	// start algorithm for the channel rack
	uint8_t previous_sample = sample;
	while (true) {
		//sample = getInstrID();

		if (status || sample != previous_sample) {
			int i;
			for (i = 0; i < 16; ++i) {
				addSamples(i);
			}
		}
		previous_sample = sample;
		vTaskDelay(10);
	}
}

static void initVariables()
{
	// TODO initialise "instance" variables

	loadDrumKit(); // load samples from drumkit

	uint16_t samples[NUM_INSTR][SAMPLE_SIZE]; 	// load samples
	uint16_t DAC_Buffer[16 * SAMPLE_SIZE];		// initialise the DAC buffer
	bool rackPins[NUM_INSTR][16];				//
	bool status;
	uint8_t sample;

}

void vCheckCurrentSample(void *pvparameters) {
	// task to cycle through the 9-GPIO pins to check which instrument is supposed to be on the channel rack
	// GPIO pins in use: PB0-8
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0)){
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0));
		// PB0
		sample = 0;
	} else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)){
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1));
		// PB1
		sample = 1;
	} else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2)){
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2));
		// PB2
		sample = 2;
	} else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3)){
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3));
		// PB3
		sample = 3;
	} else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4)){
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4));
		// PB4
		sample = 4;
	} else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)){
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5));
		// PB5
		sample = 5;
	} else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)){
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6));
		// PB6
		sample = 6;
	} else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)){
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7));
		// PB7
		sample = 7;
	}

	// insert a delay
	vTaskDelay(10);
}

void configInstrPins(void) {
	// Pins used for the freestyle pad are PB0-PB8

	/* Enable the clock for port B*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	/* Configure Button pin as input */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;		// Input mode
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		// Push - Pull
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;	// To detect a logic high

	// Pins 0-8 on port B (9 in total)
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_0
			| GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3
			| GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6
			| GPIO_PIN_7	| GPIO_PIN_8;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void configInterrupts(void)
{
	// pins being used for channel rack
	// PA0 PA1 PA2 PA3 PA4 PA5 PA6 PA7 ... PE8 PE9 PE10 PE11 PE12 PE13 PE14 PE15
	bool fail = false;
	if (TM_EXTI_Attach(GPIOA, GPIO_Pin_0, TM_EXTI_Trigger_Rising) != TM_EXTI_Result_Ok){
		// PA0
		fail = true;
	} else if (TM_EXTI_Attach(GPIOA, GPIO_Pin_1, TM_EXTI_Trigger_Rising) != TM_EXTI_Result_Ok){
		// PA1
		fail = true;
	} else if (TM_EXTI_Attach(GPIOA, GPIO_Pin_2, TM_EXTI_Trigger_Rising) != TM_EXTI_Result_Ok){
		// PA2
		fail = true;
	} else if (TM_EXTI_Attach(GPIOA, GPIO_Pin_3, TM_EXTI_Trigger_Rising) != TM_EXTI_Result_Ok){
		// PA3
		fail = true;
	} else if (TM_EXTI_Attach(GPIOA, GPIO_Pin_4, TM_EXTI_Trigger_Rising) != TM_EXTI_Result_Ok){
		// PA4
		fail = true;
	} else if (TM_EXTI_Attach(GPIOA, GPIO_Pin_5, TM_EXTI_Trigger_Rising) != TM_EXTI_Result_Ok){
		// PA5
		fail = true;
	} else if (TM_EXTI_Attach(GPIOA, GPIO_Pin_6, TM_EXTI_Trigger_Rising) != TM_EXTI_Result_Ok){
		// PA6
		fail = true;
	} else if (TM_EXTI_Attach(GPIOA, GPIO_Pin_7, TM_EXTI_Trigger_Rising) != TM_EXTI_Result_Ok){
		// PA7
		fail = true;
	} else if (TM_EXTI_Attach(GPIOE, GPIO_Pin_8, TM_EXTI_Trigger_Rising) != TM_EXTI_Result_Ok){
		// PE8
		fail = true;
	} else if (TM_EXTI_Attach(GPIOE, GPIO_Pin_9, TM_EXTI_Trigger_Rising) != TM_EXTI_Result_Ok){
		// PE9
		fail = true;
	} else if (TM_EXTI_Attach(GPIOE, GPIO_Pin_10, TM_EXTI_Trigger_Rising) != TM_EXTI_Result_Ok){
		// PE10
		fail = true;
	} else if (TM_EXTI_Attach(GPIOE, GPIO_Pin_11, TM_EXTI_Trigger_Rising) != TM_EXTI_Result_Ok){
		// PE11
		fail = true;
	} else if (TM_EXTI_Attach(GPIOE, GPIO_Pin_12, TM_EXTI_Trigger_Rising) != TM_EXTI_Result_Ok){
		// PE12
		fail = true;
	} else if (TM_EXTI_Attach(GPIOE, GPIO_Pin_13, TM_EXTI_Trigger_Rising) != TM_EXTI_Result_Ok){
		// PE13
		fail = true;
	} else if (TM_EXTI_Attach(GPIOE, GPIO_Pin_14, TM_EXTI_Trigger_Rising) != TM_EXTI_Result_Ok){
		// PE14
		fail = true;
	} else if (TM_EXTI_Attach(GPIOE, GPIO_Pin_15, TM_EXTI_Trigger_Rising) != TM_EXTI_Result_Ok){
		// PE15
		fail = true;
	}

	if (fail){
		// TODO failed configuring interrupts. (FLASH LEDs or something)
	}
}

uint16_t** loadDrumKit(void)
{
	//TODO
	return 0;
}

int getInstrID(void) {
	/**
	 * read the GPIO pin for sample selection
	 * determine the index of chosen sample based on the value read from the GPIO pin
	 * @return The index of the sample being edited.
	 */

	return 0;
}

void addSamples(int i) {
	/**
	 * Go through the samples composerPins array (for loop for the 8 samples)
	 * check status of pin "i" in each of those arrays
	 * if pin "i" is set, add the audio for that sample to the DAC_Buffer
	 * if pin "i" is low, do not add anything to the DAC_Buffer
	 * Do this for each of the 8 samples
	 */
}

void refreshUI(int sample) {
	/**
	 * This method lights up the corresponding LEDs for the pins on the composer keyboard
	 * optionally, could also update an LCD display if being used
	 */
}

#endif /* COMPOSER_H_ */
