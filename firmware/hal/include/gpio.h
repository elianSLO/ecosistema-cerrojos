#ifndef GPIO_H
#define GPIO_H

#include <avr/io.h>
#include <stdbool.h>

// Definición de niveles lógicos
#define HIGH 1
#define LOW  0

void gpio_init(void);
void gpio_write(uint8_t pin_mask, volatile uint8_t* port, bool state);
bool gpio_read(uint8_t pin_mask, volatile uint8_t* pin_reg);

void gpio_enable_int1(void);
void gpio_disable_int1(void);
void gpio_clear_int1_flag(void);

#endif