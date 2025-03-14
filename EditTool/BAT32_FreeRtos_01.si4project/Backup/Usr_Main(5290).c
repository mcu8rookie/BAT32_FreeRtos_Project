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

#include "Usr_Psf.h"

#include "core_cm0plus.h"
#include "core_cmFunc.h"

#include "flash.h"

#include "Usr_I2CA_Slave.h"

#if(defined(DEF_FREEMODBUS_EN)&&(DEF_FREEMODBUS_EN==1))
#include "mb.h"
#include "Usr_Modbus.h"
#endif

#include "Usr_E703.h"
#include "Usr_DataFlash.h"
#include "Usr_Psf.h"
#include "Usr_ALSensor.h"

unsigned char MCU_Reset_Flag;

uint8_t Flag_SysTick;
uint32_t Mcu_Timestamp;
uint32_t Mcu_ResetSource;
uint32_t Mcu_Name;
uint32_t Product_Name;
uint32_t Product_Verison;

uint16_t TimeSn_Time;
uint16_t TimeSn_SN;

uint32_t Mcu_Time1s_Cnt;



volatile unsigned int DlyMsCnt = 0;

void Sample_DelayMs(unsigned int ms)
{
    
    DlyMsCnt = ms;
    while(DlyMsCnt > 0)
    {
        
    }
}

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
        eStatus = eMBInit( MB_RTU, DEF_MB_SLAVE_ADDR, 0, Usr_Uart_Baudrate, MB_PAR_EVEN );
        
        Modbus_printf("\neStatus = eMBInit(); eStatus = %d. ",eStatus);
        
        /* Enable the Modbus Protocol Stack. */
        eStatus = eMBEnable(  );
        
        Modbus_printf("\neStatus = eMBEnable(); eStatus = %d. ",eStatus);
        
        {
            //Usr_Mb_T3d5_Value = 50*SystemCoreClock/Usr_Uart_Baudrate;
            if(Usr_Uart_Baudrate<19200)
            {
                Usr_Mb_T3d5_Value = 50*(SystemCoreClock/Usr_Uart_Baudrate);
            }
            else
            {
                Usr_Mb_T3d5_Value = 50*(SystemCoreClock/19200);
            }
            
            if(Usr_Mb_T3d5_Value>65535)
            {
                Usr_Mb_T3d5_Value = 65535;
            }
            
            TMA0_IntervalTimer(TMA_COUNT_SOURCE_FCLK, Usr_Mb_T3d5_Value);     // 50us;
        }
    }
    #endif
    
    #if 1   // Project base information;
    
    Init_printf(MCU_NAME);
    
    Init_printf(MCU_SYSCLK);
    Init_printf("%d.\n",SystemCoreClock);
    
    #endif
    
    #if(defined(DEF_DATAFLASH_EN)&&(DEF_DATAFLASH_EN==1))
    Usr_DF_InitSetup();
    #endif
    
    #if(defined(DEF_TASK_I2CS_EN)&&(DEF_TASK_I2CS_EN==1))
    Usr_I2CS_InitSetup();
    #endif
    
    
    #if((defined(SENSOR_HT_TYPE))&&(SENSOR_HT_TYPE == SENSOR_TYPE_HDC3020))
    
    ALSensor_TH_MainLoop();
    
    #endif
    
    #if(defined(SENSOR_PT_TYPE)&&(SENSOR_PT_TYPE == SENSOR_TYPE_CMP201))
    
    //ALSensor_CMP201_Stage = 0;
    
    ALSensor_CMP201_MainLoop();
    
    #endif
    
    #if 1
    Usr_I2CA_InitSetup();
    #endif
    
    //Mcu_Timestamp = 0;
    
    if((Sens_CoolTime == 0)&&(Sens_CoolTime == 0xFFFF))
    {
        Psf_State = PSF_STATE_INIT;
        Psf_Next_State = PSF_STATE_E703;
        Psf_State_KeepTime = PSF_STATE_E703_KEEPTIME;
    }
    else
    {
        Psf_State = PSF_STATE_INIT;
        Psf_Next_State = PSF_STATE_PREHEAT;
        
        if(Sens_PreHeatTime == 0xFFFF)
        {
            Psf_State_KeepTime = 0;
        }
        else
        {
            Psf_State_KeepTime = Sens_PreHeatTime;
        }
        
    }
    
    
    Debug_printf("\nMcu_Timestamp,%d,",Mcu_Timestamp);
    Flag_SysTick = 0;
    
    while(1)
    {
        Usr_I2CA_MainLoop();
        
        if(((Mcu_Timestamp%1000) == 0)&&(Flag_SysTick == 1))
        {
            if(MCU_Reset_Flag == 1)
            {
                MCU_Reset_Flag = 0;
                
                //////__set_FAULTMASK(1);
                
                NVIC_SystemReset();
            }
            
            Flag_SysTick = 0;
            // Debug_printf("\nMcu_Timestamp,%d,",Mcu_Timestamp);
            
        }
        
        if(Psf_Next_State != Psf_State)
        {
            switch(Psf_Next_State)
            {
                case PSF_STATE_INIT:
                {
                    
                }
                break;
                
                case PSF_STATE_PREHEAT:
                {
                    
                    #if 0
                    PORT_SetBit(Usr_LED2_PORT,Usr_LED2_PIN);
                    #endif
                    
                    PORT_SetBit(Usr_LDOEN_PORT,Usr_LDOEN_PIN);
                    
                    //Psf_State_KeepTime = PSF_STATE_PREHEAT_KEEPTIME;
                    
                    if(Sens_PreHeatTime == 0xFFFF)
                    {
                        Psf_State_KeepTime = 0;
                    }
                    else
                    {
                        Psf_State_KeepTime = Sens_PreHeatTime;
                    }
                }
                break;
                
                case PSF_STATE_E703:
                {
                    
                }
                break;
                
                case PSF_STATE_COOL:
                {
                    PORT_ClrBit(Usr_LDOEN_PORT,Usr_LDOEN_PIN);
                    
                    FilterIndex = 0;
                    FilterTotal = 0;
                    
                    if(Sens_CoolTime == 0xFFFF)
                    {
                        Psf_State_KeepTime = 0;
                    }
                    else
                    {
                        Psf_State_KeepTime = Sens_CoolTime;
                    }
                }
                break;
                
                default:
                
                break;
            }
            
            Psf_State = Psf_Next_State;
        }
        
        switch(Psf_State)
        {
            case PSF_STATE_INIT:
            {
                
            }
            break;
            
            case PSF_STATE_PREHEAT:
            {
                if(Psf_State_KeepTime == 0)
                {
                    Psf_Next_State = PSF_STATE_E703;
                }
            }
            break;
            
            case PSF_STATE_E703:
            {
                if((Psf_State_KeepTime == 0)&&Flag_1Ms>2)
                {
                    uint16_t tmp1;
                    #if 1
                    
                    #if 0
                    PORT_ClrBit(Usr_LED2_PORT,Usr_LED2_PIN);
                    #endif
                    
                    Usr_E703_ReadData();
                    
                    Flag_1Ms = 0;
                    
                    #if(defined(DEF_SRAW_FILTER_EN)&&(DEF_SRAW_FILTER_EN==1))
                    tmp1 = Usr_SRaw_Filter(E703_ADC_S);
                    #else
                    Sens_UpdateFlag = 1;
                    #endif
                    
                    E703_RegBuff[17] = E703_ADC_TC;
                    E703_RegBuff[18] = E703_ADC_T;
                    E703_RegBuff[19] = E703_ADC_S;
                    E703_RegBuff[21] = E703_DSP_T;
                    E703_RegBuff[22] = E703_DSP_S;
                    
                    
                    #if 0
                    Debug_printf("\nADC_TC,%d,",E703_ADC_TC);
                    Debug_printf("\tADC_T,%d,",E703_ADC_T);
                    Debug_printf("\tADC_S,%d,",E703_ADC_S);
                    Debug_printf("\tDSP_T,%d,",E703_DSP_T);
                    Debug_printf("\tDSP_S,%d,",E703_DSP_S);
                    
                    Debug_printf("\tCMD,%d,",E703_CMD);
                    Debug_printf("\tStatus_sync,0x%04X,",E703_Status_sync);
                    Debug_printf("\tStatus,0x%04X,",E703_Status);
                    Debug_printf("\tCM_Status,0x%04X,",E703_CM_Status);
                    #endif
                    
                    #endif
                    
                    if(Sens_UpdateFlag == 1)
                    {   
                        
                        
                        //Tmpr_TRaw = E703_ADC_T;
                        Tmpr_TRaw = ExtSens_Tmpr_Raw;
                        
                        #if(defined(DEF_SRAW_FILTER_EN)&&(DEF_SRAW_FILTER_EN==1))
                        Sens_SRaw = tmp1;
                        #else
                        Sens_SRaw = E703_ADC_S;
                        #endif
                        
                        Sens_UpdateFlag = 0;
                        
                        #if(defined(DEF_FUN_TCOMP_EN)&&(DEF_FUN_TCOMP_EN==1))
                        Usr_TComp_Polynomial_Cubic(Tmpr_TRaw, &Sens_DltSRaw);
                        #else
                        Sens_DltSRaw = 0;
                        #endif
                        
                        Sens_SRawComp = Sens_SRaw - Sens_DltSRaw;
                        
                        if((Sens_CoolTime == 0)&&(Sens_CoolTime == 0xFFFF))
                        {
                            
                        }
                        else
                        {
                            Psf_Next_State = PSF_STATE_COOL;
                        }
                    }
                    
                    
                }
            }
            break;
            
            case PSF_STATE_COOL:
            {
                if(Psf_State_KeepTime == 0)
                {
                    Psf_Next_State = PSF_STATE_PREHEAT;
                }
            }
            break;
            
            default:
            
            break;
        }
        
        
        #if((defined(SENSOR_HT_TYPE))&&(SENSOR_HT_TYPE > 0))
        ALSensor_TH_MainLoop();
        
        Debug_printf("\tHDC3020 ExtSens_Tmpr,%f,\tExtSens_RH,%f,",ExtSens_Tmpr,ExtSens_RH);
        #endif
        
        #if(defined(SENSOR_PT_TYPE)&&(SENSOR_PT_TYPE == SENSOR_TYPE_CMP201))
        
        //ALSensor_CMP201_Stage = 0;
        
        ALSensor_CMP201_MainLoop();
        Debug_printf("\tCMP201 ExtSens_Tmpr,%f,\tExtSens_Tmpr2,%f,",ExtSens_Prs,ExtSens_Tmpr2);
        
        #endif
        
        #if(defined(DEF_FREEMODBUS_EN)&&(DEF_FREEMODBUS_EN==1))
        {
            
            ( void )eMBPoll(  );
            
            /* Here we simply count the number of poll cycles. */
            usRegInputBuf[0]++;
            
        }
        #endif
        
        #if(defined(DEF_DATAFLASH_EN)&&(DEF_DATAFLASH_EN == 1))
        {
            if(DF_UpdateReal_Flag == 1)
            {
                EraseSector(DEF_DF_PARAM_STARTADDR);
                
                flash_write(DEF_DF_PARAM_STARTADDR, DEF_DF_DATA_LEN, DF_Data);
                
                DF_UpdateReal_Flag = 0;
                
                Usr_DFData_To_Variable();
                
            }
        }
        #endif
        
        #if 1
        {
            if(E703_Reset_Flag == 1)
            {
                E703_Reset_Flag = 0;
                
                Usr_Read_All_Reg();
                Usr_Read_All_CM();
                
                {
                    uint16_t crc16 = 0;
                    
                    crc16 = Usr_E703_CRC(16,0x8005,0xFFFF,(uint16_t*)Buff_U8,(DEF_CM_DATA_NUM-1)*16);
                    
                    Usr_E703_UnlockReg();
                    Usr_E703_UnlockCMUsr();
                    
                    Usr_E703_WriteCMUsr(0x7E,crc16);
                    
                    Usr_E703_LockCMUsr();
                    Usr_E703_LockReg();
                    
                    E703_CMData_Probe[63].addr = 0x7E;
                    E703_CMData_Probe[63].data = crc16;
                    E703_CMBuff[63] = crc16;
                    
                    
                }
                
                Sample_DelayMs(50);
                
                #if 1   // E703 Reset;
                {
                    // 0xB169: reset;   Performs a reset with complete power up sequence
                    uint16_t tmp1 = 0xB169;
                    Usr_E703_WriteReg(DEF_REGADDR_CMD, tmp1);
                    
                    Debug_printf("\nE703_Reset;");
                    
                    Usr_E703_LockCMFCT();
                    Usr_E703_LockCMUsr();
                    Usr_E703_LockReg();
                }
                
                Sample_DelayMs(50);
                
                #endif
                
                Mcu_Timestamp = 800;
            }
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
        
        eStatus = eMBInit( MB_RTU, DEF_MB_SLAVE_ADDR, 0, Usr_Uart_Baudrate, MB_PAR_EVEN );
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


