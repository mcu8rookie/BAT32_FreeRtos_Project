/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    timm.h
* @brief   This file implements device driver for TMM module.
* @version 1.0.0
* @date    2020/4/4
***********************************************************************************************************************/
#ifndef TMM_H
#define TMM_H
/***********************************************************************************************************************
Macro definitions (Motor Driver)
***********************************************************************************************************************/
#define     MTR_PWM_TIMER_FREQ      (32.0f)         /* PWM timer frequency[MHz] */
#define     MTR_CARRIER_FREQ        (20.0f)         /* carrier wave frequency[kHz] */

#define     MTR_DEADTIME            (2000)          /* dead time [nsec] */
#define     MTR_DEADTIME_SET        ((int16_t)(MTR_DEADTIME*MTR_PWM_TIMER_FREQ/1000))
                                                    /* setting value of dead time */
#define     MTR_CARRIER_SET         ((MTR_PWM_TIMER_FREQ*1000/MTR_CARRIER_FREQ/2)+MTR_DEADTIME_SET-2)
                                                    /* setting value of carrier */
#define     MTR_HALF_CARRIER_SET    (MTR_CARRIER_SET/2)
                                                    /* setting value of half carrier */
#define     MTR_NDT_CARRIER_SET     (MTR_CARRIER_SET-MTR_DEADTIME_SET)
                                                    /* "MTR_CARRIER_SET" without dead time */
/* rotational direction */
#define     MTR_CW                      (0)             /* CW */
#define     MTR_CCW                     (1)             /* CCW */

/* value of bemf signal (CW) */
#define     MTR_PATTERN_CW_V_U          (3)             /* V phase to U phase */
#define     MTR_PATTERN_CW_W_U          (1)             /* W phase to U phase */
#define     MTR_PATTERN_CW_W_V          (5)             /* W phase to V phase */
#define     MTR_PATTERN_CW_U_V          (4)             /* U phase to V phase */
#define     MTR_PATTERN_CW_U_W          (6)             /* U phase to W phase */
#define     MTR_PATTERN_CW_V_W          (2)             /* V phase to W phase */

/* value of bemf signal (CCW) */
#define     MTR_PATTERN_CCW_V_U         (2)             /* V phase to U phase */
#define     MTR_PATTERN_CCW_V_W         (6)             /* V phase to W phase */
#define     MTR_PATTERN_CCW_U_W         (4)             /* U phase to W phase */
#define     MTR_PATTERN_CCW_U_V         (5)             /* U phase to V phase */
#define     MTR_PATTERN_CCW_W_V         (1)             /* W phase to V phase */
#define     MTR_PATTERN_CCW_W_U         (3)             /* W phase to U phase */

/* voltage pattern */
#define     MTR_PATTERN_ERROR           (0)             /* bemf pattern error */
#define     MTR_UP_PWM_VN_ON            (1)             /* Up(PWM) to Vn(on) */
#define     MTR_UP_PWM_WN_ON            (2)             /* Up(PWM) to Wn(on) */
#define     MTR_VP_PWM_UN_ON            (3)             /* Vp(PWM) to Un(on) */
#define     MTR_VP_PWM_WN_ON            (4)             /* Vp(PWM) to Wn(on) */
#define     MTR_WP_PWM_UN_ON            (5)             /* Wp(PWM) to Un(on) */
#define     MTR_WP_PWM_VN_ON            (6)             /* Wp(PWM) to Vn(on) */
#define     MTR_UP_ON_VN_PWM            (7)             /* Up(on) to Vn(PWM) */
#define     MTR_UP_ON_WN_PWM            (8)             /* Up(on) to Wn(PWM) */
#define     MTR_VP_ON_UN_PWM            (9)             /* Vp(on) to Un(PWM) */
#define     MTR_VP_ON_WN_PWM            (10)            /* Vp(on) to Wn(PWM) */
#define     MTR_WP_ON_UN_PWM            (11)            /* Wp(on) to Un(PWM) */
#define     MTR_WP_ON_VN_PWM            (12)            /* Wp(on) to Vn(PWM) */
#define     MTR_U_PWM_VN_ON             (13)            /* U(PWM) to Vn(on) */
#define     MTR_U_PWM_WN_ON             (14)            /* U(PWM) to Wn(on) */
#define     MTR_V_PWM_UN_ON             (15)            /* V(PWM) to Un(on) */
#define     MTR_V_PWM_WN_ON             (16)            /* V(PWM) to Wn(on) */
#define     MTR_W_PWM_UN_ON             (17)            /* W(PWM) to Un(on) */
#define     MTR_W_PWM_VN_ON             (18)            /* W(PWM) to Vn(on) */
#define     MTR_UP_ON_V_PWM             (19)            /* Up(on) to V(PWM) */
#define     MTR_UP_ON_W_PWM             (20)            /* Up(on) to W(PWM) */
#define     MTR_VP_ON_U_PWM             (21)            /* Vp(on) to U(PWM) */
#define     MTR_VP_ON_W_PWM             (22)            /* Vp(on) to W(PWM) */
#define     MTR_WP_ON_U_PWM             (23)            /* Wp(on) to U(PWM) */
#define     MTR_WP_ON_V_PWM             (24)            /* Wp(on) to V(PWM) */

/***********************************************************************************************************************
Global Variable
***********************************************************************************************************************/
extern volatile uint16_t g_u2_pwm_duty;              /* PWM duty : No scaling */
extern volatile uint8_t  g_u1_v_pattern;             /* voltage pattern */
extern volatile uint8_t  g_u1_direction;             /* rotation direction (0:CW ,1:CCW) */
extern volatile uint8_t  g_u1_v_pattern_open[2][7];  /* array of voltage pattern for openloop drive */

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Timer M ELC Register (TMELC) 
*/
/* ELC event input 0 select for timer M input capture D0 (ELCICE0) */
#define _00_TMM0_INPUTCAPTURE                        (0x00U) /* TMIOD0 input capture is selected */
#define _01_TMM0_ELC                                 (0x01U) /* event input 0 from ELC is selected */
/* ELC event input 0 enable for timer M pulse output forced cutoff (ELCOBE0) */
#define _00_TMM0_CUTOFF_DISABLED                     (0x00U) /* forced cutoff is disabled */
#define _02_TMM0_CUTOFF_ENABLED                      (0x02U) /* forced cutoff is enabled */
/* ELC event input 1 select for timer M input capture D1 (ELCICE1) */
#define _00_TMM1_INPUTCAPTURE                        (0x00U) /* TMIOD1 input capture is selected */
#define _10_TMM1_ELC                                 (0x10U) /* event input 1 from ELC is selected */
/* ELC event input 1 enable for timer M pulse output forced cutoff (ELCOBE1) */
#define _00_TMM1_CUTOFF_DISABLED                     (0x00U) /* forced cutoff is disabled */
#define _20_TMM1_CUTOFF_ENABLED                      (0x20U) /* forced cutoff is enabled */

/*
    Timer M PWM function select register (TMPMR) 
*/
/* PWM function of TMIOB0 select (TMPWMB0) */
#define _00_TMM_TMIOB0_TIMER_MODE                    (0x00U) /* input capture function or output compare function */
#define _01_TMM_TMIOB0_PWM_MODE                      (0x01U) /* PWM function */
/* PWM function of TMIOC0 select (TMPWMC0) */
#define _00_TMM_TMIOC0_TIMER_MODE                    (0x00U) /* input capture function or output compare function */
#define _02_TMM_TMIOC0_PWM_MODE                      (0x02U) /* PWM function */
/* PWM function of TMIOD0 select (TMPWMD0) */
#define _00_TMM_TMIOD0_TIMER_MODE                    (0x00U) /* input capture function or output compare function */
#define _04_TMM_TMIOD0_PWM_MODE                      (0x04U) /* PWM function */
/* PWM function of TMIOB1 select (TMPWMB1) */
#define _00_TMM_TMIOB1_TIMER_MODE                    (0x00U) /* input capture function or output compare function */
#define _10_TMM_TMIOB1_PWM_MODE                      (0x10U) /* PWM function */
/* PWM function of TMIOC1 select (TRDPWMC1) */
#define _00_TMM_TMIOC1_TIMER_MODE                    (0x00U) /* input capture function or output compare function */
#define _20_TMM_TMIOC1_PWM_MODE                      (0x20U) /* PWM function */
/* PWM function of TMIOD1 select (TRDPWMD1) */
#define _00_TMM_TMIOD1_TIMER_MODE                    (0x00U) /* input capture function or output compare function */
#define _40_TMM_TMIOD1_PWM_MODE                      (0x40U) /* PWM function */

/*
    Timer M start register (TMSTR) 
*/
/* TM0 count start flag (TSTART0) */
#define _00_TMM_TM0_COUNT_STOP                       (0x00U) /* TM0 Count stops */
#define _01_TMM_TM0_COUNT_START                      (0x01U) /* TM0 Count starts */
/* TM1 count start flag (TSTART1) */
#define _00_TMM_TM1_COUNT_STOP                       (0x00U) /* TM1 Count stops */
#define _02_TMM_TM1_COUNT_START                      (0x02U) /* TM1 Count starts */
/* TM0 count operation select (CSEL0) */
#define _00_TMM_TM0_COUNT_STOP_MATCH                 (0x00U) /* count stops at compare match with TMGRA0 register */
#define _04_TMM_TM0_COUNT_CONTINUES                  (0x04U) /* count continues after compare match with TMGRA0 register */
/* TM1 count operation select (CSEL1) */
#define _00_TMM_TM1_COUNT_STOP_MATCH                 (0x00U) /* count stops at compare match with TMGRA1 register */
#define _08_TMM_TM1_COUNT_CONTINUES                  (0x08U) /* count continues after compare match with TMGRA1 register */

/*
    Timer M function control register (TMFCR) 
*/
/* Combination mode select (CMD1,CMD0) */
#define _01_TMM_TRANSFER_RESET_SYNCHRONOUS           (0x01U) /* reset synchronous PWM mode */
#define _02_TMM_TRANSFER_TM1_UNDERFLOW               (0x02U) /* transfer from when TM1 underflows */
#define _03_TMM_TRANSFER_TM0_MATCH                   (0x03U) /* transfer at compare match between TM0 and TMGRA0 */
/* Phase output level select (OLS0) */
#define _00_TMM_NORMAL_PHASE_LEVEl_HL                (0x00U) /* high initial output and low active level */
#define _04_TMM_NORMAL_PHASE_LEVEl_LH                (0x04U) /* low initial output and high active level */
/* Counter-phase output level select (OLS1) */
#define _00_TMM_COUNTER_PHASE_LEVEl_HL               (0x00U) /* high initial output and low active level */
#define _08_TMM_COUNTER_PHASE_LEVEl_LH               (0x08U) /* low initial output and high active level */
/* External clock input select (STCLK) */
#define _00_TMM_EXTERNAL_CLOCK_DISABLE               (0x00U) /* external clock input disabled */
#define _40_TMM_EXTERNAL_CLOCK_ENABLE                (0x40U) /* external clock input enabled */
/* PWM3 mode select (PWM3) */
#define _00_TMM_PWM3_MODE                            (0x00U) /* in PWM3 mode */
#define _80_TMM_OTHER_MODE                           (0x80U) /* in the timer mode */

/*
    Timer M output master enable register 1 (TMOER1) 
*/
/* TMIOA0 output disable (EA0) */
#define _00_TMM_TMIOA0_OUTPUT_ENABLE                 (0x00U) /* output enabled */
#define _01_TMM_TMIOA0_OUTPUT_DISABLE                (0x01U) /* output disabled */
/* TMIOB0 output disable (EB0) */
#define _00_TMM_TMIOB0_OUTPUT_ENABLE                 (0x00U) /* output enabled */
#define _02_TMM_TMIOB0_OUTPUT_DISABLE                (0x02U) /* output disabled */
/* TMIOC0 output disable (EC0) */
#define _00_TMM_TMIOC0_OUTPUT_ENABLE                 (0x00U) /* output enabled */
#define _04_TMM_TMIOC0_OUTPUT_DISABLE                (0x04U) /* output disabled */
/* TMIOD0 output disable (ED0) */
#define _00_TMM_TMIOD0_OUTPUT_ENABLE                 (0x00U) /* output enabled */
#define _08_TMM_TMIOD0_OUTPUT_DISABLE                (0x08U) /* output disabled */
/* TMIOA1 output disable (EA1) */
#define _00_TMM_TMIOA1_OUTPUT_ENABLE                 (0x00U) /* output enabled */
#define _10_TMM_TMIOA1_OUTPUT_DISABLE                (0x10U) /* output disabled */
/* TMIOB1 output disable (EB1) */
#define _00_TMM_TMIOB1_OUTPUT_ENABLE                 (0x00U) /* output enabled */
#define _20_TMM_TMIOB1_OUTPUT_DISABLE                (0x20U) /* output disabled */
/* TMIOC1 output disable (EC1) */
#define _00_TMM_TMIOC1_OUTPUT_ENABLE                 (0x00U) /* output enabled */
#define _40_TMM_TMIOC1_OUTPUT_DISABLE                (0x40U) /* output disabled */
/* TMIOD1 output disable (ED1) */
#define _00_TMM_TMIOD1_OUTPUT_ENABLE                 (0x00U) /* output enabled */
#define _80_TMM_TMIOD1_OUTPUT_DISABLE                (0x80U) /* output disabled */

/*
    Timer M output master enable register 2 (TMOER2) 
*/
/* Forced cutoff flag (TMSHUTS) */
#define _00_TMM_INTERCEPTION_STOP                    (0x00U) /* not forcibly cut off */
#define _01_TMM_INTERCEPTION                         (0x01U) /* forcibly cut off */
/* INTP0 of pulse output forced cutoff signal input enabled (TMPTO) */
#define _00_TMM_ALL_OUTPUT_DISABLE                   (0x00U) /* pulse output forced cutoff input disabled */
#define _80_TMM_ALL_OUTPUT_ENABLE                    (0x80U) /* pulse output forced cutoff input enabled */

/*
    Timer M output control register (TMOCR) 
*/
/* TMIOA0 initial output level select (TOA0) */
#define _00_TMM_TMIOA0_INITIAL_OUTPUT_L              (0x00U) /* initial output is low or isn't active level */
#define _01_TMM_TMIOA0_INITIAL_OUTPUT_H              (0x01U) /* initial output is high or is active level */
/* TMIOB0 initial output level select (TOB0) */
#define _00_TMM_TMIOB0_INITIAL_OUTPUT_L              (0x00U) /* initial output is low or isn't active level */
#define _02_TMM_TMIOB0_INITIAL_OUTPUT_H              (0x02U) /* initial output is high or is active level */
/* TMIOC0 initial output level select (TOC0) */
#define _00_TMM_TMIOC0_INITIAL_OUTPUT_L              (0x00U) /* initial output is low or isn't active level */
#define _04_TMM_TMIOC0_INITIAL_OUTPUT_H              (0x04U) /* initial output is high or is active level */
/* TMIOD0 initial output level select (TOD0) */
#define _00_TMM_TMIOD0_INITIAL_OUTPUT_L              (0x00U) /* initial output is low or isn't active level */
#define _08_TMM_TMIOD0_INITIAL_OUTPUT_H              (0x08U) /* initial output is high or is active level */
/* TMIOA1 initial output level select (TOA1) */
#define _00_TMM_TMIOA1_INITIAL_OUTPUT_L              (0x00U) /* initial output is low or isn't active level */
#define _10_TMM_TMIOA1_INITIAL_OUTPUT_H              (0x10U) /* initial output is high or is active level */
/* TMIOB1 initial output level select (TOB1) */
#define _00_TMM_TMIOB1_INITIAL_OUTPUT_L              (0x00U) /* initial output is low or isn't active level */
#define _20_TMM_TMIOB1_INITIAL_OUTPUT_H              (0x20U) /* initial output is high or is active level */
/* TMIOC1 initial output level select (TOC1) */
#define _00_TMM_TMIOC1_INITIAL_OUTPUT_L              (0x00U) /* initial output is low or isn't active level */
#define _40_TMM_TMIOC1_INITIAL_OUTPUT_H              (0x40U) /* initial output is high or is active level */
/* TMIOD1 initial output level select (TOD1) */
#define _00_TMM_TMIOD1_INITIAL_OUTPUT_L              (0x00U) /* initial output is low or isn't active level */
#define _80_TMM_TMIOD1_INITIAL_OUTPUT_H              (0x80U) /* initial output is high or is active level */

/*
    Timer M status register 0 (TMSR0) 
*/
/* Input capture/compare match flag A (IMFA) */
#define _00_TMM0_INTA_FLAG_CLEAR                     (0x00U) /* interrupt A not generate */
#define _01_TMM0_INTA_GENERATE_FLAG                  (0x01U) /* interrupt A generate */
/* Input capture/compare match flag B (IMFB) */
#define _00_TMM0_INTB_FLAG_CLEAR                     (0x00U) /* interrupt B not generate */
#define _02_TMM0_INTB_GENERATE_FLAG                  (0x02U) /* interrupt B generate */
/* Input capture/compare match flag C (IMFC) */
#define _00_TMM0_INTC_FLAG_CLEAR                     (0x00U) /* interrupt C not generate */
#define _04_TMM0_INTC_GENERATE_FLAG                  (0x04U) /* interrupt C generate */
/* Input capture/compare match flag D (IMFD) */
#define _00_TMM0_INTD_FLAG_CLEAR                     (0x00U) /* interrupt D not generate */
#define _08_TMM0_INTD_GENERATE_FLAG                  (0x08U) /* interrupt D generate */
/* Overflow flag (OVF) */
#define _00_TMM0_INTOV_FLAG_CLEAR                    (0x00U) /* interrupt overflow not generate */
#define _10_TMM0_INTOV_GENERATE_FLAG                 (0x10U) /* interrupt overflow generate */

/*
    Timer M status register 1 (TMSR1) 
*/
/* Input capture/compare match flag A (IMFA) */
#define _00_TMM1_INTA_FLAG_CLEAR                     (0x00U) /* interrupt A not generate */
#define _01_TMM1_INTA_GENERATE_FLAG                  (0x01U) /* interrupt A generate */
/* Input capture/compare match flag B (IMFB) */
#define _00_TMM1_INTB_FLAG_CLEAR                     (0x00U) /* interrupt B not generate */
#define _02_TMM1_INTB_GENERATE_FLAG                  (0x02U) /* interrupt B generate */
/* Input capture/compare match flag C (IMFC) */
#define _00_TMM1_INTC_FLAG_CLEAR                     (0x00U) /* interrupt C not generate */
#define _04_TMM1_INTC_GENERATE_FLAG                  (0x04U) /* interrupt C generate */
/* INput capture/compare match flag D (IMFD) */
#define _00_TMM1_INTD_FLAG_CLEAR                     (0x00U) /* interrupt D not generate */
#define _08_TMM1_INTD_GENERATE_FLAG                  (0x08U) /* interrupt D generate */
/* Overflow flag (OVF) */
#define _00_TMM1_INTOV_FLAG_CLEAR                    (0x00U) /* interrupt overflow not generate */
#define _10_TMM1_INTOV_GENERATE_FLAG                 (0x10U) /* interrupt overflow generate */
/* Underflow flag (UDF) */
#define _00_TMM1_INTUN_FLAG_CLEAR                    (0x00U) /* interrupt underflow not generate */
#define _20_TMM1_INTUN_GENERATE_FLAG                 (0x20U) /* interrupt underflow generate */

/*
    Timer M mode register (TMMR) 
*/
/* Timer M synchronous (TMSYNC) */
#define _00_TMM_INDEPENDENTLY                        (0x00U) /* TM0 and TM1 operate independently */
#define _01_TMM_SYNCHRONOUSLY                        (0x01U) /* TM0 and TM1 operate synchronously */
/* TMGRC0 register function select (TMBFC0) */
#define _00_TMM_TMGRC0_GENERAL                       (0x00U) /* general register */
#define _10_TMM_TMGRC0_BUFFER                        (0x10U) /* buffer register for TMGRA0 register */
/* TMGRD0 register function select (TMBFD0) */
#define _00_TMM_TMGRD0_GENERAL                       (0x00U) /* general register */
#define _20_TMM_TMGRD0_BUFFER                        (0x20U) /* buffer register for TMGRB0 register */
/* TMGRC1 register function select (TMBFC1) */
#define _00_TMM_TMGRC1_GENERAL                       (0x00U) /* general register */
#define _40_TMM_TMGRC1_BUFFER                        (0x40U) /* buffer register for TMGRA1 register */
/* TMGRD1 register function select (TMBFD1) */
#define _00_TMM_TMGRD1_GENERAL                       (0x00U) /* general register */
#define _80_TMM_TMGRD1_BUFFER                        (0x80U) /* buffer register for TMGRB1 register */

/*
    Timer M digital filter function select register m (TMDFm) 
*/
/* TMIOAm pin digital filter function select (DFA) */
#define _00_TMM_TMIOA_DIGITAL_FILTER_DISABLE         (0x00U) /* digital filter function disabled */
#define _01_TMM_TMIOA_DIGITAL_FILTER_ENABLE          (0x01U) /* digital filter function enabled */
/* TMIOBm pin digital filter function select (DFB) */
#define _00_TMM_TMIOB_DIGITAL_FILTER_DISABLE         (0x00U) /* digital filter function disabled */
#define _02_TMM_TMIOB_DIGITAL_FILTER_ENABLE          (0x02U) /* digital filter function enabled */
/* TMIOD pin pulse forced cutoff control (DFB,DFA) */
#define _00_TMM_TMIOD_FORCEDCUTOFF_DISABLE           (0x00U) /* forced cutoff disabled */
#define _01_TMM_TMIOD_HIGHIMPEDANCE_OUTPUT           (0x01U) /* high-impedance output */
#define _02_TMM_TMIOD_LOW_OUTPUT                     (0x02U) /* low output */
#define _03_TMM_TMIOD_HIGH_OUTPUT                    (0x03U) /* high output */
/* TMIOCm pin digital filter function select (DFC) */
#define _00_TMM_TMIOC_DIGITAL_FILTER_DISABLE         (0x00U) /* digital filter function disabled */
#define _04_TMM_TMIOC_DIGITAL_FILTER_ENABLE          (0x04U) /* digital filter function enabled */
/* TMIODm pin digital filter function select (DFD) */
#define _00_TMM_TMIOD_DIGITAL_FILTER_DISABLE         (0x00U) /* digital filter function disabled */
#define _08_TMM_TMIOD_DIGITAL_FILTER_ENABLE          (0x08U) /* digital filter function enabled */
/* TMIOC pin pulse forced cutoff control (DFD,DFC) */
#define _00_TMM_TMIOC_FORCEDCUTOFF_DISABLE           (0x00U) /* forced cutoff disabled */
#define _04_TMM_TMIOC_HIGHIMPEDANCE_OUTPUT           (0x04U) /* high-impedance output */
#define _08_TMM_TMIOC_LOW_OUTPUT                     (0x08U) /* low output */
#define _0C_TMM_TMIOC_HIGH_OUTPUT                    (0x0CU) /* high output */
/* TMIOB pin pulse forced cutoff control (PENB1,PENB0) */
#define _00_TMM_TMIOB_FORCEDCUTOFF_DISABLE           (0x00U) /* forced cutoff disabled */
#define _10_TMM_TMIOB_HIGHIMPEDANCE_OUTPUT           (0x10U) /* high-impedance output */
#define _20_TMM_TMIOB_LOW_OUTPUT                     (0x20U) /* low output */
#define _30_TMM_TMIOB_HIGH_OUTPUT                    (0x30U) /* high output */
/* Clock select for digital filter function (DFCK1,DFCK0) */
#define _00_TMM_DIGITAL_FILTER_CLOCK_F32             (0x00U) /* fCLK/32 */
#define _40_TMM_DIGITAL_FILTER_CLOCK_F8              (0x40U) /* fCLK/8 */
#define _80_TMM_DIGITAL_FILTER_CLOCK_F1              (0x80U) /* fCLK */
#define _C0_TMM_DIGITAL_FILTER_CLOCK_SOURCE          (0xC0U) /* count source */
/* TMIOA pin pulse forced cutoff control (DFCK1,DFCK0) */
#define _00_TMM_TMIOA_FORCEDCUTOFF_DISABLE           (0x00U) /* forced cutoff disabled */
#define _40_TMM_TMIOA_HIGHIMPEDANCE_OUTPUT           (0x40U) /* high-impedance output */
#define _80_TMM_TMIOA_LOW_OUTPUT                     (0x80U) /* low output */
#define _C0_TMM_TMIOA_HIGH_OUTPUT                    (0xC0U) /* high output */

/*
    Timer M control register m (TMCRm) 
*/
/* count source select (TCK2,TCK1,TCK0) */
#define _00_TMM_INETNAL_CLOCK_FCLK_FHOCO             (0x00U) /* fCLK, fHOCO */
#define _01_TMM_INETNAL_CLOCK_FCLK2                  (0x01U) /* fCLK/2 */
#define _02_TMM_INETNAL_CLOCK_FCLK4                  (0x02U) /* fCLK/4 */
#define _03_TMM_INETNAL_CLOCK_FCLK8                  (0x03U) /* fCLK/8 */
#define _04_TMM_INETNAL_CLOCK_FCLK32                 (0x04U) /* fCLK/32 */
#define _05_TMM_EXTERNAL_CLOCK_TMCLK                 (0x05U) /* TMCLK input */
/* external clock edge select (CKEG1,CKEG0) */
#define _00_TMM_EXTERNAL_CLOCK_EDGE_RISING           (0x00U) /* count at the rising edge */
#define _08_TMM_EXTERNAL_CLOCK_EDGE_FALLING          (0x08U) /* count at the falling edge */
#define _10_TMM_EXTERNAL_CLOCK_EDGE_BOTH             (0x10U) /* count at both edges */
/* count source select (CCLR2,CCLR1,CCLR0) */
#define _00_TMM_COUNTER_CLEAR_DISABLE                (0x00U) /* clear disabled (free-running operation) */
#define _20_TMM_COUNTER_CLEAR_TMGRA                  (0x20U) /* clear by input capture/compare match with TMGRAm */
#define _40_TMM_COUNTER_CLEAR_TMGRB                  (0x40U) /* clear by input capture/compare match with TMGRBm */
#define _60_TMM_COUNTER_CLEAR_SYNCHRONOUS            (0x60U) /* synchronous clear */
#define _A0_TMM_COUNTER_CLEAR_TMGRC                  (0xA0U) /* clear by input capture/compare match with TMGRCm */
#define _C0_TMM_COUNTER_CLEAR_TMGRD                  (0xC0U) /* clear by input capture/compare match with TMGRDm */

/*
    Timer M I/O control register Am (TMIORAm) 
*/
/* TMGRA control (IOA1,IOA0) */
#define _00_TMM_TMGRA_CAPTURE_RISING                 (0x00U) /* input capture to TMGRAm at the rising edge */
#define _01_TMM_TMGRA_CAPTURE_FALLING                (0x01U) /* input capture to TMGRAm at the falling edge */
#define _02_TMM_TMGRA_CAPTURE_BOTH                   (0x02U) /* input capture to TMGRAm at both edges */
#define _00_TMM_TMGRA_COMPARE_OUTPUT_DISABLE         (0x00U) /* pin output by compare match is disabled */
#define _01_TMM_TMGRA_COMPARE_OUTPUT_LOW             (0x01U) /* low output by compare match with TMGRAm */
#define _02_TMM_TMGRA_COMPARE_OUTPUT_HIGH            (0x02U) /* high output by compare match with TMGRAm */
#define _03_TMM_TMGRA_COMPARE_OUTPUT_TOGGLE          (0x03U) /* toggle output by compare match with TMGRAm */
/* TMGRA mode select (IOA2) */
#define _00_TMM_TMGRA_COMPARE                        (0x00U) /* output compare function */
#define _04_TMM_TMGRA_CAPTURE                        (0x04U) /* input capture function */
/* TMGRB control (IOB1,IOB0) */
#define _00_TMM_TMGRB_CAPTURE_RISING                 (0x00U) /* input capture to TMGRBm at the rising edge */
#define _10_TMM_TMGRB_CAPTURE_FALLING                (0x10U) /* input capture to TMGRBm at the falling edge */
#define _20_TMM_TMGRB_CAPTURE_BOTH                   (0x20U) /* input capture to TMGRBm at both edges */
#define _00_TMM_TMGRB_COMPARE_OUTPUT_DISABLE         (0x00U) /* pin output by compare match is disabled */
#define _10_TMM_TMGRB_COMPARE_OUTPUT_LOW             (0x10U) /* low output by compare match with TMGRBm */
#define _20_TMM_TMGRB_COMPARE_OUTPUT_HIGH            (0x20U) /* high output by compare match with TMGRBm */
#define _30_TMM_TMGRB_COMPARE_OUTPUT_TOGGLE          (0x30U) /* toggle output by compare match with TMGRBm */
/* TMGRB mode select (IOB2) */
#define _00_TMM_TMGRB_COMPARE                        (0x00U) /* output compare function */
#define _40_TMM_TMGRB_CAPTURE                        (0x40U) /* input capture function */

/*
    Timer M I/O control register Cm (TMIORCm) 
*/
/* TMGRC control (IOC1,IOC0) */
#define _00_TMM_TMGRC_CAPTURE_RISING                 (0x00U) /* input capture to TMGRCm at the rising edge */
#define _01_TMM_TMGRC_CAPTURE_FALLING                (0x01U) /* input capture to TMGRCm at the falling edge */
#define _02_TMM_TMGRC_CAPTURE_BOTH                   (0x02U) /* input capture to TMGRCm at both edges */
#define _00_TMM_TMGRC_COMPARE_OUTPUT_DISABLE         (0x00U) /* pin output by compare match is disabled */
#define _01_TMM_TMGRC_COMPARE_OUTPUT_LOW             (0x01U) /* low output by compare match with TMGRCm */
#define _02_TMM_TMGRC_COMPARE_OUTPUT_HIGH            (0x02U) /* high output by compare match with TMGRCm */
#define _03_TMM_TMGRC_COMPARE_OUTPUT_TOGGLE          (0x03U) /* toggle output by compare match with TMGRCm */
/* TMGRD control (IOD1,IOD0) */
#define _00_TMM_TMGRD_CAPTURE_RISING                 (0x00U) /* input capture to TMGRDm at the rising edge */
#define _10_TMM_TMGRD_CAPTURE_FALLING                (0x10U) /* input capture to TMGRDm at the falling edge */
#define _20_TMM_TMGRD_CAPTURE_BOTH                   (0x20U) /* input capture to TMGRDm at both edges */
#define _00_TMM_TMGRD_COMPARE_OUTPUT_DISABLE         (0x00U) /* pin output by compare match is disabled */
#define _10_TMM_TMGRD_COMPARE_OUTPUT_LOW             (0x10U) /* low output by compare match with TMGRDm */
#define _20_TMM_TMGRD_COMPARE_OUTPUT_HIGH            (0x20U) /* high output by compare match with TMGRDm */
#define _30_TMM_TMGRD_COMPARE_OUTPUT_TOGGLE          (0x30U) /* toggle output by compare match with TMGRDm */
/* TMGRC mode select (IOC2) */
#define _00_TMM_TMGRC_COMPARE                        (0x00U) /* output compare function */
#define _04_TMM_TMGRC_CAPTURE                        (0x04U) /* input capture function */
/* TMGRC register function select (IOC3) */
#define _00_TMM_TMGRC_OUTPUT_REGISTER                (0x00U) /* TMIOA output register */
#define _08_TMM_TMGRC_GENERAL_BUFFER_REGISTER        (0x08U) /* general register or buffer register */
/* TMGRD mode select (IOD2) */
#define _00_TMM_TMGRD_COMPARE                        (0x00U) /* output compare function */
#define _40_TMM_TMGRD_CAPTURE                        (0x40U) /* input capture function */
/* TMGRD register function select (IOD3) */
#define _00_TMM_TMGRD_OUTPUT_REGISTER                (0x00U) /* TMIOB output register */
#define _80_TMM_TMGRD_GENERAL_BUFFER_REGISTER        (0x80U) /* general register or buffer register */

/*
    Timer M interrupt enable register m (TMIERm) 
*/
/* Input capture/compare match interrupt enable A (IMIEA) */
#define _00_TMM_IMIA_DISABLE                         (0x00U) /* interrupt (IMIA) by the IMFA bit is disabled */
#define _01_TMM_IMIA_ENABLE                          (0x01U) /* interrupt (IMIA) by the IMFA bit is enabled */
/* Input capture/compare match interrupt enable B (IMIEB) */
#define _00_TMM_IMIB_DISABLE                         (0x00U) /* interrupt (IMIB) by the IMFB bit is disabled */
#define _02_TMM_IMIB_ENABLE                          (0x02U) /* interrupt (IMIB) by the IMFB bit is enabled */
/* Input capture/compare match interrupt enable C (IMIEC) */
#define _00_TMM_IMIC_DISABLE                         (0x00U) /* interrupt (IMIC) by the IMFC bit is disabled */
#define _04_TMM_IMIC_ENABLE                          (0x04U) /* interrupt (IMIC) by the IMFC bit is enabled */
/* Input capture/compare match interrupt enable D (IMIED) */
#define _00_TMM_IMID_DISABLE                         (0x00U) /* interrupt (IMID) by the IMFD bit is disabled */
#define _08_TMM_IMID_ENABLE                          (0x08U) /* interrupt (IMID) by the IMFD bit is enabled */
/* Overflow/underflow interrupt enable (OVIE) */
#define _00_TMM_OVIE_DISABLE                         (0x00U) /* interrupt (OVI) by bits OVF and UDF disabled */
#define _10_TMM_OVIE_ENABLE                          (0x10U) /* interrupt (OVI) by bits OVF and UDF enabled */

/*
    Timer M PWM function output level control register m (TMPOCRm) 
*/
/* PWM function output level control B (POLB) */
#define _00_TMIOB_OUTPUT_ACTIVE_L                    (0x00U) /* TMIOBm output level is low active */
#define _01_TMIOB_OUTPUT_ACTIVE_H                    (0x01U) /* TMIOBm output level is high active */
/* PWM function output level control C (POLC) */
#define _00_TMIOC_OUTPUT_ACTIVE_L                    (0x00U) /* TMIOCm output level is low active */
#define _02_TMIOC_OUTPUT_ACTIVE_H                    (0x02U) /* TMIOCm output level is high active */
/* PWM function output level control D (POLD) */
#define _00_TMIOD_OUTPUT_ACTIVE_L                    (0x00U) /* TMIODm output level is low active */
#define _04_TMIOD_OUTPUT_ACTIVE_H                    (0x04U) /* TMIODm output level is high active */

/*
    PWMOP control register 0 (OPCTL0) 
*/
/* Output cutoff hazard control selection (HAZAD_SET) */
#define _00_TMM_PWMOP_HAZARD_DIASBLE                 (0x00U) /* hazard measure disabled */
#define _40_TMM_PWMOP_HAZARD_ENASBLE                 (0x40U) /* hazard measure enabled */
/* Output forced cutoff source edge/ release edge selection (IN_EG) */
#define _00_TMM_PWMOP_FALLING_RELEASE                (0x00U) /* rising edge: Output forced cutoff/falling edge: Output forced cutoff release */
#define _20_TMM_PWMOP_RISING_RELEASE                 (0x20U) /* rising edge: output forced cutoff release/falling edge: output forced cutoff */
/* Cutoff source selection (IN_SEL1,IN_SEL0) */
#define _00_TMM_PWMOP_NO_CUTOFF                      (0x00U) /* NO cutoff source selection */
#define _08_TMM_PWMOP_COMP_CUTOFF                    (0x08U) /* comparator 0 output */
#define _10_TMM_PWMOP_INTP_CUTOFF                    (0x10U) /* INTP0 pin input */
#define _18_TMM_PWMOP_ELC_CUTOFF                     (0x18U) /* event input from ELC */
/* When software release is selected: Software release timing selection (ACT) */
#define _00_TMM_PWMOP_SOFT_IMMEDIAT_RELEASE          (0x00U) /* immediately release */
#define _04_TMM_PWMOP_SOFT_CONDITION_RELEASE         (0x04U) /* conditional release */
/* When software release is selected: Output cutoff release control (HZ_REL) */
#define _00_TMM_PWMOP_SOFT_RELEASE_REMAIN            (0x00U) /* output forced cutoff remains */
#define _02_TMM_PWMOP_SOFT_RELEASE_RESUM             (0x02U) /* output forced cutoff is released and pulse output is resumed */
/* Output forced cutoff release mode selection (HS_SEL) */
#define _00_TMM_PWMOP_HARDWARE_RELEAS                (0x00U) /* released via hardware */
#define _01_TMM_PWMOP_SOFTWARE_RELEAS                (0x01U) /* release via software */

/*
    PWMOP cutoff control register m (OPDFm) 
*/
/* TMIODm pin output forced cutoff control (DFDm1,DFDm0) */
#define _00_TMM_PWMOP_TMIODm_PROHIBIT                (0x00U) /* forced cutoff prohibited */
#define _40_TMM_PWMOP_TMIODm_HIIMPEDANCE             (0x40U) /* hi-impedance output */
#define _80_TMM_PWMOP_TMIODm_LOW                     (0x80U) /* low Level output */
#define _C0_TMM_PWMOP_TMIODm_HIGH                    (0xC0U) /* high Level output */
/* TMIOCm pin output forced cutoff control (DFCm1,DFCm0) */
#define _00_TMM_PWMOP_TMIOCm_PROHIBIT                (0x00U) /* forced cutoff prohibited */
#define _10_TMM_PWMOP_TMIOCm_HIIMPEDANCE             (0x10U) /* hi-impedance output */
#define _20_TMM_PWMOP_TMIOCm_LOW                     (0x20U) /* low Level output */
#define _30_TMM_PWMOP_TMIOCm_HIGH                    (0x30U) /* high Level output */
/* TMIOBm pin output forced cutoff control (DFBm1,DFBm0) */
#define _00_TMM_PWMOP_TMIOBm_PROHIBIT                (0x00U) /* forced cutoff prohibited */
#define _04_TMM_PWMOP_TMIOBm_HIIMPEDANCE             (0x04U) /* hi-impedance output */
#define _08_TMM_PWMOP_TMIOBm_LOW                     (0x08U) /* low Level output */
#define _0C_TMM_PWMOP_TMIOBm_HIGH                    (0x0CU) /* high Level output */
/* TMIOAm pin output forced cutoff control (DFAm1,DFAm0) */
#define _00_TMM_PWMOP_TMIOAm_PROHIBIT                (0x00U) /* forced cutoff prohibited */
#define _01_TMM_PWMOP_TMIOAm_HIIMPEDANCE             (0x01U) /* hi-impedance output */
#define _02_TMM_PWMOP_TMIOAm_LOW                     (0x02U) /* low Level output */
#define _03_TMM_PWMOP_TMIOAm_HIGH                    (0x03U) /* high Level output */

/*
    PWMOP edge select register (OPEDGE) 
*/
/* Select edge of output forced cutoff release (EG1,EG0) */
#define _00_TMM_PWMOP_RELEASE_TMIOC0_R               (0x00U) /* output cutoff release at the rising edge of TMIOC0 */
#define _01_TMM_PWMOP_RELEASE_TMIOC0_F               (0x01U) /* output cutoff release at the falling edge of TMIOC0 */
#define _02_TMM_PWMOP_RELEASE_TMIOC0_B               (0x02U) /* output cutoff release at the both edge of TMIOC0 */
#define _03_TMM_PWMOP_TMIOC0_DISABLE                 (0x03U) /* input edge of TMOIC0 disabled, cutoff retained */


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _FFFF_TMM_TM0_VALUE                            (0xFFFFU) /* timer M count 0 */
#define _FFFF_TMM_TMGRA0_VALUE                         (0xFFFFU) /* timer M general register A0 */
#define _FFFF_TMM_TMGRA1_VALUE                         (0xFFFFU) /* timer M general register A1 */
#define _FFFF_TMM_TMGRB0_VALUE                         (0xFFFFU) /* timer M general register B0 */
#define _FFFF_TMM_TMGRB1_VALUE                         (0xFFFFU) /* timer M general register B1 */
#define _FFFF_TMM_TMGRC0_VALUE                         (0xFFFFU) /* timer M general register C0 */
#define _FFFF_TMM_TMGRC1_VALUE                         (0xFFFFU) /* timer M general register C1 */
#define _FFFF_TMM_TMGRD0_VALUE                         (0xFFFFU) /* timer M general register D0 */
#define _FFFF_TMM_TMGRD1_VALUE                         (0xFFFFU) /* timer M general register D1 */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum
{
    TMM_CHANNELA,
    TMM_CHANNELB,
    TMM_CHANNELC,
    TMM_CHANNELD,
    TMM_CHANNELELC
} tmm_channel_t;

typedef enum
{
    TMM_CLOCK_FHOCO      = 0U,
    TMM_CLOCK_FCLK       = 0U,
    TMM_CLOCK_FCLK2      = 1U,
    TMM_CLOCK_FCLK4      = 2U,
    TMM_CLOCK_FCLK8      = 3U,
    TMM_CLOCK_FCLK32     = 4U,
    TMM_CLOCK_TMCLK      = 5U,
} tmm_clock_t;

/***********************************************************************************************************************
Global variables
***********************************************************************************************************************/
/* TMM0 input capture mode */
extern volatile uint16_t g_tmm0_intTaken_a;
extern volatile uint16_t g_tmm0_intTaken_b;
extern volatile uint32_t g_tmm0_active_width_a;
extern volatile uint32_t g_tmm0_active_width_b;
extern volatile uint32_t g_tmm0_active_width_c;
extern volatile uint32_t g_tmm0_active_width_d;
extern volatile uint32_t g_tmm0_active_width_elc;
extern volatile uint32_t g_tmm0_overflow_count_a;
extern volatile uint32_t g_tmm0_overflow_count_b;
/* TMM1 input capture mode */
extern volatile uint16_t g_tmm1_intTaken_a;
extern volatile uint16_t g_tmm1_intTaken_b;
extern volatile uint32_t g_tmm1_active_width_a;
extern volatile uint32_t g_tmm1_active_width_b;
extern volatile uint32_t g_tmm1_active_width_c;
extern volatile uint32_t g_tmm1_active_width_d;
extern volatile uint32_t g_tmm1_active_width_elc;
extern volatile uint32_t g_tmm1_overflow_count_a;
extern volatile uint32_t g_tmm1_overflow_count_b;
/* Motor Driver */
extern volatile uint16_t g_u2_pwm_duty;              /* PWM duty : No scaling */
extern volatile uint8_t  g_u1_v_pattern;             /* voltage pattern */
extern volatile uint8_t  g_u1_direction;             /* rotation direction (0:CW ,1:CCW) */
extern volatile uint8_t  g_u1_v_pattern_open[2][7];

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void TMM0_InputCapture(tmm_clock_t clk);
uint32_t TMM0_Get_PulseWidth(tmm_clock_t clk, tmm_channel_t ch);
uint32_t TMM0_Get_PulsePeriod(tmm_clock_t clk,tmm_channel_t ch);
void TMM0_OutputCompare(tmm_clock_t clk);
void TMM0_DoublePulseOutput(tmm_clock_t clk, uint16_t m, uint16_t n, uint16_t p, uint16_t q);
void TMM0_PWM_1Perdod_3Duty(tmm_clock_t clk, uint16_t period, uint16_t duty1, uint16_t duty2, uint16_t duty3);
void TMM0_PWM_Complementary_3Phase(tmm_clock_t clk, uint16_t period, uint16_t dead);
void TMM0_Start(void);
void TMM0_Stop(void);
void TMM1_InputCapture(tmm_clock_t clk);
uint32_t TMM1_Get_PulseWidth(tmm_clock_t clk, tmm_channel_t ch);
uint32_t TMM1_Get_PulsePeriod(tmm_clock_t clk,tmm_channel_t ch);
void TMM1_OutputCompare(tmm_clock_t clk);
void TMM1_DoublePulseOutput(tmm_clock_t clk, uint16_t m, uint16_t n, uint16_t p, uint16_t q);
void TMM1_PWM_1Perdod_3Duty(tmm_clock_t clk, uint16_t period, uint16_t duty1, uint16_t duty2, uint16_t duty3);
void TMM1_Start(void);
void TMM1_Stop(void);
void TMM_PWMOP_Set_PowerOff(void);
void TMM_Set_PowerOff(void);
void mtr_init_tmm(void);
void mtr_change_pattern(uint8_t u1_pattern);
void mtr_pattern_up_chopping(uint8_t u1_pattern);
void mtr_pattern_set(uint8_t u1_pattern);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
