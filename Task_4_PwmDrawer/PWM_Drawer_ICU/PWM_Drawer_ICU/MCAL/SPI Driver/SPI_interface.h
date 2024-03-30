/*
 * SPI_interface.h
 *
 * Created: 2024-01-06 4:05:27 PM
 *  Author: Abdelrahman Ellithy
 */ 


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#include "../../LIB/Types.h"

#define ModeMaster 1
#define ModeSlave  0

void SPI_voidInit(void);
u8 SPI_TranmitRecive(u8 data);
void SPI_changeMode(u8 mode);

#endif /* SPI_INTERFACE_H_ */