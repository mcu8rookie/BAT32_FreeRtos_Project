#ifndef __USR_INTERRUPT_C__
#define __USR_INTERRUPT_C__

#include<stdint.h>
#include "BAT32A237.h"
#include"Usr_GPIO.h"
#include"Usr_Interrupt.h"

/***********************************************************************************************************************
* Function Name: SysTick Handler
* Description  : Decreament the g_ticks value
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void SysTick_Handler(void)
{
    WDT->WDTE = 0xAC;
    
    //g_ticks--;
    
    if(Usr_GPIO_Timestamp>0)
    {
        Usr_GPIO_Timestamp--;
    }
}



#endif


