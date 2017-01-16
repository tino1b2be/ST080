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
