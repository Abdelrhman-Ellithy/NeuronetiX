/*
 * ADC_Private.h
 *
 * Created: 2023-11-15 6:45:25 AM
 *  Author: Abdelrahman Ellithy
 */ 


#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_
#include "../../LIB/Types.h"

/* Bit Masking Macros  */

#define ADC_PRE_MASK				0b11111000
#define ADC_CH_MASK				    0b11100000

#define BUSY	 1
#define NOT_BUSY 0

#define ADMUX				(*(volatile u8*)0x27)		//ADC multiplexer selection register
/* ADMUX Bits   */
#define REFS1         7							//Reference selection bit1
#define REFS0         6							//Reference selection bit0
#define ADLAR         5							//ADC left adjust result



#define ADCSRA				(*(volatile u8*)0x26)		//ADC control and status register A
/* ADSAR Bits   */
#define ADEN			7							//ADC enable
#define ADSC			6                           //Start conversion
#define	ADATE		    5                           //Auto trigger enable
#define ADIF			4                           //Interrupt flag
#define ADIE			3                           //Interrupt enable
#define ADPS2		    2                           //Prescaler bit2
#define ADPS1		    1                           //Prescaler bit1
#define ADPS0		    0                           //Prescaler bit0


/* Data Reg  */
#define ADCH				(*(volatile u8*)0x25)		//ADC high register
#define ADCL				(*(volatile u8*)0x24)		//ADC Low register
#define ADC_DATA_RE 		(*(volatile u16*)0x24)		//ADC Low + High


#define SFIOR  (*(volatile u8 *)0x50)
/* SFIOR Bits   */
#define ADTS2			7                          //Trigger Source bit2
#define ADTS1	     	6                          //Trigger Source bit1
#define ADTS0		    5                          //Trigger Source bit0


/* Values of the global var (ADC_u8ISRSource)  */
#define SINGLE_CHANNEL_ASYNCH 0
#define CHAIN_CHANNEL_ASYNCH  1





#endif /* ADC_PRIVATE_H_ */