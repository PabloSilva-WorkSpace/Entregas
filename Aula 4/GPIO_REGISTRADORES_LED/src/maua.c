#include "maua.h"

void turn_on(void)
{
	PIOA->PIO_CODR = (1 << PIN_LED_BLUE ) | (1 << PIN_LED_GREEN );		//Liga led azul e verde
	PIOC->PIO_SODR = (1 <<PIN_LED_RED);	
}

void turn_off(void)
{
	PIOA->PIO_SODR = (1 << PIN_LED_BLUE ) | (1 << PIN_LED_GREEN );		//Apaga led azul e verde
	PIOC->PIO_CODR = (1 << PIN_LED_RED);
}