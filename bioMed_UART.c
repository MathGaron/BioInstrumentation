/*
 * bioMed_UART.c
 *
 *  Created on: Oct 7, 2014
 *      Author: mathieu
 */
#include "bioMed_UART.h"

void UART_init(){
	P4SEL |= BIT4+BIT5;//  P4.4,5  =  USCI_A1  TXD/RXD
	UCA1CTL1 |= UCSWRST;//  **Put  state  machine  in  reset**
	UCA1CTL1 |= UCSSEL_2;//  SMCLK
	UCA1BR0 = 72;//  8MHz  115200  (see  User's  Guide)
	UCA1BR1 = 0;//  8MHz  115200
	UCA1MCTL |= UCBRS_1  +  UCBRF_0;//  Modulation  UCBRSx=1,  UCBRFx=0
	UCA1CTL1 &= ~UCSWRST;//  **Initialize  USCI  state  machine**
}

void UART_upload(uint8_t* buffer, int size){
	int i;
	for(i = 0; i < size; ++i){
		while(!(UCA1IFG&UCTXIFG));   //  USCI_A0  TX  buffer  ready?
		UCA1TXBUF = buffer[i]; //  TX   RXed  chara
	}
}

