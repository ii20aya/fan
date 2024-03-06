#include <avr/io.h>
//#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdbool.h>
#include "macro.h"
#include "DIO.h"
#include "lcd.h"
#include "dcmotor.h"
#include "ADC.h"
#include <stdio.h>
#include <math.h>
#include <float.h>
int main(void) {
	ADC_init();
	LCD_inti();
	DcMotor_Init();
	//PWM_Timer0_Start(56);
	unsigned long  preassur, temperatue , volt;
	double integralPart, fractionalPart ;
	while(1) {
		//calc part << negative tempreature are considred
		volt=ADC_Read()*2.5;
		temperatue=(ADC_Read()*0.25);
		
		
		//to know temp << + | -
		if(volt>=1000.00){ //mean tempreature is positive
		temperatue=(volt-1000)/10;
	        }
	if(volt< 1000.00) { // mean tempreature is negative
	temperatue=((1000-volt)/10);
            }

/////to get fan work
		if ((temperatue>= 100) && (temperatue<= 150)) {
			DcMotor_Rotate(CW, 100);
			}
			else if ((temperatue>= 70) && (temperatue<= 99)) {
				DcMotor_Rotate(CW, 75);
			} 
			else if ((temperatue>= 40) && (temperatue<= 69)) {
				DcMotor_Rotate(CW, 50);
			}
			else if ((temperatue>= 21) && (temperatue<= 39)) {
				DcMotor_Rotate(A_CW, 25);
			}
			else if ((temperatue<= -55) && (temperatue<= 20)) {
				DcMotor_Rotate(off, 0);
			}
			
		
		//to dispaly negative sign if nedded
		if(volt>=1000.00){ //mean tempreature is positive
		
                	}
	if(volt< 1000.00) { // mean tempreature is negative
	LCD_move_cursore(2,8);
	LCD_send_data('-');
                    }
		
		
		
		///////to send sign of celusis degree and display temp on lcd
			
		if( (temperatue>= 21) && (temperatue<= 150) ){
		LCD_move_cursore(1,1);
		LCD_send_string("FAN is ON");
		LCD_move_cursore(2,1);
		LCD_send_string("Temp = ");
		LCD_move_cursore(2,9);
		fractionalPart = modf(temperatue, &integralPart); //partitioning result into 2 rejon , integre rejon stored in integralPart variable
		lcd_sendFloat(integralPart); //show int part
		LCD_send_data('.');
		fractionalPart*=1000;
		lcd_sendFloat(fractionalPart); //show numbers after dot
		LCD_send_data(' ');
		LCD_send_data(0xDF);
		LCD_send_data(0x43);
		}	
		
		
		else if((temperatue<= -55) && (temperatue<= 20)){
			LCD_move_cursore(1,1);
			LCD_send_string("FAN is Off");
			LCD_move_cursore(2,1);
			LCD_send_string("Temp = ");
			LCD_move_cursore(2,9);
			fractionalPart = modf(temperatue, &integralPart); //partitioning result into 2 rejon , integre rejon stored in integralPart variable
			lcd_sendFloat(integralPart); //show int part
			LCD_send_data('.');
			fractionalPart*=1000;
			lcd_sendFloat(fractionalPart); //show numbers after dot
			LCD_send_data(' ');
			LCD_send_data(0xDF);
			LCD_send_data(0x43);
		}
		_delay_ms(2000);	
		LCD_clear_screen();
		
	}//end of while
	
	
}