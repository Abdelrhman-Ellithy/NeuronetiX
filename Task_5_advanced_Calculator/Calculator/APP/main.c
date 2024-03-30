/*
 * avr_test.c
 * Created: 2023-07-22 2:47:20 PM
 * Author : Abdelrhman Ellithy
 */
#include "../HAL/Keypad Driver/Keypad.h"
#include "../HAL/LCD Driver/CLCD_private.h"
#define F_CPU 8000000UL
#define   stack_size     5
#define NUL '\0'
#include <util/delay.h>
typedef struct {
    u8 arr[stack_size];
    char top;
}stack_sym;
typedef struct {
    u16 arr[stack_size];
    char top;

}stack_operandes;
stack_operandes operands;
stack_sym operators;
void push_oparnd(u16 data)
{
    if(operands.top==stack_size)return ;
    operands.top+=1;
    operands.arr[operands.top]=data;
}
void push_operator(u16 data)
{
    if(operators.top==stack_size) return;
    operators.top+=1;
    operators.arr[operators.top]=data;

}
u16 pop_oparnd()
{
    if((operands.top)>=0)
    {
        u16 data =operands.arr[operands.top];
        operands.top-=1;
        return data;
    }
    return NUL;
}
u8 pop_operator()
{
    if((operators.top)>=0)
    {
        u8 data =operators.arr[operators.top];
        operators.top-=1;
        return data;
    }
    return NUL;
}
int main(void)
{
	CLCD_voidInit();
	Keypad_init();
    operands.top=-1;
    operators.top=-1;
    u8 Pressed_Char;
    u8 i=0,j=0; u16 ans=0,flag_restart=FALSE;
    while(1)
    {

        if ((Pressed_Char=Get_pressed())!=NotPressed && Pressed_Char!='=')
		{
			 if(flag_restart==TRUE) {
				 CLCD_voidClearScreen();
				 u16 num=pop_oparnd();
				 CLCD_voidSendNumber(num);
				 push_oparnd(num);
				 flag_restart=FALSE;
			 }
            CLCD_voidSendData(Pressed_Char);
            if (Pressed_Char>='0'&& Pressed_Char<='9')
			{
                ans*=10;
                ans+=Pressed_Char-'0';
            }
            else if (Pressed_Char=='+'||Pressed_Char=='-'||Pressed_Char=='*'||Pressed_Char=='/')
			{
                push_oparnd(ans);
                if(operators.arr[operators.top]=='*'||operators.arr[operators.top]=='/')
				{
                    u16 ans,op1,op2; u8 sym= pop_operator();
                    op2= pop_oparnd();
                    op1=pop_oparnd();
                    if(sym=='*') ans=op2*op1;
                    else ans=op1/op2;
                    push_oparnd(ans);
                }
                else if(operators.arr[operators.top]=='-' && Pressed_Char=='+')
				{
                    u16 ans,op1,op2; u8 sym= pop_operator();
                    op2= pop_oparnd();
                    op1=pop_oparnd();
                    if(sym=='-') ans=op1-op2;
                    push_oparnd(ans);
                }
                switch (Pressed_Char)
				{
                    case '+':
                        push_operator(Pressed_Char);
                        break;
                    case '*':
                        push_operator(Pressed_Char);
                        break;
                    case '-':
                        push_operator(Pressed_Char);
                        break;
                    case '/':
                        push_operator(Pressed_Char);
                        break;
                }
                ans=0;
            }
            i++;
        }
        else if(Pressed_Char=='=')
		{
            push_oparnd(ans);
            u8 sym;
            while ( (sym= pop_operator() ) !=NUL )
			{
                u16 ans,op1,op2;
                op2= pop_oparnd();
                op1= pop_oparnd();
                switch (sym)
				{
                    case '+':
                        ans=op2+op1;
                        break;
                    case '*':
                        ans=op2*op1;
                        break;
                    case '-':
                        ans=op1-op2;
                        break;
                    case '/':
                        ans=op1/op2;
                        break;
                }
                push_oparnd(ans);
            }
            ans=pop_oparnd();
			CLCD_voidSetPosition(CLCD_ROW_2,CLCD_COL_1);
			u8 str[]="Result : ";
			CLCD_voidSendString(str);
			CLCD_voidSendNumber(ans);
            push_oparnd(ans);
			flag_restart=TRUE;
		
        }

    }

}
