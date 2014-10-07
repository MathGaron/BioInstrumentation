/*
 * bioMed_UART.c
 *
 *  Created on: Oct 7, 2014
 *      Author: mathieu
 */
#include "bioMed_UART.h"

void UART_init(){

}

void UART_send_bytes(uint8_t* buffer, int size){
	int i;
	for(i=0; i < size; ++i){
		while(!(UCA1IFG&UCTXIFG));//  USCI_A0  TX  buffer  ready?
		UCA1TXBUF = buffer[i];
	}
}

