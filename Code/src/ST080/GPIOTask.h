/*
 * GPIOTask.h
 *
 *  Created on: Sep 27, 2016
 *      Author: user
 */

#ifndef GPIOTASK_H_
#define GPIOTASK_H_

#include "Utils080.h"

void vGPIOTask(void * pvparameters);

void vGPIOTask(void * pvparameters) {
	// TODO read GPIO pins

	while (true) {
		while (MODE == COMPOSER) {

		}
		while (MODE == FREESTYLE) {

		}
		while (MODE == PLAYBACK) {

		}
		// TODO task delay
		vTaskDelay(5);
	}
}


#endif /* GPIOTASK_H_ */
