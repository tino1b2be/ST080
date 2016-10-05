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
