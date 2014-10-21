#include "driverlib.h"
#include "bioMed_UART.h"
#include "bioMed_nRF.h"
#include "bioMed_ADC.h"

//#define RXMODE
#define TXMODE
HandleNRF RF;

typedef union converter
{
	uint16_t uint;
	uint8_t character[2];
}converter;

#ifdef TXMODE
bool isTx = true;
#endif
#ifdef RXMODE
bool isTx = false;
#endif

int i;

int main(void) {

	WDTCTL = WDTPW + WDTHOLD;
    UCSCTL3 = SELREF_2;
    UCSCTL4 |= SELA_2;
    UCSCTL0 = 0x0000;

    do{
    	UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
    	SFRIFG1 &= ~OFIFG;
    }while(SFRIFG1&OFIFG);
    __bis_SR_register(SCG0);
    UCSCTL1  =  DCORSEL_5;//  Select  DCO  range  16MHz  operation
    UCSCTL2  |=  249;
    __bic_SR_register(SCG0);
    __delay_cycles(250000);

    UART_init();
    RF = nRFHL_init(isTx);
    P1DIR |= 0x01;


	#ifdef RXMODE
    	UART_upload("I am RX\n\r",9);
	#endif


    #ifdef TXMODE
    	UART_upload("I am TX\n\r",9);
    	ADC_init();
    	converter dataADC;
	#endif

    __bis_SR_register(GIE);
    while(1){

#ifdef RXMODE
    	if(RF.nRF_IRQ_flag == 1){
    		nRFHL_download(&RF);
    		UART_upload(RF.RX_data_buffer,32);

    	}
#endif

#ifdef TXMODE
    	dataADC.uint = ADC_get();
		nRFHL_upload(&RF,dataADC.character,2);
		__delay_cycles(1000000);
#endif

    }

}

//  nRF24L01+  IRQ
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
P1OUT |= 1;
P2IFG &= ~BIT3;  //  IFG  cleared
RF.nRF_IRQ_flag = 1;
P1OUT &= 0;
}
