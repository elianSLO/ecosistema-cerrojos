#include "gpio.h"
#include "params.h" 
#include <util/delay.h>

void gpio_init(void) {
    DDRD &= ~(1 << P_TX);			
	PORTD |= (1 << P_TX);
	DDRD &= ~(1 << P_RX);
	PORTD |= (1 << P_RX);
	DDRD |= (1 << P_MOTOR);
	PORTD &= ~(1 << P_MOTOR);
	DDRD &= ~(1 << P_IRQ);
	PORTD |= (1 << P_IRQ);
	DDRD |= (1 << P_RELE);
	PORTD &= ~(1 << P_RELE);
	DDRD &= ~(1 << P_SINT);
	PORTD |= (1 << P_SINT);
	DDRD &= ~(1 << P_SEXT);
	PORTD |= (1 << P_SEXT);
	DDRD |= (1 << P_ACTIVAR);
	PORTD &= ~(1 << P_ACTIVAR);

	DDRB |= (1 << P_LIBRE1);
	PORTB &= ~(1 << P_LIBRE1);
	DDRB |= (1 << P_LIBRE2);
	PORTB &= ~(1 << P_LIBRE2);
	DDRB |= (1 << P_PERIF);
	PORTB &= ~(1 << P_PERIF);
	DDRB |= (1 << P_MOSI);
	PORTB &= ~(1 << P_MOSI);
	DDRB |= (1 << P_MISO);
	PORTB &= ~(1 << P_MISO);
	DDRB |= (1 << P_SCK);
	PORTB &= ~(1 << P_SCK);
	//PB6 Y PB7 CRYSTAL, NO SE CONFIGURAN.

	DDRC &= ~(1 << PC0);
	PORTC |= (1 << PC0);

	DDRC &= ~(1 << P_TECLA);
	PORTC &= ~(1 << P_TECLA);
	
	DDRC |= (1 << P_BUZZER);
	PORTC &= ~(1 << P_BUZZER);

	DDRC &= ~(1 << P_BATERIA);
	PORTC &= ~(1 << P_BATERIA);

	DDRC &= ~(1 << P_SDA);
	PORTC |= (1 << P_SDA);
	DDRC &= ~(1 << P_SCL);
	PORTC |= (1 << P_SCL);

	EICRA |= (1 << ISC11);			// ISC11 = 1, ISC10 = 0: Interrupción en el borde de bajada
	EICRA &= ~(1 << ISC10);
	gpio_clear_int1_flag();
	//EIMSK |= (1 << INT1);			// Habilita INT1
	_delay_ms(10);
}

void hal_gpio_write(uint8_t pin_mask, volatile uint8_t* port, bool state) {
    if (state) *port |= (1 << pin_mask);
    else       *port &= ~(1 << pin_mask);
}

bool hal_gpio_read(uint8_t pin_mask, volatile uint8_t* pin_reg) {
    return (*pin_reg & (1 << pin_mask));
}

void hal_gpio_enable_int1(void) {
    EIMSK |= (1 << INT1);
}

void hal_gpio_disable_int1(void) {
    EIMSK &= ~(1 << INT1);
}

void hal_gpio_clear_int1_flag(void) {
    EIFR |= (1 << INTF1);
}