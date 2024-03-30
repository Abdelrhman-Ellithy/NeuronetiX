/************************************************************************/
/*      ADC_Program.c								*********************/
/* Created: 2023-11-12 6:59:50 PM					 *********************/
/*  Author: Abdelrahman Ellithy								            */
/************************************************************************/

/* Include Header Files From LIB */
#include "../../LIB/BIT_OPERATIONS.h"
#include "ADC_Interface.h"
#include "ADC_Private.h"
#include "ADC_Config.h"


static u8 currunetChannel=0xff, Channelreaded=1 ;


void ADC_VoidInit(void){
	
	/*  select adjustment */
	#if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
	CLEAR_BIT(ADMUX,ADLAR);
	#elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT
	SET_BIT(ADMUX,ADLAR);
	#endif
	/*  select voltage refrance */
	#if ADC_VREF == AVCC
	SET_BIT(ADMUX, REFS0);
	CLEAR_BIT(ADMUX, REFS1);
	#elif ADC_VREF == AREF
	CLEAR_BIT(ADMUX, REFS0);
	CLEAR_BIT(ADMUX, REFS1);
	#elif ADC_VREF == INTERNAL_2_56
	SET_BIT(ADMUX, REFS0);
	SET_BIT(ADMUX, REFS1);
	#endif
	
	
	/* select channel */
	ADMUX&=ADC_CH_MASK;
	ADMUX|= ADC_CHANNEL;
	
	
	/*select source */
	#if	  ADC_TRIGGERING_SOURCE == ADC_SINGLE_CONVERSION
	CLEAR_BIT(ADCSRA,ADATE);
	#endif
	
	
	/*  Set Prescaler Value  */
	ADCSRA &= ADC_PRE_MASK ;
	ADCSRA |= ADC_PRESCALLER ;
	/*                      */
	
	/* select ADC status Enable or Disable */
	#if ADC_STATUS == ADC_ENABLE
	SET_BIT(ADCSRA, ADEN);
	#elif ADC_STATUS == ADC_DATA_RE
	CLEAR_BIT(ADCSRA, ADEN);
	#endif
	
	/* select ADC Interrupt status Enable or Disable */
	#if INT_STATUS== INT_ENABLE
	SET_BIT(ADCSRA, ADIE);
	#elif INT_STATUS== INT_DISABLE
	CLEAR_BIT(ADCSRA, ADIE);
	#endif
	
}

u16 ADC_u16ReadSynchronus ( u8 Copy_u8ChannelNumber ) {
      
	u16 loc_result;
    /*   Select channel   */ 
   if (Copy_u8ChannelNumber<ADC_CHANNEL7+1 )
   {
		ADMUX&=ADC_CH_MASK;
		ADMUX|= Copy_u8ChannelNumber;
		currunetChannel=Copy_u8ChannelNumber;
    }
 
    	SET_BIT(ADCSRA,ADSC);
    	while(GET_BIT(ADCSRA,ADSC));
    	loc_result=(ADCL|ADCH<<8);
		return loc_result;
}
/************************************************************************************************/
u8 ADC_u16ReadASynchronus ( u8 Copy_u8ChannelNumber, u16 *result ) 
{	
	
	u8 ADC_u18BusyFlag=(GET_BIT(ADCSRA,ADSC));
    if ( ADC_u18BusyFlag == BUSY)
    {
		Channelreaded=0;
        return 0;
    }
    else if(ADC_u18BusyFlag==NOT_BUSY)
    {
		if(Copy_u8ChannelNumber==currunetChannel&& Channelreaded==0){

				*result=(ADCL|ADCH<<8);
				Channelreaded=1;
				return 1;
		}
		else if(Copy_u8ChannelNumber==currunetChannel&& Channelreaded==1){
			
			    	SET_BIT(ADCSRA,ADSC);
					Channelreaded=0;
					return 0;
		}
		else
		{
			
		if(Channelreaded)
			{
				currunetChannel=Copy_u8ChannelNumber;
				/*   Select channel   */
				if (Copy_u8ChannelNumber<ADC_CHANNEL7+1 )
				{
					ADMUX = (( ADMUX & ADC_CH_MASK ) | Copy_u8ChannelNumber );
				}
				/*start cnversion*/
				SET_BIT(ADCSRA,ADSC);
			}
			else
			{
				return 0;
			}
		}
	}
}
void ADC_VoidSet_prescaler(u8 prescaler){
	ADCSRA &= ADC_PRE_MASK ;
	ADCSRA |= prescaler ;
}
void __vector_16 (void)   __attribute__((signal));
void __vector_16 (void)
{

}
