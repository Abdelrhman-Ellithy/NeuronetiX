/*
 * Keypad.c
 *
 * Created: 2023-11-09 4:15:56 AM
 *  Author: Abdelrahman Ellithy
 */ 
#include "../../LIB/Types.h"
#include "Keypad_Config.h"
#include "Keypad_interface.h"
#include "Keypad_Private.h"

u8 Get_pressed(void){
	u8 loc_pressed=KPD_NotPressed;
	u8 val=1;
	u8 row,col;
	for (col= Col1 ; col<= Col4 ;col++ )
	{
			
		DIO_PIN_write(keypad_port,col,DIO_PIN_LOW);
		for (row=row1 ; row<=row4 ; row++)
		{
			DIO_PIN_read(keypad_port, row, &val);
			if(val==DIO_PIN_LOW)
			{
				while(DIO_PIN_LOW==val)
				{
					DIO_PIN_read(keypad_port, row,&val);
				}
				loc_pressed=keypad_Buttons[row][col-Col1];	
			}
		}
		DIO_PIN_write(keypad_port,col,DIO_PIN_HIGH);
	}
	return loc_pressed;
}