/*=================================================================================*/
/*  File        : PORT_PRIVATE_H_                                                 */
/*  Description : This Program file includes NVIC program for STM32f103C8T6        *
 *  Author : Abdekrahman Ellithy
 *  Layer  : MCAL
 *  SW component: PORT
 */

#ifndef PORT_PRIVATE_H_
#define PORT_PRIVATE_H_

/*   Registers         */


/*   Concatination     */

#define CONC(b7,b6,b5,b4,b3,b2,b1,b0)			CONC_HELPER(b7,b6,b5,b4,b3,b2,b1,b0)
#define CONC_HELPER(b7,b6,b5,b4,b3,b2,b1,b0)	0b##b7##b6##b5##b4##b3##b2##b1##b0


#define CONC2(b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0)			CONC_HELPER2(b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0)
#define CONC_HELPER2(b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0)	0b##b15##b14##b13##b12##b11##b10##b9##b8##b7##b6##b5##b4##b3##b2##b1##b0

#define PORTAL_DIRCTION				CONC(PORTA_PIN7_DIR,PORTA_PIN6_DIR,PORTA_PIN5_DIR,PORTA_PIN4_DIR,PORTA_PIN3_DIR,PORTA_PIN2_DIR,PORTA_PIN1_DIR,PORTA_PIN0_DIR)
#define PORTAH_DIRCTION				CONC(PORTA_PIN15_DIR,PORTA_PIN14_DIR,PORTA_PIN13_DIR,PORTA_PIN12_DIR,PORTA_PIN11_DIR,PORTA_PIN10_DIR,PORTA_PIN9_DIR,PORTA_PIN8_DIR)

#define PORTBL_DIRCTION				CONC(PORTB_PIN7_DIR,PORTB_PIN6_DIR,PORTB_PIN5_DIR,PORTB_PIN4_DIR,PORTB_PIN3_DIR,PORTB_PIN2_DIR,PORTB_PIN1_DIR,PORTB_PIN0_DIR)
#define PORTBH_DIRCTION				CONC(PORTB_PIN15_DIR,PORTB_PIN14_DIR,PORTB_PIN13_DIR,PORTB_PIN12_DIR,PORTB_PIN11_DIR,PORTB_PIN10_DIR,PORTB_PIN9_DIR,PORTB_PIN8_DIR)

#define PORTCH_DIRCTION				CONC(PORTC_PIN15_DIR,PORTC_PIN14_DIR,PORTC_PIN13_DIR,PORTC_PIN12_DIR,PORTC_PIN11_DIR,PORTC_PIN10_DIR,PORTC_PIN9_DIR,PORTC_PIN8_DIR)


#define PORTA_INITIAL_VALUE		CONC2(PORTA_PIN15_INITIAL_VALUE,PORTA_PIN14_INITIAL_VALUE,PORTA_PIN13_INITIAL_VALUE,PORTA_PIN12_INITIAL_VALUE,PORTA_PIN11_INITIAL_VALUE,PORTA_PIN10_INITIAL_VALUE,PORTA_PIN9_INITIAL_VALUE,PORTA_PIN8_INITIAL_VALUE,PORTA_PIN7_INITIAL_VALUE,PORTA_PIN6_INITIAL_VALUE,PORTA_PIN5_INITIAL_VALUE,PORTA_PIN4_INITIAL_VALUE,PORTA_PIN3_INITIAL_VALUE,PORTA_PIN2_INITIAL_VALUE,PORTA_PIN1_INITIAL_VALUE,PORTA_PIN0_INITIAL_VALUE)
#define PORTB_INITIAL_VALUE		CONC2(PORTB_PIN15_INITIAL_VALUE,PORTB_PIN14_INITIAL_VALUE,PORTB_PIN13_INITIAL_VALUE,PORTB_PIN12_INITIAL_VALUE,PORTB_PIN11_INITIAL_VALUE,PORTB_PIN10_INITIAL_VALUE,PORTB_PIN9_INITIAL_VALUE,PORTB_PIN8_INITIAL_VALUE,PORTB_PIN7_INITIAL_VALUE,PORTB_PIN6_INITIAL_VALUE,PORTB_PIN5_INITIAL_VALUE,PORTB_PIN4_INITIAL_VALUE,PORTB_PIN3_INITIAL_VALUE,PORTB_PIN2_INITIAL_VALUE,PORTB_PIN1_INITIAL_VALUE,PORTB_PIN0_INITIAL_VALUE)
#define PORTC_INITIAL_VALUE		CONC2(PORTC_PIN15_INITIAL_VALUE,PORTC_PIN14_INITIAL_VALUE,PORTC_PIN13_INITIAL_VALUE,0 ,0,0,0,0, 0,0,0,0, 0,0,0,0)


#endif
