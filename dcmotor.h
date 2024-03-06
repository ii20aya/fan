/*
 * dcmotor.h
 *
 * Created: 3/2/2024 6:09:33 PM
 *  Author: HD STORE
 */ 

#include <stdio.h>
#include <stdint.h>
void DcMotor_Init(void);

typedef enum { //creat new type that represent how dc motor will work 
	off, CW, A_CW //off //clockwise ..anti-colckwise
} DcMotor_State; //type of these variable


void DcMotor_Rotate(DcMotor_State state, uint8_t speed);
