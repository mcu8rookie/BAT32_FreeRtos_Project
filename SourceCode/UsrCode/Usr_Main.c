#ifndef __USR_MAIN_C__
#define __USR_MAIN_C__

#include<stdint.h>
#include <stdio.h>

#include "BAT32A237.h"
#include "userdefine.h"
#include "adc.h"

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

#include "Usr_ADC.h"


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
    
    Init_printf("\nHW Ver:    ");Init_printf("%d-%d-%d.",HW_VERSION_PART0,HW_VERSION_PART1,HW_VERSION_PART2);
    Init_printf("\nSW Ver:    ");Init_printf("%d-%d-%d.",FW_VERSION_PART0,FW_VERSION_PART1,FW_VERSION_PART2);
    
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
    
    #if(defined(DEF_ADC_EN)&&(DEF_ADC_EN==1))
    Usr_Adc_InitSetup();
    #endif
    
    #if(defined(DEF_HPC_FUNC_EN)&&(DEF_HPC_FUNC_EN == 1))
    HPC_InitSetup(1);
    #else
    HeatBoard_Duty = 0;
    HeatBoard_Period = 0;
    HeatBoard_Cool();
    #endif
    
    //Mcu_Timestamp = 0;
    
    if((Sens_CoolTime == 0)||(Sens_CoolTime == 0xFFFF))
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
        
        
        #if(defined(DEF_ADC_EN)&&(DEF_ADC_EN==1))
        Usr_Adc_MainLoop();
        #endif
        
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
                    Flag_HeatMems = 1;
                    Usr_Adc_ValidTime = 0;
                    g_AdcIntTaken = 0;
                    
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
                    //PORT_SetBit(Usr_LDOEN_PORT,Usr_LDOEN_PIN);
                    
                    Flag_HeatMems = 0;
                    Usr_Adc_ValidTime = 0;
                    g_AdcIntTaken = 0;
                    
                    FilterIndex = 0;
                    FilterTotal = 0;
                        
                    #if(defined(DEF_HTHH_MODE_EN)&&(DEF_HTHH_MODE_EN==1))
                    if(Flag_HighTmprHighHumi == 1)
                    {
                        Psf_State_KeepTime = 10000;
                    }
                    else
                    #endif
                    {
                        if((Sens_CoolTime==0)||(Sens_CoolTime==0xFFFF))
                        {
                            Sens_CoolTime = 0;
                        }
                        else
                        {
                            Psf_State_KeepTime = Sens_CoolTime;
                        }
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
                    int16_t tmp1;
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
                        
                        if((TComp_TRawBase == 0)||(TComp_TRawBase==0xFFFF))
                        {
                            Tmpr_DltTRaw = 0;
                        }
                        else
                        {
                            Tmpr_DltTRaw = Tmpr_TRaw - TComp_TRawBase;
                        }
                        
                        #if(defined(DEF_SRAW_FILTER_EN)&&(DEF_SRAW_FILTER_EN==1))
                        Sens_SRaw = tmp1;
                        #else
                        Sens_SRaw = E703_ADC_S;
                        #endif
                        
                        Sens_Raw_After_Filter = Sens_SRaw;
                        
                        Sens_UpdateFlag = 0;
                        
                        
                        #if(defined(DEF_DBG_SRAW_0_EN)&&(DEF_DBG_SRAW_0_EN==1))
                        if(Sens_Raw_After_Filter<=0)
                        {
                            if(Dbg_SRaw0_Cnt1<65530)
                            {
                                Dbg_SRaw0_Cnt1++;
                                
                                DF_Data[DEF_SRAW01_INDEX] = (uint8_t)Dbg_SRaw0_Cnt1;
                                DF_Data[DEF_SRAW01_INDEX+1] = (uint8_t)(Dbg_SRaw0_Cnt1>>8);
                                
                                DF_UpdateReal_Flag = 1;
                            }
                        }
                        #endif
                        
                        #if 1   // Temperature compensaton;
                        
                        #if(defined(DEF_FUN_TCOMP_EN)&&(DEF_FUN_TCOMP_EN==1))
                        Usr_TComp_Polynomial_Cubic(Tmpr_DltTRaw, &Sens_DltSRaw);
                        #else
                        Sens_DltSRaw = 0;
                        #endif
                        
                        Sens_Raw_After_TmpComp = Sens_SRaw - Sens_DltSRaw;
                        
                        #if(defined(DEF_HEAT_COMP2_EN)&&(DEF_HEAT_COMP2_EN == 1))
                        if(Flag_HtComp_2 == 1)
                        {   // 
                            Sens_DltSRaw += HtComp_CompTotal_2;
                        }
                        #endif
                        
                        Sens_Raw_After_HtComp = Sens_SRaw - Sens_DltSRaw;
                        
                        #if((defined(DEF_DELTA_RAW_EN))&&(DEF_DELTA_RAW_EN == 1))
                        Sens_Raw_After_DltRaw = Sens_Raw_After_HtComp + Usr_Delta_Raw;
                        #endif
                        
                        Sens_Raw_After_All = Sens_Raw_After_DltRaw;
                        
                        Sens_SRawComp = Sens_Raw_After_All;
                        
                        #endif
                        
                        #if 1   // Interpolation algorithm; 
                        
                        #if(defined(DEF_TABLEXY_EN)&&(DEF_TABLEXY_EN==1))
                        if(Sens_TableLen>=2)
                        {
                            Usr_BrokenLine2(Sens_SRawComp,&Sens_CaliData,Sens_TableX2,Table_32Bit,DEF_TABLE_MAX);
                        }
                        else
                        {
                            Sens_CaliData = 0;
                        }
                        #endif
                        
                        Sens_PPM = Sens_CaliData;
                        Sens_PPM_After_Cali  = Sens_PPM;
                        
                        #if(defined(DEF_HUMCOMP_EN)&&(DEF_HUMCOMP_EN==1))
                        {
                            
                            Usr_HumComp_K = Usr_HumComp_Calc_K1(ExtSens_Tmpr);
                            
                            if(Usr_HumComp_K>0.0001)
                            {
                                Usr_HumComp_K = 0;
                            }
                            
                            Usr_HumComp_PPMC = Usr_HumComp_K*ExtSens_RH*100;
                            
                            #if(defined(DEF_IMPROVE_HC_EN)&&(DEF_IMPROVE_HC_EN==1))
                            Usr_HumComp_PPMC += Usr_HumComp_Calc_D(TH_Sensor_Temperature_out, TH_Sensor_Humidity_out);
                            #endif
                            
                            Usr_HumComp_PPMC_INT = (int16_t)Usr_HumComp_PPMC;
                        }
                        #endif
                        
                        //Sens_PPM = Sens_PPM_After_Cali;
                        Sens_PPM_Dbl = Usr_HumComp_PPMC;
                        Sens_PPM -= Sens_PPM_Dbl;
                        
                        Sens_PPM_After_HumComp = Sens_PPM;
                        
                        #if(defined(DEF_PRESCOMP_EN)&&(DEF_PRESCOMP_EN==1))
                        
                        Delta_Pressure_Compensation(ExtSens_Prs);
                        
                        dlt_ppm_pressure_int = (int16_t)delta_ppm_pressure;
                        
                        Sens_PPM_Dbl = delta_ppm_pressure;
                        Sens_PPM -= Sens_PPM_Dbl;
                        
                        #endif
                        
                        Sens_PPM_After_PrsComp = Sens_PPM;
                        Sens_PPM_After_PrsComp2 = (Sens_PPM/10);
                        
                        Sens_PPM_Dbl = Sens_DC_Y;
                        Sens_PPM -= Sens_PPM_Dbl;
                        
                        Sens_PPM_After_DCY = Sens_PPM;
                        
                        #if(defined(DEF_TEMPRATE_EN)&&(DEF_TEMPRATE_EN==1))
                        {
                            double tmp1;
                            
                            tmp1 = Usr_TmpRate_Comp((double)Sens_PPM);
                            
                            Sens_PPM = tmp1;
                            
                            #if(defined(DEF_DELTA_PPM_EN)&&(DEF_DELTA_PPM_EN==1))
                            {
                                Sens_PPM += Usr_Delta_PPM1;
                            }
                            #endif
                            
                            Sens_PPM_After_TmRtComp = Sens_PPM;
                            
                            #if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))
                            
                            if((ASC_Func_En==3)&&(ASC_Adjust_Cnt>0)&&(ASC_Adjust_Cnt<=DEF_ASC_ADJUST_VALUE_MAX))
                            {
                                uint8_t i;
                                ASC_Adjust_Total = 0;
                                for(i=0;i<ASC_Adjust_Cnt;i++)
                                {
                                    ASC_Adjust_Total += ASC_Adjust_Value[i];
                                }
                            }
                            else
                            {
                                ASC_Adjust_Total = 0;
                            }
                            
                            Sens_PPM = Sens_PPM - ASC_Adjust_Total;
                            
                            #endif
                            
                            Sens_PPM_After_ASC = Sens_PPM;
                            
                            #if(defined(DEF_JUDGE_OVER_DEWP_EN)&&(DEF_JUDGE_OVER_DEWP_EN==1))
                            if(IsHumidityLargerThanDewRH(ExtSens_Tmpr) == 0)
                            #endif
                            {
                                tmp1 = Sens_PPM;
                                
                                if((Donot_Alarm_5s==0)&&(ASC_Init_Error==0))
                                {
                                    tmp1 = 0;
                                }
                                
                                #if(defined(DEF_LFL_EN)&&(DEF_LFL_EN==1))
                                
                                #if((defined(DEF_GAS_TYPE))&&(DEF_GAS_TYPE == DEF_GAS_R454B))
                                tmp1 = tmp1/115000.0f;      // For R454B;
                                #endif
                                
                                #if((defined(DEF_GAS_TYPE))&&(DEF_GAS_TYPE == DEF_GAS_R32))
                                tmp1 = tmp1/144000.0f;      // For R32;
                                #endif
                                
                                tmp1 *= 1000;
                                Sens_LFL_dbl = tmp1;
                                
                                if(Sens_LFL_dbl<0.0001)
                                {
                                    Sens_LFL_U16 = 0;
                                }
                                else
                                {
                                    Sens_LFL_U16 = Sens_LFL_dbl;
                                }
                                
                                #endif
                                
                                #if(defined(DEF_CONCEN_THRE_EN)&&(DEF_CONCEN_THRE_EN==1))
                                if((Flag_Concen_Threshold_En == 1)&&(Donot_Alarm_5s == 0))
                                {
                                    if(Sens_LFL_U16 > Concen_Threshold)
                                    {
                                        Flag_Concen_Threshol_Alarm = 1;
                                        #if(defined(DEF_ALARM5MIN_EN)&&(DEF_ALARM5MIN_EN==1))
                                        Concentration_Alarm_HoldTime = 5*60;
                                        #endif
                                    }
                                    #if(!(defined(DEF_ALARM5MIN_EN)&&(DEF_ALARM5MIN_EN==1)))
                                    else
                                    {
                                        Flag_Concen_Threshol_Alarm = 0;
                                    }
                                    #endif
                                }
                                else
                                {
                                    Flag_Concen_Threshol_Alarm = 0;
                                }
                                #endif
                                
                                #if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))
                                if((Donot_Alarm_5s==0)&&(ASC_Func_En==3))
                                {
                                    if(Flag_Concen_Threshold_En == 1)
                                    {   
                                        if(Sens_LFL_U16 > Concen_Threshold)
                                        {
                                            LFL_LeakSignal_Rt = 1;
                                        }
                                        else
                                        {
                                            LFL_LeakSignal_Rt = 0;
                                        }
                                    }
                                    else
                                    {
                                        if(Sens_LFL_U16 > 100)
                                        {
                                            LFL_LeakSignal_Rt = 1;
                                        }
                                        else
                                        {
                                            LFL_LeakSignal_Rt = 0;
                                        }
                                    }
                                }
                                else
                                {
                                    LFL_LeakSignal_Rt = 0;
                                }
                                #endif
                                
                                Flag_Over_Dewp = 0;
                            }
                            //#if(defined(DEF_JUDGE_OVER_DEWP_EN)&&(DEF_JUDGE_OVER_DEWP_EN==1))
                            #if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))
                            else
                            {
                                Sens_LFL_dbl = 0;
                                
                                Sens_LFL_U16 = 0;
                                
                                //Flag_LeakSignal = 0
                                
                                Flag_Over_Dewp = 1;
                            }
                            #endif
                        }
                        #endif
                        
                        #if 0
                        if(Sens_PPM<0.0001)
                        {
                            Sens_PPM_After_All = 0;
                        }
                        else
                        {
                            Sens_PPM_After_All = Sens_PPM;
                        }
                        #endif
                        
                        #if(defined(DEF_ASC_TEST_EN)&&(DEF_ASC_TEST_EN==1))
                        Sens_PPM = DEF_ASC_TEST_PPM_VALUE;
                        #endif
                        
                        Sens_PPM_After_All_I32 = Sens_PPM;
                        
                        #endif
                        
                        #if((defined(DEF_OVERRANGE_ALARM_EN))&&(DEF_OVERRANGE_ALARM_EN == 1))
                        if(PPM_RangeMax > 0)
                        {
                            if(Sens_PPM_After_All_I32>=PPM_RangeMax)
                            {
                                Flag_Overrange_Ppm = 1;
                            }
                            else
                            {
                                Flag_Overrange_Ppm = 0;
                            }
                        }
                        else
                        {
                            Flag_Overrange_Ppm = 0;
                        }
                        #endif
                        
                        #if((defined(DEBUG_HUMI_RATE_EN))&&(DEBUG_HUMI_RATE_EN==1))
                        // Update datas to customer; 
                        if(Flag_RH_Rate_Exceed == 0)
                        {
                            Sens_LFL_U16_Cust = Sens_LFL_U16;
                            ErrorData1_Cust = ErrorData1;
                            Psf_Gas_TypeCode_Cust = Psf_Gas_TypeCode;
                            TH_Sensor_Temperature_out_Cust = TH_Sensor_Temperature_out;
                            TH_Sensor_Humidity_out_Cust = TH_Sensor_Humidity_out;
                        }
                        else
                        {
                            
                        }
                        #else
                        {
                            Sens_LFL_U16_Cust = Sens_LFL_U16;
                            ErrorData1_Cust = ErrorData1;
                            Psf_Gas_TypeCode_Cust = Psf_Gas_TypeCode;
                            TH_Sensor_Temperature_out_Cust = TH_Sensor_Temperature_out;
                            TH_Sensor_Humidity_out_Cust = TH_Sensor_Humidity_out;
                        }
                        #endif
                        
                        if((Sens_CoolTime == 0)||(Sens_CoolTime == 0xFFFF))
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
        
        
        #if((defined(DEF_HTHH_MODE_EN))&&(DEF_HTHH_MODE_EN==1))
        
        if(((ExtSens_Tmpr>DEF_HIGH_TMPR1)&&(ExtSens_RH>DEF_HIGH_HUMI1))
            ||((ExtSens_Tmpr>DEF_HIGH_TMPR2)&&(ExtSens_RH>DEF_HIGH_HUMI2)))
        {
            Flag_HighTmprHighHumi = 1;
        }
        else
        {
            Flag_HighTmprHighHumi = 0;
        }
        
        #endif
        
        #if(defined(DEF_FREEMODBUS_EN)&&(DEF_FREEMODBUS_EN==1))
        {
            
            ( void )eMBPoll(  );
            
            /* Here we simply count the number of poll cycles. */
            // usRegInputBuf[0]++;
            
            #if(defined(DEF_HEAT_BOARD_TEST_EN)&&(DEF_HEAT_BOARD_TEST_EN == 1))
            if(HeatBoard_Flag == 10)
            {
               if((HeatBoard_Duty == 0)||(HeatBoard_Period == 0)||(HeatBoard_Duty > HeatBoard_Period)||(HeatBoard_Duty == 65535)||(HeatBoard_Period == 65535))
                {
                    HeatBoard_Flag = 0;
                }
                else if(HeatBoard_Duty < HeatBoard_Period)
                {
                    HeatBoard_Flag = 1;
                    HeatBoard_Heat();
                    HeatBoard_Cnt = 0;
                }
                else
                {
                    HeatBoard_Flag = 2;
                }
                
                HeatBoard_Cnt = 0;
            }
            #endif
        }
        #endif
        
        if(Mcu_Time1s_Cnt>0)
        {   
            int i;
            
            Mcu_Time1s_Cnt = 0;
            
            if(Donot_Alarm_5s>0)
            {
                Donot_Alarm_5s--;
            }
            
            #if(defined(DEF_CONCEN_THRE_EN)&&(DEF_CONCEN_THRE_EN==1))
            
            #if(defined(DEF_ALARM5MIN_EN)&&(DEF_ALARM5MIN_EN==1))
            if(Concentration_Alarm_HoldTime>0)
            {
                Concentration_Alarm_HoldTime--;
            }
            
            if(Concentration_Alarm_HoldTime == 0)
            {
                Flag_Concen_Threshol_Alarm = 0;
            }
            #else
            
            #endif
            
            #endif
            
            #if(defined(DEF_TMPR_RATE_EN)&&(DEF_TMPR_RATE_EN==1))
            
            if(TR_Data_Cnt<2)
            {
                TR_Tmpr[TR_Data_Cnt] = TH_Sensor_Temperature_out;
                TR_Data_Cnt++;
                TR_Tmpr_Rate = 0;
            }
            else
            {
                for(i=0;i<2-1;i++)
                {
                    TR_Tmpr[i] = TR_Tmpr[i+1];
                }
                TR_Tmpr[i] = TH_Sensor_Temperature_out;
            }
            
            if(TR_Data_Cnt==2)
            {
                TR_Tmpr_Delt = TR_Tmpr[1]-TR_Tmpr[0];
                
                TR_Tmpr_Rate = TR_Tmpr_Delt*60;
            }
            #endif
            
            #if(defined(DEF_HUMI_RATE_EN)&&(DEF_HUMI_RATE_EN==1))
            
            if(HR_Data_Cnt<2)
            {
                HR_Humi[HR_Data_Cnt] = TH_Sensor_Humidity_out;
                HR_Data_Cnt++;
                HR_Humi_Rate = 0;
            }
            else
            {
                for(i=0;i<2-1;i++)
                {
                    HR_Humi[i] = HR_Humi[i+1];
                }
                HR_Humi[i] = TH_Sensor_Humidity_out;
            }
            
            if(HR_Data_Cnt==2)
            {
                HR_Humi_Delt = HR_Humi[1]-HR_Humi[0];
                
                HR_Humi_Rate = HR_Humi_Delt*60;
            }
            
            #endif
            
            #if(defined(DEF_PRES_RATE_EN)&&(DEF_PRES_RATE_EN==1))
            
            if(PR_Data_Cnt<2)
            {
                PR_Pres[PR_Data_Cnt] = PSensor_Pressure_10Pa;
                PR_Data_Cnt++;
                PR_Pres_Rate = 0;
            }
            else
            {
                for(i=0;i<2-1;i++)
                {
                    PR_Pres[i] = PR_Pres[i+1];
                }
                PR_Pres[i] = PSensor_Pressure_10Pa;
            }
            
            if(PR_Data_Cnt==2)
            {
                PR_Pres_Delt = PR_Pres[1]-PR_Pres[0];
                
                PR_Pres_Rate = PR_Pres_Delt*60;
            }
            
            #endif 
            
            
            #if(defined(DEF_HPC_FUNC_EN)&&(DEF_HPC_FUNC_EN==1))
            #if(defined(DEF_HPC_TEST_EN)&&(DEF_HPC_TEST_EN==1))
            HPC_Tmpr = DEF_HPC_TMPR;
            HPC_Humi = DEF_HPC_HUMI;
            HPC_HumiRate = DEF_HPC_HUMIRATE;
            #else
            HPC_Tmpr = TH_Sensor_Temperature_out;
            HPC_Humi = TH_Sensor_Humidity_out;
            HPC_HumiRate = HR_Humi_Rate;
            #endif
            #endif
            
            
            if(Donot_Alarm_5s == 0)
            {
                #if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))
                
                Usr_ASC_MainLoop();
                
                #endif
            }
            
             if(Donot_Alarm_5s == 0)
            {
                #if(defined(DEF_HPC_FUNC_EN)&&(DEF_HPC_FUNC_EN==1))
                HPC_MainLoop();
                #endif
            }
            
            #if 1
            if((Donot_Alarm_5s==0)&&(ASC_Init_Error==0))
            {   // Error process;
                
                // BIT0;
                if((Flag_TH_Err_Comm == 1))
                {
                    //ErrorData0;
                    ErrorData1 |= 0x0001;
                    //ErrorData2;
                }
                else
                {
                    //ErrorData0;
                    ErrorData1 &= 0xFFFE;
                    //ErrorData2;
                }
                
                // BIT1;
                if((Flag_CMP201_Err_Comm == 1))
                {
                    //ErrorData0;
                    ErrorData1 |= 0x0002;
                    //ErrorData2;
                }
                else
                {
                    //ErrorData0;
                    ErrorData1 &= 0xFFFD;
                    //ErrorData2;
                }
                
                
                // BIT2;
                //ErrorData0;
                ErrorData1 &= 0xFFFB;
                //ErrorData2;
                
                // BIT3;
                //ErrorData0;
                ErrorData1 &= 0xFFF7;
                //ErrorData2;
                
                
                // BIT4;
                // if((Flag_TH_Err_TRange == 1)||(Flag_TH_Err_TRange == 1)||(Flag_CMP201_Err_PRange == 1))
                if((Flag_TH_Err_TRange == 1))
                {   // 
                    //ErrorData0;
                    ErrorData1 |= 0x0010;
                    //ErrorData2;
                }
                else
                {   
                    //ErrorData0;
                    ErrorData1 &= 0xFFEF;
                    //ErrorData2;
                }
                
                // BIT5;
                #if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))
                if(ASC_Func_En == 3)
                {   // Disable ASC function;
                    //ErrorData0;
                    ErrorData1 |= 0x0020;
                    //ErrorData2;
                }
                else
                #endif
                {   // Enable ASC function;
                    //ErrorData0;
                    ErrorData1 &= 0xFFDF;
                    //ErrorData2;
                }
                
                
                // BIT6;
                #if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))
                if((ASC_Func_En == 3)&&(ASC_Adjust_Cnt>=DEF_ASC_ADJUST_VALUE_MAX))
                {
                    //ErrorData0;
                    ErrorData1 |= 0x0040;
                    //ErrorData2;
                }
                else
                #endif
                {
                    //ErrorData0;
                    ErrorData1 &= 0xFFBF;
                    //ErrorData2;
                }
                
                
                // BIT7;
                if(Flag_Overrange_Ppm==1)
                {   // 
                    //ErrorData0;
                    ErrorData1 |= 0x0080;
                    //ErrorData2;
                }
                else
                {   
                    //ErrorData0;
                    ErrorData1 &= 0xFF7F;
                    //ErrorData2;
                }
                
                // BIT8;
                #if(defined(DEF_JUDGE_OVER_DEWP_EN)&&(DEF_JUDGE_OVER_DEWP_EN==1))
                if(Flag_Over_Dewp == 1)
                {
                    //ErrorData0;
                    ErrorData1 |= 0x0100;
                    //ErrorData2;
                }
                else
                {
                    //ErrorData0;
                    ErrorData1 &= 0xFEFF;
                    //ErrorData2;
                }
                #endif
                
                // BIT9;
                if((Flag_TH_Err_Comm == 1)||(Flag_CMP201_Err_Comm == 1))
                {   // 
                    //ErrorData0;
                    ErrorData1 |= 0x0200;
                    //ErrorData2;
                }
                else
                {   
                    //ErrorData0;
                    ErrorData1 &= 0xFDFF;
                    //ErrorData2;
                }
                
                // BIT10;
                //ErrorData0;
                ErrorData1 &= 0xFBFF;
                //ErrorData2;
                
                // BIT11;
                if((Flag_TH_Err_Comm == 1)||(Flag_CMP201_Err_Comm == 1))
                {   // 
                    //ErrorData0;
                    ErrorData1 |= 0x0800;
                    //ErrorData2;
                }
                else
                {   
                    //ErrorData0;
                    ErrorData1 &= 0xF7FF;
                    //ErrorData2;
                }
                
                // BIT12;
                if(Sens_TableLen<=1)
                {   // 
                    //ErrorData0;
                    ErrorData1 |= 0x1000;
                    //ErrorData2;
                }
                else
                {   
                    //ErrorData0;
                    ErrorData1 &= 0xEFFF;
                    //ErrorData2;
                }
                
                // BIT13;
                //ErrorData0;
                ErrorData1 &= 0xDFFF;
                //ErrorData2;
                
                
                // BIT14;
                #if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))
                if((ASC_Func_En == 3)&&(ASC_Adjust_Cnt>=DEF_ASC_ADJUST_VALUE_MAX-2))
                {
                    //ErrorData0;
                    ErrorData1 |= 0x4000;
                    //ErrorData2;
                }
                else
                #endif
                {
                    //ErrorData0;
                    ErrorData1 &= 0xBFFF;
                    //ErrorData2;
                }
                
                
                // BIT15;
                //ErrorData0;
                ErrorData1 &= 0x7FFF;
                //ErrorData2;
                
            }
            else
            {
                ErrorData0 = 0;
                ErrorData1 = 0;
                ErrorData2 = 0;
            }
            #endif
        }
        
        
        
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
                    uint16_t uint16_tmp1 = 0xB169;
                    Usr_E703_WriteReg(DEF_REGADDR_CMD, uint16_tmp1);
                    
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




#endif


