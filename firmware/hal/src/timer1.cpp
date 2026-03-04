#include "timer1.h"
#include "params.h"
#include <avr/interrupt.h>

// Referencia a la estructura global de banderas definida en main o parameters
extern volatile tIRQ irq; 

void timer1_init_1s(void) {

    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1  = 0;

    // Cargar valor de comparación para 1Hz (1 segundo)
    // Valor = (16,000,000 / (1024 * 1)) - 1 = 15624
    OCR1A = 15624;

    // Activar modo CTC (Clear Timer on Compare Match)
    TCCR1B |= (1 << WGM12);

    // Habilitar interrupción por comparación A
    TIMSK1 |= (1 << OCIE1A);

    // Configurar Prescaler 1024 e iniciar el reloj
    TCCR1B |= (1 << CS12) | (1 << CS10);
}

void timer1_stop(void) {
    // Detener el reloj apagando los bits de prescaler
    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
}

ISR(TIMER1_COMPA_vect) {
    irq.timer1 = 1; 
}