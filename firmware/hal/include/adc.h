#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <avr/io.h>

void adc_init(void);

// Realiza una lectura simple de un canal (0-7)
uint16_t adc_read(uint8_t channel);

// Realiza un promedio de N lecturas para mayor estabilidad
uint16_t adc_read_average(uint8_t channel, uint8_t samples);

// Apaga el ADC para ahorrar batería
void hal_adc_disable(void);

#endif