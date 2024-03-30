/**
 ******************************************************************************
 * @file           : Task_3_IntermediateCalc.c
 * @author         : Abdelrahman Ellithy
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
	Second_Digit
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
	u8 pressed, pressed_prevouis, sym,flag_negative=0,neg='-', flag_Clear=0;
	u32 result, num1=0,num2=0, char_count=0;
	input_State input=First_Digit;
	while(1){
		if((pressed=Get_pressed())!=KPD_NotPressed)
		{
			if( pressed_prevouis==pressed && pressed =='='){
				num1=0,num2=0,result=0;
				CLCD_voidClearScreen();
			}
			else{
				if( flag_Clear==1){
					CLCD_voidClearScreen();
					flag_Clear=0;
				}
				switch(input)
				{
				    case First_Digit:
				    	pressed_prevouis=pressed;

				    	if(pressed <='9' && pressed >='0' ){
				    	num1*=10;
				    	num1+=pressed-'0';
						CLCD_voidSendData(pressed);
						char_count++;
				    	}
				    	else if(pressed=='-' && char_count==0){
				    		CLCD_voidSendData(neg);
				    		flag_negative=1;
				    		char_count++;
				    	}
				    	else if( (pressed=='*' || pressed=='/' || pressed=='+' || pressed=='-') && char_count!=0 ){
							CLCD_voidSendData(pressed);
							sym=pressed;
							input=Second_Digit;
							char_count++;
						}

				    	else if(pressed=='o'){
							num1=0,num2=0,result=0,char_count=0;
							CLCD_voidClearScreen();
						}
				    	else{
				    		error();
				    		flag_Clear=1;
				    	}
				    	break;

				    case Second_Digit:
				    	char_count++;
				    	pressed_prevouis=pressed;
				    	if(pressed <='9' && pressed >='0' ){
				    	num2*=10;
				    	num2+=pressed-'0';
				    	CLCD_voidSendData(pressed);
				    	}
				    	else if(pressed=='-'){
				    		CLCD_voidSendData(neg);
				    		flag_negative^=1;
				    	}
				    	else if(pressed=='='){
				    		flag_Clear=1;
							CLCD_voidSendData(pressed);
							switch(sym){
							   case '-':
								   if(num2>num1){
									   result=num2-num1;
									   flag_negative=1;
								   }
								   else{
									   result=num1-num2;
								   }
									   break;
							   case '/':
								   result=num1/num2;
								   break;
							   case '*':
								   result=num1*num2;
								   break;
							   case '+':
								   result=num1+num2;
								   break;
							}
							if(flag_negative){
								CLCD_voidSendData(neg);
								flag_negative=0;
							}
							CLCD_voidSendNumber(result);
							num1=0;
							num2=0;
							char_count=0;
							input=First_Digit;
							sym='+';
						}
				    	else if(pressed=='o' ){
							num1=0,num2=0,result=0,char_count=0;
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

}

