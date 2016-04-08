/**
 * IMT - Rafael Corsi
 * 
 * PIO - 07
 *  Configura o PIO do SAM4S (Banco A, pino 19) para operar em
 *  modo de output. Esse pino está conectado a um LED, que em 
 *  lógica alta apaga e lógica baixa acende.
*/

#include <asf.h>
#include "Driver/pmc_maua.h"
#include "Driver/pio_maua.h"
#include "maua.h"

/**
 * Main function
 * 1. configura o clock do sistema
 * 2. desabilita wathdog
 * 3. ativa o clock para o PIOA
 * 4. ativa o controle do pino ao PIO
 * 5. desabilita a proteção contra gravações do registradores
 * 6. ativa a o pino como modo output
 * 7. coloca o HIGH no pino
 */

int main (void)
{
	//Inicializando o clock do uP
	sysclk_init();
	
	//Desabilitando o WathDog do uP
	WDT->WDT_MR = WDT_MR_WDDIS;
 
	// 29.17.4 PMC Peripheral Clock Enable Register 0
	// 1: Enables the corresponding peripheral clock.
	/*PMC->PMC_PCER0 = (1 << ID_PIOA) | (1 <<ID_PIOC) | ( 1 << ID_PIOB);*/
	_pmc_enable_clock_periferico(ID_PIOA);
	_pmc_enable_clock_periferico(ID_PIOB);
	_pmc_enable_clock_periferico(ID_PIOC);
	
	//31.6.1 PIO Enable Register
	// 1: Enables the PIO to control the corresponding pin (disables peripheral control of the pin).	
	PIOA->PIO_PER = (1 << PIN_LED_BLUE ) | (1 << PIN_LED_GREEN );
	PIOC->PIO_PER = (1 << PIN_LED_RED);
		
	// 31.6.46 PIO Write Protection Mode Register
	// 0: Disables the write protection if WPKEY corresponds to 0x50494F (PIO in ASCII).
	PIOA->PIO_WPMR = 0;
	PIOC->PIO_WPMR = 0;
	
	// 31.6.4 PIO Output Enable Register
	// value =
	//	 	1 : Enables the output on the I/O line.
	//	 	0 : do nothing
	PIOA->PIO_OER = (1 << PIN_LED_BLUE ) | (1 << PIN_LED_GREEN );
	PIOC->PIO_OER = (1 << PIN_LED_RED);
	
	// 31.6.10 PIO Set Output Data Register
	// value = 
	// 		1 : Sets the data to be driven on the I/O line.
	// 		0 : do nothing
	//PIOA->PIO_SODR |= (1 << PIN_LED_BLUE );
	//PIOA->PIO_CODR |= (1 << PIN_LED_BLUE );


	//Configurando I/O line PIOB[3] como INPUT
	PIOB->PIO_PER = (1 << PIN_BOTAO );
    PIOB->PIO_ODR = (1 << PIN_BOTAO);
	PIOB->PIO_PUER = (1 << PIN_BOTAO);

	//OPCIONAL - Debounce
	PIOB->PIO_SCDR = 1;
	PIOB->PIO_IFSCER = (1<<PIN_BOTAO);
	PIOB->PIO_IFER = (1<<PIN_BOTAO);
		
	/**
	*	Loop infinito
	*/
	while(1){
		if (!(( PIOB->PIO_PDSR >> PIN_BOTAO) & 1))
		{		
			turn_on();
			delay_ms(1000);
			turn_off();
			delay_ms(1000);
		}						
	}
}

