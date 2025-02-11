/***********************************************************************************************************************
* Copyright (C) . All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    dac.c
* @brief   This file implements device driver for DAC module.
* @version V1.0.0
* @date    2022/2/25
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "BAT32A237.h"
#include "userdefine.h"
#include "dac.h"
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
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: DAC_Init
* @brief  This function initializes the D/A converter.
* @param  ch - spcify the dac channel to initialized
* @return None
***********************************************************************************************************************/
void DAC_Init(dac_channel_t ch)
{
    CGC->PER1 |= CGC_PER1_DACEN_Msk;     /* enables input clock supply */
    DAC->DAM   = 0x00U;
    if(ch & 0x01) 
    {
        DAC->DAM |= _00_DA0_NORMAL_MODE;
        DAC->DACS0 = _00_DA0_COUVERSION_VALUE;
        /* Set ANO0 pin */
        DAC0_PORT_SETTING();
    }
    if(ch & 0x02) 
    {
        DAC->DAM |= _00_DA1_NORMAL_MODE;
        DAC->DACS1 = _00_DA1_COUVERSION_VALUE;
        /* Set ANO1 pin */
        DAC1_PORT_SETTING();
    }
}
/***********************************************************************************************************************
* Function Name: DAC_Start
* @brief  This function enables the DA converter channel [#n].
* @param  ch - spcify the dac channel to start
* @return None
***********************************************************************************************************************/
void DAC_Start(dac_channel_t ch)
{
    if(ch & 0x01) 
    {
        DAC->DAM  |= DAC_DAM_DACE0_Msk;     /* enables D/A conversion operation */
    }
    if(ch & 0x02) 
    {
        DAC->DAM  |= DAC_DAM_DACE1_Msk;     /* enables D/A conversion operation */
    }
}
/***********************************************************************************************************************
* Function Name: DAC_Stop
* @brief  This function stops the DA converter channel [#n].
* @param  ch - spcify the dac channel to stop
* @return None
***********************************************************************************************************************/
void DAC_Stop(dac_channel_t ch)
{
    if(ch & 0x01) 
    {
        DAC->DAM  &= ~DAC_DAM_DACE0_Msk;     /* stops D/A conversion operation */
    }
    if(ch & 0x02) 
    {
        DAC->DAM  &= ~DAC_DAM_DACE1_Msk;     /* stops D/A conversion operation */
    }
}
/***********************************************************************************************************************
* Function Name: DAC_Set_Value
* @brief  This function sets the DA converter channel [#n] value.
* @param  reg_value - value of conversion
* @return None
***********************************************************************************************************************/
void DAC_Set_Value(dac_channel_t ch, uint8_t regvalue)
{
    if(ch & 0x01) 
    {
        DAC->DACS0 = regvalue;
    }
    if(ch & 0x02) 
    {
        DAC->DACS1 = regvalue;
    }
}
/***********************************************************************************************************************
* Function Name: DAC_Set_PowerOff
* @brief  This function stops supply of input clock and reset all SFR.
* @param  None
* @return None
***********************************************************************************************************************/
void DAC_Set_PowerOff(void)
{
    CGC->PER1 &= ~CGC_PER1_DACEN_Msk;     /* stops input clock supply */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
