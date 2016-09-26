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

#define CHECKINSTR_STACK_SIZE 128 	// may be smaller than this
#define CHECKINSTR_PRIORITY 4		// must be higher than the priority of main task??

// variable declarations

uint16_t DAC_Buffer[16 * SAMPLE_SIZE];	// The DAC buffer to be used for output
bool rackPins[NUM_INSTR][16];// array representing the scores on the channel rack for each instrument
bool status;// This variable is set everytime the sample changes (or a score is chaged)
uint8_t sample;		// This variable is set the task vCheckCurrentSample()
uint64_t previous, current, debugLED_counter_6, debugLED_counter_5, debugLED_counter_4, debugLED_counter_3;

// function declarations
static void initVariables(); // function to initialise the variables used in the composer mode.
static uint16_t** loadDrumKit(); // function to load the default drumkit (returns a drumkit)
void initialiseRack();
void configInterrupts(void);// function to configure the GPIO interrupts to be used in the mode
void configInstrPins(void);	// function to configure the 9 buttons from the freestyle mode to select the instr to be modified in the channel rack.
int getInstrID(void);// Function to obtain the instrument being edited on the rack
void debugLED_init();
void addSamples();
void refreshUI(int sample);
void vComposerTask(void *pvparameters);	// task to perform the main computations for the rhythm composer
void vCheckCurrentSample(void *pvparameters);// task to cycle through the 9-GPIO pins to check which instrument is supposed to be on the channel rack

// ++++++++ function implementations +++++++


void vComposerTask(void * pvparameters) {
	// initialise the variables
	initVariables();
	configInterrupts();
	configInstrPins();

	debugLED_init(); // for debugging.

	// start the task to read the instrument select pins
	xTaskCreate(vCheckCurrentSample, (signed char *) "Check Instr Select Pins", CHECKINSTR_STACK_SIZE, NULL, CHECKINSTR_PRIORITY, NULL);

	// start algorithm for the channel rack
	uint8_t previous_sample = sample;
	while (true) {

		// toggle LED3 to check if this loop is running properly
		if ((tickTime - debugLED_counter_3)>500){
			// toggle LED5 (red)
			STM_EVAL_LEDToggle(LED3);
			debugLED_counter_3 = tickTime;
		}

		if (status || sample != previous_sample) {
			addSamples();
		}
		previous_sample = sample;
		vTaskDelay(10);
	}

	// debug code. flash LED when task is done
//	while (true)
//	{
//
//	}
}

void debugLED_init(){
	/* Initialize LEDs */
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);

	/* Turn off all LEDs */
	STM_EVAL_LEDOff(LED3);
	STM_EVAL_LEDOff(LED4);
	STM_EVAL_LEDOff(LED5);
	STM_EVAL_LEDOff(LED6);

	debugLED_counter_5 = tickTime;
	debugLED_counter_3 = tickTime;
}

/**
 * task to cycle through the 9-GPIO pins to check which instrument is supposed to be on the channel rack
 * GPIO pins in use: PB0-8
 */
void vCheckCurrentSample(void *pvparameters) {

	while (true) {
		// debugging code for LEDs flashing
		if ((tickTime - debugLED_counter_5) > 500) {
			// toggle LED5 (red)
			STM_EVAL_LEDToggle(LED5);
			debugLED_counter_5 = tickTime;
		}

		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0)) {
			while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0))
				;
			// PB0
			sample = 0;
		} else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)) {
			while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
				;
			// PB1
			sample = 1;
		} else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2)) {
			while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2))
				;
			// PB2
			sample = 2;
		} else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3)) {
			while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3))
				;
			// PB3
			sample = 3;
		} else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4)) {
			while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4))
				;
			// PB4
			sample = 4;
		} else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)) {
			while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5))
				;
			// PB5
			sample = 5;
//	} else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)){
//		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6));
//		// PB6
//		sample = 6;
		} else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)) {
			while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7))
				;
			// PB7
			sample = 7;
		}

		// insert a delay
		vTaskDelay(10);
	}
}

/**
 * Function to initialise the variables
 */
static void initVariables()
{
	loadDrumKit(); // TODO load samples from drumkit
	initialiseRack();
	status = true;
	sample = 0;
	previous = 0;
}

/**
 * Function to initialise the whole channel
 */
void initialiseRack(){
	int i, j;
	for (i = 0; i < NUM_INSTR; ++i){
		for (j = 0; j < SAMPLE_SIZE; ++j){
			rackPins[i][j] = false;
		}
	}
}

/**
 * Function to configure the GPIOs for the instrument pins
 */
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

/**
 * config pins being used for channel rack
 * PA0 PA1 PA2 PA3 PA4 PA5 PA6 PA7 ... PE8 PE9 PE10 PE11 PE12 PE13 PE14 PE15
 */
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

/**
 * TODO Go through the samples composerPins array (for loop for the 8 samples)
 * check status of pin "i" in each of those arrays
 * if pin "i" is set, add the audio for that sample to the DAC_Buffer
 * if pin "i" is low, do not add anything to the DAC_Buffer
 * Do this for each of the 8 samples
 */
void addSamples() {


	return;
}

/**
 * TODO This method lights up the corresponding LEDs for the pins on the composer keyboard
 * optionally, could also update an LCD display if being used
 */
void refreshUI(int sample) {
	return;
}

/**
 * IRQ for the channel rack buttons.
 */
void TM_EXTI_Handler(uint16_t GPIO_Pin) {
	// +++ debouncing logic (30 milliseconds) +++
	current = tickTime;
	if ((previous - current) < 30){
		previous = current;
		return;
	}

	/* Handle external line 0 interrupts */
	if (GPIO_Pin == GPIO_Pin_0) {
		/* Toggle rack pin button */
		rackPins[sample][0] = rackPins[sample][0] == true ? false : true;
	}

	else if (GPIO_Pin == GPIO_Pin_1) {
		/* Toggle rack pin button */
		rackPins[sample][1] = rackPins[sample][1] == true ? false : true;
	}

	else if (GPIO_Pin == GPIO_Pin_2) {
		/* Toggle rack pin button */
		rackPins[sample][2] = rackPins[sample][2] == true ? false : true;
	}

	else if (GPIO_Pin == GPIO_Pin_3) {
		/* Toggle rack pin button */
		rackPins[sample][3] = rackPins[sample][3] == true ? false : true;
	}

	else if (GPIO_Pin == GPIO_Pin_4) {
		/* Toggle rack pin button */
		rackPins[sample][4] = rackPins[sample][4] == true ? false : true;
	}

	else if (GPIO_Pin == GPIO_Pin_5) {
		/* Toggle rack pin button */
		rackPins[sample][5] = rackPins[sample][5] == true ? false : true;
	}

	else if (GPIO_Pin == GPIO_Pin_6) {
		/* Toggle rack pin button */
		rackPins[sample][6] = rackPins[sample][6] == true ? false : true;
	}

	else if (GPIO_Pin == GPIO_Pin_7) {
		/* Toggle rack pin button */
		rackPins[sample][7] = rackPins[sample][7] == true ? false : true;
	}

	else if (GPIO_Pin == GPIO_Pin_8) {
		/* Toggle rack pin button */
		rackPins[sample][8] = rackPins[sample][8] == true ? false : true;
	}

	else if (GPIO_Pin == GPIO_Pin_9) {
		/* Toggle rack pin button */
		rackPins[sample][9] = rackPins[sample][9] == true ? false : true;
	}

	else if (GPIO_Pin == GPIO_Pin_10) {
		/* Toggle rack pin button */
		rackPins[sample][10] = rackPins[sample][10] == true ? false : true;
	}

	else if (GPIO_Pin == GPIO_Pin_11) {
		/* Toggle rack pin button */
		rackPins[sample][11] = rackPins[sample][11] == true ? false : true;
	}

	else if (GPIO_Pin == GPIO_Pin_12) {
		/* Toggle rack pin button */
		rackPins[sample][12] = rackPins[sample][12] == true ? false : true;
	}

	else if (GPIO_Pin == GPIO_Pin_13) {
		/* Toggle rack pin button */
		rackPins[sample][13] = rackPins[sample][13] == true ? false : true;
	}

	else if (GPIO_Pin == GPIO_Pin_14) {
		/* Toggle rack pin button */
		rackPins[sample][14] = rackPins[sample][14] == true ? false : true;
	}

	else if (GPIO_Pin == GPIO_Pin_15) {
		/* Toggle rack pin button */
		rackPins[sample][15] = rackPins[sample][15] == true ? false : true;
	}

	previous = current; // for debouncing
}

#endif /* COMPOSER_H_ */
