/*
 * LM35_Interface.h
 *
 * Created: 2023-11-15 11:25:38 AM
 *  Author: Abdelrahman Ellithy
 */


#ifndef LM35_INTERFACE_H_
#define LM35_INTERFACE_H_

#include "../../LIB/Types.h"
#include "../../LIB/BIT_OPERATIONS.h"

#define LM_1 ADC_CHANNEL0
#define LM_2 ADC_CHANNEL1
#define LM_3 ADC_CHANNEL2
#define LM_4 ADC_CHANNEL3

void LM35_VoidRead(u8 SENSOR_ID,u8 * result);

#endif /* LM35_INTERFACE_H_ */