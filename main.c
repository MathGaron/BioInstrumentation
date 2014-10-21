#include "driverlib.h"
#include "bioMed_UART.h"
#include "bioMed_nRF.h"

#define RXMODE
//#define TXMODE
HandleNRF RF;

#ifdef TXMODE
bool isTx = true;
#endif
#ifdef RXMODE
bool isTx = false;
#endif

int i;

int main(void) {

    WDT_A_hold(WDT_A_BASE);
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
    	UART_upload("I am RX",7);
	#endif


    #ifdef TXMODE
    	UART_upload("I am TX",7);
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
		uint8_t buffer[2] = {50, 51};
		nRFHL_upload(&RF, buffer, 2);
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
