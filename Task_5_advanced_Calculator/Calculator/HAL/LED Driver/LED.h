/*
 * LED.h
 *
 * Created: 2023-07-15 1:43:19 PM
 * Author: Abdelrahman Ellithy
 */ 

#ifndef LED_H_
#define LED_H_

#include "../../MCAL/DIO Driver/DIO.h"
/************************************************************************/
/* macros                                                                     */
/************************************************************************/
#define led1 PIN0
#define led2 PIN1
#define led3 PIN2
/************************************************************************/
/* functions prototypes                                                 */
/************************************************************************/
void LED_init(  u8 portname , u8 pinnumber );
void LED_ON(  u8 portname , u8 pinnumber );
void LED_OFF( u8 portname , u8 pinnumber );
void LED_toggle(  u8 portname , u8 pinnumber );
#endif /* LED_H_ */