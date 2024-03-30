/*
 * EX_INTERRUPT.h
 *
 * Created: 2023-09-26 2:22:14 PM
 *  Author: Abdelrahman Ellithy
 */ 

#include "../../LIB/register.h"
#include "../../LIB/BIT_OPERATIONS.h"

#ifndef EX_INTERRUPT_H_
#define EX_INTERRUPT_H_
typedef enum{
	LOW_LEVEL=0,
	ANY_LOGIC_CHANGE,
	FALLING_EDGE,
	RISING_EDGE,
}Edge_trriger;

#define INT1 7
#define INT0 6
#define INT2 5

#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3

#define INTF1 7
#define INTF0 6
#define INTF2 5

void EX_INT0_Enable();
void EX_INT1_Enable();
void EX_INT2_Enable();

void EX_INT0_Disable();
void EX_INT1_Disable();
void EX_INT2_Disable();

void EX_INT0_Edge_Detect(Edge_trriger Edge_type);
void EX_INT1_Edge_Detect(Edge_trriger Edge_type);
void EX_INT2_Edge_Detect(Edge_trriger Edge_type);

void EX_INT0_SetCallBack(void(*LocalPtr)(void));
void EX_INT1_SetCallBack(void(*LocalPtr)(void));
void EX_INT2_SetCallBack(void(*LocalPtr)(void));

#endif /* EX_INTERRUPT_H_ */