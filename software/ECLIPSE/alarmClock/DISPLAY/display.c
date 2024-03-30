/****      			DeafAIDer    				****
****         Uniwersalny domowy system 			****
**** sygnalizacyjno-alarmowy dla nies³ysz¹cych	****
****************************************************
****  				Autorzy: 					****
****    £ukasz Nowarkiewicz, Jacek Martyniak  	****
****  Opiekun: dr inz. Dariusz Mostowski    	****
**** Zespó³ Szkó³ Elektryczno-elektronicznych 	****
****    im. prof. M.T. Hubera w Szczecinie    	****
**************************************************
****   				display.c					****
****      Data ostatniej mod. 03.04.2018      	****
**************************************************
****			Obs³uga wyœwietlacza			****
****		Kod zawiera funkcje biblioteki		****
****************************************************
**** 		Autor: Jacek Martyniak				****
**** 		na podstawie bilbioteki 			****
**** 		   Miros³awa Kardasia				****
***************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "display.h"
#include <avr/pgmspace.h>
#include <util/delay.h>

volatile uint8_t cy1;
volatile uint8_t cy2;
volatile uint8_t cy3;
volatile uint8_t cy4;
volatile uint8_t point, point_a;
volatile uint16_t n1=0;
volatile uint16_t Timer1, Timer2, Timer3, Timer4, Timer5, Timer6, Timer7, Timer8; //Timery programowe 100Hz

void d_init(void) {

	//ustawienie pinów wyswietlacza jako wyjœcia
	DDRD |= (1<<PD0)|(1<<PD1)|(1<<PD2)| (1<<PD4);

	//pin kropki jako wyjœcie
	DDRB |= (1<<PB6);

	//ustawienie pinów danych (cyfr) na wyjœcia
	DDRC |= (1<<PC0)|(1<<PC1)|(1<<PC2)|(1<<PC3);

	//w³¹czenie Timera 0
	TCCR0 |= (1<<CS01) | (1<<CS00);
	TIMSK |= (1<<TOIE0);

}

//wyœwietlenie czasu
void d_time(uint8_t hh, uint8_t mm) {


	if(hh<24) {
		cy4=hh/10;
		cy3=hh%10;
	} else {
		cy3=10;
		cy4=10;
	}

	if(mm<60) {
	cy2=mm/10;
	cy1=mm%10;
	} else {
		cy2=10;
		cy1=10;
	}
}

//przeliczenie cyfry w formacie BCD na kod dla sterownika wyœwietlacza
uint8_t conv(uint8_t cy) {

	return (cy & 0b1) | ((cy<<1) & 0b1100) | ((cy>>2) & 0b10);
}

ISR(TIMER0_OVF_vect) {

	uint16_t n;

	if(!n1) {
	n = Timer1;		/* 100Hz Timer1 */
	if (n) Timer1 = --n;
	n = Timer2;		/* 100Hz Timer2 */
	if (n) Timer2 = --n;
	n = Timer3;		/* 100Hz Timer3 */
	if (n) Timer3 = --n;
	n = Timer4;		/* 100Hz Timer4 */
	if (n) Timer4 = --n;
	n = Timer5;		/* 100Hz Timer5 */
	if (n) Timer5 = --n;
	n = Timer6;		/* 100Hz Timer6 */
	if (n) Timer6 = --n;
	n = Timer7;		/* 100Hz Timer7 */
	if (n) Timer7 = --n;
	n = Timer8;		/* 100Hz Timer8 */
	if (n) Timer8 = --n;
	}
	n1++;

	if(n1>4) n1=0;

		static uint8_t licznik = 1;
		if(licznik<8) PORTD = ( PORTD & 0b11101000 ) | licznik;	//wystawienie KATOD - wybranie 1 z 4 wyœwietlaczy
		else PORTD = ( PORTD & 0b11101000 ) | 0b10000;

		//wystawienie ANOD - segmentów
		if(licznik == 1) {		//cyfra 1
			PORTB &= ~(1<<PB6);
			PORTC = conv(cy4);
		}
		else if(licznik == 2) {	//cyfra 2
			PORTC = conv(cy3);
			if(point) PORTB |= (1<<PB6);
			else PORTB &= ~(1<<PB6);
		}
		else if(licznik == 4) {	//cyfra 3
			PORTB &= ~(1<<PB6);
			PORTC = conv(cy2);
		}
		else if(licznik == 8) {	//cyfra 4
			if(point_a) PORTB |= (1<<PB6);
			else PORTB &= ~(1<<PB6);
			PORTC = conv(cy1);
		}

		licznik <<= 1;
		if(licznik>8) licznik = 1;
}
