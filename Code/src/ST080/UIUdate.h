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
void clearLEDs();
void updateModeLEDs();
void updateInstrLEDs();
/**
 * return the correct GPIO and GPIO_pin based on the given channel rack's pin
 * added by Hermann
 */
LED_GPIO getGPIO(uint8_t pin, uint8_t type) {
	LED_GPIO _GPIO;
//	split in cases to reduce checking delay
	switch(type) {
	case (uint8_t)0:
			//for channel rack LEDs
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
//			For instrument selection
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
	case (uint8_t)2:
//			For Mode selection
			switch(pin) {
			case (uint8_t)0:
					_GPIO.GPIO = GPIOC;
					_GPIO.pin = GPIO_Pin_0;
					return _GPIO;
			case (uint8_t)1:
					_GPIO.GPIO = GPIOC;
					_GPIO.pin = GPIO_Pin_1;
					return _GPIO;
			case (uint8_t)2:
					_GPIO.GPIO = GPIOC;
					_GPIO.pin = GPIO_Pin_2;
					return _GPIO;
			}
	}
	return _GPIO; //to satisfy compiler
}

/**
 * Turn the channel rack LED On or Off depending on the state of the corresponding pin
 * added by Hermann
 */
void updateLED(uint8_t pin, bool On, uint8_t type) {
	LED_GPIO _GPIO = getGPIO(pin, type);
	if(On) GPIO_SetBits(_GPIO.GPIO, _GPIO.pin);
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
 * Refresh LED if there's a change in mode or
 */
void updateLCD() {
	if(UPDATE_LCD || UPDATE_TEMPO || UPDATE_BEAT) {
		switch(MODE) {
		case COMPOSER:
			UPDATE_TEMPO = false;
//			update the mode and instrument only if needed
			if (UPDATE_LCD) {
				//update the Instrument-Select Pad
				lcd_flush_write(0, " Composer Mode");
				switch(current_sample) {
				case INSTR_1:
					lcd_write(0, 1, "Open Hat");
					break;
				case INSTR_2:
					lcd_write(0, 1, "Kick");
					break;
				case INSTR_3:
					lcd_write(0, 1, "Cow Bell");
					break;
				case INSTR_4:
					lcd_write(0, 1, "Clap");
					break;
				}
				lcd_write(9, 1, "T: ");
			}
			uint8_t n = log10(tempo) + 1;
			char *numberArray = calloc(n, sizeof(char));
			itoa(tempo, numberArray, 10);
			lcd_write(12, 1, numberArray);
			if(tempo < 100)
				lcd_write(14, 1, " ");
	//		free memory
			free(numberArray);
			break;
		case PLAYBACK:
			UPDATE_BEAT = false;
			lcd_flush_write(0, " Playback Mode");
			lcd_write(0, 1, "Playing beat");
			uint8_t n_ = log10(currentBeat + 1) + 1;
			char *numberArray_ = calloc(n_, sizeof(char));
			itoa(currentBeat + 1, numberArray_, 10);
			lcd_write(13, 1, numberArray_);
			if(tempo < 10)
				lcd_write(14, 1, " ");
	//		free memory
			free(numberArray_);
			break;
		case FREESTYLE:
			lcd_flush_write(0, " Freestyle Mode");
			lcd_write(4, 1, "Enjoy :)");
			break;
		}
		UPDATE_LCD = false;
	}
}


void clearLEDs() {
	if(resetLEDs){
		resetLEDs = false;
	//	clear mode LEDs
		for (uint8_t pin = 0; pin < 3; ++pin)
			updateLED(pin, false, 2);
	//	clear channel rack LEDs
		for (uint8_t pin = 0; pin < 16; ++pin)
			updateLED(pin, false, 0);
	//	clear instrument LEDs
		for(uint8_t instr = 0; instr < 4; ++instr) {
			updateLED(instr, false, 1);
		}
	}
}

void updateModeLEDs(){
	//		update the mode LEDs
	for (uint8_t mode = 0; mode < 3; ++mode)
		updateLED(mode, MODE == mode + 1, 2);
}

void updateInstrLEDs() {
	for(uint8_t instr = 0; instr < 4; ++instr)
		updateLED(instr, instr == current_sample, 1);
}

void lcd_write_tempo(){
	lcd_write(10, 1, "T:");
	uint8_t n = log10(tempo) + 1;
	char *numberArray = calloc(n, sizeof(char));
	itoa(tempo, numberArray, 10);
	lcd_write(12, 1, numberArray);
	free(numberArray);
}

bool timeToWrite(){
	bool ret = (tickTime - lcd_timer) > 200;
	lcd_timer = tickTime;
	return ret;
}
/**
 * Task to update the LEDs depending on the current mode and status of the system
 */
void vUITask(void * pvparameters){
	while (true){
		clearLEDs();
		updateLCD();
		updateModeLEDs();
		switch(MODE){
		case COMPOSER:
			updateInstrLEDs();
			// go through channel rack and set LED status based on channel rack pins
			// NB Have to manually check each pin on the channel rack and update the corresponding GPIO pin
			for (uint8_t pin = 0; pin < 16; ++pin)
				updateLED(pin, channelRack[currentBeat][current_sample][pin], 0);
			break;
		case PLAYBACK:
			for (uint8_t i = 0; i < 16; ++i)
				updateLED(i,i==currentBeat,0);
			//LCD_funtion("Playing Song 1")
			break;
		case FREESTYLE:
			// TODO light up the corresponding LEDs for the freestyle pad depending on the status of the flags
			// * use a global array of flags (four flags) which will be set by the IRQ and reset inside this function
			// * LEDs must flash for a short period (200ms)
			// * Can use a timer to count up to 200ms. NB TODO must carefully work out algorithm
			//			reset the flag
			STATE_CHANGED = false;
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
			break;
//		case ERROR_MODE:
//			lcd_flush_write(0, "Error occurred");
//			lcd_write(0, 1, "Restarting...");
//			break;

		case SAVE:
			while(status){
				updateLED(currentBeat,true,0);
				lcd_flush_write(0, " Save Mode");
				lcd_write(0, 1,"Saving this song");
				vTaskDelay(100);
			}
			if(timeToWrite()){
				lcd_flush_write(0, " Save Mode");
				lcd_write(0, 1,"Select next song");
			}
			break;
		}
		vTaskDelay(50);
	}
}
#endif /* UIUDATE_H_ */
