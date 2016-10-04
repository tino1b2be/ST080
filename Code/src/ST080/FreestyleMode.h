/*
 * FreestyleMode.h
 *
 *  Created on: Sep 27, 2016
 *      Author: user
 */

#ifndef FREESTYLEMODE_H_
#define FREESTYLEMODE_H_

#include "Utils080.h"

// TODO implement freestle stuff

void vFreestyleTask(void * pvparameterss);

void vFreestyleTask(void * pvparameters)
{
	// TODO pre-configs

	while (true)
	{
		while(MODE == FREESTYLE)
		{
			// TODO freestyle logic
			vTaskDelay(10);
		}
		vTaskDelay(10); // TODO might need to optmise this delay
	} //
} // END of task function


#endif /* FREESTYLEMODE_H_ */
