#include "ST080/Utils080.h"
#include "ST080/ModesTask.h"
#include "ST080/AudioStuff.h"
#include "ST080/GPIOTask.h"
#include "ST080/UIUdate.h"
#include "ST080/Eeprom.h"

// define task priorities
#define MODES_TASK_PRIORITY 2
#define UI_TASK_PRIORITY 1
#define GPIO_TASK_PRIORITY 3

// define task stack sizes
#define MODES_STACK_SIZE 128
#define UI_STACK_SIZE 128
#define GPIO_STACK_SIZE 128

// ============================================================================
int main(void) {
	/* Config Eeprom*/
	EEPROM_Configuration();
	startUpConfigs();
	loadFromEeprom();		// Load the channel rack from the eeprom

	xTaskCreate(vModesTask, (signed char * ) "Modes Task", MODES_STACK_SIZE, NULL, MODES_TASK_PRIORITY, NULL);
	xTaskCreate(vUITask, (signed char * ) "UI Task", UI_STACK_SIZE, NULL, UI_TASK_PRIORITY, NULL);
	xTaskCreate(vGPIOTask, (signed char * ) "GPIO Inputs Task", GPIO_STACK_SIZE, NULL, GPIO_TASK_PRIORITY, NULL);

	vTaskStartScheduler(); // This should never return.
	// Will only get here if there was insufficient memory to create
	// the idle task.
	while(1);
}
