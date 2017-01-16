#include "ST080/Utils080.h"
#include "ST080/ModesTask.h"
#include "ST080/AudioStuff.h"
#include "ST080/GPIOTask.h"
#include "ST080/UIUdate.h"
#include "ST080/Eeprom.h"

// define task priorities
#define MODES_TASK_PRIORITY 1
#define UI_TASK_PRIORITY 2
#define GPIO_TASK_PRIORITY 3

// define task stack sizes
#define MODES_STACK_SIZE 128
#define UI_STACK_SIZE 128
#define GPIO_STACK_SIZE 128

// ============================================================================
int main(void) {
	startUpConfigs();
//	turn on reset LED
	GPIO_SetBits(GPIOB, GPIO_PIN_5);
	EEPROM_Configuration();
	lcd_write(4,0,"WELCOME");
	lcd_write(5,1,"ST080");
	loadFromEeprom();		// Load the channel rack from the eeprom

	xTaskCreate(vModesTask, (signed char * ) "Modes Task", MODES_STACK_SIZE, NULL, MODES_TASK_PRIORITY, NULL);
	xTaskCreate(vUITask, (signed char * ) "UI Task", UI_STACK_SIZE, NULL, UI_TASK_PRIORITY, NULL);
	xTaskCreate(vGPIOTask, (signed char * ) "GPIO Inputs Task", GPIO_STACK_SIZE, NULL, GPIO_TASK_PRIORITY, NULL);
//Turn off reset LED
	GPIO_ResetBits(GPIOB, GPIO_PIN_5);
	vTaskStartScheduler();
	while(1);
}
