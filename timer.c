/*
 * timer.c
 *
 * Created: 2/12/2024 1:32:21 PM
 *  Author: HD STORE
 */ 
/*
 * timer.c
 *
 * Created: 9/25/2019 7:22:07 PM
 *  Author: Mohamed Zaghlol
 */ 
 
#include "macro.h"
#include <avr/io.h>
//#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include "timer.h"
#include "DIO.h"
#include <stdio.h>
#include <stdint.h>
#define TIMER_PRESCALER 1024 // Timer0 prescaler set to 1024
#define DESIRED_PERIOD 100 // Desired interrupt period in seconds
//uint16_t compare_value = (F_CPU / (TIMER_PRESCALER * DESIRED_PERIOD)) - 1;

//void timer_CTC_init_interrupt(void)
//{
	///* select CTC mode*/
	//SET_BIT(TCCR0,WGM01);
	///* load a value in OCR0 */
	//OCR0=compare_value;
	/* select timer clock */ //prescalr is 1024
	//SET_BIT(TCCR0,CS00);
	//SET_BIT(TCCR0,CS02);
	/* enable interrupt*/
	//sei(); //active i bit
	//SET_BIT(TIMSK,OCIE0); //active enable bit to allow to send request of interrupt
//}


void timer_wave_nonPWM(void)
{
	/* set OC0 as output pin */
	SET_BIT(DDRB,3);
	/* select CTC mode*/
	SET_BIT(TCCR0,WGM01);
	/* load a value in OCR0 */
	OCR0=64;
	/* select timer clock */
	SET_BIT(TCCR0,CS00);
	SET_BIT(TCCR0,CS02);
	/* toggle OC0 on compare match*/
	SET_BIT(TCCR0,COM00);
}

void timer_wave_fastPWM(void) //////////////////////////////////////////// mood fast pmw signal 
{
	/* set OC0 as output pin */
	SET_BIT(DDRB,3);
	/* select fast PWM mode*/
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
	/* load a value in OCR0 */
	OCR0=64;
	/* select timer clock */
	SET_BIT(TCCR0,CS00);
	SET_BIT(TCCR0,CS02);
	/* Set OC0 on compare match, clear OC0 at BOTTOM,(inverting mode)*/
	SET_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
}


void timer_wave_phasecorrectPWM(void)
{
	/* set OC0 as output pin */
	SET_BIT(DDRB,3);
	/* select phase correct PWM mode*/
	SET_BIT(TCCR0,WGM00);
	/* load a value in OCR0 */
	OCR0=64;
	/* select timer clock */
	SET_BIT(TCCR0,CS00);
	SET_BIT(TCCR0,CS02);
	/* Set OC0 on compare match when up-counting. Clear OC0 on compare match when down counting.*/
	SET_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
}


void timer2_overflow_init_interrupt(void)
{
	/* select timer clock */
	SET_BIT(ASSR,AS2);
	/* select timer pre scalar */
	SET_BIT(TCCR2,CS20);
	SET_BIT(TCCR2,CS22);
	/* enable interrupt*/
	sei();
	SET_BIT(TIMSK,TOIE2);
}

void timer1_wave_fastPWM(double value) // assain time in milli sec **** not e that the clch of mc is 1 Mhz not 8 < and there is no prescalr on this clck
{
	/* set OC1A as output pin */
	SET_BIT(DDRD,5);
	/* select fast PWM mode*/
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	/* load a value in OCR1A,ICR1 */
	OCR1A=value*1000;
	ICR1=19999; //20 000 -1
	/* select timer clock, no prescaling */
	SET_BIT(TCCR1B,CS10);
	/* clear OC1A on compare match, set OC1A at BOTTOM,(non inverting mode)*/
	SET_BIT(TCCR1A,COM1A1);
}


////////////// what i work for fan project
void PWM_Timer0_Start(uint8_t duty_cycle) {
	TCNT0 = 0; // Set Timer Initial Value to 0 //???? ?? ??? ??????

	OCR0 = duty_cycle; // Set Compare Value //  ??? ???? ???? ?????? ???? ????? ?????  compare match
SET_BIT(DDRB,3);
	//DDRB = DDRB | (1 << PB3); // Configure PB3/OC0 as output pin
	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1 // ctc<< clear ,, overflow<< set
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS01);
}