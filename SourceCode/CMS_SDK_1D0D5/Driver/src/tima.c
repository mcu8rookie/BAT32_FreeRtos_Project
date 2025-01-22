/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    tima.c
* @brief   This file implements device driver for TMA module.
* @version 1.0.0
* @date    2022/2/25
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "BAT32A237.h"
#include "userdefine.h"
#include "tima.h"
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
//volatile uint16_t g_tma0_ta0_value = _03E8_TMA_TA0_VALUE;   /* TA0 = 1000 */
volatile uint16_t g_tma0_ta0_value = _FFFF_TMA_TA0_VALUE;   /* TA0 = 65535 */
/* Start user code for global. Do not edit comment generated khere */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: TMA0_IntervalTimer
* @brief  The TMA operates as interval timer.
* @param  clk - select count source clock
* @param  num - specify the count value
* @return None
***********************************************************************************************************************/
void TMA0_IntervalTimer(tma_clock_t clk, uint16_t num)
{
    CGC->PER1 |= CGC_PER1_TMAEN_Msk;     /* enables input clock supply */
    TMA->TACR0 &= (uint8_t)~_01_TMA_COUNT_START;
    INTC_DisableIRQ(TMA_IRQn);           /* disable INTTMA interrupt */
    INTC_ClearPendingIRQ(TMA_IRQn);      /* clear INTTMA interrupt flag */
    TMA->TAMR0 = clk | _00_TMA_MODE_TIMER;
    if(clk == TMA_COUNT_SOURCE_FIL)
    {
        CGC->OSMC = 0x10U;  /* WUTMMCK0 = 1 */
    }
    TMA->TA0 = num - 1;
    //TMA0_Start();
}
/***********************************************************************************************************************
* Function Name: TMA0_SquareOutput
* @brief  The TMA operates as square output.
* @param  clk - select count source clock
* @param  num - specify the count value
* @return None
***********************************************************************************************************************/
void TMA0_SquareOutput(tma_clock_t clk, uint16_t num)
{
    CGC->PER1 |= CGC_PER1_TMAEN_Msk;     /* enables input clock supply */
    TMA->TACR0 &= (uint8_t)~_01_TMA_COUNT_START;
    INTC_DisableIRQ(TMA_IRQn);/* disable INTTMA interrupt */
    INTC_ClearPendingIRQ(TMA_IRQn);/* clear INTTMA interrupt flag */
    TMA->TAMR0 = clk | _01_TMA_MODE_PULSE_OUTPUT;
    if(clk == TMA_COUNT_SOURCE_FIL)
    {
        CGC->OSMC = 0x10U;  /* WUTMMCK0 = 1 */
    }
    TMA->TAIOC0 = _00_TMA_TAO_OUTPUT_DISABLE | _00_TMA_TAIO_POLARITY_0;
    TMA->TA0 = num - 1;
    /* Set TAIO pin */
    TAIO_PORT_SETTING();
    TMA0_Start();
}
/***********************************************************************************************************************
* Function Name: TMA0_EventCount
* @brief  The TMA operates as event counter.
* @param  edge - specify the valid edge and count condition
* @param  num - specify the count value
* @return None
***********************************************************************************************************************/
void TMA0_EventCount(tma_edge_t edge, uint16_t num)
{
    CGC->PER1 |= CGC_PER1_TMAEN_Msk;     /* enables input clock supply */
    TMA->TACR0 &= (uint8_t)~_01_TMA_COUNT_START;
    INTC_DisableIRQ(TMA_IRQn);/* disable INTTMA interrupt */
    INTC_ClearPendingIRQ(TMA_IRQn);/* clear INTTMA interrupt flag */
    TMA->TA0 = num - 1;

    if(edge == TMA_RISING_EDGE_ALWAYS)
    {
        // always enabled rising edge
        TMA->TAMR0 = _00_TMA_TAIO_POLARITY_ONE | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _00_TMA_EVENT_ENABLE_ALWAYS | _00_TMA_TAIO_POLARITY_0;
    }
    if(edge == TMA_FALLING_EDGE_ALWAYS)
    {
        // always enabled falling edge
        TMA->TAMR0 = _00_TMA_TAIO_POLARITY_ONE | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _00_TMA_EVENT_ENABLE_ALWAYS | _01_TMA_TAIO_POLARITY_1;
    }
    if(edge == TMA_BOTH_EDGE_ALWAYS)
    {
        // always enabled both edge
        TMA->TAMR0 = _08_TMA_TAIO_POLARITY_BOTH | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _00_TMA_EVENT_ENABLE_ALWAYS;
    }
    if(edge == TMA_RISING_EDGE_INTP4_L)
    {
        // INTP4 L period rising edge
        TMA->TAMR0 = _00_TMA_TAIO_POLARITY_ONE | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _40_TMA_EVENT_ENABLE_INTP4 | _00_TMA_TAIO_POLARITY_0;
        TMA->TAISR0 = _00_TMA_PWM_POLARITY_L;
    }
    if(edge == TMA_RISING_EDGE_INTP4_H)
    {
        // INTP4 H period rising edge
        TMA->TAMR0 = _00_TMA_TAIO_POLARITY_ONE | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _40_TMA_EVENT_ENABLE_INTP4 | _00_TMA_TAIO_POLARITY_0;
        TMA->TAISR0 = _04_TMA_PWM_POLARITY_H;
    }
    if(edge == TMA_FALLING_EDGE_INTP4_L)
    {
        // INTP4 L period falling edge
        TMA->TAMR0 = _00_TMA_TAIO_POLARITY_ONE | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _40_TMA_EVENT_ENABLE_INTP4 | _01_TMA_TAIO_POLARITY_1;
        TMA->TAISR0 = _00_TMA_PWM_POLARITY_L;
    }
    if(edge == TMA_FALLING_EDGE_INTP4_H)
    {
        // INTP4 H period falling edge
        TMA->TAMR0 = _00_TMA_TAIO_POLARITY_ONE | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _40_TMA_EVENT_ENABLE_INTP4 | _01_TMA_TAIO_POLARITY_1;
        TMA->TAISR0 = _04_TMA_PWM_POLARITY_H;
    }
    if(edge == TMA_BOTH_EDGE_INTP4_L)
    {
        // INTP4 L period both edge
        TMA->TAMR0 = _08_TMA_TAIO_POLARITY_BOTH | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _40_TMA_EVENT_ENABLE_INTP4;
        TMA->TAISR0 = _00_TMA_PWM_POLARITY_L;
    }
    if(edge == TMA_BOTH_EDGE_INTP4_H)
    {
        // INTP4 H period both edge
        TMA->TAMR0 = _08_TMA_TAIO_POLARITY_BOTH | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _40_TMA_EVENT_ENABLE_INTP4;
        TMA->TAISR0 = _04_TMA_PWM_POLARITY_H;
    }
    if(edge == TMA_RISING_EDGE_TMIOD1_L)
    {
        // TMIOD1 L period rising edge
        TMA->TAMR0 = _00_TMA_TAIO_POLARITY_ONE | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _80_TMA_EVENT_ENABLE_TIMEROUTSIGNAL | _00_TMA_TAIO_POLARITY_0;
        TMA->TAISR0 = _00_TMA_PWM_POLARITY_L | _00_TMA_PWM_TMIOD1;
    }
    if(edge == TMA_RISING_EDGE_TMIOD1_H)
    {
        // TMIOD1 H period rising edge
        TMA->TAMR0 = _00_TMA_TAIO_POLARITY_ONE | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _80_TMA_EVENT_ENABLE_TIMEROUTSIGNAL | _00_TMA_TAIO_POLARITY_0;
        TMA->TAISR0 = _04_TMA_PWM_POLARITY_H | _00_TMA_PWM_TMIOD1;
    }
    if(edge == TMA_FALLING_EDGE_TMIOD1_L)
    {
        // TMIOD1 L period falling edge
        TMA->TAMR0 = _00_TMA_TAIO_POLARITY_ONE | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _80_TMA_EVENT_ENABLE_TIMEROUTSIGNAL | _01_TMA_TAIO_POLARITY_1;
        TMA->TAISR0 = _00_TMA_PWM_POLARITY_L | _00_TMA_PWM_TMIOD1;
    }
    if(edge == TMA_FALLING_EDGE_TMIOD1_H)
    {
        // TMIOD1 H period falling edge
        TMA->TAMR0 = _00_TMA_TAIO_POLARITY_ONE | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _80_TMA_EVENT_ENABLE_TIMEROUTSIGNAL | _01_TMA_TAIO_POLARITY_1;
        TMA->TAISR0 = _04_TMA_PWM_POLARITY_H | _00_TMA_PWM_TMIOD1;
    }
    if(edge == TMA_BOTH_EDGE_TMIOD1_L)
    {
        // TMIOD1 L period both edge
        TMA->TAMR0 = _08_TMA_TAIO_POLARITY_BOTH | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _80_TMA_EVENT_ENABLE_TIMEROUTSIGNAL;
        TMA->TAISR0 = _00_TMA_PWM_POLARITY_L | _00_TMA_PWM_TMIOD1;
    }
    if(edge == TMA_BOTH_EDGE_TMIOD1_H)
    {
        // TMIOD1 H period both edge
        TMA->TAMR0 = _08_TMA_TAIO_POLARITY_BOTH | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _80_TMA_EVENT_ENABLE_TIMEROUTSIGNAL;
        TMA->TAISR0 = _04_TMA_PWM_POLARITY_H | _00_TMA_PWM_TMIOD1;
    }
    if(edge == TMA_RISING_EDGE_TMIOC1_L)
    {
        // TMIOC1 L period rising edge
        TMA->TAMR0 = _00_TMA_TAIO_POLARITY_ONE | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _80_TMA_EVENT_ENABLE_TIMEROUTSIGNAL | _00_TMA_TAIO_POLARITY_0;
        TMA->TAISR0 = _00_TMA_PWM_POLARITY_L | _01_TMA_PWM_TMIOC1;
    }
    if(edge == TMA_RISING_EDGE_TMIOC1_H)
    {
        // TMIOC1 H period rising edge
        TMA->TAMR0 = _00_TMA_TAIO_POLARITY_ONE | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _80_TMA_EVENT_ENABLE_TIMEROUTSIGNAL | _00_TMA_TAIO_POLARITY_0;
        TMA->TAISR0 = _04_TMA_PWM_POLARITY_H | _01_TMA_PWM_TMIOC1;
    }
    if(edge == TMA_FALLING_EDGE_TMIOC1_L)
    {
        // TMIOC1 L period falling edge
        TMA->TAMR0 = _00_TMA_TAIO_POLARITY_ONE | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _80_TMA_EVENT_ENABLE_TIMEROUTSIGNAL | _01_TMA_TAIO_POLARITY_1;
        TMA->TAISR0 = _00_TMA_PWM_POLARITY_L | _01_TMA_PWM_TMIOC1;
    }
    if(edge == TMA_FALLING_EDGE_TMIOC1_H)
    {
        // TMIOC1 H period falling edge
        TMA->TAMR0 = _00_TMA_TAIO_POLARITY_ONE | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _80_TMA_EVENT_ENABLE_TIMEROUTSIGNAL | _01_TMA_TAIO_POLARITY_1;
        TMA->TAISR0 = _04_TMA_PWM_POLARITY_H | _01_TMA_PWM_TMIOC1;
    }
    if(edge == TMA_BOTH_EDGE_TMIOC1_L)
    {
        // TMIOC1 L period both edge
        TMA->TAMR0 = _08_TMA_TAIO_POLARITY_BOTH | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _80_TMA_EVENT_ENABLE_TIMEROUTSIGNAL;
        TMA->TAISR0 = _00_TMA_PWM_POLARITY_L | _01_TMA_PWM_TMIOC1;
    }
    if(edge == TMA_BOTH_EDGE_TMIOC1_H)
    {
        // TMIOC1 H period both edge
        TMA->TAMR0 = _08_TMA_TAIO_POLARITY_BOTH | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _80_TMA_EVENT_ENABLE_TIMEROUTSIGNAL;
        TMA->TAISR0 = _04_TMA_PWM_POLARITY_H | _01_TMA_PWM_TMIOC1;
    }
    if(edge == TMA_RISING_EDGE_TO02_L)
    {
        // TO02 L period rising edge
        TMA->TAMR0 = _00_TMA_TAIO_POLARITY_ONE | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _80_TMA_EVENT_ENABLE_TIMEROUTSIGNAL | _00_TMA_TAIO_POLARITY_0;
        TMA->TAISR0 = _00_TMA_PWM_POLARITY_L | _02_TMA_PWM_TO02;
    }
    if(edge == TMA_RISING_EDGE_TO02_H)
    {
        // TO02 H period rising edge
        TMA->TAMR0 = _00_TMA_TAIO_POLARITY_ONE | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _80_TMA_EVENT_ENABLE_TIMEROUTSIGNAL | _00_TMA_TAIO_POLARITY_0;
        TMA->TAISR0 = _04_TMA_PWM_POLARITY_H | _02_TMA_PWM_TO02;
    }
    if(edge == TMA_FALLING_EDGE_TO02_L)
    {
        // TO02 L period falling edge
        TMA->TAMR0 = _00_TMA_TAIO_POLARITY_ONE | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _80_TMA_EVENT_ENABLE_TIMEROUTSIGNAL | _01_TMA_TAIO_POLARITY_1;
        TMA->TAISR0 = _00_TMA_PWM_POLARITY_L | _02_TMA_PWM_TO02;
    }
    if(edge == TMA_FALLING_EDGE_TO02_H)
    {
        // TO02 H period falling edge
        TMA->TAMR0 = _00_TMA_TAIO_POLARITY_ONE | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _80_TMA_EVENT_ENABLE_TIMEROUTSIGNAL | _01_TMA_TAIO_POLARITY_1;
        TMA->TAISR0 = _04_TMA_PWM_POLARITY_H | _02_TMA_PWM_TO02;
    }
    if(edge == TMA_BOTH_EDGE_TO02_L)
    {
        // TO02 L period both edge
        TMA->TAMR0 = _08_TMA_TAIO_POLARITY_BOTH | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _80_TMA_EVENT_ENABLE_TIMEROUTSIGNAL;
        TMA->TAISR0 = _00_TMA_PWM_POLARITY_L | _02_TMA_PWM_TO02;
    }
    if(edge == TMA_BOTH_EDGE_TO02_H)
    {
        // TO02 H period both edge
        TMA->TAMR0 = _08_TMA_TAIO_POLARITY_BOTH | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _80_TMA_EVENT_ENABLE_TIMEROUTSIGNAL;
        TMA->TAISR0 = _04_TMA_PWM_POLARITY_H | _02_TMA_PWM_TO02;
    }
    if(edge == TMA_RISING_EDGE_TO03_L)
    {
        // TO03 L period rising edge
        TMA->TAMR0 = _00_TMA_TAIO_POLARITY_ONE | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _80_TMA_EVENT_ENABLE_TIMEROUTSIGNAL | _00_TMA_TAIO_POLARITY_0;
        TMA->TAISR0 = _00_TMA_PWM_POLARITY_L | _03_TMA_PWM_TO03;
    }
    if(edge == TMA_RISING_EDGE_TO03_H)
    {
        // TO03 H period rising edge
        TMA->TAMR0 = _00_TMA_TAIO_POLARITY_ONE | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _80_TMA_EVENT_ENABLE_TIMEROUTSIGNAL | _00_TMA_TAIO_POLARITY_0;
        TMA->TAISR0 = _04_TMA_PWM_POLARITY_H | _03_TMA_PWM_TO03;
    }
    if(edge == TMA_FALLING_EDGE_TO03_L)
    {
        // TO03 L period falling edge
        TMA->TAMR0 = _00_TMA_TAIO_POLARITY_ONE | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _80_TMA_EVENT_ENABLE_TIMEROUTSIGNAL | _01_TMA_TAIO_POLARITY_1;
        TMA->TAISR0 = _00_TMA_PWM_POLARITY_L | _03_TMA_PWM_TO03;
    }
    if(edge == TMA_FALLING_EDGE_TO03_H)
    {
        // TO03 H period falling edge
        TMA->TAMR0 = _00_TMA_TAIO_POLARITY_ONE | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _80_TMA_EVENT_ENABLE_TIMEROUTSIGNAL | _01_TMA_TAIO_POLARITY_1;
        TMA->TAISR0 = _04_TMA_PWM_POLARITY_H | _03_TMA_PWM_TO03;
    }
    if(edge == TMA_BOTH_EDGE_TO03_L)
    {
        // TO03 L period both edge
        TMA->TAMR0 = _08_TMA_TAIO_POLARITY_BOTH | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _80_TMA_EVENT_ENABLE_TIMEROUTSIGNAL;
        TMA->TAISR0 = _00_TMA_PWM_POLARITY_L | _03_TMA_PWM_TO03;
    }
    if(edge == TMA_BOTH_EDGE_TO03_H)
    {
        // TO03 H period both edge
        TMA->TAMR0 = _08_TMA_TAIO_POLARITY_BOTH | _02_TMA_MODE_EVENT_COUNTER;
        TMA->TAIOC0 = _80_TMA_EVENT_ENABLE_TIMEROUTSIGNAL;
        TMA->TAISR0 = _04_TMA_PWM_POLARITY_H | _03_TMA_PWM_TO03;
    }

    /* Filter with fCLK/8 sampling */
    //TMA->TAIOC0 |= _20_TMA_TAIO_FILTER_FCLK8 | _00_TMA_TAO_OUTPUT_DISABLE;
    
    /* Set TAIO pin */
    TAI_PORT_SETTING();

    TMA0_Start();
}
/***********************************************************************************************************************
* Function Name: TMA0_Get_PulseWidth
* @brief  The TMA operates as pulse width measure.
* @param  clk - select count source clock
* @param  level - specify the measure level
* @return width - the width of specified level
***********************************************************************************************************************/
uint32_t TMA0_Get_PulseWidth(tma_clock_t clk, tma_pulse_t level)
{
    uint32_t width;
    CGC->PER1 |= CGC_PER1_TMAEN_Msk;     /* enables input clock supply */
    TMA->TACR0 &= (uint8_t)~_01_TMA_COUNT_START;
    INTC_DisableIRQ(TMA_IRQn);/* disable INTTMA interrupt */
    INTC_ClearPendingIRQ(TMA_IRQn);/* clear INTTMA interrupt flag */
    TMA->TAMR0 = clk | _03_TMA_MODE_PULSE_WIDTH;
    if (level == TMA_PULSE_WIDTH_LOW)
    {
        TMA->TAIOC0 = _00_TMA_TAIO_POLARITY_0;
    }
    if (level == TMA_PULSE_WIDTH_HIGH)
    {
        TMA->TAIOC0 = _01_TMA_TAIO_POLARITY_1;
    }
    TMA->TA0 = g_tma0_ta0_value;
    /* Set TAIO pin */
    TAI_PORT_SETTING();

    //TMA->TAIOC0 |= _20_TMA_TAIO_FILTER_FCLK8;
    g_tma0_underflow_count = 0U;
    TMA0_Start();

    while((TMA->TACR0 & _10_TMA_ACTIVE_EDGE_RECEIVED) == 0U);
    TMA->TACR0 &= ~_10_TMA_ACTIVE_EDGE_RECEIVED;
    if (g_tma0_underflow_count == 0U)
    {
        width = g_tma0_ta0_value - TMA->TA0;
    }
    else
    {
        width = g_tma0_ta0_value - TMA->TA0 + (g_tma0_ta0_value + 1) * g_tma0_underflow_count;
    }
		
    TMA0_Stop();
    return (width);
    
}
/***********************************************************************************************************************
* Function Name: TMA0_Get_PulsePeriod
* @brief  The TMA operates as pulse period measure.
* @param  clk - select count source clock
* @param  edge - specify the rising edge or falling edge
* @return period - the period of pulse
***********************************************************************************************************************/
uint32_t TMA0_Get_PulsePeriod(tma_clock_t clk, tma_pulse_t edge)
{
    volatile uint16_t tmp;
    uint32_t period;
    CGC->PER1 |= CGC_PER1_TMAEN_Msk;     /* enables input clock supply */
    TMA->TACR0 &= (uint8_t)~_01_TMA_COUNT_START;
    INTC_DisableIRQ(TMA_IRQn);/* disable INTTMA interrupt */
    INTC_ClearPendingIRQ(TMA_IRQn);/* clear INTTMA interrupt flag */
    TMA->TAMR0 = clk | _04_TMA_MODE_PULSE_PERIOD;
    if(edge == TMA_PULSE_PERIOD_RISING)
    {
        TMA->TAIOC0 = _00_TMA_TAIO_POLARITY_0;
    }
    if(edge == TMA_PULSE_PERIOD_FALLING)
    {
        TMA->TAIOC0 = _01_TMA_TAIO_POLARITY_1;
    }
    TMA->TA0 = g_tma0_ta0_value;
    /* Set TAIO pin */
    TAI_PORT_SETTING();

    //TMA->TAIOC0 |= _20_TMA_TAIO_FILTER_FCLK8;
    TMA0_Start();

    while((TMA->TACR0 & _10_TMA_ACTIVE_EDGE_RECEIVED) == 0U);
    TMA->TACR0 &= ~_10_TMA_ACTIVE_EDGE_RECEIVED;
    tmp = TMA->TA0;    // dummy read to update readbuf
    g_tma0_underflow_count = 0U;

    while((TMA->TACR0 & _10_TMA_ACTIVE_EDGE_RECEIVED) == 0U);
    TMA->TACR0 &= ~_10_TMA_ACTIVE_EDGE_RECEIVED;
    if (g_tma0_underflow_count == 0U)
    {
        period = g_tma0_ta0_value - TMA->TA0 + 1U;
    }
    else
    {
        period = g_tma0_ta0_value - TMA->TA0 + 1U + (g_tma0_ta0_value + 1) * g_tma0_underflow_count;
    }
    
    TMA0_Stop();
    return (period);
}
/***********************************************************************************************************************
* Function Name: TMA0_Start
* @brief  This function starts TMA counter.
* @param  None
* @return None
***********************************************************************************************************************/
void TMA0_Start(void)
{
    INTC_ClearPendingIRQ(TMA_IRQn);/* clear INTTMA interrupt flag */
    INTC_EnableIRQ(TMA_IRQn);/* enable INTTMA interrupt */
    TMA->TACR0 |= _01_TMA_COUNT_START;
}
/***********************************************************************************************************************
* Function Name: TMA0_Stop
* @brief  This function stops TMA counter.
* @param  None
* @return None
***********************************************************************************************************************/
void TMA0_Stop(void)
{
    TMA->TACR0 &= (uint8_t)~_01_TMA_COUNT_START;
    INTC_DisableIRQ(TMA_IRQn);/* disable INTTMA interrupt */
    INTC_ClearPendingIRQ(TMA_IRQn);/* clear INTTMA interrupt flag */
}
/***********************************************************************************************************************
* Function Name: TMA0_Set_PowerOff
* @brief  This function stops the clock supplied for TMA.
* @param  None
* @return None
***********************************************************************************************************************/
void TMA0_Set_PowerOff(void)
{
    CGC->PER1 &= ~CGC_PER1_TMAEN_Msk;     /* enables input clock supply */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
