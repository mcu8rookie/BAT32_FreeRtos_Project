/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    timm_user.c
* @brief   This file implements device driver for TMM module.
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
//void IRQ27_Handler(void) __attribute__((alias("tmm0_interrupt")));
//void IRQ28_Handler(void) __attribute__((alias("tmm1_interrupt")));
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* TMM0 input capture mode */
volatile uint16_t g_tmm0_intTaken_a = 0U;
volatile uint16_t g_tmm0_intTaken_b = 0U;
volatile uint32_t g_tmm0_active_width_a = 0UL;
volatile uint32_t g_tmm0_active_width_b = 0UL;
volatile uint32_t g_tmm0_active_width_c = 0UL;
volatile uint32_t g_tmm0_active_width_d = 0UL;
volatile uint32_t g_tmm0_active_width_elc = 0UL;
volatile uint32_t g_tmm0_overflow_count_a = 0UL;
volatile uint32_t g_tmm0_overflow_count_b = 0UL;
/* TMM1 input capture mode */
volatile uint16_t g_tmm1_intTaken_a = 0U;
volatile uint16_t g_tmm1_intTaken_b = 0U;
volatile uint32_t g_tmm1_active_width_a = 0UL;
volatile uint32_t g_tmm1_active_width_b = 0UL;
volatile uint32_t g_tmm1_active_width_c = 0UL;
volatile uint32_t g_tmm1_active_width_d = 0UL;
volatile uint32_t g_tmm1_active_width_elc = 0UL;
volatile uint32_t g_tmm1_overflow_count_a = 0UL;
volatile uint32_t g_tmm1_overflow_count_b = 0UL;
/* Motor Driver */
volatile uint16_t g_u2_pwm_duty;              /* PWM duty : No scaling */
volatile uint8_t  g_u1_v_pattern;             /* voltage pattern */
volatile uint8_t  g_u1_direction;             /* rotation direction (0:CW ,1:CCW) */
volatile uint8_t  g_u1_v_pattern_open[2][7] = {
                           {0,
                            MTR_PATTERN_CW_U_V,         /* 5 */
                            MTR_PATTERN_CW_W_V,         /* 1 */
                            MTR_PATTERN_CW_W_U,         /* 3 */
                            MTR_PATTERN_CW_V_U,         /* 2 */
                            MTR_PATTERN_CW_V_W,         /* 6 */
                            MTR_PATTERN_CW_U_W},        /* 4 */
                           {0,
                            MTR_PATTERN_CCW_U_W,        /* 4 */
                            MTR_PATTERN_CCW_V_W,        /* 6 */
                            MTR_PATTERN_CCW_V_U,        /* 2 */
                            MTR_PATTERN_CCW_W_U,        /* 3 */
                            MTR_PATTERN_CCW_W_V,        /* 1 */
                            MTR_PATTERN_CCW_U_V}        /* 5 */
                  };                          /* array of voltage pattern for openloop drive */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: tmm0_interrupt
* @brief  timm0 interrupt service routine for input capture mode
* @param  None
* @return None
***********************************************************************************************************************/
void tmm0_interrupt(void)
{
    INTC_ClearPendingIRQ(TMM0_IRQn); /* clear INTTMM0 interrupt flag */
    uint8_t  tmsr0_temp = TMM->TMSR0;
    uint8_t  tmier0_temp = TMM->TMIER0;

    TMM->TMIER0 = 0x00U;

    if ((TMM->TMSR0 & _10_TMM0_INTOV_GENERATE_FLAG) == _10_TMM0_INTOV_GENERATE_FLAG)
    {
        TMM->TMSR0 = tmsr0_temp & (uint8_t)~_10_TMM0_INTOV_GENERATE_FLAG;
        g_tmm0_overflow_count_a += 1U;
        g_tmm0_overflow_count_b += 1U;
    }

    if ((TMM->TMSR0 & _01_TMM0_INTA_GENERATE_FLAG) == _01_TMM0_INTA_GENERATE_FLAG)
    {
        TMM->TMSR0 = tmsr0_temp & (uint8_t)~_01_TMM0_INTA_GENERATE_FLAG;
        g_tmm0_intTaken_a++;

        if (g_tmm0_overflow_count_a == 0U)
        {
            g_tmm0_active_width_a = (TMM->TMGRA0 - TMM->TMGRC0);
        }
        else
        {
            g_tmm0_active_width_a = (TMM->TMGRA0 - TMM->TMGRC0) + (0x10000UL * g_tmm0_overflow_count_a);
            g_tmm0_overflow_count_a = 0U;
        }
    }

    if ((TMM->TMSR0 & _02_TMM0_INTB_GENERATE_FLAG) == _02_TMM0_INTB_GENERATE_FLAG)
    {
        TMM->TMSR0 = tmsr0_temp & (uint8_t)~(_02_TMM0_INTB_GENERATE_FLAG);
        g_tmm0_intTaken_b++;

        if (g_tmm0_overflow_count_b == 0U)
        {
            g_tmm0_active_width_b = (TMM->TMGRB0 - TMM->TMGRD0);
        }
        else
        {
            g_tmm0_active_width_b = (TMM->TMGRB0 - TMM->TMGRD0) + (0x10000UL * g_tmm0_overflow_count_b);
            g_tmm0_overflow_count_b = 0U;
        }
    }
    if ((TMM->TMSR0 & _04_TMM0_INTC_GENERATE_FLAG) == _04_TMM0_INTC_GENERATE_FLAG)
    {
        TMM->TMSR0 = tmsr0_temp & (uint8_t)~_04_TMM0_INTC_GENERATE_FLAG;
    }
    if ((TMM->TMSR0 & _08_TMM0_INTD_GENERATE_FLAG) == _08_TMM0_INTD_GENERATE_FLAG)
    {
        TMM->TMSR0 = tmsr0_temp & (uint8_t)~_08_TMM0_INTD_GENERATE_FLAG;
    }

    TMM->TMIER0 = tmier0_temp;
}

/***********************************************************************************************************************
* Function Name: tmm1_interrupt
* @brief  timm1 interrupt service routine for input capture mode
* @param  None
* @return None
***********************************************************************************************************************/
void tmm1_interrupt(void)
{
    INTC_ClearPendingIRQ(TMM1_IRQn); /* clear INTTMM0 interrupt flag */
    uint8_t  tmsr1_temp = TMM->TMSR1;
    uint8_t  tmier1_temp = TMM->TMIER1;

    TMM->TMIER1 = 0x00U;

    if ((TMM->TMSR1 & _10_TMM1_INTOV_GENERATE_FLAG) == _10_TMM1_INTOV_GENERATE_FLAG)
    {
        TMM->TMSR1 = tmsr1_temp & (uint8_t)~_10_TMM1_INTOV_GENERATE_FLAG;
        g_tmm1_overflow_count_a += 1U;
        g_tmm1_overflow_count_b += 1U;
    }

    if ((TMM->TMSR1 & _01_TMM1_INTA_GENERATE_FLAG) == _01_TMM1_INTA_GENERATE_FLAG)
    {
        TMM->TMSR1 = tmsr1_temp & (uint8_t)~_01_TMM1_INTA_GENERATE_FLAG;
        g_tmm1_intTaken_a++;

        if (g_tmm1_overflow_count_a == 0U)
        {
            g_tmm1_active_width_a = (TMM->TMGRA1 - TMM->TMGRC1);
        }
        else
        {
            g_tmm1_active_width_a = (TMM->TMGRA1 - TMM->TMGRC1) + (0x10000UL * g_tmm1_overflow_count_a);
            g_tmm1_overflow_count_a = 0U;
        }
    }

    if ((TMM->TMSR1 & _02_TMM1_INTB_GENERATE_FLAG) == _02_TMM1_INTB_GENERATE_FLAG)
    {
        TMM->TMSR1 = tmsr1_temp & (uint8_t)~(_02_TMM1_INTB_GENERATE_FLAG);
        g_tmm1_intTaken_b++;

        if (g_tmm1_overflow_count_b == 0U)
        {
            g_tmm1_active_width_b = (TMM->TMGRB1 - TMM->TMGRD1);
        }
        else
        {
            g_tmm1_active_width_b = (TMM->TMGRB1 - TMM->TMGRD1) + (0x10000UL * g_tmm1_overflow_count_b);
            g_tmm1_overflow_count_b = 0U;
        }
    }
    if ((TMM->TMSR1 & _04_TMM1_INTC_GENERATE_FLAG) == _04_TMM1_INTC_GENERATE_FLAG)
    {
        TMM->TMSR1 = tmsr1_temp & (uint8_t)~_04_TMM1_INTC_GENERATE_FLAG;
    }
    if ((TMM->TMSR1 & _08_TMM1_INTD_GENERATE_FLAG) == _08_TMM1_INTD_GENERATE_FLAG)
    {
        TMM->TMSR1 = tmsr1_temp & (uint8_t)~_08_TMM1_INTD_GENERATE_FLAG;
    }

    TMM->TMIER1 = tmier1_temp;
}
/******************************************************************************
* Function Name : mtr_init_trd
* @brief  Initialize Timer M
* @param  none
* @return none
******************************************************************************/
void mtr_init_tmm(void)
{
    TMM0_PWM_Complementary_3Phase(TMM_CLOCK_FCLK, MTR_CARRIER_SET, MTR_DEADTIME_SET);
}
/******************************************************************************
* Function Name : mtr_change_pattern
* @brief  Change voltage pattern
* @param  u1_pattern - Voltage pattern
* @return none
******************************************************************************/
void mtr_change_pattern(uint8_t u1_pattern)
{
    /*========================*/
    /*     stop PWM timer     */
    /*========================*/
    //TMM->TMSTR = 0x0C;                          /* stop TM0 */

    /*======================*/
    /*     set register     */
    /*======================*/
    /* PWM output arm setting */
    switch (u1_pattern)
    {
        case MTR_V_PWM_WN_ON:
            TMM->TMOER1 = 0xAF;               /* Vp/Vn : PWM output enable */
            MTR_PORT_UP_CLR();                /* Up = OFF("Low") */
            MTR_PORT_UN_CLR();                /* Un = OFF("Low") */
            MTR_PORT_VP_CLR();                /* Vp = OFF("Low") */
            MTR_PORT_VN_CLR();                /* Vn = OFF("Low") */
            MTR_PORT_WP_CLR();                /* Wp = OFF("Low") */
            MTR_PORT_WN_SET();                /* Wn = ON ("High") */
        break;

        case MTR_W_PWM_VN_ON:
            TMM->TMOER1 = 0x5F;               /* Wp/Wn : PWM output enable */
            MTR_PORT_UP_CLR();                /* Up = OFF("Low") */
            MTR_PORT_UN_CLR();                /* Un = OFF("Low") */
            MTR_PORT_VP_CLR();                /* Vp = OFF("Low") */
            MTR_PORT_VN_SET();                /* Vn = ON ("High") */
            MTR_PORT_WP_CLR();                /* Wp = OFF("Low") */
            MTR_PORT_WN_CLR();                /* Wn = OFF("Low") */
        break;

        case MTR_W_PWM_UN_ON:
            TMM->TMOER1 = 0x5F;               /* Wp/Wn : PWM output enable */
            MTR_PORT_UP_CLR();                /* Up = OFF("Low") */
            MTR_PORT_UN_SET();                /* Un = ON ("High") */
            MTR_PORT_VP_CLR();                /* Vp = OFF("Low") */
            MTR_PORT_VN_CLR();                /* Vn = OFF("Low") */
            MTR_PORT_WP_CLR();                /* Wp = OFF("Low") */
            MTR_PORT_WN_CLR();                /* Wn = OFF("Low") */
        break;

        case MTR_U_PWM_WN_ON:
            TMM->TMOER1 = 0xF5;               /* Up/Un : PWM output enable */
            MTR_PORT_UP_CLR();                /* Up = OFF("Low") */
            MTR_PORT_UN_CLR();                /* Un = OFF("Low") */
            MTR_PORT_VP_CLR();                /* Vp = OFF("Low") */
            MTR_PORT_VN_CLR();                /* Vn = OFF("Low") */
            MTR_PORT_WP_CLR();                /* Wp = OFF("Low") */
            MTR_PORT_WN_SET();                /* Wn = ON ("High") */
        break;

        case MTR_U_PWM_VN_ON:
            TMM->TMOER1 = 0xF5;               /* Up/Un : PWM output enable */
            MTR_PORT_UP_CLR();                /* Up = OFF("Low") */
            MTR_PORT_UN_CLR();                /* Un = OFF("Low") */
            MTR_PORT_VP_CLR();                /* Vp = OFF("Low") */
            MTR_PORT_VN_SET();                /* Vn = ON ("High") */
            MTR_PORT_WP_CLR();                /* Wp = OFF("Low") */
            MTR_PORT_WN_CLR();                /* Wn = OFF("Low") */
        break;

        case MTR_V_PWM_UN_ON:
            TMM->TMOER1 = 0xAF;               /* Vp/Vn : PWM output enable */
            MTR_PORT_UP_CLR();                /* Up = OFF("Low") */
            MTR_PORT_UN_SET();                /* Un = ON ("High") */
            MTR_PORT_VP_CLR();                /* Vp = OFF("Low") */
            MTR_PORT_VN_CLR();                /* Vn = OFF("Low") */
            MTR_PORT_WP_CLR();                /* Wp = OFF("Low") */
            MTR_PORT_WN_CLR();                /* Wn = OFF("Low") */
        break;

        /* the default case is intentionally combined */
        default:
        break;
    }

    TMM->TMGRD0 = (int16_t)MTR_CARRIER_SET - g_u2_pwm_duty;    /* duty of U phase */
    TMM->TMGRC1 = (int16_t)MTR_CARRIER_SET - g_u2_pwm_duty;    /* duty of V phase */
    TMM->TMGRD1 = (int16_t)MTR_CARRIER_SET - g_u2_pwm_duty;    /* duty of W phase */

    /*===========================*/
    /*     restart PWM timer     */
    /*===========================*/
    //TMM->TM0 = (uint16_t)MTR_DEADTIME_SET;        /* reset TM0 */
    //TMM->TM1 = 0;

    //TMM->TMSTR = 0x0F;                          /* start TM0 */
}
/******************************************************************************
* Function Name : mtr_pattern_up_chopping
* @brief  Set voltage pattern upper arm chopping PWM
* @param  u1_pattern : voltage pattern
* @return none
******************************************************************************/
void mtr_pattern_up_chopping(uint8_t u1_pattern)
{
    /*** set voltage pattern ***/
    if (MTR_CW == g_u1_direction)               /* check rotation direction */
    {
        switch (u1_pattern)
        {
            case MTR_PATTERN_CW_W_V:            /* from W phase to V phase */
                g_u1_v_pattern = MTR_W_PWM_VN_ON;
                //mtr_set_tau_window_signal(MTR_TAU_TIMER_WP);
            break;

            case MTR_PATTERN_CW_U_V:            /* from U phase to V phase */
                g_u1_v_pattern = MTR_U_PWM_VN_ON;
                //mtr_set_tau_window_signal(MTR_TAU_TIMER_UP);
            break;

            case MTR_PATTERN_CW_U_W:            /* from U phase to W phase */
                g_u1_v_pattern = MTR_U_PWM_WN_ON;
                //mtr_set_tau_window_signal(MTR_TAU_TIMER_UP);
            break;

            case MTR_PATTERN_CW_V_W:            /* from V phase to W phase */
                g_u1_v_pattern = MTR_V_PWM_WN_ON;
                //mtr_set_tau_window_signal(MTR_TAU_TIMER_VP);
            break;

            case MTR_PATTERN_CW_V_U:            /* from V phase to U phase */
                g_u1_v_pattern = MTR_V_PWM_UN_ON;
                //mtr_set_tau_window_signal(MTR_TAU_TIMER_VP);
            break;

            case MTR_PATTERN_CW_W_U:            /* from W phase to U phase */
                g_u1_v_pattern = MTR_W_PWM_UN_ON;
                //mtr_set_tau_window_signal(MTR_TAU_TIMER_WP);
            break;

            default:                            /* pseudo Hall signal pattern error */
                g_u1_v_pattern = MTR_PATTERN_ERROR;
            break;
        }
    }
    else if (MTR_CCW == g_u1_direction)         /* check rotation direction */
    {
        switch (u1_pattern)
        {
            case MTR_PATTERN_CCW_W_V:           /* from W phase to V phase */
                g_u1_v_pattern = MTR_W_PWM_VN_ON;
                //mtr_set_tau_window_signal(MTR_TAU_TIMER_WP);
            break;

            case MTR_PATTERN_CCW_W_U:           /* from W phase to U phase */
                g_u1_v_pattern = MTR_W_PWM_UN_ON;
                //mtr_set_tau_window_signal(MTR_TAU_TIMER_WP);
            break;

            case MTR_PATTERN_CCW_V_U:           /* from V phase to U phase */
                g_u1_v_pattern = MTR_V_PWM_UN_ON;
                //mtr_set_tau_window_signal(MTR_TAU_TIMER_VP);
            break;

            case MTR_PATTERN_CCW_V_W:           /* from V phase to W phase */
                g_u1_v_pattern = MTR_V_PWM_WN_ON;
                //mtr_set_tau_window_signal(MTR_TAU_TIMER_VP);
            break;

            case MTR_PATTERN_CCW_U_W:           /* from U phase to W phase */
                g_u1_v_pattern = MTR_U_PWM_WN_ON;
                //mtr_set_tau_window_signal(MTR_TAU_TIMER_UP);
            break;

            case MTR_PATTERN_CCW_U_V:           /* from U phase to V phase */
                g_u1_v_pattern = MTR_U_PWM_VN_ON;
                //mtr_set_tau_window_signal(MTR_TAU_TIMER_UP);
            break;

            default:                            /* pseudo Hall signal pattern error */
                g_u1_v_pattern = MTR_PATTERN_ERROR;
            break;
        }
    }
    else
    {
        /* Do Nothing */
    }
}
/******************************************************************************
* Function Name : mtr_pattern_set
* @brief  Set voltage pattern
* @param  u1_pattern - voltage pattern value
* @return none
******************************************************************************/
void mtr_pattern_set(uint8_t u1_pattern)
{
   /*** set voltage pattern ***/
    mtr_pattern_up_chopping(u1_pattern);        /* Upper arm chopping pattern */

    mtr_change_pattern(g_u1_v_pattern);         /* change voltage pattern */
}
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
