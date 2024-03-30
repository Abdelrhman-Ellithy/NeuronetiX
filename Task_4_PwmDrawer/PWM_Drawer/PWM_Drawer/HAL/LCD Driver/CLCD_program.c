/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    CLCD_program.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Ellithy
 *
 */
/***************************************************************************************/
#define F_CPU 8000000UL
#include <util/delay.h>
#include "CLCD_private.h"
#include "CLCD_config.h"
#include "CLCD_interface.h"
/***************************************************************************************/

/*

###########  8 Bits Mode

//----------------------------------------------------------------------------------------------------------------------------------------------------

* Breif : This Function Apply initialization sequence for LCD module
* Parameters : nothing
* return : nothing
*/
void CLCD_voidInit        ( void ){

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      8 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	#if   CLCD_MODE == 8

	// 1- must wait more than 30 ms before any action (VDD rises to 4.5 v)
	_delay_ms(35);
/*
	// All Pins as OutPut pins
	DIO_PORT_init ( CLCD_DATA_PORT    , DIO_PORT_OUTPUT   );
	DIO_PIN_init ( CLCD_CONTROL_PORT , CLCD_RS , DIO_PORT_OUTPUT  );
	DIO_PIN_init ( CLCD_CONTROL_PORT , CLCD_RW , DIO_PORT_OUTPUT  );
	DIO_PIN_init ( CLCD_CONTROL_PORT , CLCD_EN , DIO_PORT_OUTPUT  );
*/
	/* Return cursor to the first position on the first line  */
	CLCD_voidSendCommand(lcd_Home);
	_delay_ms(1);

	/*FUNCTION SET Command : 2 lines , 5*8 font size */
	CLCD_voidSendCommand( EIGHT_BITS ); // 8 Bit Mode ==> 0x38
	_delay_ms(1); // wait more than 39 Ms

	/* DISPLAY & Cursor (ON / OFF) Control */
	CLCD_voidSendCommand( Cursor_Mode );
	_delay_ms(1);

	/* DISPLAY CLEAR */
	CLCD_voidClearScreen();

	/* ENTRY MODE  SET*/
	CLCD_voidSendCommand( lcd_EntryMode );
	_delay_ms(1);



	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      4 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	#elif   CLCD_MODE == 4

	// 1- must wait more than 30 ms before any action (VDD rises to 4.5 v)
	_delay_ms(35);
	/*DIO_PIN_init	(CLCD_DATA_PORT,DIO_PIN4, DIO_PORT_OUTPUT);
	DIO_PIN_init    (CLCD_DATA_PORT,DIO_PIN5, DIO_PORT_OUTPUT);
	DIO_PIN_init    (CLCD_DATA_PORT,DIO_PIN6, DIO_PORT_OUTPUT);
	DIO_PIN_init    (CLCD_DATA_PORT,DIO_PIN7, DIO_PORT_OUTPUT);
	DIO_PIN_init	( CLCD_CONTROL_PORT , CLCD_RS , DIO_PORT_OUTPUT  );
	DIO_PIN_init	( CLCD_CONTROL_PORT , CLCD_RW , DIO_PORT_OUTPUT  );
	DIO_PIN_init	( CLCD_CONTROL_PORT , CLCD_EN , DIO_PORT_OUTPUT  );
	DIO_PIN_write   ( CLCD_CONTROL_PORT , CLCD_RS , DIO_PIN_LOW  );
*/


	/*return home*/
	CLCD_voidSendCommand( lcd_Home );
	_delay_ms(30);

	/*FUNCTION SET Command*/
	CLCD_voidSendCommand( FOUR_BITS ); // 4 Bit Mode
	_delay_ms(1);

	/* DISPLAY & Cursor (ON / OFF) Control */
	CLCD_voidSendCommand( lcd_DisplayOn_CursorOn );
	_delay_ms(1);

	/* DISPLAY CLEAR */
	CLCD_voidClearScreen();

	/* ENTRY MODE  Set*/
	CLCD_voidSendCommand( lcd_EntryMode );
	_delay_ms(1);


	#endif




}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function send data to the port which is defined in config.h
* Parameters :
            => Copy_u8Data --> Data that you want to display (for every pixel )
* return : nothing
*/
void CLCD_voidSendData    ( u8 Copy_u8Data ){

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      8 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	#if   CLCD_MODE == 8

	DIO_PORT_write ( CLCD_DATA_PORT    , Copy_u8Data        );
	DIO_PIN_write ( CLCD_CONTROL_PORT , CLCD_RS ,  DIO_PIN_HIGH );
	CLCD_voidSendFallingEdge();

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      4 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	#elif   CLCD_MODE == 4

	DIO_PIN_write  ( CLCD_CONTROL_PORT , CLCD_RS , DIO_PIN_HIGH );
	DIO_low_Nipple_write (CLCD_DATA_PORT ,(Copy_u8Data>>4));            // send the most 4 bits of data to high nibbles
	CLCD_voidSendFallingEdge();
	DIO_low_Nipple_write (CLCD_DATA_PORT ,Copy_u8Data);               // send the least 4 bits of data to high nibbles
	CLCD_voidSendFallingEdge();

	#endif
	_delay_ms(1);

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function Interface to send the configuration commands to the LCD Driver
* Parameters :
            => Copy_u8Command --> Command number
* return : nothing
*Hint : RS pin Mode is the difference between this function and the previous (CLCD_voidSendData)
*/
void CLCD_voidSendCommand ( u8 Copy_u8Command ){

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      8 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	#if   CLCD_MODE == 8

	DIO_PORT_write ( CLCD_DATA_PORT    , Copy_u8Command     );
	// RW always connect to GND to Write
	DIO_PIN_write      (CLCD_CONTROL_PORT,CLCD_RS , DIO_PIN_LOW    );
	CLCD_voidSendFallingEdge();

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      4 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	#elif   CLCD_MODE == 4

	DIO_PIN_write ( CLCD_CONTROL_PORT , CLCD_RS , DIO_PIN_LOW  );
	DIO_PIN_write ( CLCD_CONTROL_PORT , CLCD_RW , DIO_PIN_LOW  );
	DIO_voidWriteHighNibbles (CLCD_DATA_PORT ,Copy_u8Command>>4);             // send the most 4 bits of data to high nibbles
	CLCD_voidSendFallingEdge();
	DIO_voidWriteHighNibbles (CLCD_DATA_PORT ,Copy_u8Command);                // send the least 4 bits of data to high nibbles
	CLCD_voidSendFallingEdge();

	#endif

	_delay_ms(1);

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function send string to the port which is defined in config.h
* Parameters :
            => * Copy_u8ptrString  --> Pointer to the string
* return : nothing
*/
void CLCD_voidSendString  (  u8 * Copy_u8ptrString ){

	u8 LOC_u8Iterator = 0 ;

	while( Copy_u8ptrString[LOC_u8Iterator] != '\0' ){

		CLCD_voidSendData( Copy_u8ptrString[LOC_u8Iterator] );
		LOC_u8Iterator++ ;

	}

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function send number to the port which is defined in config.h
* Parameters :
            => Copy_u64Number --> number that you want to display
* return : nothing
*/
void CLCD_voidSendNumber   ( u64 Copy_u64Number    ){

	u64 LOC_u64Reversed = 1 ;

	if( Copy_u64Number == 0 ){ CLCD_voidSendData('0'); }

	else{

		while( Copy_u64Number != 0 ){

			LOC_u64Reversed = ( LOC_u64Reversed * 10 ) + ( Copy_u64Number % 10 );
			Copy_u64Number /= 10 ;

		}
		while( LOC_u64Reversed != 1 ){

			CLCD_voidSendData( ( LOC_u64Reversed % 10 ) + 48 );
			LOC_u64Reversed /= 10 ;

		}

	}

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function set the curser position
* Parameters :
            => Copy_u8Row --> row number (CLCD_ROW_1 or CLCD_ROW_2)
			=> Copy_u8Col --> column number (CLCD_COL_1 ... CLCD_COL_16)
* return : nothing
*Hint :-
   In This function we send a command which =0b1xxxxxxx
   MSB = 1  ===> refers that it is command to set cursor
   xxxxxxx  ===> refers to AC ( Address Counter 7Bits / DDRAM Locations 128Location )
*/
void CLCD_voidSetPosition ( u8 Copy_u8Row , u8 Copy_u8Col ){

	u8 LOC_u8data ;
	#if CLCD_Type == CLCd_2_16
		if(Copy_u8Row>2||Copy_u8Row<1||Copy_u8Col>16||Copy_u8Col<1)  //check
		{
			LOC_u8data = lcd_Line_1 ;   // first location
		}

		else if( Copy_u8Row == CLCD_ROW_1 ){

			LOC_u8data = ( ( lcd_Line_1 ) + ( Copy_u8Col - 1 ) );              //Row1 -> 0x80+col-1

		}

		else if( Copy_u8Row == CLCD_ROW_2 ){

			LOC_u8data = ( ( lcd_Line_2)+  ( Copy_u8Col - 1 ) );       //Row2 -> 0xc0+col-1

		}
	#elif CLCD_Type == CLCd_4_16
	/* In These cases will set at (0,0) ==> if the user enter invalid location */
		if(Copy_u8Row>4||Copy_u8Row<1||Copy_u8Col>16||Copy_u8Col<1)  //check
		{
			LOC_u8data = lcd_Line_1 ;   // first location
		}

		else if( Copy_u8Row == CLCD_ROW_1 ){

			LOC_u8data = ( ( lcd_Line_1 ) + ( Copy_u8Col - 1 ) );              //Row1 -> 0x80+col-1

		}

		else if( Copy_u8Row == CLCD_ROW_2 ){

			LOC_u8data = ( ( lcd_Line_2)+  ( Copy_u8Col - 1 ) );       //Row2 -> 0xc0+col-1

		}
		
		else if( Copy_u8Row == CLCD_ROW_3 ){

			LOC_u8data = ( ( lcd_Line_3) + ( Copy_u8Col - 1 ) );       //Row3 -> 0xc0+col-1

		}
		
		else if( Copy_u8Row == CLCD_ROW_4 ){

			LOC_u8data = ( ( lcd_Line_4) + ( Copy_u8Col - 1 ) );       //Row4 -> 0xc0+col-1

		}
	#elif CLCD_Type == CLCd_4_20
				/* In These cases will set at (0,0) ==> if the user enter invalid location */
				if(Copy_u8Row>4||Copy_u8Row<1||Copy_u8Col>20||Copy_u8Col<1)  //check
				{
					LOC_u8data = lcd_Line_1 ;   // first location
				}

				else if( Copy_u8Row == CLCD_ROW_1 ){

					LOC_u8data = ( ( lcd_Line_1 ) + ( Copy_u8Col - 1 ) );              //Row1 -> 0x80+col-1

				}

				else if( Copy_u8Row == CLCD_ROW_2 ){

					LOC_u8data = ( ( lcd_Line_2)+  ( Copy_u8Col - 1 ) );       //Row2 -> 0xc0+col-1

				}
				
				else if( Copy_u8Row == CLCD_ROW_3 ){

					LOC_u8data = ( ( lcd_Line_3) + ( Copy_u8Col - 1 ) );       //Row3 -> 0xc0+col-1

				}
				
				else if( Copy_u8Row == CLCD_ROW_4 ){

					LOC_u8data = ( ( lcd_Line_4) + ( Copy_u8Col - 1 ) );       //Row4 -> 0xc0+col-1

				}
	#endif
	CLCD_voidSendCommand ( LOC_u8data );
	_delay_ms(1);

}


//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function clear LCD
* Parameters : nothing
* return : nothing
*/
void CLCD_voidClearScreen(void)
{
	CLCD_voidSendCommand(lcd_Clear);
	CLCD_voidSendCommand(lcd_Home);
	_delay_ms(2); //wait more than 1.53 ms
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function send a pulse (falling edge ) to Enable Pin
* Parameters : nothing
* return : nothing
*
* Hint : static Function to forbid calling it out this file
*
*/
static void CLCD_voidSendFallingEdge(void)
{
	DIO_PIN_write  ( CLCD_CONTROL_PORT , CLCD_EN ,DIO_PIN_HIGH );
	_delay_ms(1);
	DIO_PIN_write  ( CLCD_CONTROL_PORT , CLCD_EN , DIO_PIN_LOW  );
	_delay_ms(1);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    END    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

