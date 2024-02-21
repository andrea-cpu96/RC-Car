/*
 * rc_car.h
 *
 *  Created on: Feb 21, 2024
 *      Author: Fato
 */

#ifndef RC_CAR_H_
#define RC_CAR_H_

#define MAX_DELAY				1000 	// 1s; maximum acceptable delay from new data

#define MODE_NORM				0
#define MODE_FAST				1

#define ERROR					0xff	// Error present go into STOP mode


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
	uint8_t angle;
	uint32_t WDtimer;
	RC_CAR_STATUS status;

}rcCarStruct;


extern rcCarStruct rcCar;


void rc_car_init(void);
void rc_car_process(void);





#endif /* RC_CAR_H_ */
