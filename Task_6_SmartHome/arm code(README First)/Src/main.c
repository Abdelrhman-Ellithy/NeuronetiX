/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Abdelrahman Ellithy
 * @brief          : Main program body
*/
#include "MCAL/RCC/RCC_interface.h"
#include "MCAL/GPIO/GPIO_interface.h"
#include "HAL/LCD/CLCD_interface.h"
#include "LIB/STD_TYPES.h"
#include "LIB/ellithy_delay.h"
#include "MCAL/NVIC/NVIC_Interface.h"
#include "MCAL/EXTI/EXTI_interface.h"
#include "MCAL/AFIO/AFIO_interface.h"
#include "MCAL/DMA/DMA_interface.h"
#include "MCAL/TIMER1/TIMER1_interface.h"
#include "MCAL/UART/UART_interface.h"
#include "MCAL/SYSTICK/SysTick_Interface.h"

typedef void(*fptr_t)(void);
static fptr_t FUN_Selected;

typedef enum {
	 Comonent_ID=0
	,Comonent_VALUE
}DATA_FLAG;

typedef enum{
	 LED_ROOM_1_STATE=0
	,LED_ROOM_2_STATE=1
	,LED_ROOM_3_STATE=2
	,LED_ROOM_4_STATE=3
	,FAN_ROOM_1_SPEED=4
	,FAN_ROOM_2_SPEED=5
	,FAN_ROOM_3_SPEED=6
	,FAN_ROOM_4_SPEED=7
	,Open_Home_door	=8

}Fun_IDS;


     /* index 0 LED_ROOM_1_STATE   */
	 /* index 1 LED_ROOM_2_STATE   */
	 /* index 2 LED_ROOM_3_STATE   */
	 /* index 3 LED_ROOM_4_STATE   */
	 /* index 4 FAN_ROOM_1_SPEED   */
	 /* index 5 FAN_ROOM_2_SPEED   */
	 /* index 6 FAN_ROOM_3_SPEED   */
	 /* index 7 FAN_ROOM_4_SPEED   */


// 0 1
u8 volatile UART_DATA, Compomenent_VAL;
volatile DATA_FLAG static Flag_switch=Comonent_ID;
volatile Fun_IDS  Fun_ID ;
u8 Welcome[]="Welcome Home", Door[]="Door Opened";
void fun_Direct(){
	UART_SendByte(UART_2,Compomenent_VAL);
	if(Compomenent_VAL==5){
		CLCD_voidSendString(Door);
		CLCD_voidSetPosition(CLCD_ROW_2, CLCD_COL_1);
		CLCD_voidSendString(Welcome);
	}
}
void fun_motor1(){
	TIMER1_SetPWM(TIMER1_PWM_CHANNEL1, 100000,Compomenent_VAL );
}
void fun_motor2(){
	TIMER1_SetPWM(TIMER1_PWM_CHANNEL2, 100000,Compomenent_VAL );
}
void fun_motor3(){
	TIMER1_SetPWM(TIMER1_PWM_CHANNEL3, 100000,Compomenent_VAL );
}
void fun_motor4(){
	TIMER1_SetPWM(TIMER1_PWM_CHANNEL4, 100000,Compomenent_VAL );
}
void Fun_recieve_and_determine_and_Sent(){
	volatile DATA_FLAG static Flag=Comonent_ID;
	Flag_switch=Flag;
	switch(Flag){
        case Comonent_ID: Fun_ID=UART_DATA; Flag=Comonent_VALUE; break;
	    case Comonent_VALUE:  Compomenent_VAL=(u8)UART_DATA;  Flag=Comonent_ID; break;
	}
	if(Flag_switch==Comonent_ID)
	{
		switch(Fun_ID)
		{
		  case LED_ROOM_1_STATE: FUN_Selected=fun_Direct;  break;
		  case LED_ROOM_2_STATE: FUN_Selected=fun_Direct;  break;
		  case LED_ROOM_3_STATE: FUN_Selected=fun_Direct;  break;
		  case LED_ROOM_4_STATE: FUN_Selected=fun_Direct;  break;
		  case FAN_ROOM_1_SPEED: FUN_Selected=fun_motor1;  break;
		  case FAN_ROOM_2_SPEED: FUN_Selected=fun_motor2;  break;
		  case FAN_ROOM_3_SPEED: FUN_Selected=fun_motor3;  break;
		  case FAN_ROOM_4_SPEED: FUN_Selected=fun_motor4;  break;
		  case Open_Home_door: 	 FUN_Selected=fun_Direct;  break;
		}
	}
		else if(Flag_switch==Comonent_VALUE)
		{
			FUN_Selected();
		}
}
void Fun_Clear(){
	CLCD_voidClearScreen();
}
int main(void)
{
	RCC_InitSysClk();
	RCC_PeripheralClk(RCC_GPIOA, RCC_Enable);
	RCC_PeripheralClk(RCC_GPIOB, RCC_Enable);
	RCC_PeripheralClk(RCC_AFIO,   RCC_Enable);
	RCC_PeripheralClk(RCC_USART3, RCC_Enable);
	RCC_PeripheralClk(RCC_USART2, RCC_Enable);
	RCC_PeripheralClk(RCC_TIM1, RCC_Enable);
	RCC_PeripheralClk(RCC_DMA1, RCC_Enable);

	GPIO_PORT_voidInit();
	NVIC_Init();
	UART_Init();
	TIMER1_Init(TIMER1_COUNT_UP,1);
	DMA_voidChannelInit(	DMA_CHANNEL6,
							DMA_PRIORITY_HIGH,
							DMA_DATA_SIZE_1BYTE,
							DMA_DATA_SIZE_1BYTE,
							DMA_PER_TO_PER,
							DMA_SOURCE_INC_DISEN,
							DMA_DIST_INC_DISEN,
							DMA_TC_INT_DISABLE,
							circular
							);

	NVIC_EnableInterrupt(NVIC_EXTI0);

	EXTI_Interrupt_Enable(EXTI0, RISING_EDGE);
	EXTI_SetCallBack(EXTI0, Fun_Clear);

	AFIO_EXTI_Port_Source(AFIO_EXTI_LINE0, AFIO_PORTA);

	TIMER1_InitPwmChannel(TIMER1_PWM_CHANNEL1);
	TIMER1_InitPwmChannel(TIMER1_PWM_CHANNEL2);
	TIMER1_InitPwmChannel(TIMER1_PWM_CHANNEL3);
	TIMER1_InitPwmChannel(TIMER1_PWM_CHANNEL4);
	TIMER1_SetPWM(TIMER1_PWM_CHANNEL1, 100000,0 );
	TIMER1_SetPWM(TIMER1_PWM_CHANNEL2, 100000,0 );
	TIMER1_SetPWM(TIMER1_PWM_CHANNEL3, 100000,0 );
	TIMER1_SetPWM(TIMER1_PWM_CHANNEL4, 100000,0 );


	CLCD_voidInit();
	NVIC_EnableInterrupt(NVIC_USART3);
	UART_SetCallBack(UART_3, Fun_recieve_and_determine_and_Sent);
	NVIC_EnableInterrupt(NVIC_DMA1_CHANNEL6);
	DMA_ChannelTransfer(DMA_CHANNEL6,(u32)DMA_Transfeer_UART3_CH2,(u32)DMA_Recieve_UART2_CH6,4);
	DMA_void_DMA_Enable(DMA_CHANNEL6);

	while(1){

	}
}
