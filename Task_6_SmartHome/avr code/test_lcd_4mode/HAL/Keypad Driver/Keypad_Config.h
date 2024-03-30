/*
 * Keypad.h
 *
 * Created: 2023-11-09 4:15:42 AM
 *  Author: Abdelrahman Ellithy
 */ 
#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "../../MCAL/DIO Driver/DIO_Interface.h"
#define keypad_port DIO_PORTD
#define keypad_port_bits 0xf0

#define KPD_Col_start DIO_PIN0
#define KPD_Col_End   DIO_PIN3

#define KPD_Row_start 0
#define KPD_Row_End   4

#define row1 DIO_PIN0
#define row2 DIO_PIN1
#define row3 DIO_PIN2
#define row4 DIO_PIN3

#define Col1 DIO_PIN4
#define Col2 DIO_PIN5
#define Col3 DIO_PIN6
#define Col4 DIO_PIN7



u8 keypad_Buttons[4][4]={
	/*c1  c2  c3  c4*/
	{'7','8','9','/'}, /* row1 */
	{'4','5','6','*'}, /* row2 */
	{'1','2','3','-'}, /* row3 */
	{'o','0','=','+'}  /* row4 */
};

#endif /* KEYPAD_H_ */