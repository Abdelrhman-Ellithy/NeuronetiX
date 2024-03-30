/*
 * Timers_Config.h
 *
 * Created: 2023-09-11 8:00:26 AM
 *  Author: Abdelrahman Ellithy
 */ 


#ifndef TIMERS_CONFIG_H_
#define TIMERS_CONFIG_H_

/************************************************************************/
/* Timer 0 PRESCALER											        */
/************************************************************************/
#define TM0_NO_CLK			 0x00
#define TM0_PRESCALER_1		 0x01
#define TM0_PRESCALER_8		 0x02
#define TM0_PRESCALER_64	 0x03
#define TM0_PRESCALER_256	 0x04
#define TM0_PRESCALER_1024	 0x05

/************************************************************************/
/*  OC0 Modes										        */
/************************************************************************/
#define OCO_DISCONNECTED			'0'
#define OCO_TOGGLE					'1'
#define OC0_NON_INVERTING			'2'
#define OC0_INVERTING				'3'
/************************************************************************/
/* Timer 0 MODES												        */
/************************************************************************/
#define TIMER0_NORMAL_MODE		   '0'
#define TIMER0_PHASE_CORRECT_MODE  '1'
#define TIMER0_CTC_MODE            '2'
#define TIMER0_FASTPWM_MODE        '3'




#define TM0_prescaler		TM0_PRESCALER_1024
#define TM0_mode			TIMER0_NORMAL_MODE
#define TM0_TCNT_preload	0x00
#define TM0_OC_Mode			OCO_DISCONNECTED
#define TM0_OC0_preload		0x00
 
#endif /* TIMERS_CONFIG_H*/