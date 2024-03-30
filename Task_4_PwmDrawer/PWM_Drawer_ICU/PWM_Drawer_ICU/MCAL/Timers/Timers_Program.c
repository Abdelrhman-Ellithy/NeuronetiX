/*
 * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Timers.c>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 * Created: 2023-07-22 5:03:16 PM
 *  Author: Abdelrhman Ellithy
 */ 

#include "../../LIB/BIT_OPERATIONS.h"
#include "Timers_Interface.h"
#include "Timers_Config.H"
#include "Timers_Private.h"
#include "../../HAL/LCD Driver/CLCD_interface.h"
#include <util/delay.h>

static volatile u16 T1, T2, T3, ton, toff;
static volatile u8  done=1, ICU_TPhase_Flag=0 ;  
extern volatile u8  ICU_OV_CountTemp;

static volatile u8 flag=0;

static void (*TM0_OV_Fptr_callback)     (void)=NULLPTR;
static void (*TM0_OCO_Fptr_callback)    (void)=NULLPTR;

static void (*Timer1_OVF_Fptr_callback) (void)=NULLPTR;
static void (*Timer1_OCA_Fptr_callback) (void)=NULLPTR;

static void (*Timer1_OCB_Fptr_callback) (void)=NULLPTR;
static void (*Timer1_ICU_Fptr_callback) (void)=NULLPTR;



void Timer0_InitPreBuild(void){
				#if TM0_mode== TIMER0_NORMAL_MODE
									// mode 0
						CLEAR_BIT(TCCR0 , WGM01);
						CLEAR_BIT(TCCR0 , WGM00); 
					
					
				#elif TM0_mode== TIMER0_PHASE_CORRECT_MODE
									// mode 1
						CLEAR_BIT(TCCR0 , WGM01);
						SET_BIT(TCCR0 , WGM00);
						
						
					
				#elif TM0_mode==TIMER0_CTC_MODE 
								// mode 2
						SET_BIT(TCCR0 , WGM01);
						CLEAR_BIT(TCCR0 , WGM00);
					

					
				#elif TM0_mode== TIMER0_FASTPWM_MODE 
								// mode 3 
							SET_BIT(TCCR0, WGM01);
							SET_BIT(TCCR0 , WGM00);
		
				#else
					#error "Incorrect Timer0 mode"
				#endif
				
				#if	TM0_OC_Mode ==OCO_DISCONNECTED
				
					CLEAR_BIT(TCCR0 , COM01);
					CLEAR_BIT(TCCR0 , COM00);
					
				#elif	TM0_OC_Mode ==OCO_TOGGLE
					CLEAR_BIT(TCCR0 , COM01);
					SET_BIT(TCCR0 , COM00);
					
				#elif TM0_OC_Mode == OC0_NON_INVERTING
					SET_BIT(TCCR0, COM01);
					CLEAR_BIT(TCCR0, COM00);
					
				#elif TM0_OC_Mode == OC0_INVERTING
					SET_BIT(TCCR0, COM01);
					SET_BIT(TCCR0, COM00);
				
				#else
					#error "Incorrect Output compare Timer0 mode"
				#endif
				TCNT0 = TM0_TCNT_preload;
				OCR0 = TM0_OC0_preload;
}

void Timer0_Init_PostBuild( Timer0Mode_type mode,Timer0Scaler_type scaler ,OC0Mode_type oc_mode)
{
	switch (mode)
	{
		case TIMER0_NORMAL_MODE:
		CLEAR_BIT(TCCR0,WGM00);
		CLEAR_BIT(TCCR0,WGM01);
		break;
		case TIMER0_PHASECORRECT_MODE:
		SET_BIT(TCCR0,WGM00);
		CLEAR_BIT(TCCR0,WGM01);
		break;
		case TIMER0_CTC_MODE:
		CLEAR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
		case TIMER0_FASTPWM_MODE:
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
	}

	TCCR0&=0XF8;
	TCCR0|=scaler;

	switch (oc_mode)
	{
		case OCO_DISCONNECTED:
		CLEAR_BIT(TCCR0,COM00);
		CLEAR_BIT(TCCR0,COM01);
		break;
		case OCO_TOGGLE:
		SET_BIT(TCCR0,COM00);
		CLEAR_BIT(TCCR0,COM01);
		break;
		case OCO_NON_INVERTING:
		CLEAR_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
		case OCO_INVERTING:
		SET_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
	}
	

}
void Timer0_Run(void){
	TCCR0 &= 0xF8 ;
	TCCR0 |= TM0_prescaler;
}
void Timer0_stop(void ){
	TCCR0 &= 0xF8 ;	
}
void Timer0_OV_InterruptEnable(void){
	SET_BIT(TIMSK,TOIE0);
}
void Timer0_OV_InterruptDisable(void){
	CLEAR_BIT(TIMSK,TOIE0);
}
void Timer0_OC_InterruptEnable(void){
	SET_BIT(TIMSK,OCIE0);
}
void Timer0_OC_InterruptDisable(void){
	CLEAR_BIT(TIMSK,OCIE0);
}
void TIMER0_OVFt_SetCallBack(void(*LocalPtr)(void)){
	TM0_OV_Fptr_callback=LocalPtr;
}
void TIMER0_COMP_SetCallBack(void(*LocalPtr)(void)){
	TM0_OCO_Fptr_callback=LocalPtr;
}
void Timer0_VoidSetPWM(u8 pwm ){
		if(pwm>=0 && pwm<=100){
			OCR0=(u16)(((u32)pwm*255)/100U);
		}
}

ISR(INT_TIMER0_OVFt){
	if(TM0_OV_Fptr_callback!=NULLPTR){
		TM0_OV_Fptr_callback();
	}
}
ISR(INT_TIMER0_COMP){
	if(TM0_OCO_Fptr_callback!=NULLPTR){
		TM0_OCO_Fptr_callback();
	}
}
/************************************************************************/
/* Timer 1                                                              */
/************************************************************************/
void Timer1_Init_PostBuild( Timer1Mode_type mode,Timer1Scaler_type scaler,OC1A_Mode_type oc1a_mode,OC1B_Mode_type oc1b_mode)

{
	switch (mode)
	{
		case TIMER1_NORMAL_MODE:
		CLEAR_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);
		break;
		case TIMER1_CTC_ICR_TOP_MODE:
		CLEAR_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		
		case TIMER1_CTC_OCRA_TOP_MODE:
		CLEAR_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);
		break;
		
		case TIMER1_FASTPWM_ICR_TOP_MODE:
		CLEAR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		
		case TIMER1_FASTPWM_OCRA_TOP_MODE:
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		case TIMER1_PHASECORRECT_OCRA_TOP_MODE:
			SET_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			CLEAR_BIT(TCCR1B,WGM12);
			SET_BIT(TCCR1B,WGM13);
			break;
	}
	switch (oc1a_mode)
	{
		case OCRA_DISCONNECTED:
		CLEAR_BIT(TCCR1A,COM1A0);
		CLEAR_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_TOGGLE:
		SET_BIT(TCCR1A,COM1A0);
		CLEAR_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_NON_INVERTING:
		CLEAR_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_INVERTING:
		SET_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
	}
	switch (oc1b_mode)
	{
		case OCRB_DISCONNECTED:
		CLEAR_BIT(TCCR1A,COM1B0);
		CLEAR_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_TOGGLE:
		SET_BIT(TCCR1A,COM1B0);
		CLEAR_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_NON_INVERTING:
		CLEAR_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_INVERTING:
		SET_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
	}
	
	
	TCCR1B&=0XF8;
	TCCR1B|=scaler;

}

void Timer1_InputCaptureEdge(ICU_Edge_type edge)
{
	if(edge==RISING)
	SET_BIT(TCCR1B,ICES1);
	
	else if(edge==FALLING)
	CLEAR_BIT(TCCR1B,ICES1);

}
void Timer1_ICU_InterruptEnable(void)
{
	SET_BIT(TIMSK,TICIE1);
}
void Timer1_ICU_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK,TICIE1);
}
void Timer1_OVF_InterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE1);
}
void Timer1_OVF_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK,TOIE1);
}
void Timer1_OCA_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE1A);
}
void Timer1_OCA_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK,OCIE1A);
}
void Timer1_OCB_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE1B);
}
void Timer1_OCB_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK,OCIE1B);
}
void Timer1_OVF_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OVF_Fptr_callback=LocalFptr;
}
void Timer1_OCA_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OCA_Fptr_callback=LocalFptr;
}
void Timer1_OCB_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OCB_Fptr_callback=LocalFptr;
}
void Timer1_ICU_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_ICU_Fptr_callback=LocalFptr;
}
void Timer1_VoidTopOCRAset(u16 laod ){
	OCR1A=laod;
}
void Timer1_VoidPWMset(u8 pwm ){
	if(pwm>=0 && pwm<=100){
	OCR1B=(u16)(((u32)pwm*OCR1A)/100U);	
	}
}

void PWM_Freq_HZ(u32 freq)
{
	if (freq==0);
	else
	{
		u16 Ttotal=(u16)((u32)1000000U/(u32)freq);
		if (Ttotal>=1)
		{
			OCR1A=Ttotal-1;
		}
		else {
			OCR1A=0;
		}
	}
}

static void ICU_Flag(){
	
	if(ICU_TPhase_Flag==0){
		T1=ICR1+(ICU_OV_CountTemp*65535);
		ICU_OV_CountTemp=0;
		Timer1_InputCaptureEdge(FALLING);
		ICU_TPhase_Flag=1;
	}
	else if(ICU_TPhase_Flag==1){
		T2=ICR1+(ICU_OV_CountTemp*65535);
		ICU_OV_CountTemp=0;
		ton=(T2-T1)*(ICU_OV_CountTemp+1);
		Timer1_InputCaptureEdge(RISING);
		ICU_TPhase_Flag=2;	
	}
	else if(ICU_TPhase_Flag==2){
		T3=ICR1+(ICU_OV_CountTemp*65535);
		ICU_OV_CountTemp=0;
		toff=(T3-T2)*(ICU_OV_CountTemp+1);
		Timer1_ICU_InterruptDisable();
		ICU_OV_CountTemp=0;
		ICU_TPhase_Flag=3;
		}
}

void ICU_u8PWM_Mesure( u8 *PWM, u32* Freq){
	
	if(ICU_TPhase_Flag==3){
		*PWM=(u8)  (((u32)ton*100) / (ton+toff) );
		*Freq=(u32)( (u32)8000000 / (ton+toff) );
		ICU_TPhase_Flag=0;
		done=1;
	}
	if(done==1){
		done=0;
		TCNT1=0;
		Timer1_ICU_SetCallBack(ICU_Flag);
		Timer1_InputCaptureEdge(RISING);
		Timer1_ICU_InterruptEnable();
	}
	
}


static void Func_ICU(void)
{
	
	if (flag==0)
	{
		T1=ICR1;
		Timer1_InputCaptureEdge(FALLING);
		flag=1;
	}
	else if (flag==1)
	{
		T2=ICR1;
		Timer1_InputCaptureEdge(RISING);
		flag=2;
	}
	else if (flag==2)
	{
		Timer1_ICU_InterruptDisable();
		T3=ICR1;
		flag=3;
	}
	
}
void PWM_Measure(u32* Pfreq,u8* Pduty)
{
	u32 Ton,Toff;
	Timer1_ICU_SetCallBack(Func_ICU);
	Timer1_InputCaptureEdge(RISING);
	TCNT1=0;
	Timer1_ICU_InterruptEnable();
	flag=0;
	while(flag<3);
	Ton=T2-T1;
	Toff=T3-T2;
	u32 tot=((u32)Ton*100U);
	u32 sum=Ton+Toff;
	u16 mod=( (u32)tot % (u32)sum);
	*Pduty=((u32)tot/(u32)sum);
	if(mod>= ( (sum>>1)+(sum>>3)) ){
		(*Pduty)++;
	}
	*Pfreq=(u32)((u64)8000000UL/(sum));;
		/*
			CLCD_voidClearScreen();
			CLCD_voidSendNumber((u64)T3);
			CLCD_voidSendData(' ');
			CLCD_voidSendNumber((u64)T2);
			CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_1);
			_delay_ms(3000);
		*/
}


ISR(INT_TIMER1_OVF)
{
	if(Timer1_OVF_Fptr_callback!=NULLPTR)
	{
		Timer1_OVF_Fptr_callback();
	}
}
ISR(INT_TIMER1_COMPA)
{
	if(Timer1_OCA_Fptr_callback!=NULLPTR)
	{
		Timer1_OCA_Fptr_callback();
	}
}
ISR(INT_TIMER1_COMPB)
{
	if(Timer1_OCB_Fptr_callback!=NULLPTR)
	{
		Timer1_OCB_Fptr_callback();
	}
}
ISR(INT_TIMER1_CAPT)
{
	if(Timer1_ICU_Fptr_callback!=NULLPTR)
	{
		Timer1_ICU_Fptr_callback();
	}
}
