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

void vGPIOTask(void * pvparameters) {
	// TODO read GPIO pins

	while (true) {
		while (MODE == COMPOSER)
		{
			// read the channel rack pins
			// 1=A0, 2=A1, 3=A2, 4=A3, 5=A4, 6=A5, 7=A6, 8=A7, 9=E8, 10=E9, 11=E10, 12=E11, 13=E12, 14=E13, 15=E14, 16=E15

			vTaskDelay(10);

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
			}
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3));
				// toggle pin 4
				channelRack[currentBeat][current_sample][3] = channelRack[currentBeat][current_sample][3] == true ? false : true;
				status = true;
			}
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4));
				// toggle pin 5
				channelRack[currentBeat][current_sample][4] = channelRack[currentBeat][current_sample][4] == true ? false : true;
				status = true;
			}
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5));
				// toggle pin 6
				channelRack[currentBeat][current_sample][5] = channelRack[currentBeat][current_sample][5] == true ? false : true;
				status = true;
			}

			// these two pins are high by default for some odd reason hence why they are commented out

//			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)) { // TODO implement pull down in hardware
//				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6));
//				// toggle pin 7
//				channelRack[currentBeat][current_sample][6] = channelRack[currentBeat][current_sample][6] == true ? false : true;
//				status = true;
//			}
//			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7)) {
//				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7));
//				// toggle pin 8
//				channelRack[currentBeat][current_sample][7] = channelRack[currentBeat][current_sample][7] == true ? false : true;
			//status = true;
//			}

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
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13));
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
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15));
				// toggle pin 16
				channelRack[currentBeat][current_sample][15] = channelRack[currentBeat][current_sample][15] == true ? false : true;
				status = true;
			}
		}
		while (MODE == FREESTYLE)
		{
			// TODO freestyle code
			vTaskDelay(50);
		}
		while (MODE == PLAYBACK)
		{
			// TODO playback code
			vTaskDelay(50);
		}
		while (MODE == SAVE)
		{
			// read the GPIO pins to determine which song to edit on the channel rack
			// add a delay
			// change the mode to COMPOSER after setting the

			// Port A

			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0));
				// change to song number 1
				currentBeat = 0;
				vTaskDelay(20);
				MODE = COMPOSER;
			}
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1));
				currentBeat = 1;
				vTaskDelay(20);
				MODE = COMPOSER;
			}
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2));
				currentBeat = 2;
				vTaskDelay(20);
				MODE = COMPOSER;
			}
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3));
				currentBeat = 3;
				vTaskDelay(20);
				MODE = COMPOSER;
			}
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4));
				currentBeat = 4;
				vTaskDelay(20);
				MODE = COMPOSER;
			}
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5));
				currentBeat = 5;
				vTaskDelay(20);
				MODE = COMPOSER;
			}
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6));
				currentBeat = 6;
				vTaskDelay(20);
				MODE = COMPOSER;
			}
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7)) {
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7));
				currentBeat = 7;
				vTaskDelay(20);
				MODE = COMPOSER;
			}

			// Port E

			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8));
				currentBeat = 8;
				vTaskDelay(20);
				MODE = COMPOSER;
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9));
				currentBeat = 9;
				vTaskDelay(20);
				MODE = COMPOSER;
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10));
				currentBeat = 10;
				vTaskDelay(20);
				MODE = COMPOSER;
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11));
				currentBeat = 11;
				vTaskDelay(20);
				MODE = COMPOSER;
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12));
				currentBeat = 12;
				vTaskDelay(20);
				MODE = COMPOSER;
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13));
				currentBeat = 13;
				vTaskDelay(20);
				MODE = COMPOSER;
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14));
				currentBeat = 14;
				vTaskDelay(20);
				MODE = COMPOSER;
			}
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15)) {
				while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15));
				currentBeat = 15;
				vTaskDelay(20);
				MODE = COMPOSER;
			}
			
			// TODO task delay
			vTaskDelay(5);
		}

		vTaskDelay(50);
	}
}


#endif /* GPIOTASK_H_ */
