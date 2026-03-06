#include "params.h"
#include "pinout.h"
#include <util/delay.h>
#include <avr/interrupt.h>


void PIN_SETUP(void)
{
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
	EIFR |= (1 << INTF1);			// Limpiar bandera de interrupción INT1 si estuviera activa
	EIMSK |= (1 << INT1);			// Habilita INT1
	_delay_ms(10);
}

void BEEP(uint8_t reps)
{
	uint8_t x = 10;
	for(uint8_t j = 0; j < reps; j++)
	{
		for (uint16_t i = 0; i < x * 10; i++)
		{
			PORTC |= (1 << P_BUZZER);			//	_____------______
			_delay_us(200);						// |208us|208us|
			PORTC &= ~(1 << P_BUZZER);			// |---416us---| es aproximadamente la frecuencia de resonancia del QMT12A12
			_delay_us(200);
		}
		if(reps>1)
			_delay_ms(200);
	}
}

void LED(uint8_t reps)
{
	for(uint8_t j = 0; j < reps; j++)
	{
		PORTC |= (1 << P_BUZZER);
		_delay_ms(1);
		PORTC &= ~(1 << P_BUZZER);
		if(reps>1)
			_delay_ms(10);
	}
}

void OPEN(void)
{
	//DISABLE_INT1();
	PORTD |= (1 << P_ACTIVAR);
	_delay_ms(100);
	

	PORTD &= ~(1 << P_RELE);

	// Mientras el pestillo siga adentro
	if (!(PIND & (1 << P_SEXT)) && (PIND & (1 << P_SINT))) {
		while ((PIND & (1 << P_SINT))) {
			PORTD |= (1 << P_MOTOR);
		}
	}

	PORTD |= (1 << P_RELE);
	PORTD &= ~(1 << P_MOTOR);
	_delay_ms(50);
	PORTD &= ~(1 << P_RELE);
	PORTD &= ~(1 << P_ACTIVAR);
	//ENABLE_INT1();
}

void CLOSE(void)
{
	//DISABLE_INT1();
	PORTD |= (1 << P_ACTIVAR);
	_delay_ms(100);


	if ((((PIND & (1 << P_SEXT)) && !(PIND & (1 << P_SINT)))) || ((PIND & (1 << P_SEXT)) && (PIND & (1 << P_SINT)))) {
		PORTD |= (1 << P_RELE);
		_delay_ms(100);
		do {
			PORTD |= (1 << P_MOTOR);
		} while ((PIND & (1 << P_SEXT)));
	}

	PORTD &= ~(1 << P_RELE);
	PORTD &= ~(1 << P_MOTOR);
	PORTD &= ~(1 << P_ACTIVAR);
	//ENABLE_INT1();
}

uint8_t GET_KEY(void)
{
	_delay_ms(10);
	ADMUX = (1 << REFS0) | (1 << MUX0);									// AVCC como referencia y canal ADC1 (PC1)
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);	// Habilita el ADC y establece el prescaler a 128

	uint16_t adc_value = 0;

	// Realizar 3 lecturas del ADC y calcular el promedio
	for (uint8_t i = 0; i < 3; i++)
	{
		ADCSRA |= (1 << ADSC);						// Inicia la conversión
		while (ADCSRA & (1 << ADSC));				// Espera a que la conversión termine
		adc_value += ADC;							// Acumula la lectura
		_delay_ms(5);								// Pequeño retraso entre lecturas
	}
	adc_value /= 3;  // Obtener el promedio

	if (adc_value > 80 && adc_value < 130)        return 0x00;
	else if (adc_value > 150 && adc_value < 190)  return 0x01;
	else if (adc_value > 220 && adc_value < 260)  return 0x02;
	else if (adc_value > 280 && adc_value < 320)  return 0x03;
	else if (adc_value > 340 && adc_value < 370)  return 0x04;
	else if (adc_value > 390 && adc_value < 420)  return 0x05;
	else if (adc_value > 450 && adc_value < 490)  return 0x06;
	else if (adc_value > 520 && adc_value < 560)  return 0x07;
	else if (adc_value > 580 && adc_value < 610)  return 0x08;
	else if (adc_value > 630 && adc_value < 680)  return 0x09;
	else if (adc_value > 690 && adc_value < 730)  return 0x0A;
	else if (adc_value > 750 && adc_value < 790)  return 0x0B;
	return 'E';
}
/*
uint8_t CHECK_BATTERY(void)
{
	uint8_t i;
	for(i = 0; i < 3; i++)
	{
		_delay_ms(20);
		if(GET_BATTERY() < 7.5)
		return 0xBB;
	}
	return 1;
}*/

float GET_BATTERY(void)
{
	_delay_ms(75);
	ADMUX = (1 << REFS0) | (1 << MUX1) | (1 << MUX0);					// AVcc como referencia, canal ADC3
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // Habilita el ADC y Prescaler 128
	ADCSRA |= (1 << ADSC);												// Inicia la conversión
	while (ADCSRA & (1 << ADSC));										// Espera a que la conversión termine
	uint16_t adc_value = ADC;
	ADCSRA &= ~(1 << ADEN);												// Deshabilita el ADC
	float voltage = (adc_value / 1023.0) * 5.0;
	voltage = voltage * 2;												// Debido al divisor resistivo, multiplicamos por 2 para obtener el voltaje de la batería
	return voltage;
}


ISR(INT1_vect)  
{
  irq.key = 1;
}