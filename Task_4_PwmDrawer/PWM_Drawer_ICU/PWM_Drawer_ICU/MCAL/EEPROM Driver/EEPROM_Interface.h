/*
 * EEPROM.h
 *
 * Created: 2023-11-10 6:46:23 PM
 *  Author: Abdelrahman Ellithy
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "../../LIB/Types.h"

void EEPROM_write( u16 address,  u8 data);


void EEPROM_read( u16 address, u8 *data);

/*
  Enable eeprom ready interrupt 
 */
void EEPROM_intEnable(void);

/*
 disable eeprom ready interrupt
 * 
 */
void EEPROM_intDisable(void);

/**
  Set callback function for eeprom ready interrupt
 * 
  localFptr pointer to function to run when eeprom ready interrupt fired
 */
void EEPROM_intSetCallback(void (*localFptr)(void));

#endif /* EEPROM_H_ */