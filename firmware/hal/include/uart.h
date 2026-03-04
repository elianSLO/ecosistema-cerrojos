#ifndef _UART_H_
#define _UART_H_

#include <avr/io.h>
#include <stdint.h>
#include <stdint.h>

#define UART_BUFFER_SIZE 32

#define UART_UBRR_CALC(baud) (((F_CPU) / ((baud) * 16UL)) - 1)

void uart_init(uint32_t baud_rate);

void uart_putc(uint8_t data);

void uart_puts(const char* s);

void uart_put_num(uint8_t val);

bool uart_available(void); 

char uart_getc(void);    

void uart_flush(void);     

#endif