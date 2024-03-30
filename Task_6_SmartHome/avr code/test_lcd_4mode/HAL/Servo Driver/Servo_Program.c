
#include "../../LIB/Types.h"
#include "Servo_Interface.h"
#include "Servo_conifg.h"
#include "Servo_private.h"
#include "../../MCAL/Timers/Timers_Config.h"
#include "../../MCAL/Timers/Timers_Interface.h"
#include "../../MCAL/Timers/Timers_Private.h" 

void SERVO_Init(void)
{
	/*set timer 1 prescaler to 8to get 1us tick time
	use fast mode with top value at OCRA reg to set the freq of servo
	diconnect OC1A PIN ,and generate the PWM on OC1B PIN with nin inverting mode to use OCR1B reg as the ton value*/

	#if Servotimerreg == One_Servo
		Timer1_Init_PostBuild(TIMER1_FASTPWM_OCRA_TOP_MODE,TIMER1_SCALER_8,OCRA_DISCONNECTED,OCRB_NON_INVERTING);
		OCR1A=19999;//20000us to get 50hz 
		OCR1B=999;// 2000us ton to get angle zero
	
	#elif Servotimerreg == More_than_Servo
		Timer1_Init_PostBuild(TIMER1_CTC_ICR_TOP_MODE,TIMER1_SCALER_8,OCRA_NON_INVERTING,OCRB_DISCONNECTED);
		ICR1=19999;//20000us to get 50hz
		OCR1A=999;// 2000us ton to get angle zero
	#endif
}

void SERVO_SetAngle(u8 angle)
{	/*switch(servo->reg){
		case servo_OCR1A :
			OCR1A=(((u32)angle*1000)/180)+999;
			break;
		case servo_OCR1B :*/
			OCR1B=(((u32)angle*1000)/180)+999;
			//break;
		//}
}
