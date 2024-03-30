/*
 * Button.c
 *
 * Created: 2023-07-20 2:54:56 PM
 *  Author: Abdelrahman Ellithy
 */ 
#include "../../LIB/Types.h"
#include "../../MCAL/DIO Driver/DIO_Interface.h"
#include "Button_interface.h"
void Button_read( Button* Btn,u8 *val){
	switch(Btn->BtnPullState){
		case PullDown :
		DIO_PIN_read(Btn->BtnPort, Btn->BtnPin , val);
		if(*val==DIO_PIN_HIGH){
			while(*val==DIO_PIN_HIGH){
				DIO_PIN_read(Btn->BtnPort, Btn->BtnPin , val);
			}
		}
		else{
			*val=0;
		}
		break;
		case PullUp :
		DIO_PIN_read(Btn->BtnPort, Btn->BtnPin , val);
		if(*val==DIO_PIN_LOW){
			while(*val==DIO_PIN_LOW){
				DIO_PIN_read(Btn->BtnPort, Btn->BtnPin , val);
			}
			*val=1;
		}
		else{
			*val=1;
		}
		
		break;
	}
}