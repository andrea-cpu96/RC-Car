/*
 * rc_car.h
 *
 *  Created on: Feb 21, 2024
 *      Author: Fato
 */

#ifndef RC_CAR_H_
#define RC_CAR_H_


#define MAX_DELAY						1000 	// 1s; maximum acceptable delay from new data

#define MODE_NORM						0
#define MODE_FAST						1

#define ERROR							0xff	// Error present go into STOP mode

#define NO_NEW_DATA_AVAILABLE			0
#define NEW_DATA_AVAILABLE				1

#define IS_MOTORS_RUNNING()				(  ( M_BACKWARD_GPIO_Port->ODR & M_BACKWARD_Pin ) || ( M_FORWARD_GPIO_Port->ODR & M_FORWARD_Pin )  )

#define EXTRACT_MODE_FROM_PCK(pck)		( ( pck & 0x80 ) >> 7 )		// X-------
#define EXTRACT_ANGLE_FROM_PCK(pck)		( ( pck & 0x60 ) >> 5 )		// -XX-----
#define EXTRACT_SPEED_FROM_PCK(pck)		( ( pck & 0x1f ) )			// ---XXXXX

#define FORWARD_BORDER					19	// Value of speed; 19-31
#define BACKWARD_BORDER					12	// Value of speed; 0-12


#define ANGLE_STRAIGHT					1
#define ANGLE_TURN_LEFT					2
#define ANGLE_TURN_RIGHT 				0

#define SM1_DEFAULT						( ( ( 0 / 18.0 ) + 2 ) / 100.0 );
#define SM1_TURN						( ( ( 120 / 18.0 ) + 2 ) / 100.0 );
#define SM2_DEFAULT						( ( ( 150 / 18.0 ) + 2 ) / 100.0 );
#define SM2_TURN						( ( ( 50 / 18.0 ) + 2 ) / 100.0 );

#define SPEED_SLOWEST					0.0
#define SPEED_FASTEST 					12.0

#define MAX_DUTY						70.0
#define SPEED_TO_DUTY(speed)			( ( ( (float)speed / SPEED_FASTEST ) * MAX_DUTY ) / 100.0 )


enum DIRECTION
{

	NONE,
	BACKWARD,
	FORWARD

};

typedef enum
{

	STOP,
	RUN

}RC_CAR_STATUS;


typedef struct
{

	uint8_t newDataFlag;
	uint8_t pckReceived;
	uint8_t mode;
	uint8_t speed;
	uint8_t direction;
	uint8_t angle;
	uint32_t WDtimer;
	RC_CAR_STATUS status;

}rcCarStruct;


extern rcCarStruct rcCar;


void rc_car_init(void);
void rc_car_process(void);





#endif /* RC_CAR_H_ */
