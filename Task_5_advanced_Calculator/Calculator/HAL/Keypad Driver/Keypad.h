/*
 * Keypad.h
 *
 * Created: 2023-11-09 4:15:42 AM
 *  Author: Abdelrahman Ellithy
 */ 
#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../../LIB/Types.h"
#include "../../MCAL/DIO Driver/DIO.h"

#define keypad_port PORT_D
#define keypad_port_bits 0xf0
#define col_start 0
#define col_End   4
#define row_start 0
#define row_End   4

#define row1 PIN0
#define row2 PIN1
#define row3 PIN2
#define row4 PIN3

#define Col1 PIN4
#define Col2 PIN5
#define Col3 PIN6
#define Col4 PIN7

#define NotPressed 0xFF
void Keypad_init (void);
u8 Get_pressed(void);

#endif /* KEYPAD_H_ */