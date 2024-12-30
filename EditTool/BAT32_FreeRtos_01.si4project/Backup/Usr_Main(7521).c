#ifndef __USR_MAIN_C__
#define __USR_MAIN_C__

#include<stdint.h>
//#include <stdio.h>

#include "BAT32A237.h"

#include"Usr_Config.h"
#include"Usr_Main.h"
#include"Usr_GPIO.h"

#include"Usr_Uart.h"



#if(DEF_TEST_FUNC == DEF_TEST_NONE)
// 
int main(int argc, char *argv[])
{
    
    return 0;
}
#endif

#if(DEF_TEST_FUNC == DEF_TEST_GPIO)



void Mcu_Init(void)
{
    uint32_t msCnt;
    
    SystemCoreClockUpdate();
    msCnt = SystemCoreClock / 1000;
    SysTick_Config(msCnt); 
    
    
}

int main(int argc, char *argv[])
{
    
    Mcu_Init();
    
    Usr_GPIO_InitSetup();
    
    for(;;)
    {
        Usr_GPIO_MainLoop();
    }
    
    //return 0;
}
#endif

#if(DEF_TEST_FUNC == DEF_TEST_UART)

void Mcu_Init(void)
{
    uint32_t msCnt;
    
    SystemCoreClockUpdate();
    msCnt = SystemCoreClock / 1000;
    SysTick_Config(msCnt); 
    
    SystemCoreClockUpdate();
}

int main(int argc, char *argv[])
{
    
    Mcu_Init();
    
    Uart_St_Init_s();
    
    Usr_GPIO_InitSetup();
    
    //Usr_Uart_InitSetup();
    Usr_Uart_Init(0,115200);
    
    
    for(;;)
    {
        Usr_GPIO_MainLoop();
        
        //Usr_Uart_MainLoop();
        Usr_Uart_Echo(0);
    }
    
    //return 0;
}
#endif



#endif


