/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    rst.c
* @brief   This file implements device driver for RST module.
* @version 1.0.0
* @date    2022/2/25
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "stdio.h"
#include "BAT32A237.h"
#include "rst.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: RST_Get_Flag
* @brief  This function check the reset flag. 
* @param  None
* @return RESF register value
***********************************************************************************************************************/
/**
 * @brief This function check the reset flag. 
 *
 * @return RESF register value
 */
uint8_t RST_Get_Flag(void)
{
    uint8_t           tmp;

    tmp = RST->RESF;

    if(tmp & (1<<7))
    {
        printf("Reset is done by System Reset Request\r\n");    
    }
    if(tmp & (1<<4))
    {
        printf("Reset is done by WDT overrun\r\n"); 
    }
    if(tmp & (1<<2))
    {
        printf("Reset is done by RAM parity error\r\n");    
    }
    if(tmp & (1<<1))
    {
        printf("Reset is done by fetch instruction from reserved Flash area\r\n");  
    }
    if(tmp & (1<<0))
    {
        printf("Reset is done by Low Voltage Detection\r\n");   
    }
    return tmp;
}