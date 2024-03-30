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
****   			main.c - main.hex				****
****      Data ostatniej mod. 03.04.2018      	****
**************************************************
****		G³ówny kod programu	budzika			****
***************************************************/

#include <avr/io.h>	//wejscia i wyjscia
#include <stdbool.h>	//zmienne 1-bitowe
#include <avr/eeprom.h>	//eeprom
#include <avr/interrupt.h>	//przerwania
#include <avr/wdt.h>	//watchdog
#include "I2C_TWI/i2c_twi.h"	//I2C
#include "DISPLAY/display.h"	//wyswietlacz
#include "MK_ENCODER/mk_encoder.h"	//enkoder
#include "WS2812/light_ws2812.h"	//LED WS2812

#define PCF8583_ADDR 0xA0	// adres uk³adu RTC na I2C gdy A0 --> GND
// konwersja liczby dziesiêtnej na BCD
uint8_t dec2bcd(uint8_t dec);
// konwersja liczby BCD na dziesiêtn¹
uint8_t bcd2dec(uint8_t bcd);

uint8_t bufor[4]; // rezerwacja bufora 4 bajty (czas)

// definiujemy sobie dla polepszenia czytelnoœci programu typ wyliczeniowy
// wskazuj¹cy nam póŸniej na odpowiednie indeksy w tablicy (buforze)
enum {
	ss = 1, mm, hh
};

uint8_t sekundy, minuty, godziny;	//czas
int wynik = 50;		// wartoœæ zliczana przez enkoder

//funkcje enkodera
void my_encoder( int8_t dir, int8_t w );
void enc_switch( void );
bool clk_flag=0;

//zmienne pomocnicze obs³ugi LED
uint8_t b, g, r;
struct cRGB led[1];
uint8_t menu = 0;

EEMEM unsigned char eeprom[4];

uint8_t al_hh = 0, al_mm = 0; //czas alarmu
uint8_t alarm_on=0;	//alarm uaktywniony


uint8_t alarm_is = 0;	//jest alarm
uint8_t sig_cnt=0; // zmienna pomocnicza obs³ugi wibracji
bool lock=0;	//zmienna pomocnicza obs³ugi dotyku
uint8_t drzemka=0;	//stan dzemki 0-nie ma 1-jest
uint8_t drz_hh, drz_mm;	//godzina drzemki

uint8_t lewo=0, prawo=0;	//zmienne pomocnicze obs³ugi gestów

#define LEFT !(PIND & (1<<PD5))		//czyjnik lewo
#define RIGHT !(PINB & (1<<PB2))	//czujnik prawo

//zmienne pomocnicze obs³ugi diody LED
uint16_t mod = 0;
uint8_t z=0;
uint8_t r=1, dir_r=1;
uint8_t g=60, dir_g=0;
uint8_t b=120, dir_b=0;
uint8_t sw=0;
uint8_t rp=0, gp=0, bp=0;

//obs³uga diody LED
void ws_mod(void);

#define TOUCH (PIND & (1<<PD6)) //dotyk

//obs³uga gestów
void czujka(void);

//obs³uga budzenia
void signal(void);

//funkcja obs³ugi alarmu 0- wy³¹czenie 1-w³¹czenie 2-wyciszenie
void alarm_set(uint8_t on);

//ustawienie czasu powrotu efektów LED
void ws_rst(uint8_t sek);

//sprawdzenie alarmu
void al_check(void);

//odczytanie czasu alarmu z EEPROM
void read_alarm(void);

//odczyt czasu
void read_t(uint8_t hms);

//wyswietlenie czasu
void d_ntime(void);

//wystawienie kolorów LED
void ws_put(uint8_t rr, uint8_t gg, uint8_t bb);

//g³ówna funkcja programu
int main (void)
{
	//konfuguracja przerwania zegarka
	MCUCR |=  (1<<ISC10) | (1<<ISC11);
	GICR |=(1<<INT1);
	TIMSK |= (1<<INT1);

	PORTD |= (1<<PD3);	//podci¹gniêcie pinu przerwania zegarka
	PORTD |= (1<<PD5) | (1<<PD6);	//podci¹gniêcie pinów sensorów gestów

	d_init();	//inicjalizacja wyœwietlacza

	//ustawienie pinów jako wyjœcia
	DDRB |= (1<<PB7); 	//DP
	DDRB |= (1<<PB1); 	//wibracje
	DDRD |=(1<<PD7); 	//wyjcie

	//obs³uga enkodera
	encoder_init(1);
	register_enc_callback( my_encoder );
	register_sw_callback( enc_switch );

	sei();	//zezwolenie na przerwania

	d_ntime();	//pobranie i wyswietlenie czasu
	read_alarm();	//oczytanie danych alarmu

	ws_put(0,0,0);	//wygaszenie diody

	if(alarm_on) point_a=1;	//ustawienie kropki

	bool show = 0;
	Timer3=500;	//czas do efektów LED
	Timer8=0;
	wdt_enable( WDTO_1S );	//w³¹czenie watchdog'a

	while(1){

		wdt_reset();	//reset watchdog'a

		ENCODER_EVENT(1);	//obs³uga enkodera
		czujka();	//obs³uga gestów
		signal();	//obs³uga wibracji

		switch(menu){	//obs³uga menu
		case 0: {	//normalna praca

			if(Timer4==1) ws_put(0,0,0);	//gaszenie diody po czasie
			ws_mod();	//obs³uga LED

			if(alarm_on) al_check();	//sprawdzenie alarmu

			if(TOUCH && !lock && alarm_on && alarm_is) {	//wyciszenie alarmu jesli jest
				ws_put(0,0,0);
				Timer3=700;
				lock=1;
				alarm_set(2);
			} else if(TOUCH && !lock && !alarm_is) {	//obs³uga podgl¹du budzika
				Timer3=700;
				if(!show) {	//wystawienie koloru
					if(!drzemka) ws_put(120, 60, 10);
					else ws_put(60, 200, 60);
				}
				show=1;
				point=1;
				if(!drzemka) d_time(al_hh, al_mm);	//wyswietlenie czasu dzwonienia
				clk_flag = 1;
			} else if(alarm_is){	//wizualizacja alarmu
					if(!point) point=1;
					if(!Timer7) Timer7=90;
					if(Timer7==90) d_time(100, 100);
					if(Timer7==70) d_ntime();
			} else if(clk_flag) {	//wyswietlanie czasu
				d_ntime();
				point ^=1;
				clk_flag = 0;
			}

			if(!TOUCH && lock) {	//puszczenie przycisku po alarmie
				Timer3=700;
				lock=0;
				show=0;
				ws_put(0,0,0);
			}

			if(!TOUCH && show) {	//puszczenie przycisku po podgl¹dzie (jesli nie ma drzemki)
				if(drzemka && !alarm_is ) {
					drzemka=0;
					alarm_is=0;
					PORTD &= ~(1<<PD7);
					PORTB &=~(1<<PB1);
				}
				show=0;
				ws_put(0,0,0);
			}

		} break;

		case 1: if(Timer6==1) d_time(al_hh,al_mm); break;
		case 2: if(Timer6==1) d_time(al_hh,al_mm); break;
		case 3: if(Timer6==1) d_time(godziny,minuty); break;
		case 4: if(Timer6==1) d_time(godziny,minuty); break;
		}
	}
}

//odczyt czasu
void read_t(uint8_t hms){
	TWI_read_buf(PCF8583_ADDR, 0x01, 4, bufor);
	if(!hms) godziny = bcd2dec(bufor[hh]);
	if(hms==1) 	minuty = bcd2dec(bufor[mm]);
	if(hms==2) 	sekundy = bcd2dec(bufor[ss]);
}
//wyswietlenie czasu
void d_ntime(void) {

	TWI_read_buf(PCF8583_ADDR, 0x01, 4, bufor);

	sekundy = bcd2dec(bufor[ss]);
	minuty = bcd2dec(bufor[mm]);
	godziny = bcd2dec(bufor[hh]);

	d_time(godziny, minuty);
}

//wystawienie kolorów LED
void ws_put(uint8_t rr, uint8_t gg, uint8_t bb){
	led[0].r=rr;led[0].g=gg;led[0].b=bb;
	ws2812_sendarray((uint8_t *)&led[0],3);
}

//odczytanie czasu alarmu z EEPROM
void read_alarm(void) {

	al_hh = eeprom_read_byte(&eeprom[0]);
	eeprom_busy_wait();
	al_mm = eeprom_read_byte(&eeprom[1]);
	eeprom_busy_wait();
	alarm_on = eeprom_read_byte(&eeprom[2]);
	eeprom_busy_wait();

	if((al_hh>23) || (al_mm >59) || (alarm_on>1)) {
		eeprom_write_byte(&eeprom[0], 12); //	godziny
		eeprom_busy_wait();
		eeprom_write_byte(&eeprom[1], 30); //	minuty
		eeprom_busy_wait();
		eeprom_write_byte(&eeprom[2], 0); //	godziny
		eeprom_busy_wait();
	}
}


//sprawdzenie alarmu
void al_check(void) {

	if(!drzemka) if((godziny == al_hh) && (minuty == al_mm) && !sekundy) {
		lock=0;
		Timer5=0;
		sig_cnt=0;
		alarm_is=1;
	}
	if(drzemka) {
		if((godziny == drz_hh) && (minuty == drz_mm) && !sekundy) {
			Timer5=0;
			lock=0;
			sig_cnt=0;
			alarm_is=1;
		}
	}
}

void ws_rst(uint8_t sek){	//ustawienie czasu powrotu efektów LED
	Timer4=sek*100;
}

//funkcja obs³ugi alarmu 0- wy³¹czenie 1-w³¹czenie 2-wyciszenie
void alarm_set(uint8_t on){
	if(!on) {
		drzemka=0;
		point_a = 0;
		alarm_on=0;
		alarm_is=0;
		PORTB &=~(1<<PB1);
		PORTD &=~(1<<PD7);
		ws_put(0, 255, 0);
		ws_rst(3);
	}
	if(on==1) {
		point_a = 1;
		Timer5=0;
		sig_cnt=0;
		alarm_on = 1;
		ws_put(255, 0, 0);
		ws_rst(3);
	}
	if(on==2) {
		alarm_is=0;
		PORTD &=~(1<<PD7);
		PORTB &=~(1<<PB1);
		ws_put(60, 200, 60);
		ws_rst(3);
	}

	if(on != 2) {
		eeprom_write_byte(&eeprom[2], on); //zapis trybu alarmu
	}
	eeprom_busy_wait();
}

//obs³uga gestów
void czujka(void) {
	if(Timer1 == 1) {
		lewo=0, prawo=0;
}

	switch(lewo) {

		case 0:{ if(!Timer1 && !menu)
			if(LEFT && (!prawo)) {
				Timer1=50;
				lewo++;
			} break;
		}
		case 1:{
			if(Timer1==0){
				lewo=0;
			}
			if(RIGHT) {
				lewo++;
			}
		} break;
		case 2:{
			if(Timer1==0){
				lewo=0;
			}
			if(!LEFT) {
				lewo++;
			}
		} break;
		case 3: {
			if(Timer1==0){
				lewo=0;
			}
			if(!RIGHT) {
				lewo=0;
				if( alarm_is) {
					Timer3 = 700;
					alarm_set(2);
				}
				else {
					Timer3 = 700;
					alarm_set(0);
				}
				ws_rst(1);
			}
		} break;
	}

	switch(prawo) {

	case 0:{
		if(!Timer1 && !menu) if(RIGHT && (!lewo)) {
			Timer1=50;
			prawo++;
		}
	} break;
	case 1:{
		if(Timer1==0){
			prawo=0;
		}
		if(LEFT) {
			prawo++;
		}
	} break;
	case 2:{
		if(Timer1==0){
			prawo=0;
		}
		if(!RIGHT) {
			prawo++;
		}
	} break;
	case 3: {
		if(Timer1==0){
			prawo=0;
		}
		if(!LEFT) {
			prawo=0;
			if(alarm_is) {
				alarm_set(2);
				if(!drzemka){
				drz_hh = al_hh;
				drz_mm = al_mm+1;
				if(drz_mm>59) {
					drz_mm -= 60;
					drz_hh += 1;
					if(drz_hh>23) drz_hh=0;
				}
				ws_put(255, 150, 100);
				ws_rst(3);
				Timer3 = 700;
				drzemka=1;
				} else {
					drz_mm = drz_mm+1;
					if(drz_mm>59) {
						drz_mm -= 60;
						drz_hh += 1;
						if(drz_hh>23) drz_hh=0;
					}
					ws_put(255, 150, 100);
					ws_rst(3);
					Timer3 = 700;
				}
			} else {
				Timer3 = 700;
				alarm_set(1);
			}
			ws_rst(1);
		}
	} break;
	}
}

//obs³uga diody LED
void ws_mod(void) {

	if(!Timer8) Timer8=1700;
	if(mod != Timer8) {
		mod = Timer8;
		z++;
		if((alarm_is && z==1) || (!alarm_is && z==6)){
			z=0;
			if(!Timer3) {

				if(!sw) {
					if(rp<r) rp++;
					if(gp<g) gp++;
					if(bp<b) bp++;
					if((rp==r) && (gp==g) && (bp==b)) sw=1;

					ws_put(rp, gp, bp);
				}
				if(sw) {

					if(r>200) {
						dir_r = 0;
					}
					if(r==1) {
						dir_r =1;
					}
					if(dir_r) r++;
					else r--;


					if(g>200) {
						dir_g = 0;
					}
					if(g==1) {
						dir_g =1;
					}
					if(dir_g) g++;
					else g--;


					if(b>200) {
						dir_b = 0;
					}
					if(b==1) {
						dir_b =1;
					}
					if(dir_b) b++;
					else b--;

					ws_put(r, g, b);

				}
			} else {
				rp=0; bp=0; gp=0;
				sw=0;
			}

 		}

	}

}

//obs³uga budzenia
void signal(void) {

	if(!menu && alarm_is){


	if(!Timer5) {
		sig_cnt++;
		if(!( PIND & (1<<PD7))) PORTD |= (1<<PD7);
		Timer5= 1500;
	}
		if(sig_cnt == 1 ) {
			if(!Timer2) Timer2=170;
			if(Timer2 == 160) PORTB |= (1<<PB1) ;
			if(Timer2==130) PORTB &=~(1<<PB1);

		}
		if(sig_cnt == 2 ) {
			if(!Timer2) Timer2=100;
			if(Timer2 == 50) PORTB |= (1<<PB1) ;
			if(Timer2==10) PORTB &=~(1<<PB1);

		}
		if(sig_cnt > 2 ) {
			if(!Timer2) Timer2=50;
			if(Timer2 == 40) PORTB |= (1<<PB1) ;
			if(Timer2==5) PORTB &=~(1<<PB1);
		}
		if(sig_cnt == 4) {
			ws_put(0,0,0);
			Timer3=700;
			alarm_is=0;
			PORTD &= ~(1<<PD7);
			PORTB &=~(1<<PB1);
		}
	}
}


//obs³uga krêcenia enkodera
void my_encoder( int8_t dir, int8_t w ) {

if(menu) Timer3 = 700;

	wynik += w;
	switch(menu){
	case 1: {
		if(wynik == 24) wynik = 0;
		if(wynik == -1) wynik = 23;
		d_time(wynik, al_mm);
	}
	break;
	case 2: {
		if(wynik == 60) wynik = 0;
		if(wynik == -1) wynik = 59;
		d_time(al_hh, wynik);
	}
	break;
	case 3: {
		if(wynik == 24) wynik = 0;
		if(wynik == -1) wynik = 23;
		d_time(wynik, minuty);
	}
	break;
	case 4: {
		if(wynik == 60) wynik = 0;
		if(wynik == -1) wynik = 59;
		d_time(godziny, wynik);
	}
	break;
	}
}

//obs³uga przycisku enkodera
void enc_switch( void ) {

	Timer3 = 700;

	switch(menu) {
	case 0: {
		Timer4=0;
		if(alarm_is) alarm_set(0);
		else {
		if(TOUCH) {
			ws_put(255,255,255);
			point=1;
			Timer6=30;
			wynik= godziny;
			d_time(100, minuty);
			menu=3;
		}
		else {
			point=1;
			read_alarm();
			d_time(100, al_mm);
			Timer6=30;
			wynik = al_hh;
			menu++;
			ws_put(255,255,0);
			}
		}
	}
	break;
	case 1: {
		al_hh = wynik;
		d_time(al_hh, 100);
		Timer6=30;
		wynik=al_mm;
		menu++;
	}
	break;
	case 2: {
		Timer3 = 700;
		alarm_set(1);
		ws_put(0,0,0);
		al_mm=wynik;
		eeprom_write_byte(&eeprom[0], al_hh); //	godziny
		eeprom_busy_wait();
		eeprom_write_byte(&eeprom[1], al_mm); //	minuty
		eeprom_busy_wait();
		menu=0;
	}
	break;
	case 3: {
		godziny = wynik;
		Timer6=30;
		d_time(godziny, 100);
		wynik=minuty;
		menu++;
	} break;
	case 4: {
		ws_put(0,0,0);
		minuty=wynik;
		bufor[0] = 0; // setne czêœci sekundy
		bufor[1] = 0; // sekundy
		bufor[2] = dec2bcd(minuty); // minuty
		bufor[3] = dec2bcd(godziny); // godziny
		TWI_write_buf(PCF8583_ADDR, 0x01, 4, bufor);
		menu=0;
	}
	break;
	}
}

//przerwanie od zegarka
ISR(INT1_vect) {
	clk_flag=1;
}

// konwersja liczby dziesiêtnej na BCD
uint8_t dec2bcd(uint8_t dec) {
	return ((dec / 10) << 4) | (dec % 10);
}

// konwersja liczby BCD na dziesiêtn¹
uint8_t bcd2dec(uint8_t bcd) {
	return ((((bcd) >> 4) & 0x0F) * 10) + ((bcd) & 0x0F);
}
