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

#include "ST080/ModesTask.h"
#include "ST080/GPIOTask.h"
#include "ST080/UIUdate.h"

// ============================================================================
int main(void) {
	// Run the start up configurations.
	startUpConfigs();

	// Create the FreeRTOS tasks
	xTaskCreate(vModesTask, (signed char * ) "Modes Task", MODES_STACK_SIZE, NULL, MODES_TASK_PRIORITY, NULL);
	xTaskCreate(vUITask, (signed char * ) "UI Task", UI_STACK_SIZE, NULL, UI_TASK_PRIORITY, NULL);
	xTaskCreate(vGPIOTask, (signed char * ) "GPIO Inputs Task", GPIO_STACK_SIZE, NULL, GPIO_TASK_PRIORITY, NULL);

	// Run the task scheduler
	vTaskStartScheduler();
	while(1);
}
