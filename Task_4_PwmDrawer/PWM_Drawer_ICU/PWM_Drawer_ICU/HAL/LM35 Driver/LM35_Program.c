/*
 * LM35_Program.c
 *
 * Created: 2023-11-15 11:25:38 AM
 *  Author: lenovo
 */ 
#include "../../LIB/Types.h"
#include "../../MCAL/ADC Driver/ADC_Interface.h"

void LM35_VoidRead(u8* result){
		u16 loc_ReadVal=0;
		ADC_u16ReadASynchronus(ADC_CHANNEL0,&loc_ReadVal);
		*result=(u8) ((u32)(loc_ReadVal * 5000ul) / 10240UL) ;
}