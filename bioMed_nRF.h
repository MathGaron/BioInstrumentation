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
	char RX_data_buffer[32];
	char TX_data_buffer[32];
}HandleNRF;

HandleNRF nRFHL_init(bool isTX);
void nRFHL_clearTxBuffer(HandleNRF *handle);
void nRFHL_clearRxBuffer(HandleNRF *handle);
void nRFHL_initSPI();
void nRFHL_download(HandleNRF *handle);
void nRFHL_upload(HandleNRF *handle,char *buffer, int size);



#endif /* BIOMED_NRF_H_ */
