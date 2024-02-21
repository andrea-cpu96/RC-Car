/*
 * rc_car.c
 *
 *  Created on: Feb 21, 2024
 *      Author: Fato
 */

#include "main.h"
#include "rc_car.h"
#include "user_sysfunc.h"


rcCarStruct rcCar;


void rc_car_init(void)
{

	rcCar.newDataFlag = 0;
	rcCar.pckReceived = 0;
	rcCar.mode = MODE_NORM;
	rcCar.angle = 0;
	rcCar.speed = 0;

	rcCar.status = STOP;

	rcCar.WDtimer = getTimeMs();

}


void rc_car_process(void)
{

	switch(rcCar.status)
	{

		case STOP:

			break;

		case RUN:

			break;

	}


/********************* INTERRUPT CALLBACKS ******************************/


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	rcCar.WDtimer = getTimeMs(); // Timer reset

	// HAL_UART_Receive_IT(huart, , Size)


	if(rcCar.pckReceived != ERROR)
		rcCar.status = RUN; // New status or confirmation of RUN mode
	else
		rcCar.status = STOP; // If error occurs go into STOP mode

}


/***********************************************************************/


}
