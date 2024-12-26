/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    tima_user.c
* @brief   This file implements device driver for TMA module.
* @version 1.0.0
* @date    2022/2/25
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "BAT32A237.h"
#include "tima.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
//void IRQ26_Handler(void) __attribute__((alias("tma0_interrupt")));
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint16_t g_tma0_underflow_count = 0U;
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: tma0_interrupt
* @brief  tima0 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void tma0_interrupt(void)
{
    INTC_ClearPendingIRQ(TMA_IRQn); /* clear INTTMA interrupt flag */
    if ((TMA->TACR0 & _20_TMA_UNDERFLOW_OCCUR) != 0U)
    {
        TMA->TACR0 &= (uint8_t)~_20_TMA_UNDERFLOW_OCCUR;
        g_tma0_underflow_count += 1U;
    }
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
