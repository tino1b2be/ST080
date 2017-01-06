/*
 * UIUdate.h
 *
 *  Created on: Sep 27, 2016
 *      Author: Herman Kouamme
 */

#ifndef UIUDATE_H_
#define UIUDATE_H_

#include "Utils080.h"

void vUITask(void * pvparameters);
LED_GPIO getGPIO(uint8_t pin, uint8_t type);
void updateLED(uint8_t pin, bool condition, uint8_t type);
bool LEDOnDelay(uint32_t milli);
//bool getCondition(uint8_t instr);

/**
 * return the correct GPIO and GPIO_pin based on the given channel rack's pin
 * added by Hermann
 */
LED_GPIO getGPIO(uint8_t pin, uint8_t type) {
	LED_GPIO _GPIO;
	switch(type) {
	case (uint8_t)0:
			switch(pin) {
			case (uint8_t)0:
					_GPIO.GPIO = GPIOA;
					_GPIO.pin = GPIO_Pin_8;
					return _GPIO;
			case (uint8_t)1:
					_GPIO.GPIO = GPIOA;
					_GPIO.pin = GPIO_Pin_7;
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
					_GPIO.pin = GPIO_Pin_6;
					return _GPIO;
			case (uint8_t)1:
					_GPIO.GPIO = GPIOB;
					_GPIO.pin = GPIO_Pin_7;
					return _GPIO;
			case (uint8_t)2:
					_GPIO.GPIO = GPIOB;
					_GPIO.pin = GPIO_Pin_8;
					return _GPIO;
			case (uint8_t)3:
					_GPIO.GPIO = GPIOB;
					_GPIO.pin = GPIO_Pin_9;
					return _GPIO;
			}
	}
	return _GPIO; //to satisfy compiler
}

/**
 * Turn the channel rack LED On or Off depending on the state of the corresponding pin
 * added by Hermann
 */
void updateLED(uint8_t pin, bool condition, uint8_t type) {
	LED_GPIO _GPIO = getGPIO(pin, type);
	;
	if(condition) GPIO_SetBits(_GPIO.GPIO, _GPIO.pin);
	else GPIO_ResetBits(_GPIO.GPIO, _GPIO.pin);
}

/**
 *Delay used to keep LED on for a while when in freestyle mode
 */
bool LEDOnDelay(uint32_t milli) {
	uint32_t delay = milli * 17612;              // approximate loops per ms at 168 MHz, Debug config
	for(; delay != 0; delay--)
	{
//		quit delay if user presses the pad again
		if(STATE_CHANGED) return false;
	};
	return true;
}

/**
 * return the flag/condition upon which LED should be updated
 * when in FreeStyle mode
 * !!!!Not needed at the moment but do not remove please!!!!
 */
//bool getCondition(uint8_t instr){
//	switch(instr){
//	//for instrument 1
//	case 0(uint8_t):
//			switch(played_inst){
//			case 2:
//				return true;
//			case 6:
//				return true;
//			case 10:
//				return true;
//			case 18:
//				return true;
//			case 14:
//				return true;
//			case 22:
//				return true;
//			case 26:
//				return true;
//			case 30:
//				return true;
//			default:
//				return false;
//			}
//	//for instrument 1
//	case 1(uint8_t):
//		switch(played_inst){
//		case 4:
//			return true;
//		case 6:
//			return true;
//		case 12:
//			return true;
//		case 20:
//			return true;
//		case 14:
//			return true;
//		case 22:
//			return true;
//		case 28:
//			return true;
//		case 30:
//			return true;
//		default:
//			return false;
//		}
//	//for instrument 1
//	case 2(uint8_t):
//		switch(played_inst){
//		case 8:
//			return true;
//		case 10:
//			return true;
//		case 12:
//			return true;
//		case 24:
//			return true;
//		case 14:
//			return true;
//		case 26:
//			return true;
//		case 28:
//			return true;
//		case 30:
//			return true;
//		default:
//			return false;
//		}
//	//for instrument 1
//	case 3(uint8_t):
//		switch(played_inst){
//		case 16:
//			return true;
//		case 18:
//			return true;
//		case 20:
//			return true;
//		case 24:
//			return true;
//		case 22:
//			return true;
//		case 26:
//			return true;
//		case 28:
//			return true;
//		case 30:
//			return true;
//		default:
//			return false;
//		}
//	}
//}

/**
 * Task to update the LEDs depending on the current mode and status of the system
 */
void vUITask(void * pvparameters){

	while (true){
		while(MODE==COMPOSER || MODE==PLAYBACK)
		{
			//update the Instrument-Select Pad
			if(MODE==COMPOSER) {
				for(uint8_t instr = 0; instr < 4; ++instr)
					updateLED(instr, instr == current_sample, 1);
			}
			// go through channel rack and set LED status based on channel rack pins
			// NB Have to manually check each pin on the channel rack and update the corresponding GPIO pin
			for (uint8_t pin = 0; pin < 16; ++pin)
				updateLED(pin, channelRack[currentBeat][current_sample][pin], 0);
			vTaskDelay(50);
		}
		while(MODE==FREESTYLE)
		{
			PAD_STATE[0] = true;
//			reset the flag
			STATE_CHANGED = false;
			// TODO light up the corresponding LEDs for the freestyle pad depending on the status of the flags
			// * use a global array of flags (four flags) which will be set by the IRQ and reset inside this function
			// * LEDs must flash for a short period (200ms)
			// * Can use a timer to count up to 200ms. NB TODO must carefully work out algorithm
			for(uint8_t instr = 0; instr < 4; ++instr) {
				updateLED(instr, PAD_STATE[instr], 1);
//				reset flag
				PAD_STATE[instr] = false;
			}
			//Delay if there's at least one LED on
			if (PAD_STATE[0] || PAD_STATE[1] || PAD_STATE[2] || PAD_STATE[3]) {
				//turn LEDs off if delay is not interrupted otherwise the next loop will update it
				if ( !LEDOnDelay(200) ) {
					for(uint8_t instr = 0; instr < 4; ++instr) {
						updateLED(instr, false, 1);
					}
				}

			}
			vTaskDelay(50);
		}
		vTaskDelay(50);
	}
}
#endif /* UIUDATE_H_ */
