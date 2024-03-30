/*
 * Keypad.c
 *
 * Created: 2023-11-09 4:15:56 AM
 *  Author: Abdelrahman Ellithy
 */ 
#include "Keypad.h"
u8 keypad_Buttons[4][4]={
	/*c1  c2  c3  c4*/
	{'7','8','9','/'}, /* row1 */
	{'4','5','6','*'}, /* row2 */
	{'1','2','3','-'}, /* row3 */
	{'o','0','=','+'}  /* row4 */
};
void Keypad_init (void){
	CLEAR_BIT(SFIOR,PUD);
	DIO_PORT_bits_init(keypad_port,keypad_port_bits);
	DIO_PORT_write(keypad_port,PORT_HIGH);
}
u8 Get_pressed(void){
	u8 loc_pressed=NotPressed;
	u8 val=1;
	u8 row,col;
	for (col= Col1 ; col<= Col4 ;col++ )
	{
			
		DIO_PIN_write(keypad_port,col,PIN_LOW);
		for (row=row1 ; row<=row4 ; row++)
		{
			DIO_PIN_read(keypad_port, row, &val);
			if(val==PIN_LOW)
			{
				while(PIN_LOW==val)
				{
					DIO_PIN_read(keypad_port, row,&val);
				}
				loc_pressed=keypad_Buttons[row][col-Col1];	
			}
		}
		DIO_PIN_write(keypad_port,col,PIN_HIGH);
	}
	return loc_pressed;
}