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
	/************************************************************************/
	/* Config uC                                                            */
	/************************************************************************/
	//Inicializando o clock do uP
	sysclk_init();
	
	//Desabilitando o WathDog do uP
	WDT->WDT_MR = WDT_MR_WDDIS;
 
	_pmc_enable_clock_periferico(ID_PIOA);
	_pmc_enable_clock_periferico(ID_PIOB);
	_pmc_enable_clock_periferico(ID_PIOC);
	
	/************************************************************************/
	/* Config leds otput                                                    */
	/************************************************************************/
	_pio_set_output(PIOA, (1 << PIN_LED_BLUE ) | (1 << PIN_LED_GREEN ), 0, 0);
	_pio_set_output(PIOC, 1 << PIN_LED_RED, 1, 0);

	/************************************************************************/
	/* Config botao input                                                   */
	/************************************************************************/
	_pio_set_input(PIOB, 1 << PIN_BOTAO, PIO_PULLUP | PIO_DEBOUNCE);
	
	/**
	*	Loop infinito
	*/
	while(1){
		
		if (!(_pio_get_output_data_status(PIOB, 1<<PIN_BOTAO)))
		{		
			//Turn on
			_pio_set(PIOA, (1<<PIN_LED_BLUE | 1<<PIN_LED_GREEN));
			_pio_clear(PIOC, (1 <<PIN_LED_RED));
			delay_ms(1000);
			//Turn off
			_pio_set(PIOC, (1 <<PIN_LED_RED));
			_pio_clear(PIOA, (1<<PIN_LED_BLUE | 1<<PIN_LED_GREEN));
			delay_ms(1000);
		}						
	}
}

