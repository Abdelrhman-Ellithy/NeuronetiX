/*
 * BUZZER_Program.c
 *
 * Created: 2023-7-30 7:40:36 AM
 *  Author: Abdelrahman Ellithy
 */ 
#include "BUZZER_Interface.h"
void BUZZER_voidInit(BUZZER* Buz){
	DIO_PIN_init(Buz->BUZZER_PORT,Buz->BUZZER_pin,DIO_PIN_OUTPUT);
}
void BUZZER_voidON(BUZZER* Buz){
	switch(Buz->BUZZER_Active_Type)
	{
		case Active_High:
			DIO_PIN_write(Buz->BUZZER_PORT,Buz->BUZZER_pin,DIO_PIN_HIGH);
			break;
		case Active_Low:
			DIO_PIN_write(Buz->BUZZER_PORT,Buz->BUZZER_pin,DIO_PIN_LOW);
		break;
	}
}

void BUZZER_voidOFF(BUZZER* Buz){
	switch(Buz->BUZZER_Active_Type)
	{
		case Active_High:
		DIO_PIN_write(Buz->BUZZER_PORT,Buz->BUZZER_pin,DIO_PIN_LOW);
		break;
		case Active_Low:
		DIO_PIN_write(Buz->BUZZER_PORT,Buz->BUZZER_pin,DIO_PIN_HIGH);
		break;
	}
}
void BUZZER_voidToggle(BUZZER* Buz){
	DIO_PIN_toggle(Buz->BUZZER_PORT,Buz->BUZZER_pin);
}