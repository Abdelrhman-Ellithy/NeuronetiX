/************************************************************************/
/*      * DIO.c										**********************
* Created: 2023-07-12 6:59:50 PM					*********************
*  Author: Abdelrahman Ellithy								            */
/************************************************************************/
 
#include "DIO.h"

void DIO_PIN_init( u8 portname ,u8 pinnumber , u8 drirection ){
	switch (portname)
	{
		case  PORT_A :
		if (drirection==PIN_OUT)
		{
			SET_BIT(DDRA,pinnumber);
		}
		else if (drirection==PIN_IN)
		{
			CLEAR_BIT(DDRA,pinnumber);
		}
		break;
		
		case PORT_B :
		if (drirection==PIN_OUT)
		{
			SET_BIT(DDRB,pinnumber);
		}
		else if (drirection==PIN_IN)
		{
			CLEAR_BIT(DDRB,pinnumber);
		}
		break;
		
		case PORT_C :
		if (drirection==PIN_OUT)
		{
			SET_BIT(DDRC,pinnumber);
		}
		else if (drirection==PIN_IN)
		{
			CLEAR_BIT(DDRC,pinnumber);
		}
		break;
		
		
		case PORT_D :
		if (drirection==PIN_OUT)
		{
			SET_BIT(DDRD,pinnumber);
		}
		else if (drirection==PIN_IN)
		{
			CLEAR_BIT(DDRD,pinnumber);
		}
		break;
	}
	
}
void DIO_PORT_init( u8 portname , u8 drirection ){
	switch (portname)
	{
		case  PORT_A :
		if (drirection==PORT_OUT)
		{
			SET_REG(DDRA);
		}
		else if (drirection==PORT_IN)
		{
			CLEAR_REG(DDRA);
		}
		break;
		
		case PORT_B :
		if (drirection==PORT_OUT)
		{
			SET_REG(DDRB);
		}
		else if (drirection==PORT_IN)
		{
			CLEAR_REG(DDRB);
		}
		break;
		
		case PORT_C :
		if (drirection==PORT_OUT)
		{
			SET_REG(DDRC);
		}
		else if (drirection==PORT_IN)
		{
			CLEAR_REG(DDRC);
		}
		break;
		
		
		case PORT_D :
		if (drirection==PORT_OUT)
		{
			SET_REG(DDRD);
		}
		else if (drirection==PORT_IN)
		{
			CLEAR_REG(DDRD);
		}
		break;
	}
	
}
void DIO_PORT_bits_init( u8 portname  , u8 bits ){
	switch (portname)
	{
		case PORT_A :
		WRITE_REG(DDRA,bits);
		break;
		case PORT_B :
		WRITE_REG(DDRB,bits);
		break;
		case PORT_C :
		WRITE_REG(DDRC,bits);
		break;
		case PORT_D :
		WRITE_REG(DDRD,bits);
		break;
	}
}

void DIO_PIN_write( u8 portname ,u8 pinnumber , u8 value ){
	
	switch (portname)
	{
		case PORT_A :
		if (value==PIN_HIGH)
		{
			SET_BIT(PORTA,pinnumber);
			
		}
		else if (value==PIN_LOW)
		{
			CLEAR_BIT(PORTA,pinnumber);
		}
		break;
		
		case PORT_B :
		if (value==PIN_HIGH)
		{
			SET_BIT(PORTB,pinnumber);
		}
		else if (value==PIN_LOW)
		{
			CLEAR_BIT(PORTB,pinnumber);
		}
		break;
		
		case PORT_C :
		if (value==PIN_HIGH)
		{
			SET_BIT(PORTC,pinnumber);
		}
		else if (value==PIN_LOW)
		{
			CLEAR_BIT(PORTC,pinnumber);
		}
		break;
		
		
		case PORT_D :
		if (value==PIN_HIGH)
		{
			SET_BIT(PORTD,pinnumber);
		}
		else if (value==PIN_LOW)
		{
			CLEAR_BIT(PORTD,pinnumber);
		}
		break;
	}
	
}
void DIO_PORT_write( u8 portname , u8 value ){
	
	switch (portname)
	{
		case PORT_A :		
			WRITE_REG(PORTA,value);		
			break;	
		case PORT_B :		
			WRITE_REG(PORTB,value);		
			break;		
		case PORT_C :
			WRITE_REG(PORTC,value);
			break;
		case PORT_D :
			WRITE_REG(PORTD,value);
			break;
	}
	
}
void DIO_PORT_write_bits( u8 portname , u8 bits ){
	switch (portname)
	{
		case PORT_A :
			CLEAR_bits(PORTA,bits);
			Set_bits(PORTA,bits);
		break;
		case PORT_B :
			CLEAR_bits(PORTB,bits);
			Set_bits(PORTB,bits);
		break;
		case PORT_C :
			CLEAR_bits(PORTC,bits);
			Set_bits(PORTC,bits);
		break;
		case PORT_D :
			CLEAR_bits(PORTD,bits);
			Set_bits(PORTD,bits);
		break;
	}
}
void DIO_low_Nipple_write( u8 portname  , u8 bits ){
		bits&=0x0f;
	switch (portname)
	{
		case PORT_A :
			CLEAR_low_nipple(PORTA);
			PORTA|=bits;
		break;
		case PORT_B :
			CLEAR_low_nipple(PORTB);
			PORTB|=bits;
		break;
		case PORT_C :
			CLEAR_low_nipple(PORTC);
			PORTC|=bits;
		break;
		case PORT_D :
			CLEAR_low_nipple(PORTD);
			PORTD|=bits;
		break;
	}
}
void DIO_high_Nipple_write( u8 portname  , u8 bits ){
	bits&=0xf0;
	switch (portname)
	{
		case PORT_A :
			CLEAR_High_nipple(PORTA);
			PORTA|=bits;
		break;
		case PORT_B :
			CLEAR_High_nipple(PORTB);
			PORTB|=bits;
		break;
		case PORT_C :
			CLEAR_High_nipple(PORTC);
			PORTC|=bits;
		break;
		case PORT_D :
			CLEAR_High_nipple(PORTD);
			PORTD|=bits;
		break;
	}
}
void DIO_PIN_read( u8 portname ,u8 pinnumber , u8 * value){

	switch (portname){
	case PORT_A :
		*value = (PINA&(1<<pinnumber) );
	break;
	
	case PORT_B :
		*value = GET_BIT(PINB, pinnumber);
	break;
	
	case PORT_C :
		*value = GET_BIT(PINC, pinnumber);
	break;
	
	case PORT_D :
		*value = GET_BIT(PIND, pinnumber);
	break;
	}
}
void DIO_PORT_read( u8 portname , u8 * value){

	switch (portname){
		case PORT_A :
			 GET_REG(PINA,*value);
		break;
		
		case PORT_B :
			GET_REG(PINB,*value);
		break;
		
		case PORT_C :
			GET_REG(PINC,*value);
		break;
		
		case PORT_D :
			GET_REG(PIND,*value);
		break;
	}

}

void DIO_PIN_toggle( u8 portname ,u8 pinnumber ){
	switch (portname)
	{
		case PORT_A :
			TOGGLE_BIT(PORTA,pinnumber);
		break;
		
		case PORT_B :
			TOGGLE_BIT(PORTB,pinnumber);
		break;
		
		case PORT_C :
			TOGGLE_BIT(PORTC,pinnumber);
		break;
		
		case PORT_D :
			TOGGLE_BIT(PORTD,pinnumber);
		break;
	}
}
void DIO_PORT_toggle( u8 portname  ){
	switch (portname)
	{
		case PORT_A :
		TOGGLE_REG(PORTA);
		break;
		
		case PORT_B :
		TOGGLE_REG(PORTB);
		break;
		
		case PORT_C :
		TOGGLE_REG(PORTC);
		break;
		
		case PORT_D :
		TOGGLE_REG(PORTD);
		break;
	}
}