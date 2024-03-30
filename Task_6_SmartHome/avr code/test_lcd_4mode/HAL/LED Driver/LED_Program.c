/*
 * LED_Program.c
 *
 * Created: 2023-7-30 7:40:36 AM
 *  Author: Abdelrahman Ellithy
 */ 
#include "LED_Interface.h"
void LED_voidInit(LED* led){
	DIO_PIN_init(led->LED_PORT,led->LED_pin,DIO_PIN_OUTPUT);
}
void LED_voidON(LED* led){
	switch(led->LED_Active_Type)
	{
		case Active_High:
			DIO_PIN_write(led->LED_PORT,led->LED_pin,DIO_PIN_HIGH);
			break;
		case Active_Low:
			DIO_PIN_write(led->LED_PORT,led->LED_pin,DIO_PIN_LOW);
		break;
	}
}

void LED_voidOFF(LED* led){
	switch(led->LED_Active_Type)
	{
		case Active_High:
		DIO_PIN_write(led->LED_PORT,led->LED_pin,DIO_PIN_LOW);
		break;
		case Active_Low:
		DIO_PIN_write(led->LED_PORT,led->LED_pin,DIO_PIN_HIGH);
		break;
	}
}
void LED_voidToggle(LED* led){
	DIO_PIN_toggle(led->LED_PORT,led->LED_pin);
}