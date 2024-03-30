/*
 * Button.c
 *
 * Created: 2023-07-20 2:54:56 PM
 *  Author: Abdelrahman Ellithy
 */ 

#include "Button.h"

void Button_init(u8 portname ,u8 pinnumber){
	DIO_PIN_init(portname , pinnumber ,IN);
	 current_st =not_pressed ;
	 old_st =not_pressed;
}

void Button_read( u8 portname ,u8 pinnumber , u8 * val){
	DIO_PIN_read(portname , pinnumber , val);
	current_st = *val;
	if( current_st == pressed && old_st==not_pressed ){
		*val=HIGH;
	}
	else{
		*val=LOW;
	}
	old_st=current_st;
}