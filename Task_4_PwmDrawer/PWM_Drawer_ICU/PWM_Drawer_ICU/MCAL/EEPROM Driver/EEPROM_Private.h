/*
 * EEPROM_Private.h
 *
 * Created: 2023-11-30 7:30:53 AM
 *  Author: lenovo
 */ 


#ifndef EEPROM_PRIVATE_H_
#define EEPROM_PRIVATE_H_
#include "../../LIB/Types.h"
#define EERE    0
#define EEWE    1
#define EEMWE   2
#define EERIE   3

#define EECR	*((volatile u8  *)0x3C)/* EEPROM Control Register */
#define EEDR	*((volatile u8  *)0x3D)/* EEPROM Data Register */
#define EEAR	*((volatile u16 *)0x3E)/* EEPROM Address Register */
#define EEARL	*((volatile u8  *)0x3E)
#define EEARH	*((volatile u8  *)0x3F)

#endif /* EEPROM_PRIVATE_H_ */