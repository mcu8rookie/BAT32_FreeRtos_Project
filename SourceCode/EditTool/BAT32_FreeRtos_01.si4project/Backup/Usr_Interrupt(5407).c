#ifndef __USR_INTERRUPT_C__
#define __USR_INTERRUPT_C__

#include<stdint.h>
#include "BAT32A237.h"
#include"Usr_Config.h"
#include"Usr_Main.h"
#include"Usr_GPIO.h"
#include"Usr_Interrupt.h"

#include"Usr_Uart.h"

/***********************************************************************************************************************
* Function Name: SysTick Handler
* Description  : Decreament the g_ticks value
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
//void SysTick_Handler(void)
void SysTick_Handler_UsrPart(void)
{
    //WDT->WDTE = 0xAC;
    
    Mcu_Timestamp++;
    Flag_SysTick = 1;
    
    if(Usr_GPIO_Timestamp > 0)
    {
        Usr_GPIO_Timestamp--;
    }
    
    if(Usr_Uart_Timestamp > 0)
    {
        Usr_Uart_Timestamp--;
    }
}


#if 0
SVC_Handler               ; SVCall Handler
PendSV_Handler            ; PendSV Handler
SysTick_Handler           ; SysTick Handler
#endif

#endif


