/**
 *****************
 **	Author		: Othniel Konan
 **	Version		: Sep 2016
 **	Description	:
 *****************
 **/

#ifndef AUDIO_H_
#define AUDIO_H_

#include "ST080Utils.h"

#define AUDIO_STACK_SIZE 128
#define AUDIO_TASK_PRIORITY 1

/*
 * @brief	Reset the DMA
 * @param	*DACBuffer		:	Array to be pushed to the DMA
 * 			DACBufferSize	:	Size of the array
 * 			DMA_Mode		:	Circular or Linear
 * @return 	None
 */
static void vAudioDMATask(uint16_t *DACBuffer, uint32_t DACBufferSize, uint32_t DMA_Mode){
	// DMA configuration	[Channel_7, Stream_5]
	DMA_InitTypeDef DMA_InitStruct;
	DMA_StructInit(&DMA_InitStruct);
	DMA_InitStruct.DMA_Channel=DMA_Channel_7;
	DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t)(DAC_BASE + 0x08);  //DAC channel1 12-bit right-aligned data holding register (ref manual pg. 264)
	DMA_InitStruct.DMA_Memory0BaseAddr=(uint32_t)&DACBuffer;
	DMA_InitStruct.DMA_DIR=DMA_DIR_MemoryToPeripheral;
	DMA_InitStruct.DMA_BufferSize = DACBufferSize;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_Mode = DMA_Mode;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA1_Stream5, &DMA_InitStructure);
	DMA_Cmd(DMA1_Stream5, ENABLE);
}
/*
 * @brief	Perform audio initialization
 * @param	*DACBuffer		:	Array to be pushed to the DMA
 * 			DACBufferSize	:	Size of the array
 * 			DMA_Mode		:	Circular or Linear
 * 			wavPeriod		: 	ARR
 * 			preScaler		:	PSC
 * @return 	None
 */
static void vAudioTask(uint16_t *DACBuffer, uint32_t DACBufferSize, uint32_t DMA_Mode, uint16_t wavPeriod, uint16_t preScaler){
	// RCC configuration
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1 | RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC | RCC_APB1Perith_TIM6, ENABLE);

	// GPIO configuration [GPIOA_4]
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIOPuPd_NOPULL;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	// TIMER configuration [TIM6]
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStruct;
	TIM_TimeBaseStruct.TIM_Period = wavPariod-1;
	TIM_TimeBaseStruct.TIM_Prescaler = preScaler-1;
	TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStruct.TIM_RepetitionCounter = 0x0000;
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStruct);
	TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);
	TIM_Cmd(TIM6, ENABLE);

	// DMA configuration	[Channel_7, Stream_5]
	DMA_InitTypeDef DMA_InitStruct;
	DMA_StructInit(&DMA_InitStruct);
	DMA_InitStruct.DMA_Channel=DMA_Channel_7;
	DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t)(DAC_BASE + 0x08);  //DAC channel1 12-bit right-aligned data holding register (ref manual pg. 264)
	DMA_InitStruct.DMA_Memory0BaseAddr=(uint32_t)&DACBuffer;
	DMA_InitStruct.DMA_DIR=DMA_DIR_MemoryToPeripheral;
	DMA_InitStruct.DMA_BufferSize = DACBufferSize;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_Mode = DMA_Mode;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA1_Stream5, &DMA_InitStructure);
	DMA_Cmd(DMA1_Stream5, ENABLE);

	// DAC configuration	[Channel_1,TIM6]
	DAC_InitTypeDef DAC_InitStruct;
	DAC_InitStruct.DAC_Trigger = DAC_Trigger_T6_TRGO;
	DAC_InitStruct.WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_InitStruct.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_1, &DAC_InitStruct);
	DAC_DMACmd(DAC_Channel_1,ENABLE);
	DAC_Cmd(DAC_Channel_1, ENABLE);
}

#endif
