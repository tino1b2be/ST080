/*
 * AudioStuff.h
 *
 *  Created on: Sep 27, 2016
 *      Author: Othniel Konan
 *     Version: Oct 3, 2016
 * Description: Contains set of functions to generate sound
 */

#ifndef AUDIOSTUFF_H_
#define AUDIOSTUFF_H_


#include "Utils080.h"


#define AUDIO_FREQUENCY 11000
#define DMA_FREQUENCY  (86000000/(2*AUDIO_FREQUENCY))



/*
 * @brief Disable the DMA
 */
void AudioDisable(){
	DMA_ClearFlag(DMA1_Stream5,DMA_FLAG_TCIF5);
	DMA_Cmd(DMA1_Stream5,DISABLE);
}

/*
 * @brief	Disable DMA and Timer used for Composer mode
 * @return 	None
 */
void AudioComDisable(){

}

/*
 * @brief	Perform audio initialization
 * @param	DACBuffer		:	Array to be pushed to the DMA
 * @param	Mode			: 	DMA Mode (default:DMA_Mode_Normal)
 * @param	SIze			: 	sample size (default:SAMPLE_SIZE)
 * @return 	None
 */
void AudioInit(uint16_t *DACBuffer, uint16_t Mode, uint16_t Size){

	// RCC configuration
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1 | RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC | RCC_APB1Periph_TIM6, ENABLE);

	// GPIO configuration [GPIOA_4]
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	// TIMER configuration [TIM6]
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStruct;
	TIM_TimeBaseStruct.TIM_Period = DMA_FREQUENCY;
	TIM_TimeBaseStruct.TIM_Prescaler = 1;
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
	DMA_InitStruct.DMA_Memory0BaseAddr=(uint32_t)DACBuffer;
	DMA_InitStruct.DMA_DIR=DMA_DIR_MemoryToPeripheral;
	DMA_InitStruct.DMA_BufferSize = Size;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_Mode = Mode;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA1_Stream5, &DMA_InitStruct);
	DMA_Cmd(DMA1_Stream5, ENABLE);

	// DAC configuration	[Channel_1,TIM6]
	DAC_InitTypeDef DAC_InitStruct;
	DAC_InitStruct.DAC_Trigger = DAC_Trigger_T6_TRGO;
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_InitStruct.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_1, &DAC_InitStruct);
	DAC_DMACmd(DAC_Channel_1,ENABLE);
	DAC_Cmd(DAC_Channel_1, ENABLE);
}

/*
 * @brief	Play a sample
 * @param	DACBuffer		:	Array to be pushed to the DMA
 * @param	Mode			: 	DMA Mode (default:DMA_Mode_Normal)
 * @param	Size			: 	sample size (default:SAMPLE_SIZE)
 * @return 	None
 */
void AudioPlay(uint16_t *DACBuffer, uint16_t Mode, uint16_t Size ){
	AudioDisable();
	AudioInit(DACBuffer,Mode,Size);
}

/*
 * @brief	Play sample in freestyle mode (play one sample once)
 * @param	DACBuffer		:	Array to be pushed to the DMA
 * @return 	None
 */
void AudioFreestyle(uint16_t *DACBuffer){
	AudioPlay(DACBuffer, DMA_Mode_Normal, SAMPLE_SIZE);
}

/*
 * @brief	Play sample in playback mode (play sample infinitly)
 * @param	DACBuffer		:	Array to be pushed to the DMA
 * @return 	None
 */
void AudioPlayback(uint16_t *DACBuffer, uint16_t size){
	AudioPlay(DACBuffer, DMA_Mode_Circular, size);
}

/*
 * @brief	Play an array of sample a a given tempo
 * @param	sample		:	Pointer of Arrays to be pushed to the DMA
 * @param	tempo		: 	Tempo of the sound (default=60bpm)
 * @return 	None
 */
void AudioComposer(uint16_t *sample, uint16_t tempo){

}

#endif /* AUDIOSTUFF_H_ */
