/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    timb_user.c
* @brief   This file implements device driver for tmb module.
* @version 1.0.0
* @date    2022/2/25
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "BAT32A237.h"
#include "timb.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
//void IRQ29_Handler(void) __attribute__((alias("tmb0_interrupt")));
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint16_t g_tmb_intTaken_a = 0U;
volatile uint16_t g_tmb_intTaken_b = 0U;
volatile uint16_t g_tmb_overflow_count_a = 0U;
volatile uint16_t g_tmb_overflow_count_b = 0U;
volatile uint32_t g_tmb_overflow_count_elc = 0UL;
volatile uint32_t g_tmb_active_width_a = 0UL;
volatile uint32_t g_tmb_active_width_b = 0UL;
volatile uint32_t g_tmb_active_width_elc = 0UL;
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: tmb0_interrupt
* @brief  timb0 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void tmb0_interrupt(void)
{
    INTC_ClearPendingIRQ(TMB_IRQn); /* clear INTTMB interrupt flag */
    uint8_t tbsr_temp = TMB->TBSR;
    uint8_t tbier_temp = TMB->TBIER;

    TMB->TBIER = 0x00U;

    if ((TMB->TBSR & _08_TMB_REGISTER_OVERFLOW) == _08_TMB_REGISTER_OVERFLOW)
    {
        TMB->TBSR = tbsr_temp & (uint8_t)~_08_TMB_REGISTER_OVERFLOW;
        g_tmb_overflow_count_a += 1UL;
        g_tmb_overflow_count_b += 1UL;
    }

#if 1
    if ((TMB->TBSR & _01_TMB_INTERRUPT_TBIMFA_ENABLE) == _01_TMB_INTERRUPT_TBIMFA_ENABLE)
    {
        TMB->TBSR = tbsr_temp & ~_01_TMB_INTERRUPT_TBIMFA_ENABLE;
        g_tmb_intTaken_a++;

        if (g_tmb_overflow_count_a == 0UL)
        {
            g_tmb_active_width_a = (TMB->TBGRA - TMB->TBGRC);
        }
        else
        {
            g_tmb_active_width_a = (TMB->TBGRA - TMB->TBGRC) + (0x10000UL * g_tmb_overflow_count_a);
            g_tmb_overflow_count_a = 0UL;
        }
    }

    if ((TMB->TBSR & _02_TMB_INTERRUPT_TBIMFB_ENABLE) == _02_TMB_INTERRUPT_TBIMFB_ENABLE)
    {
        TMB->TBSR = tbsr_temp & ~_02_TMB_INTERRUPT_TBIMFB_ENABLE;
        g_tmb_intTaken_b++;

        if (g_tmb_overflow_count_b == 0UL)
        {
            g_tmb_active_width_b = (TMB->TBGRB - TMB->TBGRD);
        }
        else
        {
            g_tmb_active_width_b = (TMB->TBGRB - TMB->TBGRD) + (0x10000UL * g_tmb_overflow_count_b);
            g_tmb_overflow_count_b = 0UL;
        }
    }
#endif
    TMB->TBIER = tbier_temp;

}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
