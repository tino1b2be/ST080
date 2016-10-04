/*
 * PlaybackMode.h
 *
 *  Created on: Sep 27, 2016
 *      Author: Tinotenda Chemvura
 */

#ifndef PLAYBACKMODE_H_
#define PLAYBACKMODE_H_

#include "Utils080.h"

void vPlaybackTask(void * pvparameters);

void vPlaybackTask(void * pvparameters)
{
	while (true)
	{
		while (MODE == PLAYBACK)
		{
			// TODO implement code for playback mode
			vTaskDelay(50);
		}
		vTaskDelay(50);
	}
}

#endif /* PLAYBACKMODE_H_ */
