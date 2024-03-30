//  Created on: 31-12-2013

#include <avr/io.h>
#include <avr/interrupt.h>
#include "d_led.h"
#include <avr/pgmspace.h>


volatile uint8_t cy1;
volatile uint8_t cy2;
volatile uint8_t cy3;
volatile uint8_t cy4;
volatile uint8_t point;
volatile uint8_t sek;

void d_init(void)
{
	//disp_1
	DDRB |= SEG_A_1|SEG_B_1|SEG_F_1|SEG_G_1;
	DDRC |= SEG_C_1|SEG_H_1;
	DDRD |= SEG_D_1|SEG_E_1;

	PORTB |= (SEG_A_1|SEG_B_1|SEG_F_1|SEG_G_1);
	PORTC |= (SEG_C_1|SEG_H_1);
	PORTD |= (SEG_D_1|SEG_E_1);

	//disp_2
	DDRD |= SEG_A_2|SEG_B_2|SEG_C_2|SEG_F_2|SEG_G_2|SEG_H_2;
	DDRC |= SEG_D_2|SEG_E_2;

	PORTD |= (SEG_A_2|SEG_B_2|SEG_F_2|SEG_G_2|SEG_C_2|SEG_H_2);
	PORTC |= (SEG_D_2|SEG_E_2);

}

void disp(uint8_t l) {

	if(l<100){
		if(l>9) d_cy1(l/10);
		else d_cy1(11);
		d_cy2(l%10);
	}
	if(l==100) {
		d_cy1(10);
		d_cy2(10);
	}
	if(l==101){
		d_cy1(11);
		d_cy2(11);
	}

}

void d_cy2(uint8_t cy) {

	cy2=cy;

	PORTD |= (SEG_A_2|SEG_B_2|SEG_F_2|SEG_G_2|SEG_C_2|SEG_H_2);
	PORTC |= (SEG_D_2|SEG_E_2);

	switch(cy2){

	case 0: {
		PORTD &= ~ (SEG_A_2|SEG_B_2|SEG_F_2|SEG_C_2);
		PORTC &= ~ (SEG_D_2|SEG_E_2);
	} break;
	case 1: {
		PORTD &= ~ (SEG_B_2|SEG_C_2);
	} break;
	case 2: {
		PORTD &= ~ (SEG_A_2|SEG_B_2|SEG_G_2);
		PORTC &= ~ (SEG_D_2|SEG_E_2);
	} break;
	case 3: {
		PORTD &= ~ (SEG_A_2|SEG_B_2|SEG_G_2|SEG_C_2);
		PORTC &= ~ (SEG_D_2);
	} break;
	case 4: {
		PORTD &= ~ (SEG_B_2|SEG_F_2|SEG_G_2|SEG_C_2);
	} break;
	case 5: {
		PORTD &= ~ (SEG_A_2|SEG_F_2|SEG_G_2|SEG_C_2);
		PORTC &= ~ (SEG_D_2);
	} break;
	case 6: {
		PORTD &= ~ (SEG_A_2|SEG_F_2|SEG_G_2|SEG_C_2);
		PORTC &= ~ (SEG_D_2|SEG_E_2);
	} break;
	case 7: {
		PORTD &= ~ (SEG_A_2|SEG_B_2|SEG_C_2);
	} break;
	case 8: {
		PORTD &= ~ (SEG_A_2|SEG_B_2|SEG_F_2|SEG_G_2|SEG_C_2);
		PORTC &= ~ (SEG_D_2|SEG_E_2);
	} break;
	case 9: {
		PORTD &= ~ (SEG_A_2|SEG_B_2|SEG_F_2|SEG_G_2|SEG_C_2);
		PORTC &= ~ (SEG_D_2);
	} break;
	case 10: {
		PORTD &= ~ (SEG_G_2);
	} break;
	}

}

void d_cy1(uint8_t cy) {

	cy1=cy;

	PORTB |= (SEG_A_1|SEG_B_1|SEG_F_1|SEG_G_1);
	PORTC |= (SEG_C_1|SEG_H_1);
	PORTD |= (SEG_D_1|SEG_E_1);

	switch(cy1){

	case 0: {
		PORTB &= ~ (SEG_A_1|SEG_B_1|SEG_F_1);
		PORTC &= ~ (SEG_C_1);
		PORTD &= ~ (SEG_D_1|SEG_E_1);
	} break;
	case 1: {
		PORTB &= ~ (SEG_B_1);
		PORTC &= ~ (SEG_C_1);
	} break;
	case 2: {
		PORTB &= ~ (SEG_A_1|SEG_B_1|SEG_G_1);
		PORTD &= ~ (SEG_D_1|SEG_E_1);
	} break;
	case 3: {
		PORTB &= ~ (SEG_A_1|SEG_B_1|SEG_G_1);
		PORTC &= ~ (SEG_C_1);
		PORTD &= ~ (SEG_D_1);
	} break;
	case 4: {
		PORTB &= ~ (SEG_B_1|SEG_F_1|SEG_G_1);
		PORTC &= ~ (SEG_C_1);
	} break;
	case 5: {
		PORTB &= ~ (SEG_A_1|SEG_F_1|SEG_G_1);
		PORTC &= ~ (SEG_C_1);
		PORTD &= ~ (SEG_D_1);
	} break;
	case 6: {
		PORTB &= ~ (SEG_A_1|SEG_F_1|SEG_G_1);
		PORTC &= ~ (SEG_C_1);
		PORTD &= ~ (SEG_D_1|SEG_E_1);
	} break;
	case 7: {
		PORTB &= ~ (SEG_A_1|SEG_B_1);
		PORTC &= ~ (SEG_C_1);
	} break;
	case 8: {
		PORTB &= ~ (SEG_A_1|SEG_B_1|SEG_F_1|SEG_G_1);
		PORTC &= ~ (SEG_C_1);
		PORTD &= ~ (SEG_D_1|SEG_E_1);
	} break;
	case 9: {
		PORTB &= ~ (SEG_A_1|SEG_B_1|SEG_F_1|SEG_G_1);
		PORTC &= ~ (SEG_C_1);
		PORTD &= ~ (SEG_D_1);
	} break;
	case 10: {
		PORTB &= ~ (SEG_G_1);
	} break;
	}

}



