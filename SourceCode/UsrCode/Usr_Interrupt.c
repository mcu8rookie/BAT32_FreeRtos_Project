#ifndef __USR_INTERRUPT_C__
#define __USR_INTERRUPT_C__

#include<stdint.h>
#include "BAT32A237.h"
#include"Usr_GPIO.h"
#include"Usr_Interrupt.h"

#include"Usr_Uart.h"

/***********************************************************************************************************************
* Function Name: SysTick Handler
* Description  : Decreament the g_ticks value
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void SysTick_Handler(void)
{
    //WDT->WDTE = 0xAC;
    
    
    if(Usr_GPIO_Timestamp > 0)
    {
        Usr_GPIO_Timestamp--;
    }
    
    if(Usr_Uart_Timestamp > 0)
    {
        Usr_Uart_Timestamp--;
    }
}



#endif


