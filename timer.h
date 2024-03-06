/*
 * timer.h
 *
 * Created: 2/12/2024 1:32:39 PM
 *  Author: HD STORE
 */ 
#include <stdio.h>
#include <stdint.h>

void timer_CTC_init_interrupt(void);
void timer_wave_nonPWM(void);
void timer_wave_fastPWM(void);
void timer_wave_phasecorrectPWM(void);
void timer2_overflow_init_interrupt(void);
void timer1_wave_fastPWM(double value);

void PWM_Timer0_Start(uint8_t duty_cycle) ; // take period of on for this pmw signal