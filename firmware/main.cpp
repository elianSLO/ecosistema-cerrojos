#include <avr/interrupt.h>
#include "params.h"
#include "operational.h"
#include "uart.h"
#include "fsm.h"

volatile tIRQ irq;


int main(void)
{
    PIN_SETUP();
    fsm_init();
    sei();
    while(1)
    {
        
    }
}