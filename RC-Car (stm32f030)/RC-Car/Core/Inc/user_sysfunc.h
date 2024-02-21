/*
 * user_sysfunc.h
 *
 *  Created on: Feb 21, 2024
 *      Author: Fato
 */

#ifndef INC_USER_SYSFUNC_H_
#define INC_USER_SYSFUNC_H_

// Structure for types conversion
typedef union
{
  uint8_t un4_uchar[4];
  uint16_t un4_uint[2];
  uint32_t un4_ulong;
  long un4_long;
  float un4_float;
} UNION4_CONVERSION;


uint32_t getTimeMs(void);
uint32_t getDelayMs(uint32_t timeStamp);



#endif /* INC_USER_SYSFUNC_H_ */
