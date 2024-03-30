/*=================================================================================*/
/*  File        : TIMER1_INTERFACE_H_                                                  */
/*  Description : This Program file includes AFIO program for STM32f103C8T6        */
/*  Abdelrahman Ellithy
 *  layer: MCAL
 *  SW component: Timer1
 *  																				*/
#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_


typedef enum{
	 TIMER1_COUNT_UP=0
	,TIMER1_COUNT_DOWN
}Count_Mode;


typedef enum{
	 TIMER1_PWM_CHANNEL1=0
	,TIMER1_PWM_CHANNEL2
	,TIMER1_PWM_CHANNEL3
	,TIMER1_PWM_CHANNEL4

}PWM_CHANNEL;


void TIMER1_Init(Count_Mode Copy_Direction , u16 Copy_u16Prescaler);

void TIMER1_InitPwmChannel(PWM_CHANNEL Copy_PwmChannel);

void TIMER1_SetPWM(PWM_CHANNEL Copy_PwmChannel , u32 Copy_u8PwmFrequency , u8 Copy_u8PwmDutyCycle);


void TIMER1_Stop(void);

#endif /* TIMER1_INTERFACE_H_ */
