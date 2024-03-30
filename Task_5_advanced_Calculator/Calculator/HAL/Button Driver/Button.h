/*
 * Button.h
 *
 * Created: 2023-07-20 2:54:39 PM
 *  Author: Abdelrahman Ellithy
 */ 
#ifndef BUTTON_H_
#define BUTTON_H_
#include "../../MCAL/DIO Driver/DIO.h"

#define pressed LOW
#define not_pressed HIGH

u8 current_st ;
u8 old_st ;

void Button_init(u8 portname , u8 pinnumber);
void Button_read( u8 portname ,u8 pinnumber , u8 * value);


#endif /* BUTTON_H_ */