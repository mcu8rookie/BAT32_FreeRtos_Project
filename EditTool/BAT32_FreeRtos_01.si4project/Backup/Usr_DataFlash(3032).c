#ifndef __USR_DATAFLASH_C__
#define __USR_DATAFLASH_C__

#include "Usr_Config.h"
#include "stdint.h"

#include "flash.h"
#include "Usr_Debug.h"
#include "Usr_DataFlash.h"

#include "Usr_Main.h"
#include "Usr_PSF.h"

#include "Usr_I2CA_Slave.h"


//#define DEF_DF_PARAM_STARTADDR      (0x00500000)
//#define DEF_DF_PARAM_OVERADDR       (0x00500100)
//#define DEF_DF_DATA_LEN         (DEF_DF_PARAM_OVERADDR-DEF_DF_PARAM_STARTADDR)


uint32_t DF_StartAddress;
unsigned char DF_Rst;
unsigned char DF_UpdateInit_Flag;
unsigned char DF_UpdateReal_Flag;

#if 0
uint8_t DF_Data[DEF_DF_DATA_LEN];
uint8_t DF_DefaultData[DEF_DF_DATA_LEN] = 
#endif

#if 1
__align(4)  uint8_t DF_Data[DEF_DF_DATA_LEN];
__align(4)  uint8_t DF_DefaultData[DEF_DF_DATA_LEN] = 
#endif
//uint8_t DF_DefaultData[DEF_DF_DATA_LEN] __attribute__((at(DEF_DF_PARAM_STARTADDR))) 
//const uint8_t DF_DefaultData[DEF_DF_DATA_LEN] __attribute__((at(DEF_DF_PARAM_STARTADDR))) = 
//.\Objects\BAT32_FreeRTOS_Proj.axf: Warning: L6918W: Execution region ER_IROM2 placed at 0x00500000 needs padding to ensure alignment 1 of usr_dataflash.o(.ARM.__AT_0x00500200).
//const uint8_t DF_DefaultData[DEF_DF_DATA_LEN] __attribute__((section(".ARM.__at_0x00500200"))) = 
{
    //0x00  -->>    0x0F
    0x53,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    //0x10  -->>    0x1F
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    //0x20  -->>    0x2F
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    //0x30  -->>    0x3F
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    //0x40  -->>    0x4F
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    //0x50  -->>    0x5F
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    //0x60  -->>    0x6F
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    //0x70  -->>    0x7F
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    //0x80  -->>    0x8F
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    //0x90  -->>    0x9F
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    //0xA0  -->>    0xAF
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    //0xB0  -->>    0xBF
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    //0xC0  -->>    0xCF
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    //0xD0  -->>    0xDF
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    //0xE0  -->>    0xEF
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    //0xF0  -->>    0xFF
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x50,
};




unsigned char Usr_DF_InitSetup(void)
{
    uint32_t i,j;
    uint32_t *addr_ptr;
    uint32_t data_b4;
    uint8_t data_b1;
    uint32_t data1;
    uint32_t data2;
    
    #if 1
    DF_printf("\nDataFlash,\tStartAddress, 0x%08X,\t DataLen,%d,\tDF_DefaultData",DEF_DF_PARAM_STARTADDR,DEF_DF_DATA_LEN);
    DF_printf("\n{");
    j = 0;
    DF_printf("\n\n\t//0x%02X  -->>  0x%02X,\n",j,j+15);
    #if 0   // Running normally;
    for(i=0;i<DEF_DF_DATA_LEN;i+=4)
    {
        DF_Data[i] = DF_DefaultData[i];
        DF_printf("\t0x%02X,",DF_Data[i]);
        if((j%16) == 0)
        {   
            DF_printf("\n\t//0x%02X  -->>  0x%02X,\n",j,j+15);
        }
    }
    #endif
    
    #if 1   // 
    for(i=0;i<DEF_DF_DATA_LEN;i+=4)
    {
        addr_ptr = (uint32_t *)(DF_DefaultData+i);
        data_b4 = *addr_ptr;
        data1 = data_b4;
        
        data_b1 = (uint8_t)data1;
        DF_Data[j] = data_b1;
        DF_printf("\t0x%02X,",data_b1);
        j++;
        data_b1 = (uint8_t)(data1>>8);
        DF_Data[j] = data_b1;
        DF_printf("\t0x%02X,",data_b1);
        j++;
        data_b1 = (uint8_t)(data1>>16);
        DF_Data[j] = data_b1;
        DF_printf("\t0x%02X,",data_b1);
        j++;
        data_b1 = (uint8_t)(data1>>24);
        DF_Data[j] = data_b1;
        DF_printf("\t0x%02X,",data_b1);
        j++;
        
        if((j%16) == 0)
        {   
            DF_printf("\n\t//0x%02X  -->>  0x%02X,\n",j,j+15);
        }
    }
    #endif
    
    DF_printf("\n}\n");
    #endif
    
    
    DF_printf("\nDataFlash,\tStartAddress, 0x%08X,\t DataLen,%d,",DEF_DF_PARAM_STARTADDR,DEF_DF_DATA_LEN);
    DF_printf("\n{");
    j=0;
    DF_printf("\n\n\t//0x%02X  -->>  0x%02X,\n",j,j+15);
    for(i=0;i<DEF_DF_DATA_LEN;i+=4)
    {
        addr_ptr = (uint32_t *)(DEF_DF_PARAM_STARTADDR+i);
        data_b4 = *addr_ptr;
        data1 = data_b4;
        
        data_b1 = (uint8_t)data1;
        DF_Data[j] = data_b1;
        DF_printf("\t0x%02X,",data_b1);
        j++;
        data_b1 = (uint8_t)(data1>>8);
        DF_Data[j] = data_b1;
        DF_printf("\t0x%02X,",data_b1);
        j++;
        data_b1 = (uint8_t)(data1>>16);
        DF_Data[j] = data_b1;
        DF_printf("\t0x%02X,",data_b1);
        j++;
        data_b1 = (uint8_t)(data1>>24);
        DF_Data[j] = data_b1;
        DF_printf("\t0x%02X,",data_b1);
        j++;
        
        if((j%16) == 0)
        {   
            DF_printf("\n\t//0x%02X  -->>  0x%02X,\n",j,j+15);
        }
    }
    DF_printf("\n}\n");
    
    
    Usr_DFData_To_Variable();
    
    addr_ptr = (uint32_t *)DEF_DF_PARAM_STARTADDR;
    data_b4 = *addr_ptr;
    data1 = data_b4;
    
    DF_printf("\nDF[0x%08X],0x%08X",addr_ptr,data1);
    
    addr_ptr = (uint32_t *)DEF_DF_PARAM_OVERADDR-4;
    data_b4 = *addr_ptr;
    data2 = data_b4;
    
    DF_printf("\nDF[0x%08X],0x%08X",addr_ptr,data2);
    
    if((data1 == 0x00FF5453)&&(data2 == 0x5053FFFF))
    {
        DF_printf("\nParameter Exist.");
        
    }
    else
    {
        DF_printf("\nParameter Not Exist.");
        
        //Init_printf("\nWrite Default Parameters.");
        
        //EraseSector(DEF_DF_PARAM_STARTADDR);
        #if 0
        for(i=0;i<256;i++)
        {
            DF_DefaultData[i]=i;
        }
        #endif
        //flash_write(DEF_DF_PARAM_STARTADDR, DEF_DF_DATA_LEN, DF_DefaultData);
    }
    
    return 0;
}



void Usr_DFData_To_Variable(void)
{
    unsigned char i,j;
    unsigned char *pbyte;
    
    int16_t int16_tmp1;
    
    #if(defined(DEF_FUN_TIMESN_EN)&&(DEF_FUN_TIMESN_EN==1))
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
    
    
    #if(defined(DEF_FUN_TCOMP_EN)&&(DEF_FUN_TCOMP_EN==1))
    {
        
        TComp_TRawBase = DF_Data[DEF_TRAWBASE_INDEX+1];
        TComp_TRawBase<<=8;
        TComp_TRawBase += DF_Data[DEF_TRAWBASE_INDEX];
        
        //TComp_P0 = DF_Data[DEF_TCOMP_P0_INDEX+3];
        //TComp_P0 <<= 8;
        //TComp_P0 += DF_Data[DEF_TCOMP_P0_INDEX+2];
        //TComp_P0 <<= 8;
        int16_tmp1 = DF_Data[DEF_TCOMP_P0_INDEX+1];
        int16_tmp1 <<= 8;
        int16_tmp1 += DF_Data[DEF_TCOMP_P0_INDEX];
        
        TComp_P0 = int16_tmp1;
        
        //TComp_P1 = DF_Data[DEF_TCOMP_P1_INDEX+3];
        //TComp_P1 <<= 8;
        //TComp_P1 += DF_Data[DEF_TCOMP_P1_INDEX+2];
        //TComp_P1 <<= 8;
        int16_tmp1 = DF_Data[DEF_TCOMP_P1_INDEX+1];
        int16_tmp1 <<= 8;
        int16_tmp1 += DF_Data[DEF_TCOMP_P1_INDEX];
        
        TComp_P1 = int16_tmp1;
        
        TComp_P2 = DF_Data[DEF_TCOMP_P2_INDEX+3];
        TComp_P2<<=8;
        TComp_P2 += DF_Data[DEF_TCOMP_P2_INDEX+2];
        TComp_P2<<=8;
        TComp_P2 += DF_Data[DEF_TCOMP_P2_INDEX+1];
        TComp_P2<<=8;
        TComp_P2 += DF_Data[DEF_TCOMP_P2_INDEX];
        
        TComp_P3 = DF_Data[DEF_TCOMP_P3_INDEX+3];
        TComp_P3<<=8;
        TComp_P3 += DF_Data[DEF_TCOMP_P3_INDEX+2];
        TComp_P3<<=8;
        TComp_P3 += DF_Data[DEF_TCOMP_P3_INDEX+1];
        TComp_P3<<=8;
        TComp_P3 += DF_Data[DEF_TCOMP_P3_INDEX];
    }
    #endif
    
    Sens_PreHeatTime = DF_Data[DEF_PREHEATTIME_INDEX+1];
    Sens_PreHeatTime<<=8;
    Sens_PreHeatTime += DF_Data[DEF_PREHEATTIME_INDEX];
    
    Sens_CoolTime = DF_Data[DEF_COOLTIME_INDEX+1];
    Sens_CoolTime<<=8;
    Sens_CoolTime += DF_Data[DEF_COOLTIME_INDEX];
    
    
    Sens_FilterCnt = DF_Data[DEF_FILTERCNT_INDEX+1];
    Sens_FilterCnt<<=8;
    Sens_FilterCnt += DF_Data[DEF_FILTERCNT_INDEX];
    
    if(Sens_FilterCnt > DEF_SRAW_FILTERMAX)
    {
        Sens_FilterCnt = DEF_SRAW_FILTERMAX;
    }
    else if(Sens_FilterCnt < 1)
    {
        Sens_FilterCnt = 1;
    }
    
    FilterIndex = 0;
    FilterTotal = 0;
    
    
    #if(defined(DEF_I2C_TYPE)&&(DEF_I2C_TYPE==DEF_I2C_TYPE_MIDEA))
    {
        // Update Varialbe from Data Flash;
        Psf_Gas_TypeCode = DF_Data[DEF_GASTYPE_INDEX+1];
        Psf_Gas_TypeCode <<=8;
        Psf_Gas_TypeCode += DF_Data[DEF_GASTYPE_INDEX];
        
        if((Psf_Gas_TypeCode == 0x0018)||(Psf_Gas_TypeCode == 0x0019)||(Psf_Gas_TypeCode == 0x001B)||(Psf_Gas_TypeCode == 0x001C)||(Psf_Gas_TypeCode == 0x001D))
        {
            
        }
        else
        {
            Psf_Gas_TypeCode = PSF_GASTYPE_DEFAULT;
        }
    }
    #endif
    
    
    #if(defined(DEF_TABLEXY_EN)&&(DEF_TABLEXY_EN==1))
    {
        // Update Table X Y from Data Flash;
        
        for(i=0;i<DEF_TABLE_MAX;i++)
        {
            Sens_TableX[i] = DF_Data[DEF_TABLEX_INDEX+1+i*2];
            Sens_TableX[i] <<= 8;
            Sens_TableX[i] += DF_Data[DEF_TABLEX_INDEX+0+i*2];
            
        }
        
        for(i=0;i<DEF_TABLE_MAX;i++)
        {
            Sens_TableY[i] = DF_Data[DEF_TABLEY_INDEX+1+i*2];
            Sens_TableY[i] <<= 8;
            Sens_TableY[i] += DF_Data[DEF_TABLEY_INDEX+0+i*2];
            
        }
        
        for(i=0;i<DEF_TABLE_MAX;i++)
        {   
            Sens_TableX2[i] = Sens_TableX[i];
        }
        
        for(i=0;i<DEF_TABLE_MAX;i++)
        {   
            Table_32Bit[i] = Sens_TableY[i];
        }
        
        for(i=5;i<DEF_TABLE_MAX;i++)
        {   
            Table_32Bit[i] *= 10;
        }
    }
    
    {
        Sens_DC_Y = DF_Data[DEF_DC_Y_INDEX+1];
        Sens_DC_Y <<=8;
        Sens_DC_Y += DF_Data[DEF_DC_Y_INDEX];
    }
    
    #if(defined(DEF_DELTA_RAW_EN)&&(DEF_DELTA_RAW_EN==1))
    {
        Usr_Delta_Raw = DF_Data[DEF_DELTA_RAW_INDEX+1];
        Usr_Delta_Raw <<=8;
        Usr_Delta_Raw += DF_Data[DEF_DELTA_RAW_INDEX];
    }
    #endif
    
    #if(defined(DEF_DELTA_PPM_EN)&&(DEF_DELTA_PPM_EN==1))
    {
        Usr_Delta_PPM1 = DF_Data[DEF_DELTA_PPM_INDEX+1];
        Usr_Delta_PPM1 <<=8;
        Usr_Delta_PPM1 += DF_Data[DEF_DELTA_PPM_INDEX];
    }
    #endif
    
    #if((defined(DEF_OVERRANGE_ALARM_EN))&&(DEF_OVERRANGE_ALARM_EN == 1))
    {
        Usr_CheckRangeMax();
    }
    #endif
    
    #endif
    
    
    #if(defined(DEF_HUMCOMP_EN)&&(DEF_HUMCOMP_EN == 1))
    {   
        
        for(i=0;i<DEF_HUMCOMP_PARAM_MAX;i++)
        {   
            pbyte = (unsigned char*)(HumComp_M2_S+i);
            
            for(j=0;j<4;j++)
            {
                *(pbyte+j) = DF_Data[DEF_HUMCOMP_PARAM_INDEX+i*4+j];
            }
        }
        
        HumComp_Flag = DF_Data[DEF_HUMCOMP_FLAG_INDEX+1];
        HumComp_Flag <<= 8;
        HumComp_Flag += DF_Data[DEF_HUMCOMP_FLAG_INDEX];
        
        #if 1
        
        for(i=0;i<4;i++)
        {   
            //pbyte = (unsigned char *)&(HumComp_M2_S[i]);
            pbyte = (unsigned char *)(HumComp_M2_S+i);
            
            if(FP32_IsNumerical(pbyte) == 0)
            {   // not numerical;
                break;
            }
        }
        
        if(i == 4)
        {
            Flag_HumiCompParameter = 1;
        }
        else
        {
            Flag_HumiCompParameter = 0;
            HumComp_Flag = 0;
        }
        #endif
        
        #if(defined(DEF_IMPROVE_HC_EN)&&(DEF_IMPROVE_HC_EN==1))
        for(i=4;i<6;i++)
        {   
            //pbyte = (unsigned char *)&(HumComp_M2_S[i]);
            pbyte = (unsigned char *)(HumComp_M2_S+i);
            
            if(FP32_IsNumerical(pbyte) == 0)
            {   // not numerical;
                break;
            }
        }
        
        if(i == 6)
        {
            Flag_HumiCompParameter2 = 1;
        }
        else
        {
            Flag_HumiCompParameter2 = 0;
        }
        #endif
    }
    #endif
    
    #if(defined(DEF_PRESCOMP_EN)&&(DEF_PRESCOMP_EN==1))
    {   
        
        for(i=0;i<DEF_PRESCOMP_PARAM_MAX;i++)
        {   
            pbyte = (unsigned char*)(PresComp_K+i);
            
            for(j=0;j<4;j++)
            {
                *(pbyte+j) = DF_Data[DEF_PRESCOMP_PARAM_INDEX+i*4+j];
            }
        }
        
        PresComp_PBase = DF_Data[DEF_PRESCOMP_PBASE_INDEX+1];
        PresComp_PBase <<= 8;
        PresComp_PBase += DF_Data[DEF_PRESCOMP_PBASE_INDEX];
        
        PresComp_Flag = DF_Data[DEF_PRESCOMP_FLAG_INDEX+1];
        PresComp_Flag <<= 8;
        PresComp_Flag += DF_Data[DEF_PRESCOMP_FLAG_INDEX];
        
        #if 1
        
        for(i=0;i<DEF_PRESCOMP_PARAM_MAX;i++)
        {   
            pbyte = (unsigned char *)(PresComp_K+i);
            
            if(FP32_IsNumerical(pbyte) == 0)
            {   // not numerical;
                break;
            }
        }
        
        if(i == DEF_PRESCOMP_PARAM_MAX)
        {
            Flag_PresCompParameter = 1;
        }
        else
        {
            Flag_PresCompParameter = 0;
            PresComp_Flag = 0;
        }
        #endif
    }
    #endif
    
    #if(defined(DEF_TEMPRATE_EN)&&(DEF_TEMPRATE_EN==1))
    {
        TmpRate_P = DF_Data[DEF_TMPRATE_P_INDEX+1];
        TmpRate_P <<= 8;
        TmpRate_P += DF_Data[DEF_TMPRATE_P_INDEX];
        
    }
    #endif
    
    #if((DEF_HEAT_COMP2_EN)&&(DEF_HEAT_COMP2_EN==1))
    {   
        
        HtComp_TRaw_Base_2 = DF_Data[DEF_HTCOMP_TRAWBASE_INDEX+1];
        HtComp_TRaw_Base_2 <<= 8;
        HtComp_TRaw_Base_2 += DF_Data[DEF_HTCOMP_TRAWBASE_INDEX];
        
        HtComp_HtRaw_Base_2 = DF_Data[DEF_HTCOMP_HTRAWBASE_INDEX+1];
        HtComp_HtRaw_Base_2 <<= 8;
        HtComp_HtRaw_Base_2 += DF_Data[DEF_HTCOMP_HTRAWBASE_INDEX];
        
        HtComp_Kh_2 = DF_Data[DEF_HTCOMP_KH_INDEX+1];
        HtComp_Kh_2 <<= 8;
        HtComp_Kh_2 += DF_Data[DEF_HTCOMP_KH_INDEX];
        
        HtComp_SP_2 = DF_Data[DEF_HTCOMP_SP_INDEX+1];
        HtComp_SP_2 <<= 8;
        HtComp_SP_2 += DF_Data[DEF_HTCOMP_SP_INDEX];
        
        HtComp_Ks_2 = DF_Data[DEF_HTCOMP_KS_INDEX+1];
        HtComp_Ks_2 <<= 8;
        HtComp_Ks_2 += DF_Data[DEF_HTCOMP_KS_INDEX];
        
        HtComp_DP0 = DF_Data[DEF_HTCOMP_DP0_INDEX+1];
        HtComp_DP0 <<= 8;
        HtComp_DP0 += DF_Data[DEF_HTCOMP_DP0_INDEX];
        
        
        #if 1
        {
            if((HtComp_DP0 == 0xffff)||(HtComp_DP0%HtComp_SP_2 != 0))
            {
                HtComp_DP0 = 0;
            }
            
            #if 1
            if(((HtComp_TRaw_Base_2 == 0)||(HtComp_TRaw_Base_2 == 65535))\
                ||((HtComp_HtRaw_Base_2 == 0)||(HtComp_HtRaw_Base_2 == 65535))\
                ||((HtComp_Kh_2 == 0))\
                ||((HtComp_SP_2 == 65535))\
                 ||((HtComp_Ks_2 == 0))\
             )
            #endif
            {
                Flag_HtComp_2 = 0;
            }
            else
            {
                long temp = 0;
                
                Flag_HtComp_2 = 1;
                
                Dlt_P0 = HtComp_DP0;
                temp = Dlt_P0;
                temp *= HtComp_Ks_2;
                temp >>= 10;
                HtComp_CompTotal_2 = temp;
            }
            
        }
        #endif
    }
    #endif
    
    
    #if((defined(DEBUG_HUMI_RATE_EN))&&(DEBUG_HUMI_RATE_EN==1))
    {
        ExtSens_RH_Thre = DF_Data[DEF_HUMI_RATE_INDEX+1];
        ExtSens_RH_Thre <<= 8;
        ExtSens_RH_Thre += DF_Data[DEF_HUMI_RATE_INDEX];
        
        if(ExtSens_RH_Thre>1000)
        {
            Flag_RH_Rate_En = 0;
        }
        else
        {
            Flag_RH_Rate_En = 1;
        }
        
        ExtSens_RH_Total = 0;
        ExtSens_RH_TolIdx = 0;
        Flag_RH_Rate_Exceed = 0;
        ExtSens_RH_BufIdx = 0;
    }
    #endif
    
    #if(defined(DEF_CONCEN_THRE_EN)&&(DEF_CONCEN_THRE_EN==1))
    {
        Concen_Threshold = DF_Data[DEF_CONCEN_THRE_INDEX+1];
        Concen_Threshold <<= 8;
        Concen_Threshold += DF_Data[DEF_CONCEN_THRE_INDEX];
        
        if(Concen_Threshold==0||Concen_Threshold>1000)
        {
            Flag_Concen_Threshold_En = 0;
        }
        else
        {
            Flag_Concen_Threshold_En = 1;
        }
        
        Flag_Concen_Threshol_Alarm = 0;
        
        Donot_Alarm_5s = 5;
        Concentration_Alarm_HoldTime = 0;
    }
    
    #if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))
    {
        //ASC_Func_En = DF_Data[DEF_ASC_FUNC_EN_INDEX+1];
        //ASC_Func_En <<= 8;
        //ASC_Func_En += DF_Data[DEF_ASC_FUNC_EN_INDEX];
        
        ASC_Usr_En = DF_Data[DEF_ASC_FUNC_EN_INDEX+1];
        ASC_Usr_En <<= 8;
        ASC_Usr_En += DF_Data[DEF_ASC_FUNC_EN_INDEX];
        
        ASC_PPM_HighTh = DF_Data[DEF_ASC_PPM_HIGHTH_INDEX+1];
        ASC_PPM_HighTh <<= 8;
        ASC_PPM_HighTh += DF_Data[DEF_ASC_PPM_HIGHTH_INDEX];
        
        ASC_PPM_LowTh = DF_Data[DEF_ASC_PPM_LOWTH_INDEX+1];
        ASC_PPM_LowTh <<= 8;
        ASC_PPM_LowTh += DF_Data[DEF_ASC_PPM_LOWTH_INDEX];
        
        ASC_Tmpr_RateTh = DF_Data[DEF_ASC_TMPR_RATETH_INDEX+1];
        ASC_Tmpr_RateTh <<= 8;
        ASC_Tmpr_RateTh += DF_Data[DEF_ASC_TMPR_RATETH_INDEX];
        
        ASC_Humi_RateTh = DF_Data[DEF_ASC_HUMI_RATETH_INDEX+1];
        ASC_Humi_RateTh <<= 8;
        ASC_Humi_RateTh += DF_Data[DEF_ASC_HUMI_RATETH_INDEX];
        
        ASC_Adjust_Cnt = DF_Data[DEF_ASC_CNT_INDEX+1];
        ASC_Adjust_Cnt <<= 8;
        ASC_Adjust_Cnt += DF_Data[DEF_ASC_CNT_INDEX];
        
        ASC_Adjust_Value[0] = DF_Data[DEF_ASC_VALUE1_INDEX+1];
        ASC_Adjust_Value[0] <<= 8;
        ASC_Adjust_Value[0] += DF_Data[DEF_ASC_VALUE1_INDEX];
        
        ASC_Adjust_Value[1] = DF_Data[DEF_ASC_VALUE2_INDEX+1];
        ASC_Adjust_Value[1] <<= 8;
        ASC_Adjust_Value[1] += DF_Data[DEF_ASC_VALUE2_INDEX];
        
        ASC_Adjust_Value[2] = DF_Data[DEF_ASC_VALUE3_INDEX+1];
        ASC_Adjust_Value[2] <<= 8;
        ASC_Adjust_Value[2] += DF_Data[DEF_ASC_VALUE3_INDEX];
        
        
        
        #if(defined(DEF_ASC_FAST_EN)&&(DEF_ASC_FAST_EN == 1))
        ASC_Fast_SuccCnt = DF_Data[DEF_ASC_FAST_PROCCNT_INDEX];
        ASC_Fast_FailCnt = DF_Data[DEF_ASC_FAST_PROCCNT_INDEX+1];
        
        ASC_Fast_ProcCnt = DF_Data[DEF_ASC_FAST_PROCCNT_INDEX+1];
        ASC_Fast_ProcCnt <<= 8;
        ASC_Fast_ProcCnt += DF_Data[DEF_ASC_FAST_PROCCNT_INDEX];
        
        ASC_Fast_Value = DF_Data[DEF_ASC_FAST_VALUE_INDEX+1];
        ASC_Fast_Value <<= 8;
        ASC_Fast_Value += DF_Data[DEF_ASC_FAST_VALUE_INDEX];
        #endif
        
        
        if(ASC_Usr_En == 1)
        {
            
        }
        else
        {
            ASC_Usr_En = 0;
        }
        
        if(((ASC_Tmpr_RateTh==0)||((uint16_t)ASC_Tmpr_RateTh==0xFFFF))\
            ||((ASC_Humi_RateTh==0)||((uint16_t)ASC_Humi_RateTh==0xFFFF))\
            || ((ASC_PPM_LowTh==0)||((uint16_t)ASC_PPM_LowTh==0xFFFF))\
            || ((ASC_PPM_HighTh==0)||((uint16_t)ASC_PPM_HighTh==0xFFFF))\
            )
        {
            ASC_Param_En = 0;
        }
        else
        {
            ASC_Param_En = 2;
        }
        
        ASC_Func_En = ASC_Param_En + ASC_Usr_En;
        
        if((ASC_Func_En==3)&&(ASC_Adjust_Cnt>0)&&(ASC_Adjust_Cnt<=3))
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
        
    }
    #endif
    
    
    #if(defined(DEF_DBG_SRAW_0_EN)&&(DEF_DBG_SRAW_0_EN==1))
    
    Dbg_SRaw0_Cnt1 = DF_Data[DEF_SRAW01_INDEX+1];
    Dbg_SRaw0_Cnt1 <<= 8;
    Dbg_SRaw0_Cnt1 += DF_Data[DEF_SRAW01_INDEX];
    
    Dbg_SRaw0_Cnt2 = DF_Data[DEF_SRAW02_INDEX+1];
    Dbg_SRaw0_Cnt2 <<= 8;
    Dbg_SRaw0_Cnt2 += DF_Data[DEF_SRAW02_INDEX];
    
    if(Dbg_SRaw0_Cnt1 == 0xFFFF)
    {
        Dbg_SRaw0_Cnt1=0;
    }
    
    if(Dbg_SRaw0_Cnt2 == 0xFFFF)
    {
        Dbg_SRaw0_Cnt2=0;
    }
    
    #endif
    
    
    #if(defined(DEF_HEAT_BOARD_EN)&&(DEF_HEAT_BOARD_EN == 1))
    
    HeatBoard_Duty = DF_Data[DEF_HEAT_BOARD_DUTY_INDEX+1];
    HeatBoard_Duty <<= 8;
    HeatBoard_Duty += DF_Data[DEF_HEAT_BOARD_DUTY_INDEX];
    
    HeatBoard_Period = DF_Data[DEF_HEAT_BOARD_PROD_INDEX+1];
    HeatBoard_Period <<= 8;
    HeatBoard_Period += DF_Data[DEF_HEAT_BOARD_PROD_INDEX];
    
    if((HeatBoard_Duty == 0)||(HeatBoard_Period == 0)||(HeatBoard_Duty > HeatBoard_Period)||(HeatBoard_Duty == 65535)||(HeatBoard_Period == 65535))
    {
        Flag_HeatBoard = 0;
    }
    else if(HeatBoard_Duty < HeatBoard_Period)
    {
        Flag_HeatBoard = 1;
    }
    else
    {
        Flag_HeatBoard = 2;
    }
    
    #endif
    
    
    #if(defined(DEF_HEAT_BOARD_EN)&&(DEF_HEAT_BOARD_EN == 1))
    if(Flag_HeatBoard == 0)
    {
        HeatBoard_Cool();
    }
    else if(Flag_HeatBoard == 2)
    {
        HeatBoard_Heat();
    }
    #endif
    
    
    #endif
    
}

void Usr_DFData_To_DataFlash(void)
{

}





#endif






