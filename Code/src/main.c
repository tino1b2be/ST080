#include "ST080Utils.h"	// this is where the FreeRTOS stuff (functions and variable are too)
#include "composer.h"

// define task priorities
#define COMPOSER_TASK_PRIORITY 2

// define task stack sizes
#define COMPOSER_STACK_SIZE 128


// ============================================================================
int main(void) {

	vTaskStartScheduler(); // This should never return.
	// Will only get here if there was insufficient memory to create
	// the idle task.
	while(1);
}
