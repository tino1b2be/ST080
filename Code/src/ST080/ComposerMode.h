/*
 * ComposerMode.h
 *
 *  Created on: Sep 26, 2016
 *      Author: Tinotenda Chemvura
 */

#ifndef COMPOSERMODE_H_
#define COMPOSERMODE_H_

#include "Utils080.h"

void initVariables(void);							// Method to initialise and variables as needed.
void vComposerTask(void * pvparameters);			// FreeRTOS task for the composer mode
void addSamples(void); 								// Method to add the samples based on the layout of the channel rack
void flushBuffer(void);								// function to flush the DAC buffer before adding the samples

void vComposerTask(void * pvparameters)
{
	initVariables();
	uint8_t previous_sample = 0;
	while(1){
		// toggle LED3 faster (100ms) when not in composer mode
		if ((tickTime - debugLED_counter_3) > 100) {
			// toggle LED5 (red)
			STM_EVAL_LEDToggle(LED3);
			debugLED_counter_3 = tickTime;
		}

		while(MODE==COMPOSER){

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
		} // End of in-mode while-loop
		while(MODE==SAVE){
			// Save button has been pressed.
			if (status){ // status flag is used to make sure data is pushed to eeprom once
				// TODO Push the current channel rack configuration to the EEPROM
				status = false;
			}
			vTaskDelay(10);
			// Wait for user to select the new song channel rack to modify
			// After selecting the new song, switch back to COMPOSER mode.
		}
		vTaskDelay(10);

	}// End of forever while-loop

} // End of function

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
	// TODO load the channel rack from the EPROM
}

#endif /* COMPOSERMODE_H_ */
