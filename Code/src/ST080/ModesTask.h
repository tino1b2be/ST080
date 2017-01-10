/*
 * ModesTask.h
 *
 *  Created on: Oct 5, 2016
 *      Author: Tinotenda Chemvura
 */

#ifndef ST080_MODESTASK_H_
#define ST080_MODESTASK_H_

#include "Utils080.h"
#include "Eeprom.h"
#include "AudioStuff.h"

void initVariables(void);			// Method to initialise and variables as needed.
void addSamples(void); 				// Method to add the samples based on the layout of the channel rack
void flushBuffer(void);				// function to flush the DAC buffer before adding the samples
void initSamples(void);				// Function to create different samples for different combinations of instrument presses
uint16_t sampleAdd(					// sampleAdd (Freestylemode) method takes in 1, 2, 3 or 4 numbers and adds them, capping the numbers at 0 or 4095
		int16_t value1,
		int16_t value2,
		int16_t value3,
		int16_t value4,
		uint16_t sampleNum
);
void vModesTask(void * pvparameters);

// Function implementations

void vModesTask(void * pvparameters)
{
	initSamples();
	uint8_t previous_sample = 0;
	bool new_flag = true;			// flag to check if the composer/playback modes have been switched to

	while (true){
		initVariables();
		new_flag = true;

		while (MODE == COMPOSER) {

			if (new_flag){
				// start playing music for composer mode
				uint16_t tempo = Tempo_Convert();
				AudioComposerPlayback(tempo);
				new_flag = false;
			}

			// toggle LED3 (500ms) to check if this loop is running properly
			if ((tickTime - debugLED_counter_3) > 500)
			{
				// toggle LED5 (red)
				STM_EVAL_LEDToggle(LED3);
				debugLED_counter_3 = tickTime;
			}

			if (status || current_sample != previous_sample) {
				flushBuffer(); // flush the buffer and add the samples again
				addSamples();
				status = false;
			}
			previous_sample = current_sample;
			vTaskDelay(10);
		}
		new_flag = true; // set flag for the next iteration for composer

		while (MODE == PLAYBACK) {

			if (new_flag){
				// start playing music for composer mode
				uint16_t tempo = Tempo_Convert();
				AudioComposerPlayback(tempo);
				new_flag = false;
			}

			// toggle LED5 (500ms) to check if this loop is running properly
			if ((tickTime - debugLED_counter_3) > 500) {
				// toggle LED5 (red)
				STM_EVAL_LEDToggle(LED5);
				debugLED_counter_3 = tickTime;
			}

			if (status) {
				flushBuffer();
				addSamples();
				status = false;
			}
			vTaskDelay(50);
		}

		while (MODE == SAVE) {

			// toggle LED6 (500ms) to check if this loop is running properly
			if ((tickTime - debugLED_counter_6) > 100) {
				// toggle LED5 (red)
				STM_EVAL_LEDToggle(LED6);
				debugLED_counter_6 = tickTime;
			}

			// Save button has been pressed.
			if (status) { // status flag is used to make sure data is pushed to eeprom once
				saveToEeprom();
				status = false;
			}
			vTaskDelay(10);
			// Wait for user to select the new song channel rack to modify
			// After selecting the new song, switch back to COMPOSER mode.
		}
		while (MODE == FREESTYLE) {

			// toggle LED4 (500ms) to check if this loop is running properly
			if ((tickTime - debugLED_counter_3) > 500) {
				// toggle LED5 (red)
				STM_EVAL_LEDToggle(LED4);
				debugLED_counter_3 = tickTime;
			}

			// void AudioFreestyle(uint16_t *DACBuffer)

			// One Instrument played!
			// Instrument 1 played
			if(played_inst == 2){
				// TODO SEND SAMPLE TO BUFFER TO BE PLAYED
				AudioFreestyle(drumKit1[0]);
			}
			// Instrument 2 played
			else if(played_inst == 4){
				AudioFreestyle(drumKit1[1]);
			}
			// Instrument 3 played
			else if(played_inst == 8){
				AudioFreestyle(drumKit1[2]);
			}
			// Instrument 4 played
			else if(played_inst == 16){
				AudioFreestyle(drumKit1[3]);
			}
			// Two Instruments played!
			// Instrument 1 and 2 played
			else if(played_inst == 6){
				AudioFreestyle(freestyle_samples[0]);
			}
			// Instrument 1 and 3 played
			else if(played_inst == 10){
				AudioFreestyle(freestyle_samples[1]);
			}
			// Instrument 1 and 4 played
			else if(played_inst == 18){
				AudioFreestyle(freestyle_samples[2]);
			}
			// Instrument 2 and 3 played
			else if(played_inst == 12){
				AudioFreestyle(freestyle_samples[3]);
			}
			// Instrument 2 and 4 played
			else if(played_inst == 20){
				AudioFreestyle(freestyle_samples[4]);
			}
			// Instrument 3 and 4 played
			else if(played_inst == 24){
				AudioFreestyle(freestyle_samples[5]);
			}
			// Three Instruments played!
			// Instrument 1, 2 and 3 played
			else if(played_inst == 14){
				AudioFreestyle(freestyle_samples[6]);
			}
			// Instrument 1, 2 and 4 played
			else if(played_inst == 22){
				AudioFreestyle(freestyle_samples[7]);
			}
			// Instrument 1, 3 and 4 played
			else if(played_inst == 26){
				AudioFreestyle(freestyle_samples[8]);
			}
			// Instrument 2,3 and 4 played
			else if(played_inst == 28){
				AudioFreestyle(freestyle_samples[9]);
			}
			// Four Instruments played!
			// All 4 Instruments played!
			else if(played_inst == 30){
				AudioFreestyle(freestyle_samples[10]);
			}
			else{
				error_();
			}
			played_inst = 0;
			vTaskDelay(10);
		}
		while (MODE == ERROR_MODE){
			vTaskDelay(50);
		}
		// done witg modes
		vTaskDelay(20);
	}
}

// Functions used by the composer mode
void addSamples()
{
	uint16_t bufferSize = DEFAULT_COMPOSER_BUFFERSIZE;
	uint16_t bufferPos = 0;
	uint8_t pin = 0;

	for (; pin < 16; pin++ , bufferPos+=bufferSize/16){

		if (bufferPos >= bufferSize){
			// this is not supposed to happen
			error_();
		}

		// increment to the next pin
		// increment to the next position in the buffer
		uint8_t instrument = 0;
		for(; instrument < 4; instrument++){
			if (channelRack[currentBeat][instrument][pin]){
				// the pin is high
				// add the instrument sample to the buffer starting at bufferIndex
				// wrap around if the end is reached

				uint16_t sampleIndex = 0;
				uint16_t bufferIndex = bufferPos;
				bool mustWrap = SAMPLE_SIZE > (bufferSize-bufferIndex);
				for (; sampleIndex < SAMPLE_SIZE; ++bufferIndex, ++sampleIndex) {

					if (bufferIndex >= bufferSize){
						break;
					}

					// first shift the zero point from 2048 to 0
					// do the signal addition
					// cap the signal if it is saturated.

					int16_t temp_inst_sample = drumKit1[instrument][sampleIndex] - 2048;
					int16_t temp_buffer_sample = ComposerBuffer[bufferIndex] - 2048;
					int16_t temp = temp_inst_sample + temp_buffer_sample;
					uint16_t buffer_temp;
					if (temp < -2048) buffer_temp = 0;
					else if (temp > 2048) buffer_temp = 4095;
					else buffer_temp = temp + 2048;

					ComposerBuffer[bufferIndex] = buffer_temp;
				}
				// if the sample spills over the buffer then wrap around and add starting from the start of the buffer
				if (mustWrap) {
					for (bufferIndex = 0; sampleIndex < SAMPLE_SIZE || bufferIndex< bufferSize; ++sampleIndex, ++bufferIndex){

						if (bufferIndex < bufferSize){
							break;
						}

						// first shift the zero point from 2048 to 0
						// do the signal addition
						// cap the signal if it is saturated.

						int16_t temp_inst_sample = drumKit1[instrument][sampleIndex] - 2048;
						int16_t temp_buffer_sample = ComposerBuffer[bufferIndex] - 2048;
						int16_t temp = temp_inst_sample + temp_buffer_sample;
						uint16_t buffer_temp;
						if (temp < -2048) buffer_temp = 0;
						else if (temp > 2048) buffer_temp = 4095;
						else buffer_temp = temp + 2048;

						ComposerBuffer[sampleIndex] = buffer_temp;
					} // end of for-loop for the wrap-around
				} // end of if statement for wrap-around
			} // End of if statement to check if the pin is high
		} // end of for loop for the different instruments
	} // End of for loop for the pins
} // End of addSamples function

void flushBuffer(void)
{
	uint16_t i = 0;
	for (; i < DEFAULT_COMPOSER_BUFFERSIZE; ++i)
	{
		ComposerBuffer[i] = 2048;
	}
}

void initVariables(void)
{
	flushBuffer();
	status = true;
}

// sampleAdd (Freestylemode) method takes in 1, 2, 3 or 4 numbers and adds them, capping the numbers at 0 or 4095
uint16_t sampleAdd(int16_t value1, int16_t value2, int16_t value3, int16_t value4, uint16_t sampleNum){
	int16_t temp = 0;
	uint16_t buffer_temp = 0;
	if(sampleNum == 2){
		int16_t temp_value1 = value1 - 2048;
		int16_t temp_value2 = value2 - 2048;
		temp = temp_value1 + temp_value2;
	}
	if(sampleNum == 3){
		int16_t temp_value1 = value1 - 2048;
		int16_t temp_value2 = value2 - 2048;
		int16_t temp_value3 = value3 - 2048;
		temp = temp_value1 + temp_value2 + temp_value3;
	}
	if(sampleNum == 4){
		int16_t temp_value1 = value1 - 2048;
		int16_t temp_value2 = value2 - 2048;
		int16_t temp_value3 = value3 - 2048;
		int16_t temp_value4 = value4 - 2048;
		temp = temp_value1 + temp_value2 + temp_value3 + temp_value4;
	}
	if (temp < -2048) buffer_temp = 0;
	else if (temp > 2048) buffer_temp = 4095;
	else buffer_temp = temp + 2048;

	return buffer_temp;
}

// Function to create different samples for different combinations of instrument presses
void initSamples(void)
{

	uint16_t sampleIndex = 0;
	for(; sampleIndex < SAMPLE_SIZE; sampleIndex++)
	{
		// Combination 1 - instrument 1 and 2 - [0]
		freestyle_samples[0][sampleIndex] = sampleAdd(drumKit1[0][sampleIndex], drumKit1[1][sampleIndex],0,0,2);
		// Combination 2 - instrument 1 and 3 - [1]
		freestyle_samples[1][sampleIndex] = sampleAdd(drumKit1[0][sampleIndex], drumKit1[2][sampleIndex],0,0,2);
		// Combination 3 - instrument 1 and 4 - [2]
		freestyle_samples[2][sampleIndex] = sampleAdd(drumKit1[0][sampleIndex], drumKit1[3][sampleIndex],0,0,2);
		// Combination 4 - instrument 2 and 3 - [3]
		freestyle_samples[3][sampleIndex] = sampleAdd(drumKit1[1][sampleIndex], drumKit1[2][sampleIndex],0,0,2);
		// Combination 5 - instrument 2 and 4 - [4]
		freestyle_samples[4][sampleIndex] = sampleAdd(drumKit1[1][sampleIndex], drumKit1[3][sampleIndex],0,0,2);
		// Combination 6 - instrument 3 and 4 - [5]
		freestyle_samples[5][sampleIndex] = sampleAdd(drumKit1[2][sampleIndex], drumKit1[3][sampleIndex],0,0,2);
		// Combination 7 - instrument 1,2 and 3 - [6]
		freestyle_samples[6][sampleIndex] = sampleAdd(drumKit1[0][sampleIndex], drumKit1[1][sampleIndex], drumKit1[2][sampleIndex],0,3);
		// Combination 8 - instrument 1,2 and 4 - [7]
		freestyle_samples[7][sampleIndex] = sampleAdd(drumKit1[0][sampleIndex], drumKit1[1][sampleIndex], drumKit1[3][sampleIndex],0,3);
		// Combination 9 - instrument 1,3 and 4 - [8]
		freestyle_samples[8][sampleIndex] = sampleAdd(drumKit1[0][sampleIndex], drumKit1[2][sampleIndex], drumKit1[3][sampleIndex],0,3);
		// Combination 10 - instrument 2,3 and 4 - [9]
		freestyle_samples[9][sampleIndex] = sampleAdd(drumKit1[1][sampleIndex], drumKit1[2][sampleIndex], drumKit1[3][sampleIndex],0,3);
		// Combination 11 - instrument 1,2,3 and 4 - [10]
		freestyle_samples[10][sampleIndex] = sampleAdd(drumKit1[0][sampleIndex], drumKit1[1][sampleIndex], drumKit1[2][sampleIndex], drumKit1[3][sampleIndex],4);
	}
}

#endif /* ST080_MODESTASK_H_ */
