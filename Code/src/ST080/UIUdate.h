/*
 * UIUdate.h
 *
 *  Created on: Sep 27, 2016
 *      Author: Tinotenda Chemvura
 */

#ifndef UIUDATE_H_
#define UIUDATE_H_

#include "Utils080.h"

void vUITask(void * pvparameters);

/**
 * Task to update the LEDs depending on the current mode and status of the system
 */
void vUITask(void * pvparameters){

	while (true){
		while(MODE==COMPOSER)
		{
			// go throught channel rack and set LED status based on channel rack pins
			// NB Have to manually check each pin on the channel rack and update the corresponding GPIO pin
			// TODO if statements for each pin in the rack
			vTaskDelay(50);
		}
		while(MODE==FREESTYLE)
		{
			// TODO light up the corresponding LEDs for the freestyle pad depending on the status of the flags
			// * use a global array of flags (four flags) which will be set by the IRQ and reset inside this function
			// * LEDs must flash for a short period (200ms)
			// * Can use a timer to count up to 200ms. NB TODO must carefully work out algorithm
			vTaskDelay(50);
		}
		while(MODE==PLAYBACK)
		{
			// TODO still to figure out how to implement this mode
			// load the channel rack and use the config to play back music.
			// must enable logic to cycle through the different composed songs (use the channel rack buttons)
			vTaskDelay(50);
		}
		// TODO task delay
		vTaskDelay(50);
	}
}
#endif /* UIUDATE_H_ */
