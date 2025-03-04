/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    adc_user.c
* @brief   This file implements device driver for ADC module.
* @version 1.0.0 
* @date    2022/2/25
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "BAT32A237.h"
#include "adc.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
//void IRQ21_Handler(void) __attribute__((alias("adc_interrupt")));

/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
volatile uint8_t  * gp_u1_adc_buf;           /* adc higher 8 bit result buffer address */
volatile uint16_t * gp_u2_adc_buf;           /* adc 12 bit result buffer address */
volatile uint32_t   g_AdcIntTaken;           /* adc interrupt flag */
volatile int16_t    g_temperature = 25;        /* chip temperature */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: adc_interrupt
* @brief  ADC interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
static uint16_t adc_tmp1;

void adc_interrupt(void)
{
    INTC_ClearPendingIRQ(ADC_IRQn);     /* clear INTAD interrupt flag */
    /* Start user code. Do not edit comment generated here */
    #if 0
    *gp_u1_adc_buf++ = ADC->ADCRH;
    *gp_u2_adc_buf++ = ADC->ADCR;
    g_AdcIntTaken++;
    g_temperature = adc_get_temperature(ADC->ADCR);
    #endif
    
    #if 1
    *gp_u1_adc_buf = ADC->ADCRH;
    
    adc_tmp1 = ADC->ADCR;
    
    adc_tmp1 &= 0x0FFF;
    
    *gp_u2_adc_buf = adc_tmp1;
    
    g_AdcIntTaken++;
    #endif
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: adc_get_temperature
* @brief  ADC Get temperature
* @param  dat - the adc conversion value of ADC_TEMPERSENSOR0 channel
* @return temperature
***********************************************************************************************************************/
#if 0
double adc_get_temperature(int16_t dat)
{
    double temp;    /* temperature value */

    temp = (double)(TSN->TSN25 - dat) * 100 / (TSN->TSN25 - TSN->TSN125) + 25; /* 12bit dat */

    return (temp);
}
#else
int16_t adc_get_temperature(int16_t dat)
{
    int32_t temp;   /* temperature value */
    int32_t temp25, temp125;   /* temperature value */

    temp25 = TSN->TSN25;
    temp125 = TSN->TSN125;
    temp = (temp25 - dat) * 100 / (temp25 - temp125) + 25; /* 12bit dat */

    return ((int16_t)temp);
}
#endif

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
