/*
* composer.h
*
*  Created on: Aug 28, 2016
*      Author: Tinotenda Chemvura
*/

#ifndef COMPOSER_H_
#define COMPOSER_H_

#include <stdbool.h>

#include "TM38/defines.h"
#include "TM38/tm_stm32f4_disco.h"
#include "TM38/tm_stm32f4_exti.h"

// constansts declarations
#define SAMPLE_SIZE 100
#define NUM_INSTR 9

// variable declarations
uint16_t samples[NUM_INSTR][SAMPLE_SIZE];		// 2D array of the samples to be used
uint16_t DAC_Buffer[16 * SAMPLE_SIZE];			// The DAC buffer to be used for output
bool rackPins[NUM_INSTR][16];								// array representing the scores on the channel rack for each instrument
bool status;
uint8_t sample;

// function declarations
void configInterrupts(void);
int getSampleID(void);
void addSamples(int s);
void refreshUI(int sample);
void IRQHandler();
void vComposerTask( void *pvparameters );

// function implementations
void vComposerTask( void * pvparameters)
{
	// initialise the variables
	configInterrupts();

	uint8_t previous_sample = 10;
	while (true)
	{
		sample = getSampleID();
		if (status || sample != previous_sample)
		{
			int i;
			for (i = 0; i < 16; ++i)
			{
				addSamples(i);
			}
		}
	}
}

void configInterrupts(void)
{
	// pins being used for channel rack
	// PA0 PA1 PA2 PA3 PA4 PA5 PA6 PA7 ... PE8 PE9 PE10 PE11 PE12 PE13 PE14 PE15




}

int getSampleID(void)
{
	/**
	 * read the GPIO pin for sample selection
	 * determine the index of chosen sample based on the value read from the GPIO pin
	 * @return The index of the sample being edited.
	 */
}

void addSamples(int i)
{
	/**
	 * Go through the samples composerPins array (for loop for the 8 samples)
	 * check status of pin "i" in each of those arrays
	 * if pin "i" is set, add the audio for that sample to the DAC_Buffer
	 * if pin "i" is low, do not add anything to the DAC_Buffer
	 * Do this for each of the 8 samples
	 */
}

void refreshUI(int sample)
{
	/**
	 * This method lights up the corresponding LEDs for the pins on the composer keyboard
	 * optionally, could also update an LCD display if being used
	 */
}

#endif /* COMPOSER_H_ */
