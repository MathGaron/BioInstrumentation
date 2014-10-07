#include "driverlib.h"
#include "bioMed_UART.h"

int main(void) {

    WDT_A_hold(WDT_A_BASE);
    UART_init();
    int size = 2;
    unsigned char buff[size];
    buff[0] = 0;
    buff [1] = 100;

    while(1){
    	UART_send_bytes(buff,size);
    }



	//Enter LPM4 w/interrupts enabled
	__bis_SR_register(LPM4_bits + GIE);

	//For debugger
	__no_operation();


    return (0);
}
