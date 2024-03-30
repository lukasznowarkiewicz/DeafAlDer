/*
 * mk_encoder.h
 *
 *  Created on: 15-04-2013
 *      Author: Miros�aw Karda�
 */
#ifndef MK_ENCODER_H_
#define MK_ENCODER_H_

#include <stdbool.h>


// definicja pin�w enkodera
#define ENC_PH_A 	(1<<PC0)
#define ENC_PH_B 	(1<<PC1)
#define ENC_PORT 	C

// definicja pinu przycisku enkodera
#define ENC_SW		(1<<PB2)
#define ENC_SWPORT	B

//-----------------------------------

// wyb�r timera 0 lub 2
#define TIMER		2
//-----------------------------------


#define PHASE_A         (PIN(ENC_PORT) & ENC_PH_A)
#define PHASE_B         (PIN(ENC_PORT) & ENC_PH_B)

#if TIMER == 0
	#define ENCODER_vect TIMER2_COMP_vect
#endif

#if TIMER == 2
	#define ENCODER_vect TIMER2_COMP_vect
#endif

extern volatile bool flag;


// Makra upraszczaj�ce dost�p do port�w
// *** PORT
#define PORT(x) SPORT(x)
#define SPORT(x) (PORT##x)
// *** PIN
#define PIN(x) SPIN(x)
#define SPIN(x) (PIN##x)
// *** DDR
#define DDR(x) SDDR(x)
#define SDDR(x) (DDR##x)


void register_enc_callback( void (*callback)( int8_t dir, int8_t cnt ) );
void register_sw_callback( void (*callback)( void ) );

void ENCODER_EVENT( int8_t res );

void encoder_init( uint8_t on_off );


#endif /* MK_ENCODER_H_ */
