/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    dac.h
* @brief   This file implements device driver for DAC module.
* @version 1.0.0  
* @date    2022/2/25
***********************************************************************************************************************/
#ifndef DAC_H
#define DAC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    D/A converter mode register (DAM) 
*/
/* D/A conversion operation control (DACE1) */
#define _00_DA1_CONVERSION_STOP            (0x00U) /* stops D/A conversion operation */
#define _20_DA1_CONVERSION_ENABLE          (0x20U) /* enables D/A conversion operation */
/* D/A conversion operation control (DACE0) */
#define _00_DA0_CONVERSION_STOP            (0x00U) /* stops D/A conversion operation */
#define _10_DA0_CONVERSION_ENABLE          (0x10U) /* enables D/A conversion operation */
/* D/A converter operation mode selection (DAMD1) */
#define _00_DA1_NORMAL_MODE                (0x00U) /* Normal mode */
#define _02_DA1_TIME_OUTPUT_MODE           (0x02U) /* Real-time output mode */
/* D/A converter operation mode selection (DAMD0) */
#define _00_DA0_NORMAL_MODE                (0x00U) /* Normal mode */
#define _01_DA0_TIME_OUTPUT_MODE           (0x01U) /* Real-time output mode */

#define DAMD0                              (1<<0)
#define DAMD1                              (1<<1)
#define DACE0                              (1<<4)
#define DACE1                              (1<<5)

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _00_DA0_COUVERSION_VALUE           (0x00U) /* set the analog voltage value */
#define _00_DA1_COUVERSION_VALUE           (0x00U) /* set the analog voltage value */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum 
{
	DAC_CHANNEL_0 = 1U,  // channel 0: DAC0
	DAC_CHANNEL_1 = 2U,  // channel 1: DAC1
	DAC_CHANNEL_A = 3U   // channel all: DAC0 & DAC1
} dac_channel_t;


/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void DAC_Init(dac_channel_t ch);
void DAC_Start(dac_channel_t ch);
void DAC_Stop(dac_channel_t ch);
void DAC_Set_Value(dac_channel_t ch, uint8_t regvalue);
void DAC_Set_PowerOff(void);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
