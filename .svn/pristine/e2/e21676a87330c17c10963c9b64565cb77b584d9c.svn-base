/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    timc.h
* @brief   This file implements device driver for TMC module.
* @version 1.0.0
* @date    2020/4/4
***********************************************************************************************************************/
#ifndef TMC_H
#define TMC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Timer C function control register (TCCR1) 
*/
/* Select count source (TCK2,TCK1,TCK0) */
#define _00_TMC_CLOCK_FCLK_FHOCO                       (0x00U) /* TXCLK */
#define _20_TMC_CLOCK_FCLK2                            (0x20U) /* TXCLK/2 */
#define _40_TMC_CLOCK_FCLK4                            (0x40U) /* TXCLK/4 */
#define _60_TMC_CLOCK_FCLK8                            (0x60U) /* TXCLK/8 */
#define _80_TMC_CLOCK_FCLK32                           (0x80U) /* TXCLK/32 */
/* Select count start source (START_MD) */
#define _00_TMC_SOFTWARE_START                         (0x00U) /* starts counting of timer C by software */
#define _10_TMC_TMM_TRIGGER_START                      (0x10U) /* starts counting of timer C by using a signal from timer M as trigger */
/* Timer C reset enable signal by software (TRIG_MD_SW) */
#define _08_TMC_SOFTWARE_ENABLE                        (0x08U) /* enables software to reset counting of timer C */
#define _00_TMC_SOFTWARE_DISENABLE                     (0x00U) /* disables software from resetting counting of timer C */
/* Select operation in Count mode by trigger from timer M (TRIG_MD_HW) */
#define _00_TMC_COUNTING_START_RESET                   (0x00U) /* counting of timer C starts after reset timer C counter */
#define _04_TMC_COUNTING_START                         (0x04U) /* counting of timer C starts */
/* Select hardware start trigger from timer M (TM_TRIG) */
#define _00_TMC_TM0_COUNTING                           (0x00U) /* counting of timer M0 starts */
#define _02_TMC_TM1_COUNTING                           (0x02U) /* counting of timer M1 starts */
/* Enables overflow interrupt (OVIE) */
#define _00_TMC_INTERRUPT_DISABLE                      (0x00U) /* disables interrupt when TC register overflows */
#define _01_TMC_INTERRUPT_ENABLE                       (0x01U) /* enables interrupt when TC register overflows */

/*
    Timer C function control register2 (TCCR2) 
*/
/* Select operation when a trigger is generated from comparator 1 (CMP1_TCR1,CMP1_TCR0) */
#define _00_TMC_COUNTING_STOP                          (0x00U) /* stops counting of timer C couter */
#define _02_TMC_COUNTING_TRANSFERRED_CONTINUE          (0x02U) /* transfer timer C counter value to timer C count buffer register. Timer C counter continues counting */
#define _04_TMC_SET_0000_COUNTING                      (0x04U) /* set 0000H to timer C count value, and continue counting */
#define _06_TMC_COUNTING_TRANSFERRED_SET_0000          (0x06U) /* transfer timer C counter value to timer C count buffer register. Set 0000H to timer C count value, and continue counting */
/* Control start of timer C operation (TSTART) */
#define _00_TMC_COUNTING_STOP                          (0x00U) /* stops Timer C counting */
#define _01_TMC_COUNTING_START                         (0x01U) /* starts Timer C counting */


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum
{
    TMC_CLOCK_FHOCO      = 0U,
    TMC_CLOCK_FCLK       = 0U,
    TMC_CLOCK_FCLK2      = 1U,
    TMC_CLOCK_FCLK4      = 2U,
    TMC_CLOCK_FCLK8      = 3U,
    TMC_CLOCK_FCLK32     = 4U 
} tmc_clock_t;


/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void TMC_Init(tmc_clock_t clk);
void TMC_Start(void);
void TMC_Stop(void);
uint32_t TMC_Get_BufferValue(void);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
