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
****   				i2c_twi.h					****
****      Data ostatniej mod. 03.04.2018      	****
**************************************************
****			Obs³uga enkodera				****
****		Kod zawiera nag³ówki funkcji		****
****************************************************
**** 		Autor: Miros³aw Kardaœ				****
***************************************************/

#ifndef I2C_TWI_H_
#define I2C_TWI_H_

#define ACK 1
#define NACK 0

// ustawiamy prêdkoœæ na I2C w kHz (standardowa prêdkoœæ to 100 kHz)  i2cSetBitrate( 100 );
void i2cSetBitrate(uint16_t bitrateKHz);


void TWI_start(void);
void TWI_stop(void);
void TWI_write(uint8_t bajt);
uint8_t TWI_read(uint8_t ack);

void TWI_write_buf( uint8_t SLA, uint8_t adr, uint8_t len, uint8_t *buf );
void TWI_read_buf(uint8_t SLA, uint8_t adr, uint8_t len, uint8_t *buf);

#endif /* I2C_TWI_H_ */
