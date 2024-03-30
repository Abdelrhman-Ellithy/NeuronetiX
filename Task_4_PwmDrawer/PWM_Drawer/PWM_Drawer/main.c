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
#include "MCAL/ADC Driver/ADC_Interface.h"
#include "MCAL/EX_INT Driver/EX_INTERRUPT_Interface.h"
#include "LIB/BIT_OPERATIONS.h"

u32 static volatile Freq=1000;
u8  static volatile PWM=0;
u8  Space_STR[]="    ";

void Print_On_Screen(){

	CLCD_voidClearScreen();
	CLCD_voidSendNumber((u64)Freq);
	CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_1);
	CLCD_voidSendNumber((u64)PWM);	

}

void Increamnt_Freq(){
	if(Freq<50000){
		Freq+=500;
		PWM_Freq_HZ((u16)Freq);
		Timer1_VoidPWMset(PWM);
	}
		Print_On_Screen();
}

void decreamnt_Freq(){
	if (Freq>=500){
		 Freq-=500;
		 PWM_Freq_HZ((u16)Freq);
		 Timer1_VoidPWMset(PWM);
	}
		Print_On_Screen();
}

int main(void)
{
	PORT_voidInit();
	ADC_VoidInit();
	Timer1_VoidTopOCRAset(3999);
	Timer1_Init_PostBuild( TIMER1_PHASECORRECT_OCRA_TOP_MODE , TIMER1_SCALER_1, OCRA_DISCONNECTED,OCRB_NON_INVERTING);
	EX_INT0_Edge_Detect(FALLING_EDGE);
	EX_INT1_Edge_Detect(FALLING_EDGE);
	EX_INT0_SetCallBack(Increamnt_Freq);
	EX_INT1_SetCallBack(decreamnt_Freq);
	CLCD_voidInit();
	EX_INT0_Enable();
	EX_INT1_Enable();
	Timer1_OCA_InterruptEnable();
	Timer1_VoidPWMset(50);
	u16 ADC_result=0xff,past_result=0;
	sei();
    while (1) 
    {	
		if(ADC_u16ReadASynchronus(ADC_CHANNEL0, &ADC_result))
		{
			if(ADC_result!=past_result){	
				PWM=(u8)(((u32)ADC_result*100)/1023);
				Print_On_Screen();
				Timer1_VoidPWMset(PWM);	
				past_result=ADC_result;
			}
		}
   }
}

