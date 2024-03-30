/*
 * PWM_Drawer.c
 *
 * Created: 2024-03-04 5:53:11 PM
 * Author : Abdelrahman Ellithy
 */ 
#include "HAL/LCD Driver/CLCD_interface.h"
#include "MCAL/PORT Driver/PORT_interface.h"
#include "MCAL/DIO Driver/DIO_Interface.h"
#include "MCAL/Timers/Timers_Interface.h"
#include "LIB/BIT_OPERATIONS.h"

volatile u8  ICU_OV_CountTemp=0;

void Increamnt_ovICU(){
	ICU_OV_CountTemp++;
}

void Print_On_Screen(u8 pwm, u32 freq){
	
	CLCD_voidClearScreen();
	CLCD_voidSendNumber((u64)freq);
	CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_1);
	CLCD_voidSendNumber((u64)pwm);
	
}


int main(void)
{
	PORT_voidInit();
	Timer1_Init_PostBuild( TIMER1_NORMAL_MODE , TIMER1_SCALER_1, OCRA_DISCONNECTED,OCRB_NON_INVERTING);
	Timer1_OVF_SetCallBack(Increamnt_ovICU);
	CLCD_voidInit();
	//Timer1_OVF_InterruptEnable();
	sei();
	u32  volatile Freq_ICU;
	u8   volatile PWM_ICU;
	u8	 PWM_Prevouis=0;
	u32	 Freq_Prevouis=0;
	
    while (1) 
    {	
		// ICU_u8PWM_Mesure(&PWM_ICU, &Freq_ICU);
		  PWM_Measure(&Freq_ICU, &PWM_ICU);
		 if( (Freq_ICU!=Freq_Prevouis) || (PWM_ICU!=PWM_Prevouis) ){
			
				 Print_On_Screen(PWM_ICU,Freq_ICU); 
				 PWM_Prevouis=PWM_ICU;
				 Freq_Prevouis=Freq_ICU; 
		 }
   }
}

