/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    timm.c
* @brief   This file implements device driver for TMB module.
* @version 1.0.0
* @date    2022/2/25
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "BAT32A237.h"
#include "userdefine.h"
#include "timm.h"
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
* Function Name: TMM0_InputCapture
* @brief  The TMM0 operates in input capture mode.
* @param  clk - select count source clock
* @return None
***********************************************************************************************************************/
void TMM0_InputCapture(tmm_clock_t clk)
{
    CGC->PER1 |= CGC_PER1_TMMEN_Msk;     /* enables input clock supply */
    TMM->TMSTR |= _04_TMM_TM0_COUNT_CONTINUES;
    TMM->TMSTR &= (uint8_t)~_01_TMM_TM0_COUNT_START;
    /* the TMGRC0/GMGRD0 is used as buffer register of TMGRA0/TMGRB0 */
    TMM->TMMR = _10_TMM_TMGRC0_BUFFER | _20_TMM_TMGRD0_BUFFER;
    TMM->TMCR0 = _00_TMM_COUNTER_CLEAR_DISABLE | clk;
    TMM->TMIORA0 = _40_TMM_TMGRB_CAPTURE | _00_TMM_TMGRB_CAPTURE_RISING |
                   _04_TMM_TMGRA_CAPTURE | _00_TMM_TMGRA_CAPTURE_RISING;
    TMM->TMIORC0 = _80_TMM_TMGRD_GENERAL_BUFFER_REGISTER | _40_TMM_TMGRD_CAPTURE |
                   _08_TMM_TMGRC_GENERAL_BUFFER_REGISTER | _04_TMM_TMGRC_CAPTURE;
    TMM->TMIER0 = _10_TMM_OVIE_ENABLE | _02_TMM_IMIB_ENABLE | _01_TMM_IMIA_ENABLE;
    TMM->TMPOCR0 = _00_TMIOD_OUTPUT_ACTIVE_L | _00_TMIOC_OUTPUT_ACTIVE_L | _00_TMIOB_OUTPUT_ACTIVE_L;
    /* Set TMIOA0 pin */
    TMIA0_PORT_SETTING();
    /* Set TMIOB0 pin */
    TMIB0_PORT_SETTING();
}
/***********************************************************************************************************************
* Function Name: TMM0_Get_PulseWidth
* @brief  The TMM0 operates as pulse width measure.
* @param  clk - select count source clock
* @param  ch - specify the active channel
* @return width - the width of specified level
***********************************************************************************************************************/
uint32_t TMM0_Get_PulseWidth(tmm_clock_t clk, tmm_channel_t ch)
{
    uint32_t width;

    TMM0_InputCapture(clk);

    /* input capture at both edges*/
    TMM->TMIORA0 |= _20_TMM_TMGRB_CAPTURE_BOTH | _02_TMM_TMGRA_CAPTURE_BOTH;

    if(ch == TMM_CHANNELA)
    {
        /* Set TMIOA0 pin */
        TMIA0_PORT_SETTING();
        TMM0_Start();

        g_tmm0_intTaken_a = 0U;
        g_tmm0_overflow_count_a = 0U;
        while(g_tmm0_intTaken_a != 2);    

        width = g_tmm0_active_width_a;
    }
    if(ch == TMM_CHANNELB)
    {
        /* Set TMIOB0 pin */
        TMIB0_PORT_SETTING();
        TMM0_Start();

        g_tmm0_intTaken_b = 0U;
        g_tmm0_overflow_count_b = 0U;
        while(g_tmm0_intTaken_b != 2);    
        
        width = g_tmm0_active_width_b;
    }

    return (width);
}
/***********************************************************************************************************************
* Function Name: TMM0_Get_PulsePeriod
* @brief  The TMM0 operates as pulse period measure.
* @param  clk - select count source clock
* @param  ch - specify the active channel
* @return period - the period of pulse
***********************************************************************************************************************/
uint32_t TMM0_Get_PulsePeriod(tmm_clock_t clk,tmm_channel_t ch)
{
    volatile uint16_t tmp;
    uint32_t period;

    TMM0_InputCapture(clk);

#if 1
    /* measure the pulse period from rising edge to rising edge */
    TMM->TMIORA0 |= _00_TMM_TMGRB_CAPTURE_RISING | _00_TMM_TMGRA_CAPTURE_RISING;
#else
    /* measure the pulse period from falling edge to falling edge */
    TMM->TMIORA0 |= _10_TMM_TMGRB_CAPTURE_FALLING | _01_TMM_TMGRA_CAPTURE_FALLING;
#endif

    if(ch == TMM_CHANNELA)
    {
        /* Set TMIOA0 pin */
        TMIA0_PORT_SETTING();
        TMM0_Start();

        g_tmm0_intTaken_a = 0U;
        g_tmm0_overflow_count_a = 0U;
        while(g_tmm0_intTaken_a != 2);    

        period = g_tmm0_active_width_a;
    }
    if(ch == TMM_CHANNELB)
    {
        /* Set TMIOB0 pin */
        TMIB0_PORT_SETTING();
        TMM0_Start();

        g_tmm0_intTaken_b = 0U;
        g_tmm0_overflow_count_b = 0U;
        while(g_tmm0_intTaken_b != 2);    
        
        period = g_tmm0_active_width_b;
    }

    return (period);
}
/***********************************************************************************************************************
* Function Name: TMM0_OutputCompare
* @brief  The TMM0 operates in output compare mode.
* @param  clk - select count source clock
* @return None
***********************************************************************************************************************/
void TMM0_OutputCompare(tmm_clock_t clk)
{
    CGC->PER1 |= CGC_PER1_TMMEN_Msk;     /* enables input clock supply */
    CGC->PER1 |= 0x04U;
    TMM->TMSTR |= _04_TMM_TM0_COUNT_CONTINUES;
    TMM->TMSTR &= (uint8_t)~_01_TMM_TM0_COUNT_START;
    /* the TMGRC and TMGRD are used as general register */
    TMM->TMMR |= _00_TMM_TMGRC0_GENERAL | _00_TMM_TMGRD0_GENERAL;
#if 1
    /* the counter is cleared when it matches the TMGRA register */ 
    TMM->TMCR0 = _20_TMM_COUNTER_CLEAR_TMGRA | clk;
#else
    /* the counter is free running */
    TMM->TMCR0 = _00_TMM_COUNTER_CLEAR_DISABLE | clk;
#endif
    /* Set the output level when the counter matches with TMGRA and TMGRB reigister */
    TMM->TMIORA0 = _00_TMM_TMGRB_COMPARE | _30_TMM_TMGRB_COMPARE_OUTPUT_TOGGLE | _00_TMM_TMGRA_COMPARE | _03_TMM_TMGRA_COMPARE_OUTPUT_TOGGLE;
    /* Set the output level when the counter matches with TMGRC and TMGRD reigister */
#if 1
    TMM->TMIORC0 = _00_TMM_TMGRD_OUTPUT_REGISTER | _00_TMM_TMGRD_COMPARE | _30_TMM_TMGRD_COMPARE_OUTPUT_TOGGLE |
                   _00_TMM_TMGRC_OUTPUT_REGISTER | _00_TMM_TMGRC_COMPARE | _03_TMM_TMGRC_COMPARE_OUTPUT_TOGGLE;
#else
    TMM->TMIORC0 = _80_TMM_TMGRD_GENERAL_BUFFER_REGISTER | _00_TMM_TMGRD_COMPARE | _10_TMM_TMGRD_COMPARE_OUTPUT_LOW |
                   _08_TMM_TMGRC_GENERAL_BUFFER_REGISTER | _00_TMM_TMGRC_COMPARE | _01_TMM_TMGRC_COMPARE_OUTPUT_LOW;
#endif
    /* Set the initial level of the output pins */
    TMM->TMOCR |= _00_TMM_TMIOA0_INITIAL_OUTPUT_L | _00_TMM_TMIOB0_INITIAL_OUTPUT_L | _00_TMM_TMIOC0_INITIAL_OUTPUT_L | _00_TMM_TMIOD0_INITIAL_OUTPUT_L;
    /* The output is enabled */
    TMM->TMOER1 &= 0xF0U;
#if 1
    TMM->TMOER1 |= _00_TMM_TMIOA0_OUTPUT_ENABLE | _00_TMM_TMIOB0_OUTPUT_ENABLE | _04_TMM_TMIOC0_OUTPUT_DISABLE | _08_TMM_TMIOD0_OUTPUT_DISABLE;
#else
    TMM->TMOER1 |= _00_TMM_TMIOA0_OUTPUT_ENABLE | _00_TMM_TMIOB0_OUTPUT_ENABLE | _00_TMM_TMIOC0_OUTPUT_ENABLE | _00_TMM_TMIOD0_OUTPUT_ENABLE;
#endif
    /* Set the interrupt enable register */
    TMM->TMIER0 = _00_TMM_OVIE_DISABLE | _00_TMM_IMID_DISABLE | _00_TMM_IMIC_DISABLE | _00_TMM_IMIB_DISABLE | _01_TMM_IMIA_ENABLE;
    
    TMM->OPCTL0 = _00_TMM_PWMOP_NO_CUTOFF;
}

/***********************************************************************************************************************
* Function Name: TMM0_DoublePulseOutput
* @brief  The TMM operates as double pulse output.
* @param  clk - select count source clock
* @param  m - the value of TMGRA register. it is the period of TMIOA0 and TMIOB0 output pulse.
* @param  n - the value of TMGRC register. it is the toggle point of TMIOA0.
* @param  p - the value of TMGRB register. it is the toggle point of TMIOB0.
* @param  q - the value of TMGRD register. it is the toggle point of TMIOB0.
* @return None
* @note   The value of m MUST be greater than the value of n, p, q. [m > m/p/q]
*
*            ^
*       FFFFH|
*            |
*TMGRA0 = m-1|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
*            |                    _| |                    _| |
*            |                  _|   |                  _|   |
*            |                _|     |                _|     |
*TMGRC0 = n-1|_ _ _ _ _ _ _ _|_ _ _ _|_ _ _ _ _ _ _ _|_ _ _ _|_ _ _ _
*            |            _| |       |            _| |       |
*TMGRB0 = p-1|_ _ _ _ _ _|_ _|_ _ _ _|_ _ _ _ _ _|_ _|_ _ _ _|_ _ _ _
*            |        _| |   |       |        _| |   |       |        
*            |      _|   |   |       |      _|   |   |       |      _  
*TMGRD0 = q-1|_ _ _|_ _ _|_ _|_ _ _ _|_ _ _|_ _ _|_ _|_ _ _ _|_ _ _|    
*            |  _| |     |   |       |  _| |     |   |       |  _|      
*       0000H|_|___|_____|___|_______|_|___|_____|___|_______|_|______
*                  |     |   |       |     |     |   |       |
*                  |     |   |_______|     |     |   |_______|
*     TMIOA0 ______|_____|___|       |_____|_____|___|       |________
*                  |     |   |       |__   |     |   |       |__
* TMSR0.IMFA ______|_____|___|_______|  |__|_____|___|_______|  |_____
*                  |     |   |__________   |     |   |__________
* TMSR0.IMFC ______|_____|___|          |__|_____|___|          |_____
*                  |     |                 |     |
*                  |_____|                 |_____|
*     TMIOB0 ______|     |_________________|     |____________________
*                  |     |______________   |     |______________
* TMSR0.IMFB ______|_____|              |__|_____|              |_____
*                  |____________________   |____________________
* TMSR0.IMFD ______|                    |__|                    |_____
*                                                 
***********************************************************************************************************************/
void TMM0_DoublePulseOutput(tmm_clock_t clk, uint16_t m, uint16_t n, uint16_t p, uint16_t q)
{
    TMM0_OutputCompare(clk);
    TMM->TMGRA0 = m -1;
    TMM->TMGRC0 = n -1 ;
    TMM->TMGRB0 = p -1 ;
    TMM->TMGRD0 = q -1 ;

    /* Set TMIOA0 pin */
    TMOA0_PORT_SETTING();
    /* Set TMIOB0 pin */
    TMOB0_PORT_SETTING();

    TMM0_Start();
}
/***********************************************************************************************************************
* Function Name: TMM0_PWM_1Perdod_3Duty
* @brief  The TMM0 operates as PWM output mode.
* @param  clk - select count source clock
* @param  period - the period of PWM wave
* @param  duty1 - the duty of TMIOB0 output wave
* @param  duty2 - the duty of TMIOC0 output wave
* @param  duty3 - the duty of TMIOD0 output wave
* @return None
* @note   period = m, duty1 = n, duty2 = p, duty3 = q
*
*            ^
*       FFFFH|
*            |
*TMGRA0 = m-1|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
*            |                    _| |                    _| |
*            |                  _|   |                  _|   |
*            |                _|     |                _|     |
*TMGRB0 = n-1|_ _ _ _ _ _ _ _|_ _ _ _|_ _ _ _ _ _ _ _|_ _ _ _|_ _ _ _
*            |            _| |       |            _| |       |
*TMGRC0 = p-1|_ _ _ _ _ _|_ _|_ _ _ _|_ _ _ _ _ _|_ _|_ _ _ _|_ _ _ _
*            |        _| |   |       |        _| |   |       |        
*            |      _|   |   |       |      _|   |   |       |      _  
*TMGRD0 = q-1|_ _ _|_ _ _|_ _|_ _ _ _|_ _ _|_ _ _|_ _|_ _ _ _|_ _ _|    
*            |  _| |     |   |       |  _| |     |   |       |  _|      
*       0000H|_|___|_____|___|_______|_|___|_____|___|_______|_|______
*                  |     |   |       |     |     |   |       |
*            ______|_____|___|       |_____|_____|___|       |________
*     TMIOB0       |     |   |_______|     |     |   |_______|        
*            ______|_____|   |       |_____|_____|   |       |________
*     TMIOC0       |     |___|_______|     |     |___|_______|        
*            ______|     |   |       |_____|     |   |       |________
*     TMIOD0       |_____|___|_______|     |_____|___|_______|        
*                  |     |   |       |     |     |   |       |  
*                  |     |   |       |__   |     |   |       |__
* TMSR0.IMFA ______|_____|___|_______|  |__|_____|___|_______|  |_____
*                  |     |   |__________   |     |   |__________
* TMSR0.IMFB ______|_____|___|          |__|_____|___|          |_____
*                  |     |______________   |     |______________
* TMSR0.IMFC ______|_____|              |__|_____|              |_____
*                  |____________________   |____________________
* TMSR0.IMFD ______|                    |__|                    |_____
*                                                 
***********************************************************************************************************************/
void TMM0_PWM_1Perdod_3Duty(tmm_clock_t clk, uint16_t period, uint16_t duty1, uint16_t duty2, uint16_t duty3)
{
    CGC->PER1 |= CGC_PER1_TMMEN_Msk;     /* enables input clock supply */
    CGC->PER1 |= 0x04U;    /* PWMOPEN = 1 */
    TMM->TMSTR |= _04_TMM_TM0_COUNT_CONTINUES;
    TMM->TMSTR &= (uint8_t)~_01_TMM_TM0_COUNT_START;
    /* the TMGRC and TMGRD are used as general register */
    TMM->TMMR |= _00_TMM_TMGRC0_GENERAL | _00_TMM_TMGRD0_GENERAL;
    /* the counter is cleared when it matches the TMGRA register */ 
    TMM->TMCR0 = _20_TMM_COUNTER_CLEAR_TMGRA | clk;
    /* TMIOB0/TMIOC0/TMIOD0 is used as PWM output */
    TMM->TMPMR |= _01_TMM_TMIOB0_PWM_MODE | _02_TMM_TMIOC0_PWM_MODE | _04_TMM_TMIOD0_PWM_MODE;
    /* Set the active level of the output pins */
    TMM->TMPOCR0 = _00_TMIOD_OUTPUT_ACTIVE_L | _00_TMIOC_OUTPUT_ACTIVE_L | _00_TMIOB_OUTPUT_ACTIVE_L;
    /* Set the initial level of the output pins */
    TMM->TMOCR |= _00_TMM_TMIOB0_INITIAL_OUTPUT_L | _00_TMM_TMIOC0_INITIAL_OUTPUT_L | _00_TMM_TMIOD0_INITIAL_OUTPUT_L;
    /* PWM output pulse forced cutoff control */
    TMM->TMDF0 = _10_TMM_TMIOB_HIGHIMPEDANCE_OUTPUT | _04_TMM_TMIOC_HIGHIMPEDANCE_OUTPUT | _01_TMM_TMIOD_HIGHIMPEDANCE_OUTPUT;
    /* PWM output pulse forced cutoff enable */
    TMM->TMELC |= _20_TMM1_CUTOFF_ENABLED | _02_TMM0_CUTOFF_ENABLED;  /* ELCOBE1 = 1, ELCOBE0 = 1 */
    TMM->TMOER2 = _80_TMM_ALL_OUTPUT_ENABLE;  /* TMPTO = 1 */
    /* The output is enabled */
    TMM->TMOER1 &= 0xF0U;
    TMM->TMOER1 |= _01_TMM_TMIOA0_OUTPUT_DISABLE | _00_TMM_TMIOB0_OUTPUT_ENABLE | _00_TMM_TMIOC0_OUTPUT_ENABLE | _00_TMM_TMIOD0_OUTPUT_ENABLE;
    /* Set the interrupt enable register */
    TMM->TMIER0 = _00_TMM_OVIE_DISABLE | _00_TMM_IMID_DISABLE | _00_TMM_IMIC_DISABLE | _00_TMM_IMIB_DISABLE | _01_TMM_IMIA_ENABLE;
    /* Set PWMOP register */
    TMM->OPCTL0 = _00_TMM_PWMOP_NO_CUTOFF;

    /* Set period and duty */
    TMM->TMGRA0 = period - 1;
    TMM->TMGRB0 = duty1 - 1;
    TMM->TMGRC0 = duty2 - 1;
    TMM->TMGRD0 = duty3 - 1;

    /* Set TMIOB0 pin */
    TMOB0_PORT_SETTING();
    /* Set TMIOC0 pin */
    TMOC0_PORT_SETTING();
    /* Set TMIOD0 pin */
    TMOD0_PORT_SETTING();

    TMM0_Start();
}
/***********************************************************************************************************************
* Function Name: TMM0_PWM_Complementary_3Phase
* @brief  The TMM operates in Complementary PWM mode, i.e. three-phase, triangular wave modulation and with dead time.
* @param  clk - select count source clock
* @param  period - the period of PWM wave
* @param  dead - the dead time 
* @return None
***********************************************************************************************************************/
void TMM0_PWM_Complementary_3Phase(tmm_clock_t clk, uint16_t period, uint16_t dead)
{
    CGC->PER1 |= CGC_PER1_TMMEN_Msk;     /* enables input clock supply */
    CGC->PER1 |= 0x04U;
    TMM->TMSTR |= _04_TMM_TM0_COUNT_CONTINUES | _08_TMM_TM1_COUNT_CONTINUES;
    TMM->TMSTR &= (uint8_t)~(_02_TMM_TM1_COUNT_START | _01_TMM_TM0_COUNT_START);
    /* the TMGRD0/TMGRC1/GMGRD1 is used as buffer register of TMGRB0/TMGRA1/TMGRB1 */
    TMM->TMMR = _80_TMM_TMGRD1_BUFFER | _40_TMM_TMGRC1_BUFFER | _20_TMM_TMGRD0_BUFFER;
    /* the counter is free running */
    TMM->TMCR0 = _00_TMM_COUNTER_CLEAR_DISABLE | clk;
    TMM->TMCR1 = _00_TMM_COUNTER_CLEAR_DISABLE | clk;
    /* Set the initial level and active level: OLS1, OLS0, CMD1, CMD0 */
    TMM->TMFCR |= _02_TMM_TRANSFER_TM1_UNDERFLOW | _00_TMM_NORMAL_PHASE_LEVEl_HL | _00_TMM_COUNTER_PHASE_LEVEl_HL;
    /* PWM output pulse forced cutoff control */
    TMM->TMDF0 = _10_TMM_TMIOB_HIGHIMPEDANCE_OUTPUT | _01_TMM_TMIOD_HIGHIMPEDANCE_OUTPUT;
    TMM->TMDF1 = _40_TMM_TMIOA_HIGHIMPEDANCE_OUTPUT | _10_TMM_TMIOB_HIGHIMPEDANCE_OUTPUT | _04_TMM_TMIOC_HIGHIMPEDANCE_OUTPUT | _01_TMM_TMIOD_HIGHIMPEDANCE_OUTPUT;
    /* PWM output pulse forced cutoff enable */
    TMM->TMELC = _20_TMM1_CUTOFF_ENABLED | _02_TMM0_CUTOFF_ENABLED;
    TMM->TMOER2 = _80_TMM_ALL_OUTPUT_ENABLE;
#if 0
    /* The output is enabled */
    TMM->TMOER1 = _01_TMM_TMIOA0_OUTPUT_DISABLE | _00_TMM_TMIOB0_OUTPUT_ENABLE | _00_TMM_TMIOC0_OUTPUT_ENABLE | _00_TMM_TMIOD0_OUTPUT_ENABLE |
                  _00_TMM_TMIOA1_OUTPUT_ENABLE | _00_TMM_TMIOB1_OUTPUT_ENABLE | _00_TMM_TMIOC1_OUTPUT_ENABLE | _00_TMM_TMIOD1_OUTPUT_ENABLE;
#endif
    /* Set the interrupt enable register */
    TMM->TMIER0 = _00_TMM_OVIE_DISABLE | _00_TMM_IMID_DISABLE | _00_TMM_IMIC_DISABLE | _00_TMM_IMIB_DISABLE | _01_TMM_IMIA_ENABLE;
    TMM->TMIER1 = _00_TMM_OVIE_DISABLE | _00_TMM_IMID_DISABLE | _00_TMM_IMIC_DISABLE | _00_TMM_IMIB_DISABLE | _00_TMM_IMIA_DISABLE;

    TMM->OPCTL0 = _00_TMM_PWMOP_NO_CUTOFF;

    TMM->TM0    = (uint16_t)MTR_DEADTIME_SET;
    TMM->TM1    = 0U;
    TMM->TMGRA0 = (uint16_t)period;
    TMM->TMGRD0 = (uint16_t)period/2;
    TMM->TMGRB0 = (uint16_t)period/2;
    TMM->TMGRC1 = (uint16_t)period/2;
    TMM->TMGRA1 = (uint16_t)period/2;
    TMM->TMGRD1 = (uint16_t)period/2;
    TMM->TMGRB1 = (uint16_t)period/2;

    /* Set TMIOC0 pin */
    TMOC0_PORT_SETTING();

    /* Set TMIOB0/U+ pin */
    TMOB0_PORT_SETTING();
    /* Set TMIOD0/U- pin */
    TMOD0_PORT_SETTING();
    /* Set TMIOA1/V+ pin */
    TMOA1_PORT_SETTING();
    /* Set TMIOC1/V- pin */
    TMOC1_PORT_SETTING();
    /* Set TMIOB1/W+ pin */
    TMOB1_PORT_SETTING();
    /* Set TMIOD1/W- pin */
    TMOD1_PORT_SETTING();


    INTC_EnableIRQ(TMM0_IRQn);/* enable INTTMM0 interrupt */
    INTC_EnableIRQ(TMM1_IRQn);/* enable INTTMM0 interrupt */
    TMM->TMSTR |= _02_TMM_TM1_COUNT_START | _01_TMM_TM0_COUNT_START;
}
/***********************************************************************************************************************
* Function Name: TMM0_Start
* @brief  This function starts TM0 counter.
* @param  None
* @return None
***********************************************************************************************************************/
void TMM0_Start(void)
{
    volatile uint8_t tmsr_dummy;

    INTC_ClearPendingIRQ(TMM0_IRQn);/* clear INTTMM0 interrupt flag */
    tmsr_dummy = TMM->TMSR0; /* read TMSR0 before write 0 */
    TMM->TMSR0 = 0x00U; /* clear TM0 each interrupt request */
    INTC_EnableIRQ(TMM0_IRQn);/* enable INTTMM0 interrupt */
    TMM->TMSTR |= _04_TMM_TM0_COUNT_CONTINUES;
    TMM->TMSTR |= _01_TMM_TM0_COUNT_START;
}
/***********************************************************************************************************************
* Function Name: TMM0_Stop
* @brief  This function stops TM0 counter.
* @param  None
* @return None
***********************************************************************************************************************/
void TMM0_Stop(void)
{
    volatile uint8_t tmsr_dummy;

    TMM->TMSTR |= _04_TMM_TM0_COUNT_CONTINUES;
    TMM->TMSTR &= (uint8_t)~_01_TMM_TM0_COUNT_START;
    INTC_DisableIRQ(TMM0_IRQn);/* disable INTTMM0 interrupt */
    INTC_ClearPendingIRQ(TMM0_IRQn);/* clear INTTMM0 interrupt flag */
    tmsr_dummy = TMM->TMSR0; /* read TMSR0 before write 0 */
    TMM->TMSR0 = 0x00U; /* clear TM0 each interrupt request */
}
/***********************************************************************************************************************
* Function Name: TMM1_InputCapture
* @brief  The TMM1 operates in input capture mode.
* @param  clk - select count source clock
* @return None
***********************************************************************************************************************/
void TMM1_InputCapture(tmm_clock_t clk)
{
    CGC->PER1 |= CGC_PER1_TMMEN_Msk;     /* enables input clock supply */
    TMM->TMSTR |= _08_TMM_TM1_COUNT_CONTINUES;
    TMM->TMSTR &= (uint8_t)~_02_TMM_TM1_COUNT_START;
    /* the TMGRC1/GMGRD1 is used as buffer register of TMGRA1/TMGRB1 */
    TMM->TMMR = _40_TMM_TMGRC1_BUFFER | _80_TMM_TMGRD1_BUFFER;
    TMM->TMCR1 = _00_TMM_COUNTER_CLEAR_DISABLE | clk;
    TMM->TMIORA1 = _40_TMM_TMGRB_CAPTURE | _00_TMM_TMGRB_CAPTURE_RISING | 
                   _04_TMM_TMGRA_CAPTURE | _00_TMM_TMGRA_CAPTURE_RISING;
    TMM->TMIORC1 = _80_TMM_TMGRD_GENERAL_BUFFER_REGISTER | _40_TMM_TMGRD_CAPTURE |
                   _08_TMM_TMGRC_GENERAL_BUFFER_REGISTER | _04_TMM_TMGRC_CAPTURE;
    TMM->TMIER1 = _10_TMM_OVIE_ENABLE | _02_TMM_IMIB_ENABLE | _01_TMM_IMIA_ENABLE;
    TMM->TMPOCR1 = _00_TMIOD_OUTPUT_ACTIVE_L | _00_TMIOC_OUTPUT_ACTIVE_L | _00_TMIOB_OUTPUT_ACTIVE_L;
}
/***********************************************************************************************************************
* Function Name: TMM1_Get_PulseWidth
* @brief  The TMM1 operates as pulse width measure.
* @param  clk - select count source clock
* @param  ch - specify the active channel
* @return width - the width of specified level
***********************************************************************************************************************/
uint32_t TMM1_Get_PulseWidth(tmm_clock_t clk, tmm_channel_t ch)
{
    uint32_t width;

    TMM1_InputCapture(clk);

    /* input capture at both edges*/
    TMM->TMIORA0 |= _20_TMM_TMGRB_CAPTURE_BOTH | _02_TMM_TMGRA_CAPTURE_BOTH;

    if(ch == TMM_CHANNELA)
    {
        /* Set TMIOA1 pin */
        TMIA1_PORT_SETTING();
        TMM1_Start();

        g_tmm1_intTaken_a = 0U;
        g_tmm1_overflow_count_a = 0U;
        while(g_tmm1_intTaken_a != 2);    

        width = g_tmm1_active_width_a;
    }
    if(ch == TMM_CHANNELB)
    {
        /* Set TMIOB1 pin */
        TMIB1_PORT_SETTING();
        TMM1_Start();

        g_tmm1_intTaken_b = 0U;
        g_tmm1_overflow_count_b = 0U;
        while(g_tmm1_intTaken_b != 2);    
        
        width = g_tmm1_active_width_b;
    }

    return (width);
}
/***********************************************************************************************************************
* Function Name: TMM1_Get_PulsePeriod
* @brief  The TMM1 operates as pulse period measure.
* @param  clk - select count source clock
* @param  ch - specify the active channel
* @return period - the period of pulse
***********************************************************************************************************************/
uint32_t TMM1_Get_PulsePeriod(tmm_clock_t clk,tmm_channel_t ch)
{
    volatile uint16_t tmp;
    uint32_t period;

    TMM1_InputCapture(clk);

#if 1
    /* measure the pulse period from rising edge to rising edge */
    TMM->TMIORA0 |= _00_TMM_TMGRB_CAPTURE_RISING | _00_TMM_TMGRA_CAPTURE_RISING;
#else
    /* measure the pulse period from falling edge to falling edge */
    TMM->TMIORA0 |= _10_TMM_TMGRB_CAPTURE_BOTH | _01_TMM_TMGRA_CAPTURE_FALLING;
#endif

    if(ch == TMM_CHANNELA)
    {
        /* Set TMIOA1 pin */
        TMIA1_PORT_SETTING();
        TMM1_Start();

        g_tmm1_intTaken_a = 0U;
        g_tmm1_overflow_count_a = 0U;
        while(g_tmm1_intTaken_a != 2);    

        period = g_tmm1_active_width_a;
    }
    if(ch == TMM_CHANNELB)
    {
        /* Set TMIOB1 pin */
        TMIB1_PORT_SETTING();
        TMM1_Start();

        g_tmm1_intTaken_b = 0U;
        g_tmm1_overflow_count_b = 0U;
        while(g_tmm1_intTaken_b != 2);    
        
        period = g_tmm1_active_width_b;
    }

    return (period);
}
/***********************************************************************************************************************
* Function Name: TMM1_OutputCompare
* @brief  The TMM1 operates in output compare mode.
* @param  clk - select count source clock
* @return None
***********************************************************************************************************************/
void TMM1_OutputCompare(tmm_clock_t clk)
{
    CGC->PER1 |= CGC_PER1_TMMEN_Msk;     /* enables input clock supply */
    CGC->PER1 |= 0x04U;
    TMM->TMSTR |= _08_TMM_TM1_COUNT_CONTINUES;
    TMM->TMSTR &= (uint8_t)~_02_TMM_TM1_COUNT_START;
    /* the TMGRC and TMGRD are used as general register */
    TMM->TMMR |= _00_TMM_TMGRC1_GENERAL | _00_TMM_TMGRD1_GENERAL;
#if 1
    /* the counter is cleared when it matches the TMGRA register */ 
    TMM->TMCR1 = _20_TMM_COUNTER_CLEAR_TMGRA | clk;
#else
    /* the counter is free running */
    TMM->TMCR1 = _00_TMM_COUNTER_CLEAR_DISABLE | clk;
#endif
    /* Set the output level when the counter matches with TMGRA and TMGRB reigister */
    TMM->TMIORA1 = _00_TMM_TMGRB_COMPARE | _30_TMM_TMGRB_COMPARE_OUTPUT_TOGGLE | _00_TMM_TMGRA_COMPARE | _03_TMM_TMGRA_COMPARE_OUTPUT_TOGGLE;
    /* Set the output level when the counter matches with TMGRC and TMGRD reigister */
#if 1
    TMM->TMIORC1 = _00_TMM_TMGRD_OUTPUT_REGISTER | _00_TMM_TMGRD_COMPARE | _30_TMM_TMGRD_COMPARE_OUTPUT_TOGGLE |
                   _00_TMM_TMGRC_OUTPUT_REGISTER | _00_TMM_TMGRC_COMPARE | _03_TMM_TMGRC_COMPARE_OUTPUT_TOGGLE;
#else
    TMM->TMIORC1 = _80_TMM_TMGRD_GENERAL_BUFFER_REGISTER | _00_TMM_TMGRD_COMPARE | _10_TMM_TMGRD_COMPARE_OUTPUT_LOW |
                   _08_TMM_TMGRC_GENERAL_BUFFER_REGISTER | _00_TMM_TMGRC_COMPARE | _01_TMM_TMGRC_COMPARE_OUTPUT_LOW;
#endif
    /* Set the initial level of the output pins */
    TMM->TMOCR |= _00_TMM_TMIOA1_INITIAL_OUTPUT_L | _00_TMM_TMIOB1_INITIAL_OUTPUT_L | _00_TMM_TMIOC1_INITIAL_OUTPUT_L | _00_TMM_TMIOD1_INITIAL_OUTPUT_L;
    /* The output is enabled */
    TMM->TMOER1 &= 0x0FU;
#if 1
    TMM->TMOER1 |= _00_TMM_TMIOA1_OUTPUT_ENABLE | _00_TMM_TMIOB1_OUTPUT_ENABLE | _40_TMM_TMIOC1_OUTPUT_DISABLE | _80_TMM_TMIOD1_OUTPUT_DISABLE;
#else
    TMM->TMOER1 |= _00_TMM_TMIOA1_OUTPUT_ENABLE | _00_TMM_TMIOB1_OUTPUT_ENABLE | _00_TMM_TMIOC1_OUTPUT_ENABLE | _00_TMM_TMIOD1_OUTPUT_ENABLE;
#endif
    /* Set the interrupt enable register */
    TMM->TMIER1 = _00_TMM_OVIE_DISABLE | _00_TMM_IMID_DISABLE | _00_TMM_IMIC_DISABLE | _00_TMM_IMIB_DISABLE | _01_TMM_IMIA_ENABLE;
    
    TMM->OPCTL0 = _00_TMM_PWMOP_NO_CUTOFF;
}

/***********************************************************************************************************************
* Function Name: TMM1_DoublePulseOutput
* @brief  The TMM operates as double pulse output.
* @param  clk - select count source clock
* @param  m - the value of TMGRA register. it is the period of TMIOA1 and TMIOB1 output pulse.
* @param  n - the value of TMGRC register. it is the toggle point of TMIOA1.
* @param  p - the value of TMGRB register. it is the toggle point of TMIOB1.
* @param  q - the value of TMGRD register. it is the toggle point of TMIOB1.
* @return None
* @note   The value of m MUST be greater than the value of n, p, q. [m > m/p/q]
*
*            ^
*       FFFFH|
*            |
*TMGRA1 = m-1|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
*            |                    _| |                    _| |
*            |                  _|   |                  _|   |
*            |                _|     |                _|     |
*TMGRC1 = n-1|_ _ _ _ _ _ _ _|_ _ _ _|_ _ _ _ _ _ _ _|_ _ _ _|_ _ _ _
*            |            _| |       |            _| |       |
*TMGRB1 = p-1|_ _ _ _ _ _|_ _|_ _ _ _|_ _ _ _ _ _|_ _|_ _ _ _|_ _ _ _
*            |        _| |   |       |        _| |   |       |        
*            |      _|   |   |       |      _|   |   |       |      _  
*TMGRD1 = q-1|_ _ _|_ _ _|_ _|_ _ _ _|_ _ _|_ _ _|_ _|_ _ _ _|_ _ _|    
*            |  _| |     |   |       |  _| |     |   |       |  _|      
*       0000H|_|___|_____|___|_______|_|___|_____|___|_______|_|______
*                  |     |   |       |     |     |   |       |
*                  |     |   |_______|     |     |   |_______|
*     TMIOA1 ______|_____|___|       |_____|_____|___|       |________
*                  |     |   |       |__   |     |   |       |__
* TMSR1.IMFA ______|_____|___|_______|  |__|_____|___|_______|  |_____
*                  |     |   |__________   |     |   |__________
* TMSR1.IMFC ______|_____|___|          |__|_____|___|          |_____
*                  |     |                 |     |
*                  |_____|                 |_____|
*     TMIOB1 ______|     |_________________|     |____________________
*                  |     |______________   |     |______________
* TMSR1.IMFB ______|_____|              |__|_____|              |_____
*                  |____________________   |____________________
* TMSR1.IMFD ______|                    |__|                    |_____
*                                                 
***********************************************************************************************************************/
void TMM1_DoublePulseOutput(tmm_clock_t clk, uint16_t m, uint16_t n, uint16_t p, uint16_t q)
{
    TMM1_OutputCompare(clk);
    TMM->TMGRA1 = m -1;
    TMM->TMGRC1 = n -1 ;
    TMM->TMGRB1 = p -1 ;
    TMM->TMGRD1 = q -1 ;

    /* Set TMIOA1 pin */
    TMOA1_PORT_SETTING();
    /* Set TMIOB1 pin */
    TMOB1_PORT_SETTING();

    TMM1_Start();
}
/***********************************************************************************************************************
* Function Name: TMM1_PWM_1Perdod_3Duty
* @brief  The TMM1 operates as PWM output mode.
* @param  clk - select count source clock
* @param  period - the period of PWM wave
* @param  duty1 - the duty of TMIOB1 output wave
* @param  duty2 - the duty of TMIOC1 output wave
* @param  duty3 - the duty of TMIOD1 output wave
* @return None
* @note   period = m, duty1 = n, duty2 = p, duty3 = q
*
*            ^
*       FFFFH|
*            |
*TMGRA1 = m-1|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
*            |                    _| |                    _| |
*            |                  _|   |                  _|   |
*            |                _|     |                _|     |
*TMGRB1 = n-1|_ _ _ _ _ _ _ _|_ _ _ _|_ _ _ _ _ _ _ _|_ _ _ _|_ _ _ _
*            |            _| |       |            _| |       |
*TMGRC1 = p-1|_ _ _ _ _ _|_ _|_ _ _ _|_ _ _ _ _ _|_ _|_ _ _ _|_ _ _ _
*            |        _| |   |       |        _| |   |       |        
*            |      _|   |   |       |      _|   |   |       |      _  
*TMGRD1 = q-1|_ _ _|_ _ _|_ _|_ _ _ _|_ _ _|_ _ _|_ _|_ _ _ _|_ _ _|    
*            |  _| |     |   |       |  _| |     |   |       |  _|      
*       0000H|_|___|_____|___|_______|_|___|_____|___|_______|_|______
*                  |     |   |       |     |     |   |       |
*            ______|_____|___|       |_____|_____|___|       |________
*     TMIOB1       |     |   |_______|     |     |   |_______|        
*            ______|_____|   |       |_____|_____|   |       |________
*     TMIOC1       |     |___|_______|     |     |___|_______|        
*            ______|     |   |       |_____|     |   |       |________
*     TMIOD1       |_____|___|_______|     |_____|___|_______|        
*                  |     |   |       |     |     |   |       |  
*                  |     |   |       |__   |     |   |       |__
* TMSR1.IMFA ______|_____|___|_______|  |__|_____|___|_______|  |_____
*                  |     |   |__________   |     |   |__________
* TMSR1.IMFB ______|_____|___|          |__|_____|___|          |_____
*                  |     |______________   |     |______________
* TMSR1.IMFC ______|_____|              |__|_____|              |_____
*                  |____________________   |____________________
* TMSR1.IMFD ______|                    |__|                    |_____
*                                                 
***********************************************************************************************************************/
void TMM1_PWM_1Perdod_3Duty(tmm_clock_t clk, uint16_t period, uint16_t duty1, uint16_t duty2, uint16_t duty3)
{
    CGC->PER1 |= CGC_PER1_TMMEN_Msk;     /* enables input clock supply */
    CGC->PER1 |= 0x04U;    /* PWMOPEN = 1 */
    TMM->TMSTR |= _08_TMM_TM1_COUNT_CONTINUES;
    TMM->TMSTR &= (uint8_t)~_02_TMM_TM1_COUNT_START;
    /* the TMGRC and TMGRD are used as general register */
    TMM->TMMR |= _00_TMM_TMGRC1_GENERAL | _00_TMM_TMGRD1_GENERAL;
    /* the counter is cleared when it matches the TMGRA register */ 
    TMM->TMCR1 = _20_TMM_COUNTER_CLEAR_TMGRA | clk;
    /* TMIOB1/TMIOC1/TMIOD1 is used as PWM output */
    TMM->TMPMR |= _10_TMM_TMIOB1_PWM_MODE | _20_TMM_TMIOC1_PWM_MODE | _40_TMM_TMIOD1_PWM_MODE;
    /* Set the active level of the output pins */
    TMM->TMPOCR1 = _00_TMIOD_OUTPUT_ACTIVE_L | _00_TMIOC_OUTPUT_ACTIVE_L | _00_TMIOB_OUTPUT_ACTIVE_L;
    /* Set the initial level of the output pins */
    TMM->TMOCR |= _00_TMM_TMIOB1_INITIAL_OUTPUT_L | _00_TMM_TMIOC1_INITIAL_OUTPUT_L | _00_TMM_TMIOD1_INITIAL_OUTPUT_L;
    /* PWM output pulse forced cutoff control */
    TMM->TMDF1 = _10_TMM_TMIOB_HIGHIMPEDANCE_OUTPUT | _04_TMM_TMIOC_HIGHIMPEDANCE_OUTPUT | _01_TMM_TMIOD_HIGHIMPEDANCE_OUTPUT;
    /* PWM output pulse forced cutoff enable */
    TMM->TMELC |= _20_TMM1_CUTOFF_ENABLED | _02_TMM0_CUTOFF_ENABLED;  /* ELCOBE1 = 1, ELCOBE0 = 1 */
    TMM->TMOER2 = _80_TMM_ALL_OUTPUT_ENABLE;  /* TMPTO = 1 */
    /* The output is enabled */
    TMM->TMOER1 &= 0x0FU;
    TMM->TMOER1 |= _10_TMM_TMIOA1_OUTPUT_DISABLE | _00_TMM_TMIOB1_OUTPUT_ENABLE | _00_TMM_TMIOC1_OUTPUT_ENABLE | _00_TMM_TMIOD1_OUTPUT_ENABLE;
    /* Set the interrupt enable register */
    TMM->TMIER1 = _00_TMM_OVIE_DISABLE | _00_TMM_IMID_DISABLE | _00_TMM_IMIC_DISABLE | _00_TMM_IMIB_DISABLE | _01_TMM_IMIA_ENABLE;
    /* Set PWMOP register */
    TMM->OPCTL0 = _00_TMM_PWMOP_NO_CUTOFF;

    /* Set period and duty */
    TMM->TMGRA1 = period - 1;
    TMM->TMGRB1 = duty1 - 1;
    TMM->TMGRC1 = duty2 - 1;
    TMM->TMGRD1 = duty3 - 1;

    /* Set TMIOB1 pin */
    TMOB1_PORT_SETTING();
    /* Set TMIOC1 pin */
    TMOC1_PORT_SETTING();
    /* Set TMIOD1 pin */
    TMOD1_PORT_SETTING();

    TMM1_Start();
}
/***********************************************************************************************************************
* Function Name: TMM1_Start
* @brief  This function starts TM1 counter.
* @param  None
* @return None
***********************************************************************************************************************/
void TMM1_Start(void)
{
    volatile uint8_t tmsr_dummy;

    INTC_ClearPendingIRQ(TMM1_IRQn);/* clear INTTMM1 interrupt flag */
    tmsr_dummy = TMM->TMSR1; /* read TMSR1 before write 0 */
    TMM->TMSR1 = 0x00U; /* clear TM1 each interrupt request */
    INTC_EnableIRQ(TMM1_IRQn);/* enable INTTMM1 interrupt */
    TMM->TMSTR |= _08_TMM_TM1_COUNT_CONTINUES;
    TMM->TMSTR |= _02_TMM_TM1_COUNT_START;
}
/***********************************************************************************************************************
* Function Name: TMM1_Stop
* @brief  This function stops TM1 counter.
* @param  None
* @return None
***********************************************************************************************************************/
void TMM1_Stop(void)
{
    volatile uint8_t tmsr_dummy;

    TMM->TMSTR |= _08_TMM_TM1_COUNT_CONTINUES;
    TMM->TMSTR &= (uint8_t)~_02_TMM_TM1_COUNT_START;
    INTC_DisableIRQ(TMM1_IRQn);/* disable INTTMM1 interrupt */
    INTC_ClearPendingIRQ(TMM1_IRQn);/* clear INTTMM1 interrupt flag */
    tmsr_dummy = TMM->TMSR1; /* read TMSR1 before write 0 */
    TMM->TMSR1 = 0x00U; /* clear TM0 each interrupt request */
}
/***********************************************************************************************************************
* Function Name: TMM_Set_PowerOff
* @brief  This function stops the clock supplied for TMM.
* @param  None
* @return None
***********************************************************************************************************************/
void TMM_Set_PowerOff(void)
{
    CGC->PER1 &= ~CGC_PER1_TMMEN_Msk;     /* disables input clock supply */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
