//  Created on: 31-12-2013


#ifndef _d_led_h
#define _d_led_h

#include <avr/io.h>

#define LED_DATA PORTD
#define LED_DATA_DIR DDRD
#define ANODY_PORT PORTC
#define ANODY_DIR DDRC

#define SEG_A_1 (1<<PB1)
#define SEG_B_1 (1<<PB0)
#define SEG_C_1 (1<<PC2)
#define SEG_D_1 (1<<PD3)
#define SEG_E_1 (1<<PD4)
#define SEG_F_1 (1<<PB6)
#define SEG_G_1 (1<<PB7)
#define SEG_H_1 (1<<PC3)

#define SEG_A_2 (1<<PD6)
#define SEG_B_2 (1<<PD5)
#define SEG_C_2 (1<<PD1)
#define SEG_D_2 (1<<PC5)
#define SEG_E_2 (1<<PC4)
#define SEG_F_2 (1<<PD7)
#define SEG_G_2 (1<<PD0)
#define SEG_H_2 (1<<PD2)

#define PORT_A_1 B
#define PORT_B_1 D
#define PORT_C_1 C
#define PORT_D_1 D
#define PORT_E_1 D
#define PORT_F_1 B
#define PORT_G_1 B
#define PORT_H_1 C

#define PORT_A_2 D
#define PORT_B_2 D
#define PORT_C_2 D
#define PORT_D_2 C
#define PORT_E_2 C
#define PORT_F_2 D
#define PORT_G_2 D
#define PORT_H_2 D

extern volatile uint8_t cy1;
extern volatile uint8_t cy2;

extern volatile uint8_t point;

void d_init(void);
void d_cy1(uint8_t cy);
void d_cy2(uint8_t cy);
void disp(uint8_t l);

// Makra upraszczaj¹ce dostêp do portów
// *** PORT
#define PORT(x) SPORT(x)
#define SPORT(x) (PORT##x)
// *** PIN
#define PIN(x) SPIN(x)
#define SPIN(x) (PIN##x)
// *** DDR
#define DDR(x) SDDR(x)
#define SDDR(x) (DDR##x)

#endif
