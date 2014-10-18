/*
 * bioMed_ADC.c
 *
 *  Created on: Oct 18, 2014
 *      Author: mathieu
 */
#include"bioMed_ADC.h"

void ADC_init(){
	int i;
	WDTCTL = WDTPW+WDTHOLD;		//  Stop  watchdog  timer
	P6DIR &= ~BIT0;				//  P6.0  input
	P6SEL |= BIT0;              //  Enable  A/D  channel  A0
	REFCTL0 &= ~REFMSTR;        //  Reset  REFMSTR  to  hand  over  control  to
								//  ADC12_A  ref  control  registers
	ADC12CTL0 = ADC12ON +		//  Turn  on  ADC12,  Sampling  time
				ADC12SHT02 +
				ADC12REFON +	//  On  Reference  Generator  and  set  to
				ADC12REF2_5V;	//  2.5V
	ADC12CTL1 = ADC12SHP;		//  Use  sampling  timer
	ADC12MCTL0 = ADC12SREF_1;
	for(  i=0; i<0x30; i++);//  Delay  for  reference  start
	ADC12CTL0 |= ADC12ENC;//  Enable  conversions
}

uint16_t ADC_get(){
	ADC12CTL0 |= ADC12SC;         //  Start  conversion
	while(!(ADC12IFG & BIT0));
	return ADC12MEM0;
}


