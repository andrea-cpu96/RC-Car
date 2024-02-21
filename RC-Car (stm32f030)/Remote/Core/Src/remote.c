/*
 * remote.c
 *
 *  Created on: Feb 21, 2024
 *      Author: Fato
 */

#include "main.h"
#include "remote.h"
#include "user_sysfunc.h"


/* Private function prototypes */
uint16_t getSingleVal(void);
/*******************************/

/* Global Variable */
remoteStruct remote;
/*******************/


void remote_init(void)
{

	// 1. Data initialization

	remote.send_timeStamp = getTimeMs();	 // Timer reset
	remote.data = 0; 						 // Data reset
	remote.send = SEND_OK; 					 // Default value
	remote.status = RUN;					 // Default state

	return;

}


void remote_process(void)
{

	uint8_t mode = 0;
	uint8_t angle = 0;
	uint8_t speed = 0;
	uint8_t dataPck = ERROR;		// Error by default

	uint16_t adcRawData[2] = {0};	// Reset value



	// 1. Read data from adc

	// Read first channel
	adcRawData[0] = getSingleVal();
	//Read second channel
	adcRawData[1] = getSingleVal();

	if(remote.send == SEND_ERROR)
	{

		// An error occurred

		// Set an error to be sent
		dataPck = ERROR;

		// Reset of the error flag
		remote.send = SEND_OK;

	}
	else
	{

		// 2. Convert raw data into engineering values

		mode = MODE_NORM;						// For now only normal mode available
		angle = U16_TO_ANGLE(adcRawData[0]);
		speed = U16_TO_SPEED(adcRawData[1]);

		// 3. Encrypt data into 8-bit packet format

		dataPck = GEN_PACKET(mode, angle, speed);

		// If in STOP mode evaluate to switch in RUN mode (do not go into STOP mode here if you already are not in)
		if(remote.status == STOP)
			remote.status = REMOTE_STATUS(angle, speed);

	}

	remote.data = dataPck;

	// 4. Wait for the next transmission

	if(getDelayMs(remote.send_timeStamp) < SENDING_TIME)
		// Time not yet elapsed
		return;

	// Timer reset
	remote.send_timeStamp = getTimeMs();

	// 5. Time elapsed; send the data packet

	// Save energy; if in stop I don't send data (no problem in case of missing data; missed send will considered a STOP condition also)
	if(remote.status == RUN)
		// Send data
		HAL_UART_Transmit(&huart3, &remote.data, 1, HAL_MAX_DELAY);


	// Evaluating possible STOP condition in order to avoid successive sending of data
	remote.status = REMOTE_STATUS(angle, speed);


}



/************************** PRIVATE FUNCTION *******************************/

uint16_t getSingleVal(void)
{

	uint8_t errorFlag = 0;


	// Start reading
	errorFlag |= HAL_ADC_Start(&hadc);

	// Wait until the conversion is done
	errorFlag |= HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);

	if(errorFlag)
		remote.send |= SEND_ERROR;
	else
		remote.send |= SEND_OK;

	return HAL_ADC_GetValue(&hadc);

}

/*************************************************************************/
