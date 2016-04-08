/**
 * @file pmc_maua.h
 * @author Rafael Corsi
 * @date 22/3/2016
 * @brief Funções para configurar o PMC do SAM4S
 */

#ifndef PMC_MAUA_H
#define PMC_MAUA_H

/*****************
 * Includes
 *****************/

/**
 * @brief STDINT possui as definições dos tipos de variáveis
 * e constantes
 */
#include <stdint.h>

/**
 * @brief Inclui as definições prévias do uc em uso
 */
#include <sam4sd32c.h>


/***************** 
 * Defines
 *****************/



/***************** 
 * PROTOTYPES 
 *****************/
/*
 * aqui é onde definimos os cabeçalhos das funções que devem
 * ser implementadas no .c 
 */

/**
 * @brief Ativa o clock no periferico
 * @param ID ID do periferico
 * @note ID não deve ser shiftado, i.e : (1 << ID_xxx). 
 * @retval 0 se bem-sucedido
 * @retval 1 se malsucedido
 */
uint32_t _pmc_enable_clock_periferico(uint32_t ID);

/**
 * @brief Desativamos o clocks no periferico
 * @param ID ID do periferico
 * @note ID não deve ser shiftado, i.e : (1 << ID_xxx). 
 * @retval 0 se bem-sucedido
 * @retval 1 se malsucedido
 */
uint32_t _pmc_disable_clock_periferico(uint32_t ID);

#endif /* _PMC_MAUA.H */