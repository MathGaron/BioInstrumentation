#include "driverlib.h"

int main(void) {

    WDT_A_hold(WDT_A_BASE);
    //PA.x output
	GPIO_setAsOutputPin(
			GPIO_PORT_PA,
			GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2 + GPIO_PIN3 +
			GPIO_PIN4 + GPIO_PIN5 + GPIO_PIN6 + GPIO_PIN7 +
			GPIO_PIN8 + GPIO_PIN9 + GPIO_PIN10 + GPIO_PIN11 +
			GPIO_PIN12 + GPIO_PIN13 + GPIO_PIN14 + GPIO_PIN15
			);


	//Set all PA pins HI
	GPIO_setOutputHighOnPin(

			GPIO_PORT_PA,
			GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2 + GPIO_PIN3 +
			GPIO_PIN4 + GPIO_PIN5 + GPIO_PIN6 + GPIO_PIN7 +
			GPIO_PIN8 + GPIO_PIN9 + GPIO_PIN10 + GPIO_PIN11 +
			GPIO_PIN12 + GPIO_PIN13 + GPIO_PIN14 + GPIO_PIN15
			);

	//Enter LPM4 w/interrupts enabled
	__bis_SR_register(LPM4_bits + GIE);

	//For debugger
	__no_operation();


    return (0);
}
