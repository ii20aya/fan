/*
 * dcmotor.c
 *
 * Created: 3/2/2024 6:09:13 PM
 *  Author: HD STORE
 */ 

#include "dcmotor.h"
#include "macro.h"
#include "DIO.h"
#include "timer.h"
#include <stdio.h>
#include <stdint.h>
#include <float.h>

void DcMotor_Init(void) {
	/*out pin*/
//DIO_SET_BINDIR('D', 2, 1); // enable pin
DIO_SET_BINDIR('D', 0, 1); //  pin1
DIO_SET_BINDIR('D', 1, 1); // pin2

	/*Stop*/
	DIO_WRITE('D', 0, 0);
	DIO_WRITE('D', 1, 0);
}

void DcMotor_Rotate(DcMotor_State state, uint8_t speed) {
	uint8_t duty_cycle;
	switch (state) {
		case off:
		DIO_WRITE('D', 0, 0);
		DIO_WRITE('D', 1, 0);
		break;
		case CW: //with direction of clock
		DIO_WRITE('D', 0, 1);
		DIO_WRITE('D', 1, 0);
		break;
		case A_CW:
		DIO_WRITE('D', 0, 0);
		DIO_WRITE('D', 1, 1);
		break;
	}
	/*Speed*/
	if (speed > 100) {
		speed = 100; //max << mean i cannot exceed this limit
	}
	if (speed < 0) { //no negative
		speed = 0;
	}
	duty_cycle = ((float) speed / 100) * 255; //peroid of on/ totl peroid
	PWM_Timer0_Start(duty_cycle);

}
