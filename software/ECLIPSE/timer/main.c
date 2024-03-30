//  Created on: 29-03-2018

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "MK_ENCODER/mk_encoder.h"
#include "d_led.h"
#include <avr/eeprom.h>

// w³asne funkcje do zarejestrowania
void my_encoder( int8_t dir, int8_t w );
void enc_switch( void );
uint8_t wynik=0, speed;
volatile uint16_t n1=0;
volatile uint16_t Timer1, Timer2;
uint8_t set=0;
volatile uint8_t clk=0;
volatile uint8_t flag_sek=0;
uint8_t min=0, sek=0;
int min_t=0;
EEMEM unsigned char eeprom[1];

int main (void)
{

	min = eeprom_read_byte(&eeprom[0]);
	eeprom_busy_wait();
	if((min>95) || (!min)){
		min=30;
		eeprom_write_byte(&eeprom[0], 30); //minity
		eeprom_busy_wait();
	}



	DDRB |= (1<<PB3);
	encoder_init(1);
	register_enc_callback( my_encoder );
	register_sw_callback( enc_switch );

	//start timer
	TCCR0 |= (1<<CS00);
	TIMSK |= (1<<TOIE0);

	sei();

	d_init();
	disp(100);

	while(1){
		ENCODER_EVENT(speed);

		if(!set) {
			if(!Timer1) Timer1=40;
			if(Timer1==40) disp(100);
			if(Timer1==20) disp(101);
		}
		if(set==2) {
			if(!Timer1) Timer1=18;
			if(Timer1==18) disp(101);
			if(Timer1==12 ) disp(min_t);
			if(flag_sek) {
				flag_sek=0;
				clk++;
				if(clk==10) {
					sek++;
					if(sek==60) {
						sek=0;
						min_t--;
						if(!min_t) {
							PORTB |= (1<<PB3);
							set=3;
						}
					}
					clk=0;
//					wynik++;
//					disp(wynik);
				}
			}
		}
		if(set==3) {
			if(!Timer1) Timer1=8;
			if(Timer1==8) {
				d_cy1(0);
				d_cy2(0);
			}
			if(Timer1==4) {
				disp(101);
			}
		}





	}

}

void my_encoder( int8_t dir, int8_t w ) {

	switch(set){
	case 0: {
		disp(min);
		set=1;
	} break;
	case 1: {
		if((min>29) && (w>0)) min += 5*w;
		if(min<30) min += w;
		if((min==30) && (w<0)) min += w;

		if((min>30) && (w<0)) min += 5*w;
		if(min>99) min=95;
		if(!min) min=1;
		if(set==1) disp(min);
	} break;
	case 2: {
		Timer1=12;
		if((min_t>29) && (w>0)) min_t += 5*w;
		if(min_t<30) min_t += w;
		if((min_t==30) && (w<0)) min_t += w;

		if((min_t>30) && (w<0)) min_t += 5*w;
		if(min_t>99) min_t=95;
		if(!min_t) min_t=1;
	} break;
	}

}

void enc_switch( void ) {

	switch(set){
	case 0: {
		set=1;
		disp(min);
	} break;
	case 1: {
		eeprom_write_byte(&eeprom[0], min); //minity
		eeprom_busy_wait();
		sek=0;
		min_t = min;
		set=2;
	} break;
	case 2: {
		set=0;
		disp(100);
	} break;
	case 3: {
		PORTB &= ~(1<<PB3);
		disp(100);
		set=0;
	} break;

	}

//	wynik=0;
//	n1=0;
//	clk=0;
//	flag_sek=0;
//	disp(wynik);
}

ISR(TIMER0_OVF_vect) {

	uint16_t n;

	if(!n1) {
	n = Timer1;		/* 100Hz Timer1 */
	if (n) Timer1 = --n;
	n = Timer2;		/* 100Hz Timer2 */
	if (n) Timer2 = --n;
	}
	n1++;
	if(n1>3220) {//3125
		n1=0;
		flag_sek=1;
	}
}
