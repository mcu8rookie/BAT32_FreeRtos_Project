/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    timc.c
* @brief   This file implements device driver for TMC module.
* @version 1.0.0
* @date    2022/2/25
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "BAT32A237.h"
#include "userdefine.h"
#include "timc.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: TMC_Init
* @brief  This function initializes the TMC module.
* @param  clk - select count clock
* @return None
***********************************************************************************************************************/
void TMC_Init(tmc_clock_t clk)
{
    CGC->PER1 |= CGC_PER1_TMCEN_Msk;     /* enables input clock supply */
    TMC->TCCR2 &= (uint8_t)~_01_TMC_COUNTING_START;
    INTC_DisableIRQ(TMC_IRQn);/* disable INTTMC interrupt */
    INTC_ClearPendingIRQ(TMC_IRQn);/* clear INTTMC interrupt flag */
    /* select count clock */
    TMC->TCCR1  = clk << 5;
    /* software start and trigger enable, tm0 trigger */
    TMC->TCCR1 |=  _00_TMC_SOFTWARE_START | _08_TMC_SOFTWARE_ENABLE | _01_TMC_INTERRUPT_ENABLE;
    /* transfer counter value to buffer register, set 0000H to counter,  and then continue counting */
    TMC->TCCR2 = _06_TMC_COUNTING_TRANSFERRED_SET_0000 | _00_TMC_COUNTING_STOP;

    TMC_Start();
}

/***********************************************************************************************************************
* Function Name: TMC_Start
* @brief  This function starts TMC counter.
* @param  None
* @return None
***********************************************************************************************************************/
void TMC_Start(void)
{
    INTC_ClearPendingIRQ(TMC_IRQn);/* clear INTTMC interrupt flag */
    INTC_EnableIRQ(TMC_IRQn);/* enable INTTMC interrupt */
    TMC->TCCR2 |= _01_TMC_COUNTING_START;
}
/***********************************************************************************************************************
* Function Name: TMC_Stop
* @brief  This function stops TMC counter.
* @param  None
* @return None
***********************************************************************************************************************/
void TMC_Stop(void)
{
    INTC_DisableIRQ(TMC_IRQn);/* disable INTTMC interrupt */
    INTC_ClearPendingIRQ(TMC_IRQn);/* clear INTTMC interrupt flag */
    TMC->TCCR2 &= (uint8_t)~_01_TMC_COUNTING_START;
}
/***********************************************************************************************************************
* Function Name: TMC_Get_BufferValue
* @brief  This function get TMC buffer value.
* @param  None
* @return buffer value
***********************************************************************************************************************/
uint32_t TMC_Get_BufferValue(void)
{
    uint32_t value;
    if (1U == (TMC->TCSR & 0x01U))
    {
        TMC->TCSR &= ~0x01U;  /* clear TCOVF flag */ 
        value = TMC->TCBUF + 0x10000U;
    }
    else
    {
        value = TMC->TCBUF;
    }

    return (value);
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
