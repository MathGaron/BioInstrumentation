/*
 * bioMed_UART.h
 *
 *  Created on: Oct 7, 2014
 *      Author: mathieu
 */

#ifndef BIOMED_UART_H_
#define BIOMED_UART_H_

#include "driverlib.h"

void UART_init();
void UART_send_bytes(uint8_t* buffer, int size);
void UART_upload(char* buffer, int size);

#endif /* BIOMED_UART_H_ */
