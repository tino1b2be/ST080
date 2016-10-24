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
 * struct used to store a GPIO and a GPIO_pin
 * added by Hermann
 */
struct LED_GPIO {
	GPIO_TypeDef * GPIO;
	uint16_t pin;
};

//added by Hermann
struct LED_GPIO getGPIO(uint8_t pin, uint8_t type);
void updateLED(uint8_t pin, bool condition, uint8_t type);


/**
 * Turn the channel rack LED On or Off depending on the state of the corresponding pin
 * added by Hermann
 */
void updateLED(uint8_t pin, bool condition, uint8_t type) {
	struct LED_GPIO _GPIO = getGPIO(pin, type);
	;
	if(condition) GPIO_SetBits(_GPIO.GPIO, _GPIO.pin);
	else GPIO_ResetBits(_GPIO.GPIO, _GPIO.pin);
}

/**
 * return the correct GPIO and GPIO_pin based on the given channel rack's pin
 * added by Hermann
 */
struct LED_GPIO getGPIO(uint8_t pin, uint8_t type) {
	struct LED_GPIO _GPIO;
	switch(type) {
	case (uint8_t)0:
			switch(pin) {
			case (uint8_t)0:
					_GPIO.GPIO = GPIOA;
					_GPIO.pin = GPIO_Pin_8;
					return _GPIO;
			case (uint8_t)1:
					_GPIO.GPIO = GPIOA;
					_GPIO.pin = GPIO_Pin_9;
					return _GPIO;
			case (uint8_t)2:
					_GPIO.GPIO = GPIOA;
					_GPIO.pin = GPIO_Pin_10;
					return _GPIO;
			case (uint8_t)3:
					_GPIO.GPIO = GPIOC;
					_GPIO.pin = GPIO_Pin_3;
					return _GPIO;
			case (uint8_t)4:
					_GPIO.GPIO = GPIOC;
					_GPIO.pin = GPIO_Pin_4;
					return _GPIO;
			case (uint8_t)5:
					_GPIO.GPIO = GPIOC;
					_GPIO.pin = GPIO_Pin_5;
					return _GPIO;
			case (uint8_t)6:
					_GPIO.GPIO = GPIOC;
					_GPIO.pin = GPIO_Pin_6;
					return _GPIO;
			case (uint8_t)7:
					_GPIO.GPIO = GPIOC;
					_GPIO.pin = GPIO_Pin_7;
					return _GPIO;
			case (uint8_t)8:
					_GPIO.GPIO = GPIOC;
					_GPIO.pin = GPIO_Pin_8;
					return _GPIO;
			case (uint8_t)9:
					_GPIO.GPIO = GPIOC;
					_GPIO.pin = GPIO_Pin_9;
					return _GPIO;
			case (uint8_t)10:
					_GPIO.GPIO = GPIOC;
					_GPIO.pin = GPIO_Pin_10;
					return _GPIO;
			case (uint8_t)11:
					_GPIO.GPIO = GPIOC;
					_GPIO.pin = GPIO_Pin_11;
					return _GPIO;
			case (uint8_t)12:
					_GPIO.GPIO = GPIOE;
					_GPIO.pin = GPIO_Pin_0;
					return _GPIO;
			case (uint8_t)13:
					_GPIO.GPIO = GPIOE;
					_GPIO.pin = GPIO_Pin_1;
					return _GPIO;
			case (uint8_t)14:
					_GPIO.GPIO = GPIOE;
					_GPIO.pin = GPIO_Pin_2;
					return _GPIO;
			case (uint8_t)15:
					_GPIO.GPIO = GPIOE;
					_GPIO.pin = GPIO_Pin_3;
					return _GPIO;
			}
	case (uint8_t)1:
			switch(pin) {
			case (uint8_t)0:
					_GPIO.GPIO = GPIOB;
					_GPIO.pin = GPIO_Pin_0;
					return _GPIO;
			case (uint8_t)1:
					_GPIO.GPIO = GPIOB;
					_GPIO.pin = GPIO_Pin_1;
					return _GPIO;
			case (uint8_t)2:
					_GPIO.GPIO = GPIOB;
					_GPIO.pin = GPIO_Pin_2;
					return _GPIO;
			case (uint8_t)3:
					_GPIO.GPIO = GPIOB;
					_GPIO.pin = GPIO_Pin_3;
					return _GPIO;
			}
	}
	return _GPIO; //to satisfy compiler
}

/**
 * Task to update the LEDs depending on the current mode and status of the system
 */
void vUITask(void * pvparameters){

	while (true){
		while(MODE==COMPOSER)
		{
			//update the Instrument-Select Pad
			for(uint8_t instr = 0; instr < 4; ++instr)
				updateLED(instr, instr == current_sample, 1);
			// go through channel rack and set LED status based on channel rack pins
			// NB Have to manually check each pin on the channel rack and update the corresponding GPIO pin
			// TODO if statements for each pin in the rack
			for (uint8_t pin = 0; pin < 16; ++pin)
				updateLED(pin, channelRack[currentBeat][current_sample][pin], 0);
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
