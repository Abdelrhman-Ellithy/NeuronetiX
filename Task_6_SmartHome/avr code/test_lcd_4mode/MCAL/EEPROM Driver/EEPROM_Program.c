/*
 * EEPROM.c
 *
 * Created: 2023-11-10 6:54:23 PM
 *  Author: lenovo
 */ 
#include "EEPROM_Config.h"
#include "EEPROM_Interface.h"
#include "EEPROM_Private.h"
static void (*eeprom_rdy_fPtr)(void) = NULLPTR;

void EEPROM_write( u16 address, u8 data)
{
    /* Wait for completion of previous write */
    while (1 == GET_BIT(EECR, EEWE));

    /* Set up address and data registers */
    EEAR = address;
    EEDR = data;

    /* disable global interrupt */
    cli();

    /* Write logical one to EEMWE */
    SET_BIT(EECR, EEMWE);

    /* Start EEPROM write by setting EEWE--> must be done withing four clock cycles
    *  after setting EEMWE so I use cli() and sei() 
    */
    SET_BIT(EECR, EEWE);
    /* enable global interrupt */
    sei();
}

void EEPROM_read( u16 address, u8 *data)
{
    /* Wait for completion of previous write */
    while (1 == GET_BIT(EECR, EEWE));

    /* Set up address register */
    EEAR = address;

    /* Start EEPROM read by writing EERE */
    SET_BIT(EECR, EERE);

    /* Return data from data register */
    *data=EEDR;
}

void EEPROM_intEnable(void)
{
    SET_BIT(EECR, EERIE);
}

void EEPROM_intDisable(void)
{
    CLEAR_BIT(EECR, EERIE);
}

void EEPROM_intSetCallback(void (*localFptr)(void))
{
    eeprom_rdy_fPtr = localFptr;
}
/*
ISR(EE_RDY_VECT)
{
    if (eeprom_rdy_fPtr != NULLPTR)
    {
        eeprom_rdy_fPtr();
    }
}
*/