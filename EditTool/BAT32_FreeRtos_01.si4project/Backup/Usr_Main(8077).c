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

#include "Usr_E703.h"
#include "Usr_DataFlash.h"
#include "Usr_Psf.h"

unsigned char MCU_Reset_Flag;

uint8_t Flag_SysTick;
uint32_t Mcu_Timestamp;
uint32_t Mcu_ResetSource;
uint32_t Mcu_Name;
uint32_t Product_Name;
uint32_t Product_Verison;

uint16_t TimeSn_Time;
uint16_t TimeSn_SN;



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
        eStatus = eMBInit( MB_RTU, DEF_MB_SLAVE_ADDR, 0, 38400, MB_PAR_EVEN );
        
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
    
    //Init_printf("\nProgram Running...");
    
    //Init_printf(MCU_CORE);
    //Init_printf(MCU_Vender);
    Init_printf(MCU_NAME);
    
    //Init_printf(LANGUAGE_NAME);
    //Init_printf("%d,",__STDC_VERSION__);
    
    //Init_printf(IDE_INFOR);
    //Init_printf(COMPILER_INFOR);
    //Init_printf(PROJ_NAME);
    
    //Init_printf("\nCompiling Date:      %s;",__DATE__);
    //Init_printf("\nCompiling Time:      %s;",__TIME__);
    //Init_printf("\n");
    
    //Init_printf("\nFirmware Version:    %d-%d-%d;",FW_VERSION_PART0,FW_VERSION_PART1,FW_VERSION_PART2);
    //Init_printf("\nHardware Version:    %d-%d-%d;",HW_VERSION_PART0,HW_VERSION_PART1,HW_VERSION_PART2);
    //Init_printf("\n");
    
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
    
    #if 0
    if(1)
    {
        unsigned int i;
        
        for(i=0;i<2;i++)
        {
            i2c20_rdbuf[i] = 0xFF;
        }
        
        HDC3020_ReadID(hdc3020_rdbuf);
        
        ALSensor_TH_VID = hdc3020_rdbuf[0];
        ALSensor_TH_VID <<= 8;
        ALSensor_TH_VID += hdc3020_rdbuf[1];
        
        ALSensor_TH_PID = DEF_HT_PID;
        if((ALSensor_TH_VID == DEF_HT_VID)&&(ALSensor_TH_PID == DEF_HT_PID))  
        {
            
    #if(defined(DBG_PRINT_UART)&&(DBG_PRINT_UART>0))
    #else
                PORT_ToggleBit(Usr_DBGIO2_PORT,Usr_DBGIO2_PIN);
    #endif
        }
        
        Debug_printf("\nI2C2: WT: 0x%02X,0x%02X,",DEF_HDC3020_I2C_ADDR_WT,0x81);
        Debug_printf("\nI2C2: RD: 0x%02X,0x%02X,0x%02X,",DEF_E703_I2C_ADDR_RD,hdc3020_rdbuf[0],hdc3020_rdbuf[1]);
        Debug_printf("\nHDC3020 ChipID: 0x%02X,0x%02X,\n",hdc3020_rdbuf[0],hdc3020_rdbuf[1]);
    }
    #endif
    
    ALSensor_TH_MainLoop();
    #endif
    
    
    #if(defined(SENSOR_PT_TYPE)&&(SENSOR_PT_TYPE == SENSOR_TYPE_CMP201))
    
    
    #if 0
    if(1)
    {
        CMP201_ChipID = 0xFF;
        
        /*****  check sensor ID *****/
    #define CMP201_REG_CHIP_ID          0x00
        i2c_burst_read(I2C_CHANNEL_CMP201,DEF_CMP201_I2C_ADDR_7B,CMP201_REG_CHIP_ID,&CMP201_ChipID, 1);
        
        if(CMP201_ChipID == 0xA0)
        {
            
    #if(defined(DBG_PRINT_UART)&&(DBG_PRINT_UART>0))
    #else
            //PORT_ToggleBit(Usr_HTMNBD_PORT,Usr_HTMNBD_PIN);
    #endif
        }
        
        Debug_printf("\nI2C3: WT: 0x%02X,0x%02X,",DEF_CMP201_I2C_ADDR_WT,CMP201_REG_CHIP_ID);
        Debug_printf("\nI2C3: RD: 0x%02X,0x%02X,",DEF_E703_I2C_ADDR_RD,CMP201_ChipID);
        Debug_printf("\nCMP201 ChipID: 0x%02X,\n",CMP201_ChipID);
        
    }
    #endif
    //ALSensor_CMP201_Stage = 0;
    
    ALSensor_CMP201_MainLoop();
    
    #endif
    
    
    Debug_printf("\nMcu_Timestamp,%d,",Mcu_Timestamp);
    Flag_SysTick = 0;
    
    for(;;)
    {
        
        if(((Mcu_Timestamp%1000) == 0)&&(Flag_SysTick == 1))
        {
            if(MCU_Reset_Flag == 1)
            {
                MCU_Reset_Flag = 0;
                
                NVIC_SystemReset();
            }
            
            Flag_SysTick = 0;
            // Debug_printf("\nMcu_Timestamp,%d,",Mcu_Timestamp);
            
            Usr_I2CS_MainLoop();
            
            #if((defined(SENSOR_HT_TYPE))&&(SENSOR_HT_TYPE > 0))
            ALSensor_TH_MainLoop();
            
            Debug_printf("\tHDC3020 ExtSens_Tmpr,%f,\tExtSens_RH,%f,",ExtSens_Tmpr,ExtSens_RH);
            #endif
            
            #if(defined(SENSOR_PT_TYPE)&&(SENSOR_PT_TYPE == SENSOR_TYPE_CMP201))
            
            //ALSensor_CMP201_Stage = 0;
            
            ALSensor_CMP201_MainLoop();
            Debug_printf("\tCMP201 ExtSens_Tmpr,%f,\tExtSens_Tmpr2,%f,",ExtSens_Prs,ExtSens_Tmpr2);
            
            #endif
            
            
            Tmpr_TRaw = E703_ADC_T;
            Sens_SRaw = E703_ADC_S;
            
            #if(defined(DEF_FUN_TCOMP_EN)&&(DEF_FUN_TCOMP_EN==1))
            Usr_TComp_Polynomial_Cubic(Tmpr_TRaw, &Sens_DltSRaw);
            #else
            Sens_DltSRaw = 0;
            #endif
            
            Sens_SRawComp = Sens_SRaw - Sens_DltSRaw;
            
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
        
        #if(defined(DEF_DATAFLASH_EN)&&(DEF_DATAFLASH_EN == 1))
        {
            if(DF_UpdateReal_Flag == 1)
            {
                EraseSector(DEF_DF_PARAM_STARTADDR);
                
                flash_write(DEF_DF_PARAM_STARTADDR, DEF_DF_DATA_LEN, DF_Data);
                
                DF_UpdateReal_Flag = 0;
                
                #if 0
                {
                    // Update Varialbe from Data Flash;
                    TimeSn_Time = DF_Data[DEF_TIME_SN_INDEX+1];
                    TimeSn_Time<<=8;
                    TimeSn_Time += DF_Data[DEF_TIME_SN_INDEX];
                    
                    TimeSn_SN = DF_Data[DEF_TIME_SN_INDEX+1+2];
                    TimeSn_SN<<=8;
                    TimeSn_SN += DF_Data[DEF_TIME_SN_INDEX+2];
                }
                #endif
                
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
                    
                    #if 1
                    //Init_printf("\nWrite new CRC16 data;");
                    
                    Usr_E703_UnlockReg();
                    Usr_E703_UnlockCMUsr();
                    
                    Usr_E703_WriteCMUsr(0x7E,crc16);
                    
                    Usr_E703_LockCMUsr();
                    Usr_E703_LockReg();
                    
                    E703_CMData_Probe[63].addr = 0x7E;
                    E703_CMData_Probe[63].data = crc16;
                    E703_CMBuff[63] = crc16;
                    
                    #endif
                    
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
        
        eStatus = eMBInit( MB_RTU, DEF_MB_SLAVE_ADDR, 0, 38400, MB_PAR_EVEN );
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


