/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    elc.h
* @brief   This file implements device driver for ELC module.
* @version 1.0.0  
* @date    2022/2/25
***********************************************************************************************************************/
#ifndef ELC_H
#define ELC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Event input resources number (ELSELRn) 
*/
#define _00_ELC_EVENT_INTP0           (0x00U) /* ELSELR00 */
#define _01_ELC_EVENT_INTP1           (0x01U) /* ELSELR01 */
#define _02_ELC_EVENT_INTP2           (0x02U) /* ELSELR02 */
#define _03_ELC_EVENT_INTP3           (0x03U) /* ELSELR03 */
#define _04_ELC_EVENT_INTP4           (0x04U) /* ELSELR04 */
#define _05_ELC_EVENT_INTP5           (0x05U) /* ELSELR05 */
#define _06_ELC_EVENT_INTKR           (0x06U) /* ELSELR06 */
#define _07_ELC_EVENT_INTRTC          (0x07U) /* ELSELR07 */
#define _08_ELC_EVENT_TMIMFA0         (0x08U) /* ELSELR08 */
#define _09_ELC_EVENT_TMIMFB0         (0x09U) /* ELSELR09 */
#define _0A_ELC_EVENT_TMIMFA1         (0x0AU) /* ELSELR10 */
#define _0B_ELC_EVENT_TMIMFB1         (0x0BU) /* ELSELR11 */
#define _0C_ELC_EVENT_TMUDF1          (0x0CU) /* ELSELR12 */
#define _0D_ELC_EVENT_INTTA           (0x0DU) /* ELSELR13 */
#define _0E_ELC_EVENT_TBIMFA          (0x0EU) /* ELSELR14 */
#define _0F_ELC_EVENT_TBIMFB          (0x0FU) /* ELSELR15 */
#define _10_ELC_EVENT_INTTM00         (0x10U) /* ELSELR16 */
#define _11_ELC_EVENT_INTTM01         (0x11U) /* ELSELR17 */
#define _12_ELC_EVENT_INTTM02         (0x12U) /* ELSELR18 */
#define _13_ELC_EVENT_INTTM03         (0x13U) /* ELSELR19 */
#define _14_ELC_EVENT_INTCMP0         (0x14U) /* ELSELR20 */
#define _15_ELC_EVENT_INTCMP1         (0x15U) /* ELSELR21 */

/*
    Event output destination select register n (ELSELRn) 
*/
/* Event output destination select register n (ELSELn3 - ELSELn0) */
#define _00_ELC_EVENT_LINK_OFF            (0x00U) /* event link disabled */
#define _01_ELC_EVENT_LINK_AD             (0x01U) /* select operation of peripheral function 1 to A/D converter */
#define _02_ELC_EVENT_LINK_TI00           (0x02U) /* select operation of peripheral function 2 to Timer input of timer 4 channel 0 */
#define _03_ELC_EVENT_LINK_TI01           (0x03U) /* select operation of peripheral function 3 to Timer input of timer 4 channel 1 */
#define _04_ELC_EVENT_LINK_TA             (0x04U) /* select operation of peripheral function 4 to Timer A */
#define _05_ELC_EVENT_LINK_TB             (0x05U) /* select operation of peripheral function 5 to Timer B */
#define _06_ELC_EVENT_LINK_TM0            (0x06U) /* select operation of peripheral function 6 to Timer M0 */
#define _07_ELC_EVENT_LINK_TM1            (0x07U) /* select operation of peripheral function 7 to Timer M1 */
#define _08_ELC_EVENT_LINK_DA0            (0x08U) /* select operation of peripheral function 8 to DA0 */
#define _09_ELC_EVENT_LINK_DA1            (0x09U) /* select operation of peripheral function 9 to DA1 */
#define _0A_ELC_EVENT_LINK_PWMOP          (0x0AU) /* select operation of peripheral function 10 to PWMOP */


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define ELC_DESTINATION_COUNT              (0x16U)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void ELC_Start(uint32_t event_src, uint32_t event_dst);
void ELC_Stop(uint32_t event);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
