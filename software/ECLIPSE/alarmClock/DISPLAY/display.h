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
****   				display.h					****
****      Data ostatniej mod. 03.04.2018      	****
**************************************************
****			Obs³uga wyœwietlacza			****
****		Kod zawiera nag³ówki funkcji		****
***************************************************/

#ifndef DISPLAY_H_
#define DISPLAY_H_

void d_init( void);
void d_time(uint8_t hh, uint8_t mm);

extern volatile uint16_t Timer1, Timer2, Timer3, Timer4, Timer5, Timer6, Timer7, Timer8;

extern volatile uint8_t cy1;
extern volatile uint8_t cy2;
extern volatile uint8_t cy3;
extern volatile uint8_t cy4;
extern volatile uint8_t point, point_a;


#endif /* DISPLAY_H_ */
