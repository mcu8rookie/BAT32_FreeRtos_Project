/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    intp_user.c
* @brief   This file implements device driver for INTP module.
* @version 1.0.0
* @date    2022/2/25
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "userdefine.h"
#include "BAT32A237.h"
#include "intp.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
//void IRQ01_Handler(void) __attribute__((alias("intp_0_6_interrupt")));
//void IRQ02_Handler(void) __attribute__((alias("intp_1_7_interrupt")));
//void IRQ03_Handler(void) __attribute__((alias("intp_2_8_interrupt")));
//void IRQ04_Handler(void) __attribute__((alias("intp_3_9_interrupt")));
//void IRQ05_Handler(void) __attribute__((alias("intp_4_10_interrupt")));
//void IRQ06_Handler(void) __attribute__((alias("intp_5_11_interrupt")));

/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
volatile uint32_t g_intp0Taken;  	/* INTP0 taken */
volatile uint32_t g_intp1Taken;  	/* INTP1 taken */
volatile uint32_t g_intp2Taken;  	/* INTP2 taken */
volatile uint32_t g_intp3Taken;  	/* INTP3 taken */
volatile uint32_t g_intp4Taken;  	/* INTP4 taken */
volatile uint32_t g_intp5Taken;  	/* INTP5 taken */
volatile uint32_t g_intp6Taken;  	/* INTP6 taken */
volatile uint32_t g_intp7Taken;  	/* INTP7 taken */
volatile uint32_t g_intp8Taken;  	/* INTP8 taken */
volatile uint32_t g_intp9Taken;  	/* INTP9 taken */
volatile uint32_t g_intp10Taken;  	/* INTP10 taken */
volatile uint32_t g_intp11Taken;  	/* INTP11 taken */

/***********************************************************************************************************************
* Function Name: intp0_interrupt
* @brief  INTP0 interrupt entry
* @param  None
* @return None
***********************************************************************************************************************/
void intp0_interrupt(void)
{
    
        INTC_ClearPendingIRQ(INTP0_IRQn);
        intp0_callback();   
    
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp6_interrupt
* @brief  INTP6 interrupt entry
* @param  None
* @return None
***********************************************************************************************************************/
void intp6_interrupt(void)
{
    
        INTC_ClearPendingIRQ(INTP6_IRQn);
        intp6_callback();   
    
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp0_callback
* @brief  This function is a callback function when INTP0 interrupt occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void intp0_callback(void)
{
    /* Start user code. Do not edit comment generated here */
    g_intp0Taken++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp6_callback
* @brief  This function is a callback function when INTP6 interrupt occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void intp6_callback(void)
{
    /* Start user code. Do not edit comment generated here */
    g_intp6Taken++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp1_interrupt
* @brief  INTP1 interrupt entry
* @param  None
* @return None
***********************************************************************************************************************/
void intp1_interrupt(void)
{
    
        INTC_ClearPendingIRQ(INTP1_IRQn);
        intp1_callback();   
    
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp7_interrupt
* @brief  INTP7 interrupt entry
* @param  None
* @return None
***********************************************************************************************************************/
void intp7_interrupt(void)
{
    
        INTC_ClearPendingIRQ(INTP7_IRQn);
        intp7_callback();   
    
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp1_callback
* @brief  This function is a callback function when INTP1 interrupt occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void intp1_callback(void)
{
    /* Start user code. Do not edit comment generated here */
    g_intp1Taken++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp7_callback
* @brief  This function is a callback function when INTP7 interrupt occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void intp7_callback(void)
{
    /* Start user code. Do not edit comment generated here */
    g_intp7Taken++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp2_interrupt
* @brief  INTP2 interrupt entry
* @param  None
* @return None
***********************************************************************************************************************/
void intp2_interrupt(void)
{
    
        INTC_ClearPendingIRQ(INTP2_IRQn);
        intp2_callback();   
    
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp8_interrupt
* @brief  INTP8 interrupt entry
* @param  None
* @return None
***********************************************************************************************************************/
void intp8_interrupt(void)
{
    
        INTC_ClearPendingIRQ(INTP8_IRQn);
        intp8_callback();   
    
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp2_callback
* @brief  This function is a callback function when INTP2 interrupt occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void intp2_callback(void)
{
    /* Start user code. Do not edit comment generated here */
    g_intp2Taken++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp8_callback
* @brief  This function is a callback function when INTP8 interrupt occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void intp8_callback(void)
{
    /* Start user code. Do not edit comment generated here */
    g_intp8Taken++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp3_interrupt
* @brief  INTP3 interrupt entry
* @param  None
* @return None
***********************************************************************************************************************/
void intp3_interrupt(void)
{
    
        INTC_ClearPendingIRQ(INTP3_IRQn);
        intp3_callback();   
    
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp9_interrupt
* @brief  INTP9 interrupt entry
* @param  None
* @return None
***********************************************************************************************************************/
void intp9_interrupt(void)
{
    
        INTC_ClearPendingIRQ(INTP9_IRQn);
        intp9_callback();   
    
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp3_callback
* @brief  This function is a callback function when INTP3 interrupt occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void intp3_callback(void)
{
    /* Start user code. Do not edit comment generated here */
    g_intp3Taken++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp9_callback
* @brief  This function is a callback function when INTP9 interrupt occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void intp9_callback(void)
{
    /* Start user code. Do not edit comment generated here */
    g_intp9Taken++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp4_interrupt
* @brief  INTP4 interrupt entry
* @param  None
* @return None
***********************************************************************************************************************/
void intp4_interrupt(void)
{
    
        INTC_ClearPendingIRQ(INTP4_IRQn);
        intp4_callback();   
    
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp10_interrupt
* @brief  INTP10 interrupt entry
* @param  None
* @return None
***********************************************************************************************************************/
void intp10_interrupt(void)
{
    
        INTC_ClearPendingIRQ(INTP10_IRQn);
        intp10_callback();  
    
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp4_callback
* @brief  This function is a callback function when INTP4 interrupt occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void intp4_callback(void)
{
    /* Start user code. Do not edit comment generated here */
    g_intp4Taken++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp10_callback
* @brief  This function is a callback function when INTP10 interrupt occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void intp10_callback(void)
{
    /* Start user code. Do not edit comment generated here */
    g_intp10Taken++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp5_interrupt
* @brief  INTP5 interrupt entry
* @param  None
* @return None
***********************************************************************************************************************/
void intp5_interrupt(void)
{
    
        INTC_ClearPendingIRQ(INTP5_IRQn);
        intp5_callback();   
    
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp11_interrupt
* @brief  INTP11 interrupt entry
* @param  None
* @return None
***********************************************************************************************************************/
void intp11_interrupt(void)
{
    
        INTC_ClearPendingIRQ(INTP11_IRQn);
        intp11_callback();  
    
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp5_callback
* @brief  This function is a callback function when INTP5 interrupt occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void intp5_callback(void)
{
    /* Start user code. Do not edit comment generated here */
    g_intp5Taken++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp11_callback
* @brief  This function is a callback function when INTP11 interrupt occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void intp11_callback(void)
{
    /* Start user code. Do not edit comment generated here */
    g_intp11Taken++;
    /* End user code. Do not edit comment generated here */
}
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
