/*
 * LM35_Program.c
 *
 * Created: 2023-11-15 11:25:38 AM
 *  Author: Abdelrahman Ellithy
 */ 
#include "../../LIB/Types.h"
#include "../../MCAL/ADC Driver/ADC_Interface.h"

void LM35_VoidRead(u8 SENSOR_ID,u8 * result){
		u8 val= *result;
		u16 loc_ReadVal=0;
		if(ADC_u16ReadASynchronus(SENSOR_ID,&loc_ReadVal)){
			*result=( (u8)( (u32)(loc_ReadVal * 5000UL) / 10240UL) ) ;
		}
		else{
			*result=0xff;
		}
}