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


static void stopCondition(void);
static void speed_control(void);
static void angle_control(void);
static void direction_control(void);
static void motors_handler(void);
static void setStop(void);
static void setForward(void);
static void setBackward(void);
static void unpackedData(void);


void rc_car_init(void)
{

	rcCar.newDataFlag = NO_NEW_DATA_AVAILABLE;
	rcCar.pckReceived = 0;
	rcCar.mode = MODE_NORM;	// Start in NORMAL mode
	rcCar.angle = 0;
	rcCar.speed = 0;
	rcCar.direction = NONE;

	rcCar.status = STOP;	// Start in STOP and wait for new command

	// Start with a stop condition
	stopCondition();

	// First reception enabled
	HAL_UART_Receive_IT(&huart3, &rcCar.pckReceived, 1);

	// Timer initialization
	rcCar.WDtimer = getTimeMs();

}


void rc_car_process(void)
{

	switch(rcCar.status)
	{

		case STOP:

			if(rcCar.newDataFlag == NEW_DATA_AVAILABLE)
			{

				// Don't reset newDataFlag here, because in case of right data
				// the flag will be reset when in RUN mode

				if(rcCar.pckReceived == ERROR)
				{

					// Reset of the flag
					rcCar.newDataFlag = NO_NEW_DATA_AVAILABLE;

					// Assure stop condition
					stopCondition();

					// Stay into STOP mode
					rcCar.status = STOP;

				}
				else
				{

					// Go into RUN mode
					rcCar.status = RUN;

				}

			}
			else
			{

				// Check that motors are actually stopped
				if(IS_MOTORS_RUNNING())
					stopCondition();

				// Stay into STOP mode
				rcCar.status = STOP;

			}

			break;

		case RUN:

			if(rcCar.newDataFlag == NEW_DATA_AVAILABLE)
			{

				// Reset of the flag
				rcCar.newDataFlag = NO_NEW_DATA_AVAILABLE;

				if(rcCar.pckReceived == ERROR)
				{

					// Stop and go into STOP mode

					stopCondition();
					rcCar.status = STOP;

				}
				else
				{

				    // Handle new data for motors control

					motors_handler();
					rcCar.status = RUN;

				}

			}
			else
			{

				if(getDelayMs(rcCar.WDtimer) > MAX_DELAY)
				{

					// No data received for long time

					// Stop motors and go into STOP mode
					stopCondition();
					rcCar.mode = STOP;

				}
				else
				{

					// Stay into RUN mode
					rcCar.mode = RUN;

				}

			}

			break;

	}

}

/********************** PRIVATE FUNCTIONS ********************************/

static void motors_handler(void)
{

	uint8_t directionOld = rcCar.direction;
	uint8_t speedOld = rcCar.speed;
	uint8_t angleOld = rcCar.angle;


	unpackedData();

	if(rcCar.angle != angleOld)
		// Evaluate new angle
		angle_control();

	if(rcCar.direction != directionOld)
		// Evaluate new direction
		direction_control();

	if(rcCar.speed != speedOld)
		// Evaluate new speed
		speed_control();

}


static void stopCondition(void)
{

	// Default configuration

	rcCar.mode = MODE_NORM;
	rcCar.direction = NONE;				// This will stop the motors
	rcCar.angle = ANGLE_STRAIGHT;
	rcCar.speed = SPEED_SLOWEST;

	motors_handler();

	return;

}


static void direction_control(void)
{

	if(rcCar.direction == FORWARD)
		setForward();
	else if(rcCar.direction == BACKWARD)
		setBackward();
	else
		setStop();

}


static void angle_control(void)
{




}


static void speed_control(void)
{




}


static void unpackedData(void)
{

	rcCar.mode = EXTRACT_MODE_FROM_PCK(rcCar.pckReceived);
	rcCar.angle = EXTRACT_ANGLE_FROM_PCK(rcCar.pckReceived);
	rcCar.speed = EXTRACT_SPEED_FROM_PCK(rcCar.pckReceived);

	if(rcCar.speed >= FORWARD_BORDER)
	{

		rcCar.direction = FORWARD;

		// Normalize speed for 13 values
		rcCar.speed -= FORWARD_BORDER;		// 0-12

	}
	else if(rcCar.speed <= BACKWARD_BORDER)
	{

		rcCar.direction = BACKWARD;

		// Normalize speed for 13 values
		rcCar.speed = FORWARD_BORDER - rcCar.speed;		// 0-12

	}
	else
	{

		rcCar.direction = NONE;

		rcCar.speed = SPEED_ZERO_VAL;

	}

}


static void setForward(void)
{

	HAL_GPIO_WritePin(M_BACKWARD_GPIO_Port, M_BACKWARD_Pin, 1);
	HAL_GPIO_WritePin(M_FORWARD_GPIO_Port, M_FORWARD_Pin, 0);

}


static void setBackward(void)
{

	HAL_GPIO_WritePin(M_BACKWARD_GPIO_Port, M_BACKWARD_Pin, 0);
	HAL_GPIO_WritePin(M_FORWARD_GPIO_Port, M_FORWARD_Pin, 1);

}


static void setStop(void)
{

	HAL_GPIO_WritePin(M_BACKWARD_GPIO_Port, M_BACKWARD_Pin, 0);
	HAL_GPIO_WritePin(M_FORWARD_GPIO_Port, M_FORWARD_Pin, 0);

}


/************************************************************************/


/********************* INTERRUPT CALLBACKS ******************************/


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	// Timer reset
	rcCar.WDtimer = getTimeMs();

	// New data available
	rcCar.newDataFlag = NEW_DATA_AVAILABLE;

	if(rcCar.pckReceived != ERROR)
		// If no error occurs go into RUN mode
		rcCar.status = RUN;
	else
		// If error occurs go into STOP mode
		rcCar.status = STOP;

	// Start a new reception
	HAL_UART_Receive_IT(&huart3, &rcCar.pckReceived, 1);

}


/***********************************************************************/



