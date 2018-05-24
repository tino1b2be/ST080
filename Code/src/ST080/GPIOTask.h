/*
 * The MIT License (MIT)

Copyright (c) 2015 Tinotenda Chemvura, John Odetokun, Othniel Konan, Herman Kouassi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

 */

/*
 * GPIOTask.h
 *
 *  Created on: Sep 27, 2016
 *      Author: Tinotenda Chemvura
 */

#ifndef GPIOTASK_H_
#define GPIOTASK_H_

#include "Utils080.h"

void vGPIOTask(void * pvparameters);
void updateVars();

void vGPIOTask(void * pvparameters) {

	while (true) {
		while (MODE == COMPOSER)
		{
			// read the channel rack pins
			// 1=A0, 2=A1, 3=A2, 4=A3, 5=D4, 6=A5, 7=D6, 8=D7, 9=E8, 10=E9, 11=E10, 12=E11, 13=E12, 14=E13, 15=E14, 16=E15
			// Port A
			
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0));
				// toggle pin 1

				channelRack[currentBeat][current_sample][0] = channelRack[currentBeat][current_sample][0] == true ? false : true;
				status = true;
			}
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1));
				// toggle pin 2
				channelRack[currentBeat][current_sample][1] = channelRack[currentBeat][current_sample][1] == true ? false : true;
				status = true;
			}
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2));
				// toggle pin 3
				channelRack[currentBeat][current_sample][2] = channelRack[currentBeat][current_sample][2] == true ? false : true;
				status = true;
			}
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3));
				// toggle pin 4
				channelRack[currentBeat][current_sample][3] = channelRack[currentBeat][current_sample][3] == true ? false : true;
				status = true;
			}
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5));
				// toggle pin 6
				channelRack[currentBeat][current_sample][5] = channelRack[currentBeat][current_sample][5] == true ? false : true;
				status = true;
			}

			// Port D

			if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4)) {
				while (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4));
				// toggle pin 5
				channelRack[currentBeat][current_sample][4] = channelRack[currentBeat][current_sample][4] == true ? false : true;
				status = true;
			}
			if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_6)) {
				while (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_6));
				// toggle pin 7
				channelRack[currentBeat][current_sample][6] = channelRack[currentBeat][current_sample][6] == true ? false : true;
				status = true;
			}
			if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7)) {
				while (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7));
				// toggle pin 8
				channelRack[currentBeat][current_sample][7] = channelRack[currentBeat][current_sample][7] == true ? false : true;
				status = true;
			}

			// Port E
			
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8));
				// toggle pin 9
				channelRack[currentBeat][current_sample][8] = channelRack[currentBeat][current_sample][8] == true ? false : true;
				status = true;
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9));
				// toggle pin 10
				channelRack[currentBeat][current_sample][9] = channelRack[currentBeat][current_sample][9] == true ? false : true;
				status = true;
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10));
				// toggle pin 11
				channelRack[currentBeat][current_sample][10] = channelRack[currentBeat][current_sample][10] == true ? false : true;
				status = true;
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11));
				// toggle pin 12
				channelRack[currentBeat][current_sample][11] = channelRack[currentBeat][current_sample][11] == true ? false : true;
				status = true;
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12));
				// toggle pin 13
				channelRack[currentBeat][current_sample][12] = channelRack[currentBeat][current_sample][12] == true ? false : true;
				status = true;
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13)){
					if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14)) {
						while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14)){
							lcd_flush_write(0, "   ST080");
							UPDATE_LCD = true;
						}
					}
				}

				// toggle pin 14
				channelRack[currentBeat][current_sample][13] = channelRack[currentBeat][current_sample][13] == true ? false : true;
				status = true;
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14));
				// toggle pin 15
				channelRack[currentBeat][current_sample][14] = channelRack[currentBeat][current_sample][14] == true ? false : true;
				status = true;
			}

			// MOVE TO FREESTYLE MODE
//			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15)) {
//				bool reset = false;
//				// reset logic. Reset if you press and hold Pin_16 + Pin_15 + Pin_14
//				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15)) {
//					if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14)) {
//						while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14)){
//							if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13)) {
//								flushRack();
//								flushBuffer();
//								reset = true;
//								lcd_flush_write(0, "   DONE");
//								break;
//							}
//						}
//					}
//				}
//				if (!reset)
//				{
//					// toggle pin 16
//					channelRack[currentBeat][current_sample][15] = channelRack[currentBeat][current_sample][15] == true ? false : true;
//					status = true;
//				}
//			} // end of checking pin 16

			vTaskDelay(10);

		} // end of composer while loop

		/*
		 * FEATURE: Flush the LCD
		 * */
		while (MODE == FREESTYLE)
		{
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13)) {
					if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14)) {
						while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14)) {
							lcd_flush_write(0, "   LCD CLEARED");
							UPDATE_LCD = true;
						}
					}
				}
			}
			// no GPIO functionality for this mode

			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15)) {
				bool reset = false;
				// reset logic. Reset if you press and hold Pin_16 + Pin_15 + Pin_14
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15)) {
					if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14)) {
						while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14)){
							if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13)) {
								flushRack();
								flushBuffer();
								formatEeprom();
								reset = true;
								lcd_flush_write(0, "   EEPROM FLASHED");
								break;
							}
						}
					}
				}
				if (!reset)
				{
					// toggle pin 16
					channelRack[currentBeat][current_sample][15] = channelRack[currentBeat][current_sample][15] == true ? false : true;
					status = true;
				}
			} // end of checking pin 16
			vTaskDelay(50);
		}

		while (MODE == PLAYBACK)
		{
			// Port A

			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0));
				// change to song number 1
				currentBeat = 0;
				status = true;
//				flag to update beat number on the LCD
				UPDATE_BEAT = true;
				vTaskDelay(10); // delay to allow the Modes task to sum the samples
			}
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1));
				currentBeat = 1;
				status = true;
//				flag to update beat number on the LCD
				UPDATE_BEAT = true;
				vTaskDelay(10); // delay to allow the Modes task to sum the samples
			}
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2));
				currentBeat = 2;
				status = true;
//				flag to update beat number on the LCD
				UPDATE_BEAT = true;
				vTaskDelay(10); // delay to allow the Modes task to sum the samples
			}
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3));
				currentBeat = 3;
				status = true;
//				flag to update beat number on the LCD
				UPDATE_BEAT = true;
				vTaskDelay(10); // delay to allow the Modes task to sum the samples
			}
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5));
				currentBeat = 5;
				status = true;
//				flag to update beat number on the LCD
				UPDATE_BEAT = true;
				vTaskDelay(10); // delay to allow the Modes task to sum the samples
			}
			// Port D

			if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4)) {
				while (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4));
				currentBeat = 4;
				status = true;
//				flag to update beat number on the LCD
				UPDATE_BEAT = true;
				vTaskDelay(10); // delay to allow the Modes task to sum the samples
			}
			if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_6)) {
				while (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_6));
				currentBeat = 6;
				status = true;
//				flag to update beat number on the LCD
				UPDATE_BEAT = true;
				vTaskDelay(10); // delay to allow the Modes task to sum the samples
			}
			if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7)) {
				while (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7));
				currentBeat = 7;
				status = true;
//				flag to update beat number on the LCD
				UPDATE_BEAT = true;
				vTaskDelay(10); // delay to allow the Modes task to sum the samples
			}

			// Port E

			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8));
				currentBeat = 8;
				status = true;
//				flag to update beat number on the LCD
				UPDATE_BEAT = true;
				vTaskDelay(10); // delay to allow the Modes task to sum the samples
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9));
				currentBeat = 9;
				status = true;
//				flag to update beat number on the LCD
				UPDATE_BEAT = true;
				vTaskDelay(10); // delay to allow the Modes task to sum the samples
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10));
				currentBeat = 10;
				status = true;
//				flag to update beat number on the LCD
				UPDATE_BEAT = true;
				vTaskDelay(10); // delay to allow the Modes task to sum the samples
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11));
				currentBeat = 11;
				status = true;
//				flag to update beat number on the LCD
				UPDATE_BEAT = true;
				vTaskDelay(10); // delay to allow the Modes task to sum the samples
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12));
				currentBeat = 12;
				status = true;
//				flag to update beat number on the LCD
				UPDATE_BEAT = true;
				vTaskDelay(10); // delay to allow the Modes task to sum the samples
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13)) {
					if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14)) {
						while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14)) {
							lcd_flush_write(0, "   ST080");
						}
					}
				}
				currentBeat = 13;
				status = true;
//				flag to update beat number on the LCD
				UPDATE_BEAT = true;
				vTaskDelay(10); // delay to allow the Modes task to sum the samples
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14));
				currentBeat = 14;
				status = true;
//				flag to update beat number on the LCD
				UPDATE_BEAT = true;
				vTaskDelay(10); // delay to allow the Modes task to sum the samples
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15));
				currentBeat = 15;
				status = true;
//				flag to update beat number on the LCD
				UPDATE_BEAT = true;
				vTaskDelay(10); // delay to allow the Modes task to sum the samples
			}
			vTaskDelay(10);
		}
		while (MODE == SAVE || MODE == ENTER)
		{
			// read the GPIO pins to determine which song to edit on the channel rack
			// add a delay
			// change the mode to COMPOSER after setting the

			// Port A

			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0));
				// change to song number 1
				currentBeat = 0;
				updateVars();
			}
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1));
				// change to song number 2
				currentBeat = 1;
				updateVars();
			}
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2));
				// change to song number 3
				currentBeat = 2;
				updateVars();
			}
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3));
				// change to song number 4
				currentBeat = 3;
				updateVars();
			}
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5));
				currentBeat = 5;
				updateVars();
			}

			// Port D

			if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4)) {
				while (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4));
				currentBeat = 4;
				updateVars();
			}
			if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_6)) {
				while (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_6));
				currentBeat = 6;
				updateVars();
			}
			if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7)) {
				while (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7));
				currentBeat = 7;
				updateVars();
			}

			// Port E

			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8));
				currentBeat = 8;
				updateVars();
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9));
				currentBeat = 9;
				updateVars();
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10));
				currentBeat = 10;
				updateVars();
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11));
				currentBeat = 11;
				updateVars();
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12));
				currentBeat = 12;
				updateVars();
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13));
				currentBeat = 13;
				updateVars();
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14));
				currentBeat = 14;
				updateVars();
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15));
				currentBeat = 15;
				updateVars();
			}
			vTaskDelay(5);
		}
		vTaskDelay(50);
	}
}

void updateVars(){
	MODE = COMPOSER;
	UPDATE_LCD = true;
	GPIO_ResetBits(GPIOB, GPIO_PIN_4);
}

#endif /* GPIOTASK_H_ */
