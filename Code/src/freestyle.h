/*
 * FreestyleMode.h
 *
 *  Created on: Sep 27, 2016
 *      Author: Tinotenda Chemvura
 */

/*
 * TODO
 *
 * NB:
 *
 * This header file is for the freestyle mode task. This is a temporary file
 * that will be merged into one task for all the modes but I thought that in
 * the meantime, to avoid breaking the code and other conflicts, we code them
 * as seperate tasks and then merge them together once we are certain that they work.
 *
 * Look at the TODO's in the code for more details
 */




#ifndef FREESTYLEMODE_H_
#define FREESTYLEMODE_H_

#include "Utils080.h"

void initSamples(void);							// Method to initialise and variables as needed.

// TODO implement freestle stuff

void vFreestyleTask(void * pvparameterss);

void vFreestyleTask(void * pvparameters)
{
	/* TODO This is where you do any configs
	 * that you may need before going into the endless while loop.
	 *
	 * 	PLEASE NOTE that the interrupts have already been configured
	 * 	along with their interrupt handlers so no need to do that.
	 *
	 *  To access the interrupt handlers for the 4 instrument buttons,
	 *  Go to Utils080.h under the function "void TM_EXTI_Handler(uint16_t GPIO_Pin)".
	 *  The interrupts for the instrument buttons are on lines 0, 1, 2 and 3.
	 *  Refer to the TODO's inside this functino for more details.
	 *
	 * Ideally we want the configs to take place when the STM boots
	 * (inside the "startUpConfigs() function in the Utils080.h"
	 */
	initSamples();


	while (true)
	{
		while(MODE == FREESTYLE)
		{
			// TODO freestyle logic

			// void AudioFreestyle(uint16_t *DACBuffer)

			// One Instrument played!
			// Instrument 1 played
			if(played_inst == 2){
				// TODO SEND SAMPLE TO BUFFER TO BE PLAYED
				// AudioFreestyle(*drumKit1[0]);
			}
			// Instrument 2 played
			else if(played_inst == 4){
				// AudioFreestyle(*drumKit1[1];
			}
			// Instrument 3 played
			else if(played_inst == 8){
				// AudioFreestyle(*drumKit1[2]);
			}
			// Instrument 4 played
			else if(played_inst == 16){
				// AudioFreestyle(*drumKit1[3]);
			}
			// Two Instruments played!
			// Instrument 1 and 2 played
			else if(played_inst == 6){
				// AudioFreestyle(*freestyle_samples[0]);
			}
			// Instrument 1 and 3 played
			else if(played_inst == 10){
				// AudioFreestyle(*freestyle_samples[1]);
			}
			// Instrument 1 and 4 played
			else if(played_inst == 18){
				// AudioFreestyle(*freestyle_samples[2]);
			}
			// Instrument 2 and 3 played
			else if(played_inst == 12){
				// AudioFreestyle(*freestyle_samples[3]);
			}
			// Instrument 2 and 4 played
			else if(played_inst == 20){
				// AudioFreestyle(*freestyle_samples[4]);
			}
			// Instrument 3 and 4 played
			else if(played_inst == 24){
				// AudioFreestyle(*freestyle_samples[5]);
			}
			// Three Instruments played!
			// Instrument 1, 2 and 3 played
			else if(played_inst == 14){
				// AudioFreestyle(*freestyle_samples[6]);
			}
			// Instrument 1, 2 and 4 played
			else if(played_inst == 22){
				// AudioFreestyle*freestyle_samples[7]();
			}
			// Instrument 1, 3 and 4 played
			else if(played_inst == 26){
				// AudioFreestyle(*freestyle_samples[8]);
			}
			// Instrument 2,3 and 4 played
			else if(played_inst == 28){
				// AudioFreestyle(*freestyle_samples[9]);
			}
			// Four Instruments played!
			// All 4 Instruments played!
			else if(played_inst == 30){
				// AudioFreestyle(*freestyle_samples[10]);
			}
			else{
				// AudioFreestyle();
			}
			played_inst = 0;
			vTaskDelay(10);
		}
		vTaskDelay(10); // TODO might need to optmise this delay
	} //
} // END of task function

void initSamples(void)
{

	uint16_t sampleIndex = 0;
	for(; sampleIndex < SAMPLE_SIZE; sampleIndex++)
	{
		// Combination 1 - instrument 1 and 2 - [0]
		freestyle_samples[0][sampleIndex] = drumKit1[0][sampleIndex]+drumKit1[1][sampleIndex];
		// Combination 2 - instrument 1 and 3 - [1]
		freestyle_samples[1][sampleIndex] = drumKit1[0][sampleIndex]+drumKit1[2][sampleIndex];
		// Combination 3 - instrument 1 and 4 - [2]
		freestyle_samples[2][sampleIndex] = drumKit1[0][sampleIndex]+drumKit1[3][sampleIndex];
		// Combination 4 - instrument 2 and 3 - [3]
		freestyle_samples[3][sampleIndex] = drumKit1[1][sampleIndex]+drumKit1[2][sampleIndex];
		// Combination 5 - instrument 2 and 4 - [4]
		freestyle_samples[4][sampleIndex] = drumKit1[1][sampleIndex]+drumKit1[3][sampleIndex];
		// Combination 6 - instrument 3 and 4 - [5]
		freestyle_samples[5][sampleIndex] = drumKit1[2][sampleIndex]+drumKit1[3][sampleIndex];
		// Combination 7 - instrument 1,2 and 3 - [6]
		freestyle_samples[6][sampleIndex] = drumKit1[0][sampleIndex]+drumKit1[1][sampleIndex]+drumKit1[2][sampleIndex];
		// Combination 8 - instrument 1,2 and 4 - [7]
		freestyle_samples[7][sampleIndex] = drumKit1[0][sampleIndex]+drumKit1[1][sampleIndex]+drumKit1[3][sampleIndex];
		// Combination 9 - instrument 1,3 and 4 - [8]
		freestyle_samples[8][sampleIndex] = drumKit1[0][sampleIndex]+drumKit1[2][sampleIndex]+drumKit1[3][sampleIndex];
		// Combination 10 - instrument 2,3 and 4 - [9]
		freestyle_samples[9][sampleIndex] = drumKit1[1][sampleIndex]+drumKit1[2][sampleIndex]+drumKit1[3][sampleIndex];
		// Combination 11 - instrument 1,2,3 and 4 - [10]
		freestyle_samples[10][sampleIndex] = drumKit1[0][sampleIndex]+drumKit1[1][sampleIndex]+drumKit1[2][sampleIndex]+drumKit1[3][sampleIndex];
	}
}


#endif /* FREESTYLEMODE_H_ */
