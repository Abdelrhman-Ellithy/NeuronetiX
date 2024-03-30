/*
 * Smart_home.c
 *
 * Created: 2024-02-05 6:07:57 PM
 * Author : Abdelrahman Ellithy
 */ 

#include "LIB/Types.h"
#include "MCAL/DIO Driver/DIO_Interface.h"
#include "MCAL/PORT Driver/PORT_interface.h"
#include "MCAL/UART Driver/UART_Interface.h"
#include "MCAL/ADC Driver/ADC_Interface.h"
#include "HAL/LM35 Driver/LM35_Interface.h"
#include "MCAL/Timers/Timers_Interface.h"
#include "HAL/LED Driver/LED_Interface.h"
#include <util/delay.h>

#define LED1_ON		1
#define LED2_ON		2
#define LED3_ON		3
#define LED4_ON		4

#define SERVO_ON	5

#define LED1_OFF	6
#define LED2_OFF	7
#define LED3_OFF	8
#define LED4_OFF	9

u8 volatile UART_Data=0,UART_COUNT=0,ServoCount=0, Flag_Servo=0 ;
u8 tmp0,tmp1,tmp2,tmp3, read ,SENSORS_VALS[4]; 

		LED   LED1={DIO_PORTA,DIO_PIN4, Active_High}
			, LED2={DIO_PORTA,DIO_PIN5, Active_High}
			, LED3={DIO_PORTA,DIO_PIN6, Active_High}
			, LED4={DIO_PORTA,DIO_PIN7, Active_High};

void fun_INC_TM0(){
	UART_COUNT++;
	if(Flag_Servo){
		ServoCount++;
	}
}
int main(void){
	PORT_voidInit();
	UART_Init();
	ADC_VoidInit();
	Timer0_InitPreBuild();
	SERVO_Init();
	UART_RX_InterruptEnable();
	TIMER0_OVFt_SetCallBack(fun_INC_TM0);
	Timer0_OV_InterruptEnable();
	Timer0_Run();
	sei(); 
	u8 register sensor_id=0;
    while (1) 
    {
		LM35_VoidRead(LM_1, &tmp0);
		if (tmp0!=0xff && tmp0!=0)
		{
			SENSORS_VALS[0]=tmp0;
		}
		if(UART_COUNT>19)
		{
			UART_COUNT=0;
			if(sensor_id>3)
			{
				sensor_id=0;
			}
			read=SENSORS_VALS[sensor_id];
			if(read!=0)
			{
			UART_SendByte(read);
			sensor_id++;
			}
		}
		LM35_VoidRead(LM_2, &tmp1);
		if (tmp1!=0xff&& tmp1!=0)
		{
			SENSORS_VALS[1]=tmp1;
		}		
		if(UART_Data!=0)
		{
		switch(UART_Data){
			case  LED1_ON	: LED_voidON(&LED1);		break;
			case  LED2_ON	: LED_voidON(&LED2);	    break;
			case  LED3_ON	: LED_voidON(&LED3);	    break;
			case  LED4_ON	: LED_voidON(&LED4);	    break;
			case  SERVO_ON : ServoCount=0; Flag_Servo=1; SERVO_SetAngle(90);    break;
			case  LED1_OFF	: LED_voidOFF(&LED1);      break;
			case  LED2_OFF	: LED_voidOFF(&LED2);	   break;
			case  LED3_OFF	: LED_voidOFF(&LED3);      break;
			case  LED4_OFF	: LED_voidOFF(&LED4);      break;
		}
			
			UART_Data=0;
		}
		
		LM35_VoidRead(LM_3, &tmp2);
		if (tmp2!=0xff&& tmp2!=0)
		{
			SENSORS_VALS[2]=tmp2;
		}
		if(ServoCount>91)
		{
			Flag_Servo=0;
			SERVO_SetAngle(0);
			DIO_PIN_write(DIO_PORTB,DIO_PIN0,DIO_PIN_HIGH);
			_delay_us(5);
			DIO_PIN_write(DIO_PORTB,DIO_PIN0,DIO_PIN_LOW);
		}
		LM35_VoidRead(LM_4, &tmp3);	
		if (tmp3!=0xff&& tmp3!=0)
		{
			SENSORS_VALS[3]=tmp3;
		}
	}
	return 0;
}
