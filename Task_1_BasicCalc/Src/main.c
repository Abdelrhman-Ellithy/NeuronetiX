/**
 ******************************************************************************
 * @file           : Task_1_BasicCalc.c
 * @author         : Abdelrahman Ellithy
 * @brief          : Main program body
*/
#include "MCAL/RCC/RCC_interface.h"
#include "MCAL/GPIO/GPIO_interface.h"
#include "HAL/LCD/CLCD_interface.h"
#include "HAL/Keypad/Keypad_interface.h"
#include "LIB/STD_TYPES.h"
#include "LIB/ellithy_delay.h"
#include "LIB/Types.h"

typedef enum {
	First_Digit=0,
	Sympol,
	Second_Digit,
	Sympol_Result
}input_State;

void error(){
	u8 STR_invalid[]="Invalid Input";
	u8 STR_Error[]="Error!";
	 CLCD_voidClearScreen();
	 CLCD_voidSendString(STR_invalid);
	 CLCD_voidSetPosition(CLCD_ROW_2, CLCD_COL_1);
	 CLCD_voidSendString(STR_Error);
}

int main(void)
{
    /* Loop forever */
	RCC_InitSysClk();
	RCC_PeripheralClk(RCC_GPIOA, RCC_Enable);
	RCC_PeripheralClk(RCC_GPIOB, RCC_Enable);
	GPIO_PORT_voidInit();
	CLCD_voidInit();
	u8 pressed,result, num1,num2,sym,flag_negative=0;
	input_State input=First_Digit;
	while(1){
		if((pressed=Get_pressed())!=KPD_NotPressed){
			switch(input){
			 case First_Digit:
				 input=Sympol;
				 CLCD_voidClearScreen();
				 if(pressed <='9' && pressed>='0'){
					 num1=pressed-'0';
					 CLCD_voidSendData(pressed);
				 }
				 else if(pressed=='o' ){
						num1=0,num2=0,result=0;
						input=First_Digit;
						CLCD_voidClearScreen();
					}
				 else{
					 error();
				 }
				 break;
			 case Sympol:
				 input=Second_Digit;
				 if(pressed!='+' && pressed!='-' && pressed!='*' && pressed!='/'){
					 error();
				 }
			     else if(pressed=='o' ){
						num1=0,num2=0,result=0;
						input=First_Digit;
						CLCD_voidClearScreen();
				 }
				 else{
					 sym=pressed;
					 CLCD_voidSendData(pressed);
				 }
				 break;
			 case Second_Digit:
				 input=Sympol_Result;
				 if(pressed <='9' && pressed>='0'){
					 num2=pressed-'0';
					 CLCD_voidSendData(pressed);
					 switch(sym){
					  case '+': result=num1+num2;   break;
					  case '-':
					  	  if (num2>num1){
					  		  flag_negative=1;
					  		  result=num2-num1;
					  	  }
					  	  else{
					  		result=num1-num2;
					  	  }
					  		  break;
					  case '/': result=num1/num2;   break;
					  case '*': result=num1*num2;   break;
					 }

				 }
		    	else if(pressed=='o' ){
					num1=0,num2=0,result=0;
					input=First_Digit;
					CLCD_voidClearScreen();
				 }
				 else{
					 error();
				 }
				 break;
			 case Sympol_Result:
				 if((sym=pressed)=='='){
					 sym=pressed;
					 CLCD_voidSendData(pressed);
					 if(flag_negative){
						 CLCD_voidSendData('-');
					 }
					 CLCD_voidSendNumber(result);
				 }
			     else if(pressed=='o'){
						num1=0,num2=0,result=0;
						input=First_Digit;
						CLCD_voidClearScreen();
					}
				 else{
					 error();
				 }
				 break;
			}

		}

	}
}
