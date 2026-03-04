#include "uart.h"
#include <avr/interrupt.h>

// Buffer circular para recepción
static volatile char rx_buffer[UART_BUFFER_SIZE];
static volatile uint8_t rx_head = 0;
static volatile uint8_t rx_tail = 0;

void uart_init(uint32_t baud_rate) {
    uint16_t ubrr_val = UART_UBRR_CALC(baud_rate);
    
    UBRR0H = (uint8_t)(ubrr_val >> 8);
    UBRR0L = (uint8_t)ubrr_val;

    // UCSR0B: Habilitar TX, RX y la Interrupción de Recepción (RXCIE0)
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    
    // UCSR0C: 8 bits de datos, 1 bit de parada (8N1)
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_putc(uint8_t data) {
    // Esperar a que el buffer de transmisión esté vacío (UDRE0 bit)
    while (!(UCSR0A & (1 << UDRE0)));
    
    // Cargar el dato al registro de datos de la UART
    UDR0 = data;
}

void uart_puts(const char* s) {
    while (*s) {
        uart_putc(*s++);
    }
}

void uart_put_num(uint8_t val) {

    if (val <= 9) {
        uart_putc(val + '0');
    } else 
    if (val == 0x0A){
        uart_putc('*');
    } else
    if (val == 0x0B){
        uart_putc('#');
    } else{
        uart_putc('?'); 
    }
}


bool uart_available(void) {
    return (rx_head != rx_tail);
}

char uart_getc(void) {
    if (rx_head == rx_tail) return 0; // Buffer vacío
    
    char data = rx_buffer[rx_tail];
    rx_tail = (rx_tail + 1) % UART_BUFFER_SIZE;
    return data;
}

void uart_flush(void) {
    rx_head = rx_tail;
}

ISR(USART_RX_vect) {
    char data = UDR0;
    uint8_t next_head = (rx_head + 1) % UART_BUFFER_SIZE;

    // Si el buffer no está lleno, guardamos el dato
    if (next_head != rx_tail) {
        rx_buffer[rx_head] = data;
        rx_head = next_head;
    }
}