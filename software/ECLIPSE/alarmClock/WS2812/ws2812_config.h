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
****   				ws2812_config.h				****
****      Data ostatniej mod. 03.04.2018      	****
**************************************************
****		Obs�uga diody LED WS2812			****
****			Plik konfiguracyjny				****
***************************************************/

#ifndef WS2812_CONFIG_H_
#define WS2812_CONFIG_H_

///////////////////////////////////////////////////////////////////////
// Define Reset time in �s.
//
// This is the time the library spends waiting after writing the data.
//
// WS2813 needs 300 �s reset time
// WS2812 and clones only need 50 �s
//
///////////////////////////////////////////////////////////////////////

#define ws2812_resettime  300 

///////////////////////////////////////////////////////////////////////
// Define I/O pin
///////////////////////////////////////////////////////////////////////


#define ws2812_port B     // Data port
#define ws2812_pin  7     // Data out pin

#endif /* WS2812_CONFIG_H_ */
