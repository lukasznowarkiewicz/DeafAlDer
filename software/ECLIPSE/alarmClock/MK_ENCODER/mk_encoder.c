/****      			DeafAIDer    				****
****         Uniwersalny domowy system 			****
**** sygnalizacyjno-alarmowy dla nies�ysz�cych	****
****************************************************
****  				Autorzy: 					****
****    �ukasz Nowarkiewicz, Jacek Martyniak  	****
****  Opiekun: dr inz. Dariusz Mostowski    	****
**** Zesp� Szk� Elektryczno-elektronicznych 	****
****    im. prof. M.T. Hubera w Szczecinie    	****
**************************************************
****   				mk_encoder.c				****
****      Data ostatniej mod. 03.04.2018      	****
**************************************************
****				Obs�uga enkodera			****
****		Kod zawiera funkcje biblioteki		****
****************************************************
**** 		Modyfikacja: Miros�aw Karda�		****
**** 		na podstawie biblioteki z:			****
**** www.mikrocontroller.net/articles/Drehgeber ****
***************************************************/

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "mk_encoder.h"


volatile int8_t ed;

volatile int8_t enc_cnt;
volatile uint8_t enc_flag;

const int8_t table[16] PROGMEM = {0,1,-1,0,-1,0,0,1,1,0,0,-1,0,-1,1,0};

// obs�uga enkodera
void (*enc_callback)( int8_t dir, int8_t cnt );

void register_enc_callback( void (*callback)( int8_t dir, int8_t cnt ) ) {
	enc_callback = callback;
}

// obs�uga klawisza
void (*sw_callback)( void );

void register_sw_callback( void (*callback)( void ) ) {
	sw_callback = callback;
}

void encoder_init( uint8_t on_off ) {

	if( !on_off ) {
#if TIMER == 0
		TCCR0 &= ~(1<<CS02);        // stop timer0
		TIMSK &= ~(1<<OCIE0);					// disable interrupt
#endif

#if TIMER == 2
		TCCR2 &= ~(1<<CS22);			        // stop timer2
		TIMSK &= ~(1<<OCIE2);					// disable interrupt
#endif
		return;
	}

	PIN(ENC_PORT)  &= ~(ENC_PH_A|ENC_PH_B);
	PORT(ENC_PORT) |= ENC_PH_A|ENC_PH_B;

	PIN(ENC_SWPORT) &= ~ENC_SW;
	PORT(ENC_SWPORT) |= ENC_SW;


#if TIMER == 0
	TCCR0 = (1<<WGM01);					// tryb CTC
	TCCR0 |= (1<<CS02);         // prescaler 64
	OCR0 = (uint8_t)(F_CPU / 64 / 1000 );           // 1ms  --> poprawka do VIDEO
	TIMSK |= (1<<OCIE0);
#endif

#if TIMER == 2
	TCCR2 |= (1<<WGM21);					// tryb CTC
	TCCR2 |= (1<<CS22);			        // prescaler 64
	OCR2 = (uint8_t)(F_CPU / 64 / 1250 );           // 1ms
	TIMSK |= (1<<OCIE2);
#endif

}

void ENCODER_EVENT( int8_t res ) {
	uint8_t sreg;
	int8_t ecnt;
	static uint8_t key_lock;

	// obs�uga zdarzeia enkodera
	if( enc_callback && enc_flag  ) {

		sreg = SREG;
		cli();
		ecnt = ed>>2; ed &= 3;
		SREG = sreg;


		if(ecnt>1) ecnt=1;
		if(ecnt<-1) ecnt=-1;

		if(!res) res=1;

		if(ecnt) {
			enc_callback( ecnt*-1, ecnt*res );
		}
		enc_flag=0;

	}

	// obs�uga zdarzenia przycisku
	if( sw_callback ) {
		if( !key_lock && !(PIN(ENC_SWPORT) & ENC_SW) ) {
			key_lock=1;

			// reakcja na wcini�cie klawisza
			sw_callback();
		}
		else if( key_lock && (PIN(ENC_SWPORT) & ENC_SW ) ) {
			if( !++key_lock ) {
				// ewentualnie reakcja na zwolnienie klawisza ;)
				//sw_callback();
			}
		}
	}

}


// Przerwanie timera co 1 ms
ISR( ENCODER_vect , ISR_NOBLOCK ) {

    static int8_t last;
    static int8_t last_ed;

    last = (last << 2)  & 0x0F;
    if (PHASE_A) last |=2;
    if (PHASE_B) last |=1;
    ed += pgm_read_byte( &table[last] );

    if( last_ed != ed ) enc_flag=1;

    last_ed=ed;
}
