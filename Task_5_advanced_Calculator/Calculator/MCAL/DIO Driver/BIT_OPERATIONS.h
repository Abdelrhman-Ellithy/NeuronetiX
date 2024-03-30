/*
 * BIT_OPERATIONS.h
 *
 * Created: 2023-08-05 10:37:02 AM
 *  Author: lenovo
 */ 


#ifndef BIT_OPERATIONS_H_
#define BIT_OPERATIONS_H_

#define SET_REG(Reg)				Reg|=0xFF
#define CLEAR_REG(Reg)				Reg&=0x00
#define TOGGLE_REG(Reg)				Reg^=0xFF
#define WRITE_REG(Reg,Value)		Reg=Value
#define SET_BIT(Reg,bit)			Reg|=(1<<bit)
#define CLEAR_BIT(Reg,bit)			Reg&=~(1<<bit)
#define TOGGLE_BIT(Reg,bit)			Reg^=(1<<bit)
#define GET_BIT(Reg,bit)			(Reg>>pinnumber)&0x01
#define MAKE_input(port,pin)		port&=~(1<<pin)
#define MAKE_output(port,pin)		port|=(1<<pin)

#define BitAccess_set( pin)			pin |= 1
#define BitAccess_clear( pin)		pin &= 0
#define BitAccess_toggle( pin)		pin ^= 1
#define BitAccess_input( pin)		pin &= 0
#define BitAccess_output( pin)		pin |= 1

# define sei()  __asm__ __volatile__ ("sei" ::)
# define cli()  __asm__ __volatile__ ("cli" ::)
# define reti()  __asm__ __volatile__ ("reti" ::)


#endif /* BIT_OPERATIONS_H_ */