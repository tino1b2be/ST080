/*
 * ModesTask.h
 *
 *  Created on: Oct 5, 2016
 *      Author: Tinotenda Chemvura
 */

#ifndef ST080_MODESTASK_H_
#define ST080_MODESTASK_H_

#include "Utils080.h"

void vModesTask(void * pvparameters);

void vModesTask(void * pvparameters)
{
	while (true){
		// TODO merge all code for the three different modes in here
		while (MODE == COMPOSER) {
			// TODO code for the composer mode
			vTaskDelay(50);
		}
		while (MODE == FREESTYLE) {
			// TODO code for the freestyle mode
			vTaskDelay(50);
		}
		while (MODE == PLAYBACK) {
			// TODO code for the playback mode
			vTaskDelay(50);
		}
		// TODO task delay
		vTaskDelay(50);
	}
}

#endif /* ST080_MODESTASK_H_ */
