/*
 * FreeModbus Libary: BARE Demo Application
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id$
 */

/* ----------------------- Modbus includes ----------------------------------*/
#include "stdint.h"
#include "mb.h"
#include "mbport.h"

#include "Usr_Config.h"

#include "Usr_Modbus.h"

#include "Usr_E703.h"

//#include "userdefine.h"
#include "BAT32A237.h"

//#include "core_cm0plus.h"                       /*!< ARM Cortex-M0+ processor and core peripherals                             */
//#include "system_BAT32A237.h"                   /*!< BAT32A237 System                                                          */

#include "Usr_Main.h"
#include "Usr_ALSensor.h"
#include "Usr_DataFlash.h"
#include "Usr_Psf.h"
#include "Usr_E703.h"
/* ----------------------- Defines ------------------------------------------*/
//#define REG_INPUT_START 1000
//#define REG_INPUT_NREGS 4

/* ----------------------- Static variables ---------------------------------*/
//static USHORT   usRegInputStart = REG_INPUT_START;
//static USHORT   usRegInputBuf[REG_INPUT_NREGS];

/* ----------------------- Start implementation -----------------------------*/
int
main_disable( void )
{
    eMBErrorCode    eStatus;
    
    eStatus = eMBInit( MB_RTU, 0x0A, 0, 38400, MB_PAR_EVEN );
    
    /* Enable the Modbus Protocol Stack. */
    eStatus = eMBEnable(  );
    
    for( ;; )
    {
        ( void )eMBPoll(  );
        
        /* Here we simply count the number of poll cycles. */
        usRegInputBuf[0]++;
    }
}

eMBErrorCode
eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    int             iRegIndex;

    if( ( usAddress >= REG_INPUT_START )
        && ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
    {
        iRegIndex = ( int )( usAddress - usRegInputStart );
        while( usNRegs > 0 )
        {
            *pucRegBuffer++ =
                ( unsigned char )( usRegInputBuf[iRegIndex] >> 8 );
            *pucRegBuffer++ =
                ( unsigned char )( usRegInputBuf[iRegIndex] & 0xFF );
            iRegIndex++;
            usNRegs--;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }

    return eStatus;
}

eMBErrorCode
eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs,
                 eMBRegisterMode eMode )
{
    //return MB_ENOREG;
    unsigned char i;
    
    if(eMode == MB_REG_READ)
    {   
        if((usAddress>=768)&&(usAddress<1024))
        {   // Read Debug informastion area;
            for(i=0;i<usNRegs;i++)
            {   
                #if 0
                E703_RegBuff[17] = E703_ADC_TC;
                E703_RegBuff[18] = E703_ADC_T;
                E703_RegBuff[19] = E703_ADC_S;
                E703_RegBuff[21] = E703_DSP_T;
                E703_RegBuff[22] = E703_DSP_S;
                #endif
                
                if(usAddress+i==768)
                {   
                    // Read  E703 ADC_T;
                    //*(pucRegBuffer+i*2) = E703_ADC_T>>8;
                    //*(pucRegBuffer+i*2+1) = E703_ADC_T;
                    
                    // Read HDC3020 Tmpr Raw;
                    *(pucRegBuffer+i*2) = ExtSens_Tmpr_Raw>>8;
                    *(pucRegBuffer+i*2+1) = ExtSens_Tmpr_Raw;
                }
                else if(usAddress+i==769)
                {   // Read E703 ADC_S
                    //*(pucRegBuffer+i*2) = E703_ADC_S>>8;
                    //*(pucRegBuffer+i*2+1) = E703_ADC_S;
                    
                    *(pucRegBuffer+i*2) = Sens_SRaw>>8;
                    *(pucRegBuffer+i*2+1) = Sens_SRaw;
                }
                else if(usAddress+i==770)
                {   // Read Sens_SRawComp
                    *(pucRegBuffer+i*2) = Sens_SRawComp>>8;
                    *(pucRegBuffer+i*2+1) = Sens_SRawComp;
                }
                else if(usAddress+i==777)
                {   // Read Sens_LFL_U16
                    *(pucRegBuffer+i*2) = Sens_LFL_U16>>8;
                    *(pucRegBuffer+i*2+1) = Sens_LFL_U16;
                }
                else if(usAddress+i==778)
                {   // Read Flag_Concen_Threshol_Alarm
                    *(pucRegBuffer+i*2) = Flag_Concen_Threshol_Alarm>>8;
                    *(pucRegBuffer+i*2+1) = Flag_Concen_Threshol_Alarm;
                }
                else if(usAddress+i==779)
                {
                    *(pucRegBuffer+i*2) = CPS122_Temperature_0D1C>>8;
                    *(pucRegBuffer+i*2+1) = CPS122_Temperature_0D1C;
                }
                else if(usAddress+i==780)
                {   // Read HDC3020 Temperature;
                    *(pucRegBuffer+i*2) = TH_Sensor_Temperature_out>>8;
                    *(pucRegBuffer+i*2+1) = TH_Sensor_Temperature_out;
                }
                else if(usAddress+i==781)
                {   // Read HDC3020 Humidity;
                    *(pucRegBuffer+i*2) = TH_Sensor_Humidity_out>>8;
                    *(pucRegBuffer+i*2+1) = TH_Sensor_Humidity_out;
                }
                else if(usAddress+i==782)
                {   // Read CMP201 Pressure;
                    *(pucRegBuffer+i*2) = PSensor_Pressure_10Pa>>8;
                    *(pucRegBuffer+i*2+1) = PSensor_Pressure_10Pa;
                }
                else if(usAddress+i==785)
                {   // Read Sens_DC_Y;
                    *(pucRegBuffer+i*2) = Sens_DC_Y>>8;
                    *(pucRegBuffer+i*2+1) = Sens_DC_Y;
                }
                
                #if(defined(DEF_CONCEN_THRE_EN)&&(DEF_CONCEN_THRE_EN==1))
                else if(usAddress+i==786)
                {   // Read Concen_Threshold;
                    *(pucRegBuffer+i*2) = Concen_Threshold>>8;
                    *(pucRegBuffer+i*2+1) = Concen_Threshold;
                }
                #endif
                
                //else if((usAddress+i>=788)&&(usAddress+i<=805))
                else if((usAddress+i>=788)&&(usAddress+i<=803))
                {   // Read HumComp_M2_S;
                    uint8_t index,H2b_f;
                    uint8_t *ptr;
                    
                    index = (usAddress+i-788);
                    
                    H2b_f = index%2;
                    index >>= 1;
                    
                    ptr = (uint8_t*)(HumComp_M2_S+index);
                    
                    if(H2b_f == 1)
                    {   
                        ptr+=2;
                        
                        *(pucRegBuffer+i*2) = *(ptr+1);
                        *(pucRegBuffer+i*2+1) = *ptr;
                    }
                    else
                    {   
                        ptr+=0;
                        
                        *(pucRegBuffer+i*2) = *(ptr+1);
                        *(pucRegBuffer+i*2+1) = *ptr;
                    }
                }
                else if(usAddress+i==806)
                {   // Read HumComp_Flag;
                    *(pucRegBuffer+i*2) = HumComp_Flag>>8;
                    *(pucRegBuffer+i*2+1) = HumComp_Flag;
                }
                else if((usAddress+i>=808)&&(usAddress+i<=813))
                {   // Read PresComp_K;
                    uint8_t index,H2b_f;
                    uint8_t *ptr;
                    
                    index = (usAddress+i-808);
                    
                    H2b_f = index%2;
                    index >>= 1;
                    
                    ptr = (uint8_t*)(PresComp_K+index);
                    
                    if(H2b_f == 1)
                    {   
                        ptr+=2;
                        
                        *(pucRegBuffer+i*2) = *(ptr+1);
                        *(pucRegBuffer+i*2+1) = *ptr;
                    }
                    else
                    {   
                        ptr+=0;
                        
                        *(pucRegBuffer+i*2) = *(ptr+1);
                        *(pucRegBuffer+i*2+1) = *ptr;
                    }
                }
                else if(usAddress+i==814)
                {   // Read PresComp_Flag;
                    *(pucRegBuffer+i*2) = PresComp_Flag>>8;
                    *(pucRegBuffer+i*2+1) = PresComp_Flag;
                }
                else if(usAddress+i==815)
                {   // Read Range value L16b, PPM_RangeMax;
                    *(pucRegBuffer+i*2) = PPM_RangeMax>>8;
                    *(pucRegBuffer+i*2+1) = PPM_RangeMax;
                }
                #if(defined(DEF_FUN_TIMESN_EN)&&(DEF_FUN_TIMESN_EN==1))
                else if(usAddress+i==822)
                {   // Read TimeSn_Time;
                    *(pucRegBuffer+i*2) = TimeSn_Time>>8;
                    *(pucRegBuffer+i*2+1) = TimeSn_Time;
                }
                else if(usAddress+i==823)
                {   // Read TimeSn_SN;
                    *(pucRegBuffer+i*2) = TimeSn_SN>>8;
                    *(pucRegBuffer+i*2+1) = TimeSn_SN;
                }
                #endif
                
                else if(usAddress+i==825)
                {   // Read ;
                    *(pucRegBuffer+i*2) = Psf_State>>8;
                    *(pucRegBuffer+i*2+1) = Psf_State;
                }
                
                else if(usAddress+i==826)
                {   // Read Sens_FilterCnt;
                    *(pucRegBuffer+i*2) = Sens_FilterCnt>>8;
                    *(pucRegBuffer+i*2+1) = Sens_FilterCnt;
                }
                
                else if(usAddress+i==827)
                {   // Read Sens_PreHeat;
                    *(pucRegBuffer+i*2) = Sens_PreHeatTime>>8;
                    *(pucRegBuffer+i*2+1) = Sens_PreHeatTime;
                }
                
                else if(usAddress+i==828)
                {   // Read Sens_CoolTime;
                    *(pucRegBuffer+i*2) = Sens_CoolTime>>8;
                    *(pucRegBuffer+i*2+1) = Sens_CoolTime;
                }
                
                #if(defined(DEF_FUN_TCOMP_EN)&&(DEF_FUN_TCOMP_EN==1))
                
                else if(usAddress+i==830)
                {   // Read TComp_TRawBase;
                    *(pucRegBuffer+i*2) = TComp_TRawBase>>8;
                    *(pucRegBuffer+i*2+1) = TComp_TRawBase;
                }
                else if(usAddress+i==831)
                {   // Read TComp_P0;
                    uint16_t tmp1 = TComp_P0;
                    *(pucRegBuffer+i*2) = TComp_P0>>8;
                    *(pucRegBuffer+i*2+1) = TComp_P0;
                }
                else if(usAddress+i==832)
                {   // Read TComp_P1;
                    uint16_t tmp1 = TComp_P1;
                    *(pucRegBuffer+i*2) = TComp_P1>>8;
                    *(pucRegBuffer+i*2+1) = TComp_P1;
                }
                else if(usAddress+i==833)
                {   // Read TComp_P2 Low D16b;
                    uint16_t tmp1 = TComp_P2;
                    *(pucRegBuffer+i*2) = tmp1>>8;
                    *(pucRegBuffer+i*2+1) = tmp1;
                }
                else if(usAddress+i==834)
                {   // Read TComp_P2 High D16b;
                    uint16_t tmp1 = TComp_P2>>16;
                    *(pucRegBuffer+i*2) = tmp1>>8;
                    *(pucRegBuffer+i*2+1) = tmp1;
                }
                else if(usAddress+i==835)
                {   // Read TComp_P3 Low D16b;
                    uint16_t tmp1 = TComp_P3;
                    *(pucRegBuffer+i*2) = tmp1>>8;
                    *(pucRegBuffer+i*2+1) = tmp1;
                }
                else if(usAddress+i==836)
                {   // Read TComp_P3 High D16b;
                    uint16_t tmp1 = TComp_P3>>16;
                    *(pucRegBuffer+i*2) = tmp1>>8;
                    *(pucRegBuffer+i*2+1) = tmp1;
                }
                #endif
                #if(defined(DEBUG_HEAT_COMP2_EN)&&(DEBUG_HEAT_COMP2_EN==1))
                else if(usAddress+i==846)
                {   // Read HtComp_TRaw_Base_2;
                    uint16_t tmp1 = HtComp_TRaw_Base_2;
                    *(pucRegBuffer+i*2) = tmp1>>8;
                    *(pucRegBuffer+i*2+1) = tmp1;
                }
                else if(usAddress+i==847)
                {   // Read HtComp_HtRaw_Base_2;
                    uint16_t tmp1 = HtComp_HtRaw_Base_2;
                    *(pucRegBuffer+i*2) = tmp1>>8;
                    *(pucRegBuffer+i*2+1) = tmp1;
                }
                else if(usAddress+i==848)
                {   // Read HtComp_Kh_2;
                    uint16_t tmp1 = HtComp_Kh_2;
                    *(pucRegBuffer+i*2) = tmp1>>8;
                    *(pucRegBuffer+i*2+1) = tmp1;
                }
                else if(usAddress+i==849)
                {   // Read HtComp_SP_2;
                    uint16_t tmp1 = HtComp_SP_2;
                    *(pucRegBuffer+i*2) = tmp1>>8;
                    *(pucRegBuffer+i*2+1) = tmp1;
                }
                else if(usAddress+i==850)
                {   // Read HtComp_Ks_2;
                    uint16_t tmp1 = HtComp_Ks_2;
                    *(pucRegBuffer+i*2) = tmp1>>8;
                    *(pucRegBuffer+i*2+1) = tmp1;
                }
                else if(usAddress+i==851)
                {   // Read Undefined;
                    uint16_t tmp1 = 0;
                    *(pucRegBuffer+i*2) = tmp1>>8;
                    *(pucRegBuffer+i*2+1) = tmp1;
                }
                else if(usAddress+i==852)
                {   // Read Monitor_Raw1;
                    uint16_t tmp1 = Monitor_Raw1;
                    *(pucRegBuffer+i*2) = tmp1>>8;
                    *(pucRegBuffer+i*2+1) = tmp1;
                }
                else if(usAddress+i==853)
                {   // Read ExtSens_Tmpr_Raw;
                    uint16_t tmp1 = ExtSens_Tmpr_Raw;
                    *(pucRegBuffer+i*2) = tmp1>>8;
                    *(pucRegBuffer+i*2+1) = tmp1;
                }
                else if(usAddress+i==854)
                {   // Read HtComp_HtRaw_Base_rt_2;
                    uint16_t tmp1 = HtComp_HtRaw_Base_rt_2;
                    *(pucRegBuffer+i*2) = tmp1>>8;
                    *(pucRegBuffer+i*2+1) = tmp1;
                }
                else if(usAddress+i==855)
                {   // Read Dlt_P0;
                    uint16_t tmp1 = Dlt_P0;
                    *(pucRegBuffer+i*2) = tmp1>>8;
                    *(pucRegBuffer+i*2+1) = tmp1;
                }
                else if(usAddress+i==856)
                {   // Read Dlt_P;
                    uint16_t tmp1 = Dlt_P;
                    *(pucRegBuffer+i*2) = tmp1>>8;
                    *(pucRegBuffer+i*2+1) = tmp1;
                }
                else if(usAddress+i==857)
                {   // Read Delta_Ht_Raw_2;
                    uint16_t tmp1 = Delta_Ht_Raw_2;
                    *(pucRegBuffer+i*2) = tmp1>>8;
                    *(pucRegBuffer+i*2+1) = tmp1;
                }
                else if(usAddress+i==858)
                {   // Read Sens_Raw_After_TmpComp;
                    uint16_t tmp1 = Sens_Raw_After_TmpComp;
                    *(pucRegBuffer+i*2) = tmp1>>8;
                    *(pucRegBuffer+i*2+1) = tmp1;
                }
                else if(usAddress+i==859)
                {   // Read HtComp_CompTotal_2;
                    uint16_t tmp1 = HtComp_CompTotal_2;
                    *(pucRegBuffer+i*2) = tmp1>>8;
                    *(pucRegBuffer+i*2+1) = tmp1;
                }
                else if(usAddress+i==860)
                {   // Read Sens_Raw_After_HtComp;
                    uint16_t tmp1 = Sens_Raw_After_HtComp;
                    *(pucRegBuffer+i*2) = tmp1>>8;
                    *(pucRegBuffer+i*2+1) = tmp1;
                }
                #endif
                else
                {
                    *(pucRegBuffer+i*2) = 0;
                    *(pucRegBuffer+i*2+1) = 0;
                }
            }
        }
        else if((usAddress>=1024)&&(usAddress<1280))
        {   // Read E703 Register area;
            for(i=0;i<usNRegs;i++)
            {   
                if(usAddress+i<=1101)
                {
                    *(pucRegBuffer+i*2) = E703_RegBuff[usAddress-1024 + i]>>8;
                    *(pucRegBuffer+i*2+1) = E703_RegBuff[usAddress-1024 + i];
                }
                else
                {
                    *(pucRegBuffer+i*2) = 0;
                    *(pucRegBuffer+i*2+1) = 0;
                }
            }
        }
        else if((usAddress>=1280)&&(usAddress<1536))
        {   // Read E703 CM area;
            for(i=0;i<usNRegs;i++)
            {   
                if(usAddress+i<=1343)
                {
                    *(pucRegBuffer+i*2) = E703_CMBuff[usAddress-1280 + i]>>8;
                    *(pucRegBuffer+i*2+1) = E703_CMBuff[usAddress-1280 + i];
                }
                else
                {
                    *(pucRegBuffer+i*2) = 0;
                    *(pucRegBuffer+i*2+1) = 0;
                }
            }
        }
        else if((usAddress>=1536)&&(usAddress<1536+128))
        {   // Read Data Flash area;
            for(i=0;i<usNRegs;i++)
            {   
                if(usAddress+i<1536+128)
                {
                    *(pucRegBuffer+i*2)     = DF_Data[(usAddress+i-1536)*2+1];
                    *(pucRegBuffer+i*2+1)   = DF_Data[(usAddress+i-1536)*2  ];
                }
                else
                {
                    *(pucRegBuffer+i*2) = 0;
                    *(pucRegBuffer+i*2+1) = 0;
                }
            }
        }
        else
        {
            
        }
    }
    
    if(eMode == MB_REG_WRITE)
    {   
        uint8_t ea;
        uint16_t ma;
        uint16_t val;
        #if 0
        for(i=0;i<usNRegs;i++)
        {   
            usRegHoldingBuf[usAddress+i] = *(pucRegBuffer+i*2);
            usRegHoldingBuf[usAddress+i] <<= 8;
            usRegHoldingBuf[usAddress+i] += *(pucRegBuffer+i*2+1);
        }
        #endif
        
        if((usAddress>=768)&&(usAddress<=900))
        {   // Write Debug Information area;
            for(i=0;i<usNRegs;i++)
            {   
                #if 0
                E703_RegBuff[17] = E703_ADC_TC;
                E703_RegBuff[18] = E703_ADC_T;
                E703_RegBuff[19] = E703_ADC_S;
                E703_RegBuff[21] = E703_DSP_T;
                E703_RegBuff[22] = E703_DSP_S;
                #endif
                
                if(usAddress+i==768)
                {
                    
                }
                else if(usAddress+i==769)
                {
                    
                }
                else if(usAddress+i == 785)
                {   // Write Sens_DC_Y;
                
                    val = *(pucRegBuffer+i*2);
                    val <<= 8;
                    val += *(pucRegBuffer+i*2+1);
                    
                    DF_Data[DEF_DC_Y_INDEX] = (uint8_t)val;
                    DF_Data[DEF_DC_Y_INDEX+1] = (uint8_t)(val>>8);
                    
                    Sens_DC_Y = val;
                    
                    DF_UpdateReal_Flag = 1;
                }
                
                #if(defined(DEF_CONCEN_THRE_EN)&&(DEF_CONCEN_THRE_EN==1))
                else if(usAddress+i==786)
                {   // Write Concen_Threshold;
                    val = *(pucRegBuffer+i*2);
                    val <<= 8;
                    val += *(pucRegBuffer+i*2+1);
                    
                    DF_Data[DEF_CONCEN_THRE_INDEX] = (uint8_t)val;
                    DF_Data[DEF_CONCEN_THRE_INDEX+1] = (uint8_t)(val>>8);
                    
                    Concen_Threshold = val;
                    
                    DF_UpdateReal_Flag = 1;
                }
                #endif
                //else if((usAddress+i>=788)&&(usAddress+i<=805))
                else if((usAddress+i>=788)&&(usAddress+i<=803))
                {   // Write HumComp_M2_S;
                    uint8_t index,H2b_f;
                    uint8_t *ptr;
                    
                    index = (usAddress+i-788);
                    
                    H2b_f = index%2;
                    index >>= 1;
                    
                    ptr = (uint8_t*)(HumComp_M2_S+index);
                    
                    if(H2b_f == 1)
                    {
                        ptr += 2;
                        
                        DF_Data[DEF_HUMCOMP_PARAM_INDEX+0+index*4+2] = (uint8_t)val;
                        *(ptr+0) = (uint8_t)val;
                        DF_Data[DEF_HUMCOMP_PARAM_INDEX+1+index*4+2] = (uint8_t)(val>>8);
                        *(ptr+1) = (uint8_t)(val>>8);
                    }
                    else
                    {
                        ptr += 0;
                        
                        DF_Data[DEF_HUMCOMP_PARAM_INDEX+0+index*4+2] = (uint8_t)val;
                        *(ptr+0) = (uint8_t)val;
                        DF_Data[DEF_HUMCOMP_PARAM_INDEX+1+index*4+2] = (uint8_t)(val>>8);
                        *(ptr+1) = (uint8_t)(val>>8);
                    }
                    
                    DF_UpdateReal_Flag = 1;
                }
                else if(usAddress+i == 806)
                {   // Write HumComp_Flag;
                    
                    val = *(pucRegBuffer+i*2);
                    val <<= 8;
                    val += *(pucRegBuffer+i*2+1);
                    
                    DF_Data[DEF_HUMCOMP_FLAG_INDEX] = (uint8_t)val;
                    DF_Data[DEF_HUMCOMP_FLAG_INDEX+1] = (uint8_t)(val>>8);
                    
                    HumComp_Flag = val;
                    
                    DF_UpdateReal_Flag = 1;
                }
                else if((usAddress+i>=808)&&(usAddress+i<=813))
                {   // Write PresComp_K;
                    uint8_t index,H2b_f;
                    uint8_t *ptr;
                    
                    index = (usAddress+i-788);
                    
                    H2b_f = index%2;
                    index >>= 1;
                    
                    ptr = (uint8_t*)(PresComp_K+index);
                    
                    if(H2b_f == 1)
                    {
                        ptr += 2;
                        
                        DF_Data[DEF_HUMCOMP_PARAM_INDEX+0+index*4+2] = (uint8_t)val;
                        *(ptr+0) = (uint8_t)val;
                        DF_Data[DEF_HUMCOMP_PARAM_INDEX+1+index*4+2] = (uint8_t)(val>>8);
                        *(ptr+1) = (uint8_t)(val>>8);
                    }
                    else
                    {
                        ptr += 0;
                        
                        DF_Data[DEF_HUMCOMP_PARAM_INDEX+0+index*4+2] = (uint8_t)val;
                        *(ptr+0) = (uint8_t)val;
                        DF_Data[DEF_HUMCOMP_PARAM_INDEX+1+index*4+2] = (uint8_t)(val>>8);
                        *(ptr+1) = (uint8_t)(val>>8);
                    }
                    
                    DF_UpdateReal_Flag = 1;
                }
                else if(usAddress+i == 814)
                {   // Write PresComp_Flag;
                    
                    val = *(pucRegBuffer+i*2);
                    val <<= 8;
                    val += *(pucRegBuffer+i*2+1);
                    
                    DF_Data[DEF_PRESCOMP_FLAG_INDEX] = (uint8_t)val;
                    DF_Data[DEF_PRESCOMP_FLAG_INDEX+1] = (uint8_t)(val>>8);
                    
                    PresComp_Flag = val;
                    
                    DF_UpdateReal_Flag = 1;
                }
                #if(defined(DEF_FUN_TIMESN_EN)&&(DEF_FUN_TIMESN_EN==1))
                else if(usAddress+i==822)
                {   // Write TimeSn_Time;
                
                    val = *(pucRegBuffer+i*2);
                    val <<= 8;
                    val += *(pucRegBuffer+i*2+1);
                    
                    DF_Data[DEF_TIME_SN_INDEX] = (uint8_t)val;
                    DF_Data[DEF_TIME_SN_INDEX+1] = (uint8_t)(val>>8);
                    
                    TimeSn_Time = val;
                    
                    DF_UpdateReal_Flag = 1;
                }
                else if(usAddress+i==823)
                {   // Write TimeSn_SN;
                    
                    val = *(pucRegBuffer+i*2);
                    val <<= 8;
                    val += *(pucRegBuffer+i*2+1);
                    
                    DF_Data[DEF_TIME_SN_INDEX+2] = (uint8_t)val;
                    DF_Data[DEF_TIME_SN_INDEX+2+1] = (uint8_t)(val>>8);
                    
                    TimeSn_SN = val;
                    
                    DF_UpdateReal_Flag = 1;
                }
                #endif
                
                else if(usAddress+i==826)
                {   // Write Sens_FilterCnt;
                
                    val = *(pucRegBuffer+i*2);
                    val <<= 8;
                    val += *(pucRegBuffer+i*2+1);
                    
                    if(val>DEF_SRAW_FILTERMAX)
                    {
                        val = DEF_SRAW_FILTERMAX;
                    }
                    
                    DF_Data[DEF_FILTERCNT_INDEX] = (uint8_t)val;
                    DF_Data[DEF_FILTERCNT_INDEX+1] = (uint8_t)(val>>8);
                    
                    Sens_FilterCnt = val;
                    
                    FilterIndex = 0;
                    FilterTotal = 0;
                    
                    DF_UpdateReal_Flag = 1;
                }
                
                else if(usAddress+i==827)
                {   // Write Sens_PreHeat;
                
                    val = *(pucRegBuffer+i*2);
                    val <<= 8;
                    val += *(pucRegBuffer+i*2+1);
                    
                    DF_Data[DEF_PREHEATTIME_INDEX] = (uint8_t)val;
                    DF_Data[DEF_PREHEATTIME_INDEX+1] = (uint8_t)(val>>8);
                    
                    Sens_PreHeatTime = val;
                    
                    DF_UpdateReal_Flag = 1;
                }
                
                else if(usAddress+i==828)
                {   // Write Sens_CoolTime;
                
                    val = *(pucRegBuffer+i*2);
                    val <<= 8;
                    val += *(pucRegBuffer+i*2+1);
                    
                    DF_Data[DEF_COOLTIME_INDEX] = (uint8_t)val;
                    DF_Data[DEF_COOLTIME_INDEX+1] = (uint8_t)(val>>8);
                    
                    Sens_CoolTime = val;
                    
                    DF_UpdateReal_Flag = 1;
                }
                
                #if(defined(DEF_FUN_TCOMP_EN)&&(DEF_FUN_TCOMP_EN==1))
                
                else if(usAddress+i==830)
                {   // Write TComp_TRawBase;
                    val = *(pucRegBuffer+i*2);
                    val <<= 8;
                    val += *(pucRegBuffer+i*2+1);
                    
                    DF_Data[DEF_TRAWBASE_INDEX] = (uint8_t)val;
                    DF_Data[DEF_TRAWBASE_INDEX+1] = (uint8_t)(val>>8);
                    
                    TComp_TRawBase = val;
                    
                    DF_UpdateReal_Flag = 1;
                }
                else if(usAddress+i==831)
                {   // Write TComp_P0;
                    int16_t tmp1;
                    
                    val = *(pucRegBuffer+i*2);
                    val <<= 8;
                    val += *(pucRegBuffer+i*2+1);
                    
                    DF_Data[DEF_TCOMP_P0_INDEX] = (uint8_t)val;
                    DF_Data[DEF_TCOMP_P0_INDEX+1] = (uint8_t)(val>>8);
                    
                    tmp1 = val;
                    
                    TComp_P0 = tmp1;
                    
                    DF_UpdateReal_Flag = 1;
                }
                else if(usAddress+i==832)
                {   // Write TComp_P1;
                    int16_t tmp1;
                    
                    val = *(pucRegBuffer+i*2);
                    val <<= 8;
                    val += *(pucRegBuffer+i*2+1);
                    
                    DF_Data[DEF_TCOMP_P1_INDEX] = (uint8_t)val;
                    DF_Data[DEF_TCOMP_P1_INDEX+1] = (uint8_t)(val>>8);
                    
                    tmp1 = val;
                    
                    TComp_P1 = tmp1;
                    
                    DF_UpdateReal_Flag = 1;
                }
                else if(usAddress+i==833)
                {   // Write TComp_P2 Low D16b;
                    uint32_t tmp0;
                    val = *(pucRegBuffer+i*2);
                    val <<= 8;
                    val += *(pucRegBuffer+i*2+1);
                    
                    DF_Data[DEF_TCOMP_P2_INDEX] = (uint8_t)val;
                    DF_Data[DEF_TCOMP_P2_INDEX+1] = (uint8_t)(val>>8);
                    
                    tmp0 = TComp_P2;
                    tmp0 &= 0xFFFF0000;
                    tmp0 += val;
                    
                    TComp_P2 = tmp0;
                    
                    DF_UpdateReal_Flag = 1;
                }
                else if(usAddress+i==834)
                {   // Write TComp_P2 High D16b;
                    uint32_t tmp0;
                    val = *(pucRegBuffer+i*2);
                    val <<= 8;
                    val += *(pucRegBuffer+i*2+1);
                    
                    DF_Data[DEF_TCOMP_P2_INDEX+2] = (uint8_t)val;
                    DF_Data[DEF_TCOMP_P2_INDEX+2+1] = (uint8_t)(val>>8);
                    
                    tmp0 = val;
                    tmp0 <<= 16;
                    tmp0 += (TComp_P2&0x0000FFFF);
                    
                    TComp_P2 = tmp0;
                    
                    DF_UpdateReal_Flag = 1;
                }
                else if(usAddress+i==835)
                {   // Write TComp_P3 Low D16b;
                    uint32_t tmp0;
                    val = *(pucRegBuffer+i*2);
                    val <<= 8;
                    val += *(pucRegBuffer+i*2+1);
                    
                    DF_Data[DEF_TCOMP_P3_INDEX] = (uint8_t)val;
                    DF_Data[DEF_TCOMP_P3_INDEX+1] = (uint8_t)(val>>8);
                    
                    tmp0 = TComp_P3;
                    tmp0 &= 0xFFFF0000;
                    tmp0 += val;
                    
                    TComp_P3 = tmp0;
                    
                    DF_UpdateReal_Flag = 1;
                }
                else if(usAddress+i==836)
                {   // Write TComp_P3 High D16b;
                    uint32_t tmp0;
                    val = *(pucRegBuffer+i*2);
                    val <<= 8;
                    val += *(pucRegBuffer+i*2+1);
                    
                    DF_Data[DEF_TCOMP_P3_INDEX+2] = (uint8_t)val;
                    DF_Data[DEF_TCOMP_P3_INDEX+2+1] = (uint8_t)(val>>8);
                    
                    tmp0 = val;
                    tmp0 <<= 16;
                    tmp0 += (TComp_P3&0x0000FFFF);
                    
                    TComp_P3 = tmp0;
                    
                    DF_UpdateReal_Flag = 1;
                }
                
                #if(defined(DEBUG_HEAT_COMP2_EN)&&(DEBUG_HEAT_COMP2_EN==1))
                else if(usAddress+i==846)
                {   // Write HtComp_TRaw_Base_2;
                
                    val = *(pucRegBuffer+i*2);
                    val <<= 8;
                    val += *(pucRegBuffer+i*2+1);
                    
                    DF_Data[DEF_HTCOMP_TRAWBASE_INDEX] = (uint8_t)val;
                    DF_Data[DEF_HTCOMP_TRAWBASE_INDEX+1] = (uint8_t)(val>>8);
                    
                    HtComp_TRaw_Base_2 = val;
                    
                    DF_UpdateReal_Flag = 1;
                }
                else if(usAddress+i==847)
                {   // Write HtComp_HtRaw_Base_2;
                
                    val = *(pucRegBuffer+i*2);
                    val <<= 8;
                    val += *(pucRegBuffer+i*2+1);
                    
                    DF_Data[DEF_HTCOMP_HTRAWBASE_INDEX] = (uint8_t)val;
                    DF_Data[DEF_HTCOMP_HTRAWBASE_INDEX+1] = (uint8_t)(val>>8);
                    
                    HtComp_HtRaw_Base_2 = val;
                    
                    DF_UpdateReal_Flag = 1;
                }
                else if(usAddress+i==848)
                {   // Write HtComp_Kh_2;
                
                    val = *(pucRegBuffer+i*2);
                    val <<= 8;
                    val += *(pucRegBuffer+i*2+1);
                    
                    DF_Data[DEF_HTCOMP_KH_INDEX] = (uint8_t)val;
                    DF_Data[DEF_HTCOMP_KH_INDEX+1] = (uint8_t)(val>>8);
                    
                    HtComp_Kh_2 = val;
                    
                    DF_UpdateReal_Flag = 1;
                }
                else if(usAddress+i==849)
                {   // Write HtComp_SP_2;
                
                    val = *(pucRegBuffer+i*2);
                    val <<= 8;
                    val += *(pucRegBuffer+i*2+1);
                    
                    DF_Data[DEF_HTCOMP_SP_INDEX] = (uint8_t)val;
                    DF_Data[DEF_HTCOMP_SP_INDEX+1] = (uint8_t)(val>>8);
                    
                    HtComp_SP_2 = val;
                    
                    DF_UpdateReal_Flag = 1;
                }
                else if(usAddress+i==850)
                {   // Write HtComp_Ks_2;
                
                    val = *(pucRegBuffer+i*2);
                    val <<= 8;
                    val += *(pucRegBuffer+i*2+1);
                    
                    DF_Data[DEF_HTCOMP_KS_INDEX] = (uint8_t)val;
                    DF_Data[DEF_HTCOMP_KS_INDEX+1] = (uint8_t)(val>>8);
                    
                    HtComp_Ks_2 = val;
                    
                    DF_UpdateReal_Flag = 1;
                }
                #endif
                #endif
                
                else
                {
                    
                }
            }
        }
        else if((usAddress>=1024)&&(usAddress<=1101))
        {   // Write E703 Register area;
            for(i=0;i<usNRegs;i++)
            {   
                if(usAddress+i<=1101)
                {
                    
                    if(Usr_MbToE703_Addr(usAddress+i,&ea) == 1)
                    {
                        
                        #if(defined(DEF_E703_HOLDKEYWORD)&&(DEF_E703_HOLDKEYWORD == 1))
                        if((ea>=0x06)&&(ea<=0x10))
                        {
                            
                        }
                        else
                        #endif
                        {
                            val = *(pucRegBuffer+i*2);
                            val <<= 8;
                            val += *(pucRegBuffer+i*2+1);
                            
                            E703_RegBuff[usAddress+i-1024] = val;
                            
                            Usr_E703_WriteReg(ea,val);
                            
                            //Usr_E703_LockReg();
                        }
                    }
                }
            }
            
            
            #if 1
            {
                if((usAddress <= 1068)&&(usAddress+usNRegs > 1068)&&(E703_RegBuff[44]==11))
                {
                    
                    E703_Reset_Flag = 1;
                    MCU_Reset_Flag = 1;
                    
                }
                
                if((usAddress <= 1068)&&(usAddress+usNRegs > 1068)&&(E703_RegBuff[44]==12))
                {
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
                    //E703_Reset_Flag = 1;
                    //MCU_Reset_Flag = 1;
                    
                }
                
            }
            #endif
            
        }
        else if((usAddress>=1280)&&(usAddress<=1343))
        {   // Write E703 CM Usr area;
            for(i=0;i<usNRegs;i++)
            {   
                if(usAddress+i<=1343)
                {
                    if(Usr_MbToE703_Addr(usAddress+i,&ea) == 1)
                    {   
                        #if 0
                        #if(defined(DEF_E703_HOLDKEYWORD)&&(DEF_E703_HOLDKEYWORD == 1))
                        if((ea>=0x22)&&(ea<=0x2C))
                        {
                            
                        }
                        else
                        #endif
                        #endif
                        if((ea == 0x20)||(ea == 0x24)||(ea == 0x2A)||(ea == 0x30)||(ea == 0x32)||(ea == 0x34)||(ea == 0x38)||(ea == 0x3C))
                        {
                            val = *(pucRegBuffer+i*2);
                            val <<= 8;
                            val += *(pucRegBuffer+i*2+1);
                            
                            E703_CMBuff[usAddress+i-1280] = val;
                            
                            Usr_E703_WriteCMUsr(ea,val);
                            
                            //Usr_E703_LockCMUsr();
                            //Usr_E703_LockReg();
                        }
                    }
                }
            }
        }
        else if((usAddress>=1536)&&(usAddress<1536+128))
        {   // Write Data Flash area;
            for(i=0;i<usNRegs;i++)
            {   
                if(usAddress+i<1536+128)
                {
                    val = *(pucRegBuffer+i*2);
                    val <<= 8;
                    val += *(pucRegBuffer+i*2+1);
                    
                    DF_Data[(usAddress+i-1536)*2+0] = (uint8_t)val;
                    DF_Data[(usAddress+i-1536)*2+1] = (uint8_t)(val>>8);
                    
                    DF_UpdateReal_Flag = 1;
                }
            }
        }
        else
        {
            
        }
    }
    
    return MB_ENOERR;
}


eMBErrorCode
eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,
               eMBRegisterMode eMode )
{
    return MB_ENOREG;
}

eMBErrorCode
eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
    return MB_ENOREG;
}
