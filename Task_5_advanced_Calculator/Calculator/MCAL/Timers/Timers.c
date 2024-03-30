/*
 * Timers.c
 *
 * Created: 2023-07-22 5:03:16 PM
 *  Author: Abdelrhman Ellithy
 */ 

#include "Timers_Config.H"
static void (*TM0_OV_Fptr_callback) (void)=NULLPTR;
static void (*TM0_OCO_Fptr_callback) (void)=NULLPTR;
void Timer0_init(void){
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
				//TCNT0 = TM0_TCNT_preload;
				OCR0 = TM0_OC0_preload;
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
ISR(INT_TIMER0_OVFt){
	if(TM0_OV_Fptr_callback!=NULLPTR){
		TM0_OV_Fptr_callback();
	}
}
ISR(INT_TIMER0_COMP){
	if(TM0_OV_Fptr_callback!=NULLPTR){
		TM0_OCO_Fptr_callback();
	}
}
