#ifndef __USR_MAIN_C__
#define __USR_MAIN_C__

#include<stdint.h>
#include <stdio.h>

#include "BAT32A237.h"

#include"gpio.h"

#include"Usr_Config.h"
#include"Usr_Main.h"
#include"Usr_GPIO.h"

#include"Usr_Uart.h"
#include "Usr_I2C.h"

#include "tima.h"

#if(defined(DEF_FREEMODBUS_EN)&&(DEF_FREEMODBUS_EN==1))
#include "mb.h"
#include "Usr_Modbus.h"
#endif



uint8_t Flag_SysTick;
uint32_t Mcu_Timestamp;
uint32_t Mcu_ResetSource;
uint32_t Mcu_Name;
uint32_t Product_Name;
uint32_t Product_Verison;


#if(defined(DEF_SOFT_ARCH)&&(DEF_SOFT_ARCH == DEF_MAINLOOP))

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
    
    #if(defined(DEF_FREEMODBUS_EN)&&(DEF_FREEMODBUS_EN==1))
    {
        eMBErrorCode    eStatus;
        
        //eStatus = eMBInit( MB_RTU, 0x0A, 0, 38400, MB_PAR_EVEN );
        eStatus = eMBInit( MB_RTU, 0x01, 0, 38400, MB_PAR_EVEN );
        
        Modbus_printf("\neStatus = eMBInit(); eStatus = %d. ",eStatus);
        
        /* Enable the Modbus Protocol Stack. */
        eStatus = eMBEnable(  );
        
        Modbus_printf("\neStatus = eMBEnable(); eStatus = %d. ",eStatus);
        
        {
            Usr_Mb_T3d5_Value = 50*SystemCoreClock/Usr_Uart_Baudrate;
            
            TMA0_IntervalTimer(TMA_COUNT_SOURCE_FCLK, Usr_Mb_T3d5_Value);     // 50us;
        }
    }
    #endif
    
    #if 1   // Project base information;
    
    Debug_printf("\nProgram Running...");
    
    Debug_printf(MCU_CORE);
    Debug_printf(MCU_Vender);
    Debug_printf(MCU_NAME);
    
    Debug_printf(LANGUAGE_NAME);
    Debug_printf("%d,",__STDC_VERSION__);
    
    Debug_printf(IDE_INFOR);
    Debug_printf(COMPILER_INFOR);
    Debug_printf(PROJ_NAME);
    
    //Debug_printf("\nCompiling Date:      %s;",__DATE__);
    //Debug_printf("\nCompiling Time:      %s;",__TIME__);
    //Debug_printf("\n");
    
    Debug_printf("\nFirmware Version:    %d-%d-%d;",FW_VERSION_PART0,FW_VERSION_PART1,FW_VERSION_PART2);
    Debug_printf("\nHardware Version:    %d-%d-%d;",HW_VERSION_PART0,HW_VERSION_PART1,HW_VERSION_PART2);
    Debug_printf("\n");
    
    Debug_printf(MCU_SYSCLK);
    Debug_printf("%d.\n",SystemCoreClock);
    
    #endif
    
    #if(defined(DEF_TASK_I2CS_EN)&&(DEF_TASK_I2CS_EN==1))
    Usr_I2CS_InitSetup();
    #endif
    
    
    Debug_printf("\nMcu_Timestamp,%d,",Mcu_Timestamp);
    Flag_SysTick = 0;
    
    for(;;)
    {
        
        if(((Mcu_Timestamp%1000) == 0)&&(Flag_SysTick == 1))
        {
            Flag_SysTick = 0;
            // Debug_printf("\nMcu_Timestamp,%d,",Mcu_Timestamp);
            
            Usr_I2CS_MainLoop();
            
        }
        
        //Usr_GPIO_MainLoop();
        
        //Usr_Uart_MainLoop();
        
        #if(defined(DEF_FREEMODBUS_EN)&&(DEF_FREEMODBUS_EN==1))
        {
            
            ( void )eMBPoll(  );
            
            /* Here we simply count the number of poll cycles. */
            usRegInputBuf[0]++;
            
        }
        #endif
        
    }
    
    //return 0;
}
#endif



#if(defined(DEF_SOFT_ARCH)&&(DEF_SOFT_ARCH == DEF_FREERTOS))

#include"FreeRTOSConfig.h"

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
    
    
    #if 1   // Project base information;
    
    NOS_printf("\nProgram Running...");
    
    NOS_printf(MCU_CORE);
    NOS_printf(MCU_Vender);
    NOS_printf(MCU_NAME);
    
    NOS_printf(LANGUAGE_NAME);
    NOS_printf("%d,",__STDC_VERSION__);
    
    NOS_printf(IDE_INFOR);
    NOS_printf(COMPILER_INFOR);
    NOS_printf(PROJ_NAME);
    
    //NOS_printf("\nCompiling Date:      %s;",__DATE__);
    //NOS_printf("\nCompiling Time:      %s;",__TIME__);
    //NOS_printf("\n");
    
    NOS_printf("\nFirmware Version:    %d-%d-%d;",FW_VERSION_PART0,FW_VERSION_PART1,FW_VERSION_PART2);
    NOS_printf("\nHardware Version:    %d-%d-%d;",HW_VERSION_PART0,HW_VERSION_PART1,HW_VERSION_PART2);
    NOS_printf("\n");
    
    NOS_printf(MCU_SYSCLK);
    NOS_printf("%d.\n",SystemCoreClock);
    
    NOS_printf("Mcu_Timestamp,%d,\n",Mcu_Timestamp);
    
    Flag_SysTick = 0;
    
    #endif
    
    
    #if 1
    
    
    #endif
    
    
    Usr_Task_Create();
    
    SysTick_Config(SystemCoreClock / 1000); 
    
    {
        #include "mb.h"
        
        eMBErrorCode    eStatus;
        
        eStatus = eMBInit( MB_RTU, 0x0A, 0, 38400, MB_PAR_EVEN );
        if(eStatus == MB_ENOERR)
        {
            
        }
        
        TMA0_IntervalTimer(TMA_COUNT_SOURCE_FCLK, 800);     // 50us;
    }
    
    vTaskStartScheduler();
    
    while(1);
    
    //return 0;
}
#endif


#endif


