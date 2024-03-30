/*
 * SPI_Program.c
 *
 * Created: 2024-01-06 4:06:04 PM
 *  Author: Abdelrahman Ellithy
 */ 

#include "../../LIB/BIT_OPERATIONS.h"
#include "SPI_Config.h"
#include "SPI_private.h"
#include "SPI_interface.h"
void SPI_voidInit(void){
	
		SET_BIT(SPCR,SPE);
	
		#if SPI_Mode==ModeMaster
			SET_BIT(SPCR,MSTR);
		#elif SPI_Mode==ModeSlave
			CLEAR_BIT(SPCR,MSTR);
		#endif
	
		#if SPI_DATA_ORDER == SPI_DATA_LSB_FIRST
			SET_BIT(SPCR , DORD) ;
		#elif SPI_DATA_ORDER == SPI_DATA_MSP_FIRST
			CLEAR_BIT(SPCR , DORD) ;
		#endif
		

		/*Clock Polarity*/
		#if SPI_CLOCK_POLARITY == SPI_RISING_LEADING_FALLING_TRAILING
			CLEAR_BIT(SPCR , CPOL) ;
		#elif SPI_CLOCK_POLARITY == SPI_FALLING_LEADING_RISING_TRAILING
			SET_BIT(SPCR , CPOL) ;
		#endif

		/*Clock Phase*/
		#if SPI_CLOCK_PHASE == SPI_SAMPLE_LEADING_SETUP_TRAILING
		CLEAR_BIT(SPCR , CPHA) ;

		#elif SPI_CLOCK_PHASE == SPI_SETUP_LEADING_SAMPLE_TRAILING
			SET_BIT(SPCR , CPHA) ;
		#endif

		/*Clock Rate*/
		SPCR&=0xfc;
		SPCR|=SPI_CLOCK_RATE;


		/*SPI Enable*/
		#if SPI_ENABLE_MODE == SPI_DISABLE
			CLEAR_BIT(SPCR , SPE) ;
		#elif SPI_ENABLE_MODE == SPI_ENABLE
			SET_BIT(SPCR , SPE) ;
		#endif

}
u8 SPI_TranmitRecive(u8 Copy_u8Data){
		/*Send The Data*/
		SPDR = Copy_u8Data;
		/*Polling until Transfer is complete*/
		while( !( GET_BIT(SPSR, SPIF) ));
		/*Return data*/
		return SPDR;
}
void SPI_changeMode(u8 mode){
	switch(mode){
		case ModeMaster:
			SET_BIT(SPCR,MSTR);	
		break;
		case ModeSlave:
			CLEAR_BIT(SPCR,MSTR);
		break;
	}
}