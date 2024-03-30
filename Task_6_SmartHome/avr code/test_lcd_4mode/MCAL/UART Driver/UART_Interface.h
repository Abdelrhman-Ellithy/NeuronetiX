/*
 * UART_Interface.h
 *
 * Created: 2023-12-08 1:05:43 AM
 *  Author: Abdelrahman Ellithy
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_
#include "../../LIB/Types.h"
/*
void UART_Init(void);
void UART_TX_SetCallBack(void (*LocalFptr)(void));
void UART_RX_SetCallBack(void (*LocalFptr)(void));

void UART_RX_InterruptEnable(void);
void UART_RX_InterruptDisable(void);
void UART_TX_InterruptEnable(void);
void UART_TX_InterruptDisable(void);
*/

void UART_Init();
void UART_RX_InterruptEnable();
void UART_RX_InterruptDisable(void);
void UART_TX_InterruptEnable(void);
void UART_TX_InterruptDisable(void);
void UART_SendByte(u8 data);
u8 UART_Receive_NoBlock(u8*pdata);
#endif /* UART_INTERFACE_H_ */