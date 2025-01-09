#ifndef __USR_MAIN_C__
#define __USR_MAIN_C__

#include<stdint.h>
//#include <stdio.h>

#include "BAT32A237.h"

#include"Usr_Config.h"
#include"Usr_Main.h"
#include"Usr_GPIO.h"

#include"Usr_Uart.h"

uint8_t Flag_SysTick;
uint32_t Mcu_Timestamp;
uint32_t Mcu_ResetSource;
uint32_t Mcu_Name;
uint32_t Product_Name;
uint32_t Product_Verison;



#if 0//(DEF_TEST_FUNC == DEF_TEST_NONE)
// 

void Mcu_Init(void)
{
    uint32_t msCnt;
    
    SystemCoreClockUpdate();
    msCnt = SystemCoreClock / 1000;
    SysTick_Config(msCnt); 
    
    SystemCoreClockUpdate();
    
    Mcu_Timestamp = 0;
}

int main(int argc, char *argv[])
{
    Mcu_Init();
    
    #if(defined(DEF_TASK_I2C20_EN)&&(DEF_TASK_I2C20_EN==1))
    Usr_I2C20_InitSetup();
    #endif

    while(1)
    {
        Usr_I2C20_MainLoop();
    }
    
    return 0;
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
    
    Mcu_Timestamp = 0;
}

int main(int argc, char *argv[])
{
    
    Mcu_Init();
    
    Uart_St_Init_s();
    
    Usr_GPIO_InitSetup();
    
    Usr_Uart_InitSetup();
    
    #if 1
    Debug_printf("\nProgram start...");
    Debug_printf(MCU_CORE);
    Debug_printf(MCU_NAME);
    Debug_printf(MCU_SYSCLK); printf("%d.\n",SystemCoreClock);
    Debug_printf(PROJ_NAME);
    #endif
    
    #if(defined(DEF_TASK_I2C20_EN)&&(DEF_TASK_I2C20_EN==1))
    Usr_I2C20_InitSetup();
    #endif
    
    
    Debug_printf("Mcu_Timestamp,%d,\n",Mcu_Timestamp);
    Flag_SysTick = 0;
    
    for(;;)
    {
        if(((Mcu_Timestamp%1000) == 0)&&(Flag_SysTick == 1))
        {
            Flag_SysTick = 0;
            Debug_printf("Mcu_Timestamp,%d,\n",Mcu_Timestamp);
            
            Usr_I2C20_MainLoop();
        }
        
        Usr_GPIO_MainLoop();
        
        Usr_Uart_MainLoop();
        
        
    }
    
    //return 0;
}
#endif



#if(DEF_TEST_FUNC == DEF_TEST_FREERTOS)

void Mcu_Init(void)
{
    //uint32_t msCnt;
    
    SystemCoreClockUpdate();
    //msCnt = SystemCoreClock / 1000;
    //SysTick_Config(msCnt); 
    
    SystemCoreClockUpdate();
    
    Mcu_Timestamp = 0;
}

int main(int argc, char *argv[])
{
    
    //__enable_irq()
    
    Mcu_Init();
    
    Uart_St_Init_s();
    
    Usr_GPIO_InitSetup();
    
    Usr_Uart_InitSetup();
    
    #if 1
    Init_printf("\r\nMCU Core:          ARM Cotex-M0+;");
    Init_printf("\r\nMCU Vender:        Cmsemicon;");
    Init_printf("\r\nMCU Product:       BAT32A237KH40NB;  (24NA/32FP/40NB/48FA/64FB)");
    
    Init_printf("\r\n");
    Init_printf("\r\nCompiler:          Armcc5.05;");
    Init_printf("\r\n__STDC__VERSION__: %ld;",__STDC_VERSION__);
    Init_printf("\r\n");
    
    Init_printf("\r\nCompiling Date:    %s;",__DATE__);
    Init_printf("\r\nCompiling Time:    %s;",__TIME__);
    Init_printf("\r\n");
    
    Init_printf("\r\nCorporate Name:    Posifa;");
    Init_printf("\r\nPorduct Name:      RS485_I2CS;");
    Init_printf("\r\n");
    
    Init_printf("\r\nFirmware Version:  %d-%d-%d;",FW_VERSION_PART0,FW_VERSION_PART1,FW_VERSION_PART2);
    Init_printf("\r\nHardware Version:  %d-%d-%d;",HW_VERSION_PART0,HW_VERSION_PART1,HW_VERSION_PART2);
    Init_printf("\r\n");
    
    Init_printf("\r\nSystemCoreClock:   %d;",SystemCoreClock);
    Init_printf("\r\nUart Boadrate:     %d;",115200);
    
    Init_printf("\r\n");
    #endif
    
    
    #if 1
    
    
    #endif
    
    
    Debug_printf("Mcu_Timestamp,%d,\n",Mcu_Timestamp);
    Flag_SysTick = 0;
    
    
    Usr_Task_Create();

    SysTick_Config(SystemCoreClock / 1000); 
    
    vTaskStartScheduler();
    
    while(1);
    
    //return 0;
}
#endif


#endif


