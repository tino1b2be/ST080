/**
 *****************************************************************************
 **
 **  File        : main.c
 **
 **  Abstract    : main function.
 **
 **  Functions   : main
 **
 **  Environment : Atollic TrueSTUDIO(R)
 **                STMicroelectronics STM32F4xx Standard Peripherals Library
 **
 **  Distribution: The file is distributed as is, without any warranty
 **                of any kind.
 **
 **  (c)Copyright Atollic AB.
 **  You may use this file as-is or modify it according to the needs of your
 **  project. Distribution of this file (unmodified or modified) is not
 **  permitted. Atollic AB permit registered Atollic TrueSTUDIO(R) users the
 **  rights to distribute the assembled, compiled & linked contents of this
 **  file as part of an application binary file, provided that it is built
 **  using the Atollic TrueSTUDIO(R) toolchain.
 **
 **
 *****************************************************************************
 */

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "utils.h"
#include "debug.h"
#include "mems.h"

#include "composer.h"

xQueueHandle delayQueue;

#define LED_STACK_SIZE 128
#define LED_TASK_PRIORITY 1 /* Low Priority */
#define BUTTON_STACK_SIZE 128
#define BUTTON_TASK_PRIORITY 2 /* Higher Priority */

// Task priorities: Higher numbers are higher priority.
static void vLEDTask( void *pvparameters );
static void vButtonTask( void *pvparameters );

uint64_t tickTime=0;        // Counts OS ticks (default = 1000Hz).
uint64_t u64IdleTicks=0;    // Value of u64IdleTicksCnt is copied once per sec.
uint64_t u64IdleTicksCnt=0; // Counts when the OS has no task to execute.
uint16_t u16PWM1=0;
uint32_t tempo = 120;		/* in bpm */
uint32_t averageTime = 600;	/* in ms */

/**
  * @brief  This function handles External line 0 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		/* Clear the EXTI line 0 pending bit */
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

// ============================================================================
int main( void )
{

	/* Create Tasks */
	xTaskCreate( vLEDTask, ( signed char * ) "LED Task", LED_STACK_SIZE, NULL, LED_TASK_PRIORITY, NULL );

    vTaskStartScheduler(); // This should never return.

    // Will only get here if there was insufficient memory to create
    // the idle task.
    for( ;; );  
}

/*
 * LED Toggle Task
 */
static void vLEDTask( void *pvparameters )
{

	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDOff(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDOff(LED5);

	for(;;)
	{
		STM_EVAL_LEDToggle(LED4);
		STM_EVAL_LEDToggle(LED5);

		vTaskDelay(configTICK_RATE_HZ*1);
	}
}


// This FreeRTOS callback function gets called once per tick (default = 1000Hz).
// ---------------------------------------------------------------------------- 
void vApplicationTickHook( void ) {
    ++tickTime;
}

// This FreeRTOS call-back function gets when no other task is ready to execute.
// On a completely unloaded system this is getting called at over 2.5MHz!
// ---------------------------------------------------------------------------- 
void vApplicationIdleHook( void ) {
    ++u64IdleTicksCnt;
}

// A required FreeRTOS function.
// ---------------------------------------------------------------------------- 
void vApplicationMallocFailedHook( void ) {
    configASSERT( 0 );  // Latch on any failure / error.
}




