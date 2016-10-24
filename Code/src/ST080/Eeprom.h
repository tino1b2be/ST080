/*
 * Eeprom.h
 *
 *  Created on: Oct 24, 2016
 *      Author: Othniel Konan
 * Description:	Manage eeprom access
 * EEPROM Pins:		MOSI	PB15
 * 					MISO	PB14
 * 					CLK		PB13
 * 					CS		PB12
 * Using SPI2
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include "Utils080.h"

// TODO needed functions
void saveToEeprom(void); 	// TODO this function saves the array "channelRack[][][]" to the eeprom, the size of this array is CHANNEL_RACK_SIZE
void loadFromEeprom(void);	// TODO this function initialises the "channelRack[][][]" using data read from the eeprom

void saveToEeprom(void)
{
	// todo
}

void loadFromEeprom(void)
{
	// todo
}

// EEPROM instructions
#define WREN 0b00000110 // enable writing
#define WRDI 0b00000100 // disable writing
#define RDSR 0b00000101 // read status register
#define WRSR 0b00000001 // write status register
#define READ 0b00000011	// read instruction
#define WRITE 0b00000010 // write instruction

#define PAGE_LENGTH 32
/*
 * @brief Configuration of the eeprom
 * Using SPI2 with
 * 		MOSI	PB15
 * 		MISO	PB14
 * 		CLK		PB13
 * 		CS		PB12
 */
void EEPROM_Configuration(){
	/* RCC Configuration */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

	/* GPIO Configuration */
	// MOSI, MISO, CLK configuration
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	// CS configuration
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_SetBits(GPIOB, GPIO_Pin_12); // set CS High
	// Configuring MISO,MOSI,CLK as Alternate function of SPI2
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);

	/* SPI Configuration */
	SPI_InitTypeDef SPI_InitStrcut;
	SPI_I2S_DeInit(SPI2);
	SPI_InitStrcut.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	SPI_InitStrcut.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStrcut.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStrcut.SPI_CRCPolynomial = 7;
	SPI_InitStrcut.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStrcut.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStrcut.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStrcut.SPI_Mode = SPI_Mode_Master;
	SPI_InitStrcut.SPI_NSS = SPI_NSS_Soft;

	SPI_Init(SPI2, &SPI_InitStrcut);
	SPI_Cmd(SPI2, ENABLE);
}

/*
 * @brief	Delay
 */
static void delay(uint32_t microseconds) {
  /* Hangs for specified number of microseconds. */
  volatile uint32_t counter = 0;
  microseconds *= 3;
  for(; counter<microseconds; counter++);
}

/*
 * @brief	Write a byte to the eeprom
 * @param	address	:	The address of th memory
 * @param	data	:	The data to be written to the memory
 * @return 	None
 */
void EEPROM_Write(uint16_t address, uint8_t data){
	// write enable latch
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	delay(1);
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(SPI2,WREN);
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE)==RESET);
	SPI_I2S_ReceiveData(SPI2); // junk
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	delay(5000);

	// start transmission
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	delay(1);
	// send write instruction
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(SPI2,WRITE);
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE)==RESET);
	SPI_I2S_ReceiveData(SPI2); // junk
	// send the address of the register
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(SPI2, address>>8);
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE)==RESET);
	SPI_I2S_ReceiveData(SPI2); // junk
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(SPI2, address);
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE)==RESET);
	SPI_I2S_ReceiveData(SPI2); // junk
	// send data
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(SPI2, data);
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE)==RESET);
	SPI_I2S_ReceiveData(SPI2); // junk

	// end transmission
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	delay(5000);

}

/*
 * @brief	Read a byte from the eeprom
 * @param	address	:	The address of the memory
* @return 	data
 */
uint8_t EEPROM_Read(uint16_t address){
	uint8_t value;
	GPIO_ResetBits(GPIOB,GPIO_Pin_12); // CS Low -- start transmission
	delay(1);

	// send read instruction
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)==RESET);

	SPI_I2S_SendData(SPI2,READ); // read instruction
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE)==RESET);
	SPI_I2S_ReceiveData(SPI2); // junk data
	// send 16 bits address register
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(SPI2,address>>8); // send address of register
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE)==RESET);
	SPI_I2S_ReceiveData(SPI2); // junk data
	SPI_I2S_SendData(SPI2,address);
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE)==RESET);
	SPI_I2S_ReceiveData(SPI2); // junk data

	// get data
	SPI_I2S_SendData(SPI2,0x42);
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE)==RESET);
	value = SPI_I2S_ReceiveData(SPI2); // data

	GPIO_SetBits(GPIOB, GPIO_Pin_12); // CS High -- end transmission
	delay(5000);
	return value;
}

/*
 * @brief	Write a page to the eeprom
 *	@param	baseAddress	: 	The base address of the page
 *	@param 	data		: 	An array of data to be send
 *	@param	pageLength	: 	The lenght/size of the page/array (max is 32)
 */
void EEPROMWritePage32(uint16_t baseAddress, uint8_t *data){
	// write enable latch
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	delay(1);
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(SPI2,WREN);
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE)==RESET);
	SPI_I2S_ReceiveData(SPI2); // junk
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	delay(5000);

	// start transmission
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	delay(1);
	// send write instruction
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(SPI2,WRITE);
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE)==RESET);
	SPI_I2S_ReceiveData(SPI2); // junk
	// send the address of the register
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(SPI2, baseAddress>>8);
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE)==RESET);
	SPI_I2S_ReceiveData(SPI2); // junk
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(SPI2, baseAddress);
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE)==RESET);
	SPI_I2S_ReceiveData(SPI2); // junk
	// send data
	for(int i=0; i<PAGE_LENGTH; i++){
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)==RESET);
		SPI_I2S_SendData(SPI2, data[i]);
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE)==RESET);
		SPI_I2S_ReceiveData(SPI2); // junk
	}
	// end transmission
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	delay(5000);
}


/*
 * 	@brief	Read a page to the eeprom
 *	@param	baseAddress	: 	The base address of the page
 *	@param		size	: 	The number of uint8_t to read from eeprom
 */
void EEPROMWritePage(uint8_t *data, uint16_t size){
	for(int i=0; i<size; i+=32){
		EEPROMWritePage32(i,(uint8_t *)&data[i]);
	}
}


/*
 * @brief	Read a page to the eeprom
 *	@param	data	: 	The array in which data need to be copied
 *	@param	size	: 	The number of uint8_t to read from eeprom
 */
void EEPROMReadPage(uint8_t*data,uint16_t size){
	for(int i=0; i<size; i++){
		data[i] = EEPROM_Read(i);
	}
}

#endif /* EEPROM_H_ */

