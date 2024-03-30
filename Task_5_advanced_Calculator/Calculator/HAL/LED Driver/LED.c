/*
 * LED.c
 *
 * Created: 2023-07-15 1:43:01 PM
 *  Author: Abdelrahman Ellithy
 */ 
#include "LED.h"
void LED_init( u8 portname ,u8 pinnumber ){
	DIO_PIN_init(portname,pinnumber,OUT);
}
void LED_ON( u8 portname ,u8 pinnumber ){
	DIO_PIN_write(portname , pinnumber , HIGH);
}
void LED_OFF( u8 portname ,u8 pinnumber ){
	DIO_PIN_write(portname , pinnumber , LOW);
}
void LED_toggle( u8 portname ,u8 pinnumber ){
	DIO_PIN_toggle(portname , pinnumber);
}