#include "adc.h"
#include <util/delay.h>

void adc_init(void) {
    // Referencia: AVCC con capacitor en AREF
    // Prescaler: 128 (Precisión máxima para 16MHz)
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

void adc_disable(void) {
    ADCSRA &= ~(1 << ADEN);
}

uint16_t adc_read(uint8_t channel) {
    // Seleccionar canal (limpia los 4 bits bajos de MUX y pone el canal)
    ADMUX = (ADMUX & 0xF0) | (channel & 0x07);
    
    // Iniciar conversión
    ADCSRA |= (1 << ADSC);
    
    // Esperar a que termine (polling)
    while (ADCSRA & (1 << ADSC));
    
    return ADC;
}

uint16_t adc_read_average(uint8_t channel, uint8_t samples) {
    uint32_t accumulator = 0;
    for (uint8_t i = 0; i < samples; i++) {
        accumulator += adc_read(channel);
        _delay_ms(1); 
    }
    return (uint16_t)(accumulator / samples);
}