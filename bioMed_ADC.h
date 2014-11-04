/*
 * bioMed_ADC.h
 *
 *  Created on: Oct 18, 2014
 *      Author: mathieu
 */

#ifndef BIOMED_ADC_H_
#define BIOMED_ADC_H_

#include "driverlib.h"

void ADC_init();
uint16_t ADC_get();
uint8_t ADC_get_8bit();


#endif /* BIOMED_ADC_H_ */
