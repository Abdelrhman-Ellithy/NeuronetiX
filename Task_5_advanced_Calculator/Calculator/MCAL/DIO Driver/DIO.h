/********************************************************
 * DIO.h ******************************************
 ******************************************
 * Created: 2023-07-12 7:00:12 PM
 *  Author: Abdelrahman Ellithy
 */ 

#ifndef DIO_H_
#define DIO_H_

#include "../../LIB/Types.h"
#include "../../LIB/BIT_OPERATIONS.h"
#include "../../LIB/register.h"
/************************************************************************/
/* define macros                                                                     */
/************************************************************************/
#define PORT_A 'A'
#define PORT_B 'B'
#define PORT_C 'C'
#define PORT_D 'D'
#define PIN_LOW 0
#define PIN_HIGH 1
#define PORT_LOW 0x00
#define PORT_HIGH 0xff
#define PIN_IN 0
#define PIN_OUT 1
#define PORT_IN 0x00
#define PORT_OUT 0xff
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

/************************************************************************/
/* define macro functions											    */
/************************************************************************/
void DIO_PIN_init( u8 portname ,u8 pinnumber , u8 drirection );
void DIO_PORT_init( u8 portname  , u8 drirection );
void DIO_PORT_bits_init( u8 portname  , u8 bits );

void DIO_PIN_write( u8 portname ,u8 pinnumber , u8 value );
void DIO_PORT_write( u8 portname  , u8 value );
void DIO_low_Nipple_write( u8 portname  , u8 bits );
void DIO_high_Nipple_write( u8 portname  , u8 bits );

void DIO_PIN_read( u8 portname ,u8 pinnumber , u8 * value);
void DIO_PORT_read( u8 portname  , u8 * value);

void DIO_PIN_toggle( u8 portname ,u8 pinnumber );
void DIO_PORT_toggle( u8 portname );

#endif /* DIO_H_ */