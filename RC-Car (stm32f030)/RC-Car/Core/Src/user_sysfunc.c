/*
 * user_sysfunc.c
 *
 *  Created on: Feb 21, 2024
 *      Author: Fato
 */


#include "main.h"
#include "user_sysfunc.h"


/*
 *	@ Function; getDelayms
 *  @ Return; uint32_t -> current time in ms
 */
uint32_t getTimeMs(void)
{

	// Tick frequency is by default 1kHz (1ms period)
	return ( HAL_GetTick() * HAL_GetTickFreq() );

}


/*
 *	@ Function; getDelayms
 * 	@ Par1; uint32_t timeStamp -> captured time
 *  @ Return; uint32_t tDiff -> time elapsed since timeStamp in ms
 */
uint32_t getDelayMs(uint32_t timeStamp)
{

	uint32_t tDiff;
	uint32_t currentTime;

	currentTime = ( getTimeMs() * HAL_GetTickFreq() );

	if(currentTime >= timeStamp)
		tDiff = currentTime - timeStamp;
	else
		tDiff = timeStamp - currentTime;

	return tDiff;

}
