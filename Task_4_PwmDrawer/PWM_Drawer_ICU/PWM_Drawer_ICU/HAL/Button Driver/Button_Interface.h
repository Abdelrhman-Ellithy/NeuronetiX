/*
 * Button.h
 *
 * Created: 2023-07-20 2:54:39 PM
 *  Author: Abdelrahman Ellithy
 */ 
#ifndef BUTTON_H_
#define BUTTON_H_


#define BTN_Pressed DIO_PIN_HIGH
#define BTN_NotPressed DIO_PIN_LOW
typedef enum{
	Inputfloating=0,
	PullDown,
	PullUp,
}PullState;
typedef struct{
	GPIO_PORT* BtnPort;
	u8 BtnPin;
	PullState BtnPullState;
}Button;

void Button_read(Button * Btn, u8 *val);

#endif /* BUTTON_H_ */