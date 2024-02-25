/*
 * remote.h
 *
 *  Created on: Feb 21, 2024
 *      Author: Fato
 */

#ifndef INC_REMOTE_H_
#define INC_REMOTE_H_


#define SENDING_TIME			200		// 100[ms] between every new data

#define SEND_OK					0
#define SEND_ERROR				1

#define ERROR					0xff	// Message to be sent in case of error

// 8-bits available for the data packet

#define MODE_NORM				0
#define MODE_FAST				1

#define ANGLE_QUANT				3		// 00->straight ; 01->turn left ; 10->turn right ; 11; not used (only in case of error)
#define SPEED_QUANT				31		// 0-12->backward ; 13-18->stop ; 19-31->forward

#define U16_TO_ANGLE(data)		( ( (float)data / 4096.0 ) * ANGLE_QUANT )
#define U16_TO_SPEED(data)      ( ( ( 1.0 - (float)data / 4096.0 ) ) * SPEED_QUANT )

#define GEN_PACKET(pck77, pck65, pck40)		(  ( pck77 << 7 ) | ( pck65 << 5 ) | ( pck40 )  )

//

#define REMOTE_STATUS(angle, speed)		( !( angle == 1 ) || !( ( speed >= 13 ) && ( speed <= 18 ) ) ) ? RUN : STOP


typedef enum
{

	STOP = 0,
	RUN = 1

}REMOTE_STATUS;

typedef struct
{

	uint32_t send_timeStamp;
	uint8_t data;
	uint8_t send;
	REMOTE_STATUS status;

}remoteStruct;


extern remoteStruct remote;

void remote_init(void);
void remote_process(void);


#endif /* INC_REMOTE_H_ */
