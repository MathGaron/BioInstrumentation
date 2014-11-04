/*
 * bioMed_nRF.c
 *
 *  Created on: Oct 7, 2014
 *      Author: mathieu
 */

#include "bioMed_nRF.h"

HandleNRF nRFHL_init(bool isTX){
	HandleNRF handle;
	nRFHL_clearRxBuffer(&handle);
	nRFHL_clearTxBuffer(&handle);
	P2DIR |= BIT2; //  Set  nRF_CE  (Chip  Enable)  pin  to  output
	P2DIR |= BIT5; //  Set  nRF_CSN  (Chip  Select)  pin  to  output
	P2DIR &= ~BIT3;//  Set  nRF_IRQ  pin  to  input
	P2IE = BIT3;   //  Enable  nRF_IRQ  interrupt
	P2IES = BIT3;  //  hiow  interrupt
	P2IFG &= ~BIT3;//  clear  nRF_IRQ  inte

	nRFHL_initSPI();

	nRF_init();
	if(isTX)
		nRF_set_TX_mode();
	else
		nRF_set_RX_mode();

	nRF_clear_IRQ();

	if(isTX)
		nRF_CE_low;
	else
		nRF_CE_high;

	return handle;
}

void nRFHL_clearRxBuffer(HandleNRF *handle){
	int i;
	for(i = 0; i < 32; ++i){
		handle->RX_data_buffer[i] = 0;
	}
}
void nRFHL_clearTxBuffer(HandleNRF *handle){
	int i;
	for(i = 0; i < 32; ++i){
		handle->TX_data_buffer[i] = 0;
	}
}

void nRFHL_initSPI(){
	P2DIR |= BIT7;//  Set  CLK  pin  to  output
	P3DIR |= BIT3;//  Set  MOSI  pin  to  output
	P3DIR &= ~BIT4;//  Set  MISO  pin  to  input
	P3SEL |= BIT3 + BIT4;//  MISO  and  MOSI  pin  functionality  select
	P2SEL |= BIT7;//  CLK  pin  functionality  select
	UCA0CTL0 = UCCKPH + UCMSB + UCMST + UCMODE0 + UCSYNC;
	UCA0CTL1 = UCSSEL1 + UCSSEL0 + UCSWRST;
	UCA0BR0 = 1;//  clock prescaler  = 1
	UCA0BR1 = 0;
	UCA0CTL1 &= ~UCSWRST;  //  bring  the  state  machine  output
}

void nRFHL_download(HandleNRF *handle){
	nRF_clear_IRQ();
	nRF_download_RX_payload(handle->RX_data_buffer);
	handle->nRF_IRQ_flag = 0;
}

void nRFHL_upload(HandleNRF *handle, converter *buffer, int size){
	int i;
	for(i = 0; i < size; ++i){
		handle->TX_data_buffer[i] = buffer[i].uint;
	}
	nRF_upload_TX_payload(handle->TX_data_buffer);
	nRF_CE_high;
	__delay_cycles(85);
	nRF_CE_low;

	nRFHL_clearTxBuffer(handle);

	while(!handle->nRF_IRQ_flag);
	handle->nRF_IRQ_flag  =  0;
	nRF_clear_IRQ();

}



