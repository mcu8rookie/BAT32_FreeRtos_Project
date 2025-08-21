/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    timb.h
* @brief   This file implements device driver for TMB module.
* @version 1.0.0
* @date    2020/4/4
***********************************************************************************************************************/
#ifndef TMB_H
#define TMB_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Timer B status resister (TBSR) 
*/
/* Count direction flag (TBDIRF) */
#define _00_TMB_REGISTER_DECREMENTED              (0x00U) /* TB register is decremented */
#define _10_TMB_REGISTER_INCREMENTED              (0x10U) /* TB register is incremented */
/* Overflow flag (TBOVF) */
#define _00_TMB_WRITE0_OVERFLOW                   (0x00U) /* write 0 after reading */
#define _08_TMB_REGISTER_OVERFLOW                 (0x08U) /* when the TB register overflows */
/* Underflow flag (TBUDF) */
#define _00_TMB_WRITE0_UNDERFLOW                  (0x00U) /* write 0 after reading */
#define _04_TMB_REGISTER_UNDERFLOW                (0x04U) /* when the TB register underflows */
/* Input-capture/compare-match interrupt enable B (TBIMFB) */
#define _00_TMB_WRITE0_MATCHB                     (0x00U) /* write 0 after reading */
#define _02_TMB_TBIOB_MATCH                       (0x02U) /* input edge of TBIOB pin/When the values of registers TB and TBGRB match */
/* Input-capture/compare-match interrupt enable A (TBIMFA) */
#define _00_TMB_WRITE0_MATCHA                     (0x00U) /* write 0 after reading */
#define _01_TMB_TBIOA_MATCH                       (0x01U) /* input edge of TBIOA pin/When the values of registers TB and TBGRA match */

/*
    Timer B mode resister (TBMR) 
*/
/* TB count start (TBSTART) */
#define _00_TMB_COUNT_STOP                        (0x00U) /* count stops */
#define _80_TMB_COUNT_START                       (0x80U) /* count starts */
/* ELC input capture request select (TBELCICE) */
#define _00_TMB_SIGNALB_SELECTED                  (0x00U) /* external output signal B/digital filtering signal B is selected */
#define _40_TMB_ELC_SELECTED                      (0x40U) /* event input (input capture) from ELC is selected */
/* Digital filter function clock select (TBDFCK1,TBDFCK0) */
#define _00_TMB_fCLK_32_SELECTED                  (0x00U) /* fCLK/32 */
#define _10_TMB_fCLK_8_SELECTED                   (0x10U) /* fCLK/8 */
#define _20_TMB_fCLK_SELECTED                     (0x20U) /* fCLK */
#define _30_TMB_REGISTER_SELECT                   (0x30U) /* clock selected by bits TBTCK0 to TBTCK2 in TBCR register */
/* Digital filer function select for TBIOB pin (TBDFB) */
#define _00_TMB_TBIOB_FILTER_USED                 (0x00U) /* digital filter function not used */
#define _08_TMB_TBIOB_FILTER_UNUSED               (0x08U) /* digital filter function used */
/* Digital filer function select for TBIOA pin (TBDFA) */
#define _00_TMB_TBIOA_FILTER_USED                 (0x00U) /* digital filter function not used */
#define _04_TMB_TBIOA_FILTER_UNUSED               (0x04U) /* digital filter function used */
/* Phase counting mode select (TBMDF) */
#define _00_TMB_INCREMENT_MODE                    (0x00U) /* increment */
#define _02_TMB_COUNTING_MODE                     (0x02U) /* phase counting mode */
/* PWM mode select (TBPWM) */
#define _00_TMB_TIMER_MODE                        (0x00U) /* timer Mode */
#define _01_TMB_PWM_MODE                          (0x01U) /* pwm mode */

/*
    Timer B count control resister (TBCNTC) 
*/
/* Counter enable 7 (CNTEN7) */
#define _00_TMB_COUNTER7_DISABLE                  (0x00U) /* disabled */
#define _80_TMB_COUNTER7_INCREMNET                (0x80U) /* increment */
/* Counter enable 6 (CNTEN6) */
#define _00_TMB_COUNTER6_DISABLE                  (0x00U) /* disabled */
#define _40_TMB_COUNTER6_INCREMNET                (0x40U) /* increment */
/* Counter enable 5 (CNTEN5) */
#define _00_TMB_COUNTER5_DISABLE                  (0x00U) /* disabled */
#define _20_TMB_COUNTER5_INCREMNET                (0x20U) /* increment */
/* Counter enable 4 (CNTEN4) */
#define _00_TMB_COUNTER4_DISABLE                  (0x00U) /* disabled */
#define _10_TMB_COUNTER4_INCREMNET                (0x10U) /* increment */
/* Counter enable 3 (CNTEN3) */
#define _00_TMB_COUNTER3_DISABLE                  (0x00U) /* disabled */
#define _08_TMB_COUNTER3_INCREMNET                (0x08U) /* increment */
/* Counter enable 2 (CNTEN2) */
#define _00_TMB_COUNTER2_DISABLE                  (0x00U) /* disabled */
#define _04_TMB_COUNTER2_INCREMNET                (0x04U) /* increment */
/* Counter enable 1 (CNTEN1) */
#define _00_TMB_COUNTER1_DISABLE                  (0x00U) /* disabled */
#define _02_TMB_COUNTER1_INCREMNET                (0x02U) /* increment */
/* Counter enable 0 (CNTEN0) */
#define _00_TMB_COUNTER0_DISABLE                  (0x00U) /* disabled */
#define _01_TMB_COUNTER0_INCREMNET                (0x01U) /* increment */

/*
    Timer B control resister (TBCR) 
*/
/* TB register clear source select (TBCCLR1,TBCCLR0) */
#define _00_TMB_CLEAR_DISABLEED                   (0x00U) /* clear disabled */
#define _20_TMB_CLEAR_TBGRA                       (0x20U) /* clear by input capture or compare match with TBGRA */
#define _40_TMB_CLEAR_TBGRB                       (0x40U) /* clear by input capture or compare match with TBGRB */
/* External clock active edge select (TBCKEG1,TBCKEG0) */
#define _00_TMB_COUNT_RISING                      (0x00U) /* count at the rising edge */
#define _08_TMB_COUNT_FALLING                     (0x08U) /* count at the falling edge */
#define _10_TMB_COUNT_BOTH                        (0x10U) /* count at both the rising/falling edges */
/* Count source select (TBTCK2,TBTCK1,TBTCK0) */
#define _00_TMB_fCLK_SELECTED                     (0x00U) /* fCLK */
#define _01_TMB_fCLK_2_SELECTED                   (0x01U) /* fCLK/2 */
#define _02_TMB_fCLK_4_SELECTED                   (0x02U) /* fCLK/4 */
#define _03_TMB_fCLK_8_SELECTED                   (0x03U) /* fCLK/8 */
#define _04_TMB_fCLK_32_SELECTED                  (0x04U) /* fCLK/32 */
#define _05_TMB_TBCLKA_INPUT                      (0x05U) /* TBCLKA input */
#define _07_TMB_TBCLKB_INPUT                      (0x07U) /* TBCLKB input */

/*
    Timer B interrupt enable resister (TBIER) 
*/
/* Overflow interrupt enable (TBOVIE) */
#define _00_TMB_INTERRUPT_TBOVF_DISABLE           (0x00U) /* interrupt by TBOVF bit disabled */
#define _08_TMB_INTERRUPT_TBOVF_ENABLE            (0x08U) /* interrupt by TBOVF bit enabled */
/* Underflow interrupt enable (TBUDIE) */
#define _00_TMB_INTERRUPT_TBUDF_DISABLE           (0x00U) /* interrupt by TBUDF bit disabled */
#define _04_TMB_INTERRUPT_TBUDF_ENABLE            (0x04U) /* interrupt by TBUDF bit enabled */
/* Input-capture/compare-match interrupt enable B (TBIMIEB) */
#define _00_TMB_INTERRUPT_TBIMFB_DISABLE          (0x00U) /* interrupt by TBIMFB bit disabled */
#define _02_TMB_INTERRUPT_TBIMFB_ENABLE           (0x02U) /* interrupt by TBIMFB bit enabled */
/* Input-capture/compare-match interrupt enable A (TBIMIEA) */
#define _00_TMB_INTERRUPT_TBIMFA_DISABLE          (0x00U) /* interrupt by TBIMFA bit disabled */
#define _01_TMB_INTERRUPT_TBIMFA_ENABLE           (0x01U) /* interrupt by TBIMFA bit enabled */

/*
    Timer B I/O control resister (TBIOR) 
*/
/* TBGRD register function select (TBBUFB) */
#define _00_TMB_TBGRB_REGISTER_UNUSED             (0x00U) /* not used as buffer register for TBGRB register */
#define _80_TMB_TBGRB_REGISTER_USED               (0x80U) /* used as buffer register for TBGRB register */
/* TBGRB mode select (TBIOB2) */
#define _00_TMB_TBGRB_OUTPUT_COMPARE              (0x00U) /* output compare function */
#define _40_TMB_TBGRB_INPUT_CAPTURE               (0x40U) /* input capture function */
/* TBGRB control (TBIOB1,TBIOB0) */
#define _00_TMB_TBGRB_OUTPUT_DISABLED             (0x00U) /* pin output by compare match is disabled */
#define _10_TMB_TBGRB_LOW_OUTPUT                  (0x10U) /* low output */
#define _20_TMB_TBGRB_HIGH_OUTPUT                 (0x20U) /* high output */
#define _30_TMB_TBGRB_TOGGLE_OUTPUT               (0x30U) /* toggle output */
/* TBGRB control (TBIOB1,TBIOB0) */
#define _00_TMB_TBGRB_RISING_EDGE                 (0x00U) /* rising edge of TBIOB */
#define _10_TMB_TBGRB_FALLING_EDGE                (0x10U) /* falling edge of TBIOB */
#define _20_TMB_TBGRB_BOTH_EDGES                  (0x20U) /* both edges of TBIOB */
/* TBGRC register function select (TBBUFA) */
#define _00_TMB_TBGRA_REGISTER_UNUSED             (0x00U) /* not used as buffer register for TBGRA register */
#define _08_TMB_TBGRA_REGISTER_USED               (0x08U) /* used as buffer register for TBGRA register */
/* TBGRA mode select (TBIOA2) */
#define _00_TMB_TBGRA_OUTPUT_COMPARE              (0x00U) /* output compare function */
#define _04_TMB_TBGRA_INPUT_CAPTURE               (0x04U) /* input capture function */
/* TBGRA control (TBIOA1,TBIOA0) */
#define _00_TMB_TBGRA_OUTPUT_DISABLED             (0x00U) /* pin output by compare match is disabled */
#define _01_TMB_TBGRA_LOW_OUTPUT                  (0x01U) /* low output */
#define _02_TMB_TBGRA_HIGH_OUTPUT                 (0x02U) /* high output */
#define _03_TMB_TBGRA_TOGGLE_OUTPUT               (0x03U) /* toggle output */
/* TBGRB control (TBIOA1,TBIOA0) */
#define _00_TMB_TBGRA_RISING_EDGE                 (0x00U) /* rising edge of TBIOA */
#define _01_TMB_TBGRA_FALLING_EDGE                (0x01U) /* falling edge of TBIOA */
#define _02_TMB_TBGRA_BOTH_EDGES                  (0x02U) /* both edges of TBIOA */


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum
{
    TMB_CHANNELA,
    TMB_CHANNELB,
    TMB_CHANNELELC
} tmb_channel_t;

typedef enum
{
    TMB_CLOCK_FCLK       = 0U,
    TMB_CLOCK_FCLK2      = 1U,
    TMB_CLOCK_FCLK4      = 2U,
    TMB_CLOCK_FCLK8      = 3U,
    TMB_CLOCK_FCLK32     = 4U,
    TMB_CLOCK_TBCLKA     = 5U,
    TMB_CLOCK_TBCLKB     = 7U,
} tmb_clock_t;

/***********************************************************************************************************************
Global variables
***********************************************************************************************************************/
extern volatile uint16_t g_tmb_intTaken_a;
extern volatile uint16_t g_tmb_intTaken_b;
extern volatile uint16_t g_tmb_overflow_count_a;
extern volatile uint16_t g_tmb_overflow_count_b;
extern volatile uint32_t g_tmb_overflow_count_elc;
extern volatile uint32_t g_tmb_active_width_a;
extern volatile uint32_t g_tmb_active_width_b;
extern volatile uint32_t g_tmb_active_width_elc;

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void TMB0_InputCapture(tmb_clock_t clk);
uint32_t TMB0_Get_PulseWidth(tmb_clock_t clk, tmb_channel_t ch);
uint32_t TMB0_Get_PulsePeriod(tmb_clock_t clk,tmb_channel_t ch);
void TMB0_OutputCompare(tmb_clock_t clk);
void TMB0_DoublePulseOutput(tmb_clock_t clk, uint16_t period, uint16_t skew);
void TMB0_PWM_1Period_1Duty(tmb_clock_t clk, uint16_t period, uint16_t duty);
void TMB0_PhaseCount(uint8_t cntc_reg);
void TMB0_Start(void);
void TMB0_Stop(void);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
