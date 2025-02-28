#ifndef __USR_MAIN_C__
#define __USR_MAIN_C__

#include<stdint.h>
#include"Usr_Config.h"
#include"Usr_Main.h"
#include"Usr_GPIO.h"



#if(DEF_TEST_FUNC == DEF_TEST_NONE)
// 
int main(int argc, char *argv[])
{
    
    return 0;
}
#endif

#if(DEF_TEST_FUNC == DEF_TEST_GPIO)
// 
//#include <stdio.h>
#include "BAT32A237.h"


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


#endif


