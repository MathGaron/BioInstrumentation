/*
 * bioMed_nRF.h
 *
 *  Created on: Oct 7, 2014
 *      Author: mathieu
 */

#ifndef BIOMED_NRF_H_
#define BIOMED_NRF_H_

#include "driverlib.h"
#include "nRF24L01p_lib/nRF.h"

typedef struct HandleRF{
	char nRF_IRQ_flag;
	uint8_t RX_data_buffer[32];
	uint8_t TX_data_buffer[32];
}HandleNRF;

typedef union converter
{
	uint16_t uint;
	uint8_t character[2];
}converter;

HandleNRF nRFHL_init(bool isTX);
void nRFHL_clearTxBuffer(HandleNRF *handle);
void nRFHL_clearRxBuffer(HandleNRF *handle);
void nRFHL_initSPI();
void nRFHL_download(HandleNRF *handle);
void nRFHL_upload(HandleNRF *handle, converter *buffer, int size);



#endif /* BIOMED_NRF_H_ */
