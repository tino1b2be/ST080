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

#define LED_STACK_SIZE 128
#define LED_TASK_PRIORITY 1 /* Low Priority */
#define BUTTON_STACK_SIZE 128
#define BUTTON_TASK_PRIORITY 2 /* Higher Priority */

uint32_t del = 1000;
uint32_t tog = 0;


/* Handle PA0 interrupt */
void EXTI0_IRQHandler(void) {
	/* Make sure that interrupt flag is set */
	if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
		/* Clear interrupt flag */
		EXTI_ClearITPendingBit(EXTI_Line0);
		/* Do your stuff when PD0 is changed */

		if (++tog % 2) {
			del = tickTime;
		} else {
			int temp = del;
			del = tickTime - del;
			portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
			if (del > 50)
				xQueueSendFromISR(delayQueue, &del, &xHigherPriorityTaskWoken);
			else{
				del = temp;
				tog--;
			}
		}

	}
}

void configStuff() {
	delayQueue = xQueueCreate(5, sizeof(uint32_t));

	// configure GPIO interrupt for user button (PA0)

	/* Set variables used */
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;

	/* Enable clock for GPIOD */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	/* Enable clock for SYSCFG */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Set pin PA0 as input */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* Tell system that you will use PA0 for EXTI_Line0 */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

	/* PA0 is connected to EXTI_Line0 */
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	/* Enable interrupt */
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	/* Interrupt mode */
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	/* Triggers on rising and falling edge */
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	/* Add to EXTI */
	EXTI_Init(&EXTI_InitStruct);

	/* Add IRQ vector to NVIC */
	/* PA0 is connected to EXTI_Line0, which has EXTI0_IRQn vector */
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	/* Set priority */
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	/* Set sub priority */
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	/* Enable interrupt */
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	/* Add to NVIC */
	NVIC_Init(&NVIC_InitStruct);
}
/*
 * LED Toggle Task
 */
void vLEDTask(void *pvparameters) {
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDOff(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDOff(LED5);
	uint32_t del = 1000;
	for (;;) {
		STM_EVAL_LEDToggle(LED4);
		STM_EVAL_LEDToggle(LED5);
		uint8_t waiting = uxQueueMessagesWaiting(delayQueue);
		if (waiting)
			xQueueReceive(delayQueue, &del, 10);
		vTaskDelay(del);
	}
}

void vButtonTask(void *pvparameters) {
	int tog = 0;

	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);
	uint32_t del = 0;
	while (1) {
		if (STM_EVAL_PBGetState(BUTTON_USER)) {
			while (STM_EVAL_PBGetState(BUTTON_USER))
				;

			if (++tog % 2) {
				del = tickTime;
			} else {
				del = tickTime - del;
				xQueueSend(delayQueue, &del, 10);
			}
		}
		vTaskDelay(10);
	}
}
// ============================================================================
int main(void) {

	/* Create Tasks */
	xTaskCreate(vLEDTask, (signed char * ) "LED Task", LED_STACK_SIZE, NULL,
			LED_TASK_PRIORITY, NULL);
	configStuff();
//	xTaskCreate(vButtonTask, (signed char * ) "BUTTON Task", BUTTON_STACK_SIZE,
//			NULL, BUTTON_TASK_PRIORITY, NULL);
	vTaskStartScheduler(); // This should never return.

	// Will only get here if there was insufficient memory to create
	// the idle task.
	for (;;)
		;
}

// This FreeRTOS callback function gets called once per tick (default = 1000Hz).
// ---------------------------------------------------------------------------- 
void vApplicationTickHook(void) {
	++tickTime;
}

// This FreeRTOS call-back function gets when no other task is ready to execute.
// On a completely unloaded system this is getting called at over 2.5MHz!
// ---------------------------------------------------------------------------- 
void vApplicationIdleHook(void) {
	++u64IdleTicksCnt;
}

// A required FreeRTOS function.
// ---------------------------------------------------------------------------- 
void vApplicationMallocFailedHook(void) {
	configASSERT(0);  // Latch on any failure / error.
}

