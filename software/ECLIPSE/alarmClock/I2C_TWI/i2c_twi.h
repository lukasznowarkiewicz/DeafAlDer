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
****   				i2c_twi.h					****
****      Data ostatniej mod. 03.04.2018      	****
**************************************************
****			Obs�uga enkodera				****
****		Kod zawiera nag��wki funkcji		****
****************************************************
**** 		Autor: Miros�aw Karda�				****
***************************************************/

#ifndef I2C_TWI_H_
#define I2C_TWI_H_

#define ACK 1
#define NACK 0

// ustawiamy pr�dko�� na I2C w kHz (standardowa pr�dko�� to 100 kHz)  i2cSetBitrate( 100 );
void i2cSetBitrate(uint16_t bitrateKHz);


void TWI_start(void);
void TWI_stop(void);
void TWI_write(uint8_t bajt);
uint8_t TWI_read(uint8_t ack);

void TWI_write_buf( uint8_t SLA, uint8_t adr, uint8_t len, uint8_t *buf );
void TWI_read_buf(uint8_t SLA, uint8_t adr, uint8_t len, uint8_t *buf);

#endif /* I2C_TWI_H_ */
