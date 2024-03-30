/*
 * Timers.h
 *
 * Created: 2023-07-22 5:03:01 PM
 *  Author: Abdelrhman Ellithy
 */ 

/************************************************************************/
/* 1_ choose timer mode                                                 */
/* 2_load timer                                                         */
/* 3_set prescaler                                                      */
/* 4_clear timer overflow flag                                          */
/************************************************************************/
#ifndef TIMERS_H_
#define TIMERS_H_

#include "../Types.h"
#include "../BIT_OPERATIONS.h"
#include "../register.h"
/************************************************************************/
/* timer 0 & macros									        */
/************************************************************************/
/* TCCR0 */
#define FOC0    7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0
/************************************************************************/
/* Timer 0 PRESCALER											        */
/************************************************************************/
#define TM0_NO_CLK	 (u8)0x00
#define TM0_PRESCALER_CLK_NORMAL (u8)0x01
#define TM0_PRESCALER_CLK_8		 (u8)0x02
#define TM0_PRESCALER_CLK_64	 (u8)0x03
#define TM0_PRESCALER_CLK_256	 (u8)0x04
#define TM0_PRESCALER_CLK_1024	 (u8)0x05
/************************************************************************/
/* Timer 0 MODES												        */
/************************************************************************/
#define TIMER0_NORMAL_MODE		  (u8)'0'
#define TIMER0_PHASE_CORRECT_MODE (u8)'1'
#define TIMER0_CTC_MODE           (u8)'2'
#define TIMER0_FASTPWM_MODE       (u8)'3'
/************************************************************************/
/*                Timer0 Functions                                      */
/************************************************************************/
void Timer0_init(u8 timermode , u8 preload ,u8 oc_mode);
void Timer0_Run(u8 prescaler );
void Timer0_OV_InterruptEnable(void);
void Timer0_OV_InterruptDisable(void);
void Timer0_OC_InterruptEnable(void);
void Timer0_OC_InterruptDisable(void);
void Timer0_stop(void );
/************************************************************************/
/* timer 1 & macros                                                     */
/************************************************************************/
/* TCCR1A */
#define COM1A1  7
#define COM1A0  6
#define COM1B1  5
#define COM1B0  4
#define FOC1A   3
#define FOC1B   2
#define WGM11   1
#define WGM10   0
/* TCCR1B */
#define ICNC1   7
#define ICES1   6
#define WGM13   4
#define WGM12   3
#define CS12    2
#define CS11    1
#define CS10    0

/************************************************************************/
/* timer 2  & macros                                                    */
/************************************************************************/
/* TCCR2 */
#define FOC2    7
#define WGM20   6
#define COM21   5
#define COM20   4
#define WGM21   3
#define CS22    2
#define CS21    1
#define CS20    0
/************************************************************************/
/* timer Special function registers  & macros                           */
/************************************************************************/
/* TIMSK */
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0
/* TIFR */
#define OCF2    7
#define TOV2    6
#define ICF1    5
#define OCF1A   4
#define OCF1B   3
#define TOV1    2
#define OCF0    1
#define TOV0    0
/************************************************************************/
/*                timer macros										    */
/************************************************************************/
#define Timer0 (u8)0x01
#define Timer1 (u8)0x04
#define Timer2 (u8)0x40
/************************************************************************/
/*                Timer Functions                                       */
/************************************************************************/
void timer1_init(u8 timermode , u16 preload ,u8 oc_mode);
void timer2_init(u8 timermode , u8 preload,u8 oc_mode);
void timer2_Run(u8 prescaler );
#endif /* TIMERS_H_ */