#ifndef PARAMS_H_
#define PARAMS_H_
#include <inttypes.h>



typedef struct  
{
	volatile uint8_t key;
	volatile uint8_t wdt;
	volatile uint8_t timer1;
}tIRQ;


extern volatile tIRQ irq;

#endif