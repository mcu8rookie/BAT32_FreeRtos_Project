/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    timb.c
* @brief   This file implements device driver for TMB module.
* @version 1.0.0
* @date    2022/2/25
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "BAT32A237.h"
#include "userdefine.h"
#include "timb.h"
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
/* Start user code for global. Do not edit comment generated khere */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: TMB0_InputCapture
* @brief  The TMB operates as input capture mode.
* @param  clk - select count source clock
* @return None
***********************************************************************************************************************/
void TMB0_InputCapture(tmb_clock_t clk)
{
    CGC->PER1 |= CGC_PER1_TMBEN_Msk;     /* enables input clock supply */
    TMB->TBMR &= (uint8_t)~_80_TMB_COUNT_START;
    INTC_DisableIRQ(TMB_IRQn);/* disable INTTMB interrupt */
    INTC_ClearPendingIRQ(TMB_IRQn);/* clear INTTMB interrupt flag */
    TMB->TBCR = _00_TMB_CLEAR_DISABLEED | _00_TMB_COUNT_RISING | clk;
    TMB->TBMR = _00_TMB_SIGNALB_SELECTED | _00_TMB_INCREMENT_MODE | _00_TMB_TIMER_MODE;
    TMB->TBIOR = _80_TMB_TBGRB_REGISTER_USED | _40_TMB_TBGRB_INPUT_CAPTURE |
                 _08_TMB_TBGRA_REGISTER_USED | _04_TMB_TBGRA_INPUT_CAPTURE;
    TMB->TBIER = _08_TMB_INTERRUPT_TBOVF_ENABLE | _02_TMB_INTERRUPT_TBIMFB_ENABLE | _01_TMB_INTERRUPT_TBIMFA_ENABLE;
}
/***********************************************************************************************************************
* Function Name: TMB0_Get_PulseWidth
* @brief  The TMB operates as pulse width measure.
* @param  clk - select count source clock
* @param  ch - specify the active channel
* @return width - the width of specified level
***********************************************************************************************************************/
uint32_t TMB0_Get_PulseWidth(tmb_clock_t clk, tmb_channel_t ch)
{
    uint32_t width;

    TMB0_InputCapture(clk);

    TMB->TBIOR |= _20_TMB_TBGRB_BOTH_EDGES | _02_TMB_TBGRA_BOTH_EDGES;

    if(ch == TMB_CHANNELA)
    {
        /* Set TBIO0 pin */
        TBI0_PORT_SETTING();
        TMB0_Start();

        g_tmb_intTaken_a = 0U;
        g_tmb_overflow_count_a = 0U;
        while(g_tmb_intTaken_a != 2);    

        width = g_tmb_active_width_a;
    }
    if(ch == TMB_CHANNELB)
    {
        /* Set TBIO1 pin */
        TBI1_PORT_SETTING();
        TMB0_Start();

        g_tmb_intTaken_b = 0U;
        g_tmb_overflow_count_b = 0U;
        while(g_tmb_intTaken_b != 2);    
        
        width = g_tmb_active_width_b;
    }

    return (width);

}
/***********************************************************************************************************************
* Function Name: TMB0_Get_PulsePeriod
* @brief  The TMB operates as pulse period measure.
* @param  clk - select count source clock
* @param  ch - specify the active channel
* @return period - the period of pulse
***********************************************************************************************************************/
uint32_t TMB0_Get_PulsePeriod(tmb_clock_t clk,tmb_channel_t ch)
{
    volatile uint16_t tmp;
    uint32_t period;

    TMB0_InputCapture(clk);

#if 1
    /* pulse period from rising edge to rising edge */
    TMB->TBIOR |= _00_TMB_TBGRB_RISING_EDGE | _00_TMB_TBGRA_RISING_EDGE;
#else
    /* pulse period from falling edge to falling edge */
    TMB->TBIOR |= _01_TMB_TBGRB_FALLING_EDGE | _01_TMB_TBGRA_FALLING_EDGE;
#endif

    if(ch == TMB_CHANNELA)
    {
        /* Set TBIO0 pin */
        TBI0_PORT_SETTING();
        TMB0_Start();

        g_tmb_intTaken_a = 0U;
        g_tmb_overflow_count_a = 0U;
        while(g_tmb_intTaken_a != 2);    

        period = g_tmb_active_width_a;
    }
    if(ch == TMB_CHANNELB)
    {
        /* Set TBIO1 pin */
        TBI1_PORT_SETTING();
        TMB0_Start();

        g_tmb_intTaken_b = 0U;
        g_tmb_overflow_count_b = 0U;
        while(g_tmb_intTaken_b != 2);    
        
        period = g_tmb_active_width_b;
    }

    return (period);
}
/***********************************************************************************************************************
* Function Name: TMB0_OutputCompare
* @brief  The TMB operates as output compare mode.
* @param  clk - select count source clock
* @return None
***********************************************************************************************************************/
void TMB0_OutputCompare(tmb_clock_t clk)
{
    CGC->PER1 |= CGC_PER1_TMBEN_Msk;     /* enables input clock supply */
    TMB->TBMR &= (uint8_t)~_80_TMB_COUNT_START;
    INTC_DisableIRQ(TMB_IRQn);/* disable INTTMB interrupt */
    INTC_ClearPendingIRQ(TMB_IRQn);/* clear INTTMB interrupt flag */
    /* the counter is cleared when it matches the TMGRB register */ 
    TMB->TBCR = _40_TMB_CLEAR_TBGRB | _00_TMB_COUNT_RISING | clk;
    /* increment timer mode */
    TMB->TBMR = _00_TMB_SIGNALB_SELECTED | _00_TMB_INCREMENT_MODE | _00_TMB_TIMER_MODE;
    /* TBGRD/TBGRC is used as buffer register for TBGRB/TBGRA register, toggle output when matches */
    TMB->TBIOR = _80_TMB_TBGRB_REGISTER_USED | _00_TMB_TBGRB_OUTPUT_COMPARE | _30_TMB_TBGRB_TOGGLE_OUTPUT |
                 _08_TMB_TBGRA_REGISTER_USED | _00_TMB_TBGRA_OUTPUT_COMPARE | _03_TMB_TBGRA_TOGGLE_OUTPUT;
    /* Set the interrupt enable register */
    TMB->TBIER = _08_TMB_INTERRUPT_TBOVF_ENABLE | _02_TMB_INTERRUPT_TBIMFB_ENABLE | _01_TMB_INTERRUPT_TBIMFA_ENABLE;
}

/***********************************************************************************************************************
* Function Name: TMB0_DoublePulseOutput
* @brief  The TMB operates as double pulse output.
* @param  clk - select count source clock
* @param  period - the period of TBIO0 and TBIO1 output square wave.
* @param  skew - the phase skew from the risging edge of TBIO0 to the rising edge of TBIO1.
* @return None
* @note   The value of skew MUST be less than the value of half period. [skew < (period / 2)]
*
*            ^
*       FFFFH|
*            |
* TBGRB = m-1|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
*            |                    _| |                    _| |                    _| |
*            |                  _|   |                  _|   |                  _|   |
*            |                _|     |                _|     |                _|     |
*            |              _|       |              _|       |              _|       |        
*            |            _|         |            _|         |            _|         |
* TMGRA = n-1|_ _ _ _ _ _|_ _ _ _ _ _|_ _ _ _ _ _|_ _ _ _ _ _|_ _ _ _ _ _|_ _ _ _ _ _|_ _ _ _ 
*            |        _| |           |        _| |           |        _| |           |         
*            |      _|   |           |      _|   |           |      _|   |           |       _  
*            |    _|     |           |    _|     |           |    _|     |           |     _|    
*            |  _|       |           |  _|       |           |  _|       |           |   _|      
*       0000H|_|_________|___________|_|_________|___________|_|_________|___________|__|______
*                        |           |           |           |           |           |
*                        |___________|___________|           |           |___________|_________
*     TBIO0 _____________|           |           |___________|___________|           |         
*                        |____       |           |____       |           |____       |   
* TBSR.IMFA _____________|    |______|___________|    |______|___________|    |______|_________
*                                    |                       |                       |          
*                                    |_______________________|                       |_________
*     TBIO1 _________________________|                       |_______________________|         
*                                    |____                   |____                   |____
* TBSR.IMFB _________________________|    |__________________|    |__________________|    |____
*                                                 
***********************************************************************************************************************/
void TMB0_DoublePulseOutput(tmb_clock_t clk, uint16_t period, uint16_t skew)
{
    uint16_t half_period;

    half_period = period / 2;

    TMB0_OutputCompare(clk);
    TMB->TBGRA = (half_period - skew) - 1;
    TMB->TBGRB = half_period - 1;
    TMB->TBGRC = TMB->TBGRA;
    TMB->TBGRD = TMB->TBGRB;

    /* Set TBIO0 pin */
    TBO0_PORT_SETTING();
    /* Set TBIO1 pin */
    TBO1_PORT_SETTING();

    TMB0_Start();
}
/***********************************************************************************************************************
* Function Name: TMB0_PWM_1Period_1Duty
* @brief  The TMB operates as PWM output mode.
* @param  clk - select count source clock
* @param  period - the period of TBIO0 output wave
* @param  duty - the duty of TBIO0 output wave
* @return None
*
*            ^
*       FFFFH|
*            |
* TBGRA = m-1|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
*            |                    _| |                    _| |                    _| |
*            |                  _|   |                  _|   |                  _|   |
*            |                _|     |                _|     |                _|     |
*            |              _|       |              _|       |              _|       |        
*            |            _|         |            _|         |            _|         |
* TMGRB = n-1|_ _ _ _ _ _|_ _ _ _ _ _|_ _ _ _ _ _|_ _ _ _ _ _|_ _ _ _ _ _|_ _ _ _ _ _|_ _ _ _ 
*            |        _| |           |        _| |           |        _| |           |         
*            |      _|   |           |      _|   |           |      _|   |           |       _  
*            |    _|     |           |    _|     |           |    _|     |           |     _|    
*            |  _|       |           |  _|       |           |  _|       |           |   _|      
*       0000H|_|_________|___________|_|_________|___________|_|_________|___________|__|______
*                        |           |           |           |           |           |
*           _____________|           |___________|           |___________|           |_________
*     TBIO0              |___________|           |___________|           |___________|         
*                        |____       |           |____       |           |____       |   
* TBSR.IMFB _____________|    |______|___________|    |______|___________|    |______|_________
*                                    |____                   |____                   |____      
* TBSR.IMFA _________________________|    |__________________|    |__________________|    |____
*                                                 
***********************************************************************************************************************/
void TMB0_PWM_1Period_1Duty(tmb_clock_t clk, uint16_t period, uint16_t duty)
{
    CGC->PER1 |= CGC_PER1_TMBEN_Msk;     /* enables input clock supply */
    TMB->TBMR &= (uint8_t)~_80_TMB_COUNT_START;
    INTC_DisableIRQ(TMB_IRQn);/* disable INTTMB interrupt */
    INTC_ClearPendingIRQ(TMB_IRQn);/* clear INTTMB interrupt flag */
    /* the counter is cleared when it matches the TMGRA register */ 
    TMB->TBCR = _20_TMB_CLEAR_TBGRA | _00_TMB_COUNT_RISING | clk;
    /* increment pwm mode */
    TMB->TBMR = _00_TMB_INCREMENT_MODE | _01_TMB_PWM_MODE;
    /* Please note that TBBUFB and TBBUFA bit of TBIOR register are still valid in PWM mode. */
    /* TBGRD/TBGRC is used as buffer register for TBGRB/TBGRA register */
    TMB->TBIOR = _80_TMB_TBGRB_REGISTER_USED | _08_TMB_TBGRA_REGISTER_USED;  
    /* Set the interrupt enable register */
    TMB->TBIER = _08_TMB_INTERRUPT_TBOVF_ENABLE | _02_TMB_INTERRUPT_TBIMFB_ENABLE | _01_TMB_INTERRUPT_TBIMFA_ENABLE;

    /* Set period and duty */
    TMB->TBGRA = period - 1;
    TMB->TBGRB = duty - 1;
    TMB->TBGRC = TMB->TBGRA;
    TMB->TBGRD = TMB->TBGRB;

    /* Set TBIO0 pin */
    TBO0_PORT_SETTING();

    TMB0_Start();
}
/***********************************************************************************************************************
* Function Name: TMB0_PhaseCount
* @brief  The TMB operates as Phase Count mode.
* @param  cntc_reg - the setting value of TBCNTC register
* @return None
***********************************************************************************************************************/
void TMB0_PhaseCount(uint8_t cntc_reg)
{
    CGC->PER1 |= CGC_PER1_TMBEN_Msk;     /* enables input clock supply */
    TMB->TBMR &= (uint8_t)~_80_TMB_COUNT_START;
    INTC_DisableIRQ(TMB_IRQn);/* disable INTTMB interrupt */
    INTC_ClearPendingIRQ(TMB_IRQn);/* clear INTTMB interrupt flag */
    TMB->TBCR = _00_TMB_CLEAR_DISABLEED;
    TMB->TB = 0U;
    TMB->TBMR = _02_TMB_COUNTING_MODE;
#if 1
    TMB->TBCNTC = cntc_reg;
#else
    TMB->TBCNTC = _80_TMB_COUNTER7_INCREMNET | _40_TMB_COUNTER6_INCREMNET | 
                  _20_TMB_COUNTER5_INCREMNET | _10_TMB_COUNTER4_INCREMNET |
                  _08_TMB_COUNTER3_INCREMNET | _04_TMB_COUNTER2_INCREMNET |
                  _02_TMB_COUNTER1_INCREMNET | _01_TMB_COUNTER0_INCREMNET;
#endif
    TMB->TBIER = _08_TMB_INTERRUPT_TBOVF_ENABLE | _04_TMB_INTERRUPT_TBUDF_ENABLE;

    /* Set TBCLK0 pin */
    TBCLK0_PORT_SETTING();
    /* Set TBCLK1 pin */
    TBCLK1_PORT_SETTING();

    TMB0_Start();
}
/***********************************************************************************************************************
* Function Name: TMB0_Start
* @brief  This function starts TMB counter.
* @param  None
* @return None
***********************************************************************************************************************/
void TMB0_Start(void)
{
    volatile uint8_t tbsr_dummy;

    tbsr_dummy = TMB->TBSR; /* read TBSR before write 0 */
    TMB->TBSR = 0x00U;
    INTC_ClearPendingIRQ(TMB_IRQn);/* clear INTTMA interrupt flag */
    INTC_EnableIRQ(TMB_IRQn);/* enable INTTMA interrupt */
    TMB->TBMR |= _80_TMB_COUNT_START;

}
/***********************************************************************************************************************
* Function Name: TMB0_Stop
* @brief  This function stops TMB counter.
* @param  None
* @return None
***********************************************************************************************************************/
void TMB0_Stop(void)
{
    volatile uint8_t tbsr_dummy;

    TMB->TBMR &= (uint8_t)~_80_TMB_COUNT_START;
    INTC_DisableIRQ(TMB_IRQn);/* disable INTTMA interrupt */
    INTC_ClearPendingIRQ(TMB_IRQn);/* clear INTTMA interrupt flag */
    tbsr_dummy = TMB->TBSR; /* read TBSR before write 0 */
    TMB->TBSR = 0x00U;
}
/***********************************************************************************************************************
* Function Name: TMB0_Set_PowerOff
* @brief  This function stops the clock supplied for TMB.
* @param  None
* @return None
***********************************************************************************************************************/
void TMB0_Set_PowerOff(void)
{
    CGC->PER1 &= ~CGC_PER1_TMBEN_Msk;     /* disables input clock supply */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
