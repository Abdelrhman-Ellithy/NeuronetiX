/*
 * Servo_interface.h
 *
 * Created: 2023-12-03 1:20:34 PM
 *  Author: Abdelrahman Ellithy
 */ 

#ifndef SERVO_H_
#define SERVO_H_

#include "../../MCAL/DIO Driver/DIO_Interface.h"
#include "../../MCAL/Timers/Timers_Interface.h"

typedef enum{
	Clock_Wize,
	UntiClock_Wize
}Direction_type;

typedef enum{
	servo_OCR1A=0,
	servo_OCR1B
}Comp_Reg;

typedef struct{
	GPIO_PORT * ServoPort;
	u8 ServoPin ;
	Comp_Reg reg ;
	Direction_type ServorDir;
}Servo;

void SERVO_Init(void);
void SERVO_SetAngle(u8 angle);

#endif /* SERVO_H_ */