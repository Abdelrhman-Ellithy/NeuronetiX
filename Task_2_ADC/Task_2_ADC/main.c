/*
 * Task_2_ADC.c
 *
 * Created: 2024-03-03 3:15:08 PM
 * Author : Abdelrahman Ellithy
 */ 

#include "MCAL/ADC Driver/ADC_Interface.h"
#include "MCAL/PORT Driver/PORT_interface.h"
#include "MCAL/DIO Driver/DIO_Interface.h"
#include "HAL/LCD Driver/CLCD_interface.h"
int main(void)
{
    /* Replace with your application code */
	PORT_voidInit();
	ADC_VoidInit();
	CLCD_voidInit();
	u16 result,past_result;u64 Answer;
	u8 ML_Volt[]="mv";
    while (1) 
    {
		ADC_u16ReadASynchronus(ADC_CHANNEL0, &result);
		if(past_result!=result){
			CLCD_voidClearScreen();
			Answer=( (u64)((u64)result*5000)/1023);
			CLCD_voidSendNumber((u64)Answer);
			CLCD_voidSendString(ML_Volt);
			past_result=result;
		}
		
    }
}

