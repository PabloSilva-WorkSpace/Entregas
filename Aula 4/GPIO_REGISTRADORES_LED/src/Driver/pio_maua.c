#include "pio_maua.h"


void _pio_set_output(Pio *p_pio, const uint32_t ul_mask, const uint32_t ul_default_level, const uint32_t ul_pull_up_enable) //?
{
	p_pio->PIO_WPMR = ul_mask;
	
	if(ul_default_level)
		_pio_set(p_pio, ul_mask);
	else
		_pio_clear(p_pio, ul_mask);
		
	_pio_pull_up(p_pio, ul_mask, ul_pull_up_enable);
	
	p_pio->PIO_OER = ul_mask;
	p_pio->PIO_PER = ul_mask;
}


void _pio_set_input(Pio *p_pio, const uint32_t ul_mask, const uint32_t ul_attribute) 
{
	
	if(ul_attribute & PIO_PULLUP)
		_pio_pull_up(p_pio, ul_mask, 1);
		
	if(ul_attribute & PIO_DEGLITCH){
		p_pio->PIO_IFER   = ul_mask;
		p_pio->PIO_IFSCDR = ul_mask;
	}
	
	if(ul_attribute & PIO_DEBOUNCE){
		p_pio->PIO_IFER   = ul_mask;
		p_pio->PIO_IFSCER = ul_mask;	
	}
		
	p_pio->PIO_ODR = ul_mask;
	p_pio->PIO_PER = ul_mask;
}


void _pio_pull_up(Pio *p_pio, const uint32_t ul_mask, const uint32_t ul_pull_up_enable) //?
{
	if(ul_pull_up_enable)
		p_pio->PIO_PUER = ul_mask;	//liga pull up
	else
		p_pio->PIO_PUDR = ul_mask;	//DESLIGA pull up

}


void _pio_pull_down(Pio *p_pio, const uint32_t ul_mask, const uint32_t ul_pull_down_enable) //?
{
	p_pio->PIO_PPDER = ul_mask;	//liga pull down
}


void _pio_set(Pio *p_pio, const uint32_t ul_mask)
{
	p_pio->PIO_SODR = ul_mask;
}


void _pio_clear(Pio *p_pio, const uint32_t ul_mask)
{
	p_pio->PIO_CODR = ul_mask;
}


uint32_t _pio_get_output_data_status(const Pio *p_pio, const uint32_t ul_mask) 
{
	if(p_pio->PIO_PDSR & ul_mask)
		return(1);
	return(0);
	
}