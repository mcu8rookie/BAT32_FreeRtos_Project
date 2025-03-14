#ifndef __USR_DATAFLASH_C__
#define __USR_DATAFLASH_C__

#include "Usr_Config.h"
#include "stdint.h"

#include "flash.h"
#include "Usr_Debug.h"
#include "Usr_DataFlash.h"

#include "Usr_Main.h"
#include "Usr_PSF.h"

//#define DEF_DF_PARAM_STARTADDR      (0x00500000)
//#define DEF_DF_PARAM_OVERADDR       (0x00500100)
//#define DEF_DF_DATA_LEN         (DEF_DF_PARAM_OVERADDR-DEF_DF_PARAM_STARTADDR)


uint32_t DF_StartAddress;
unsigned char DF_Rst;
unsigned char DF_UpdateInit_Flag;
unsigned char DF_UpdateReal_Flag;


uint8_t DF_Data[256];
uint8_t DF_DefaultData[256] = 
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
    uint32_t i,j,j1;
    uint32_t *addr_ptr;
    uint32_t data_b4;
    uint8_t data_b1;
    uint32_t data1;
    uint32_t data2;
    
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
    
    addr_ptr = (uint32_t *)DEF_DF_PARAM_STARTADDR;
    data_b4 = *addr_ptr;
    data1 = data_b4;
    
    DF_printf("\nDF[0x%08X],0x%08X",addr_ptr,data1);
    
    addr_ptr = (uint32_t *)DEF_DF_PARAM_OVERADDR-4;
    data_b4 = *addr_ptr;
    data2 = data_b4;
    
    DF_printf("\nDF[0x%08X],0x%08X",addr_ptr,data2);
    
    if((data1 == 0x00FF5453)&&(data1 == 0x5053FFFF))
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
    
}




void Usr_DFData_To_Variable(void)
{
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
        TComp_P0 = DF_Data[DEF_TCOMP_P0_INDEX+1];
        TComp_P0 <<= 8;
        TComp_P0 += DF_Data[DEF_TCOMP_P0_INDEX];
        
        //TComp_P1 = DF_Data[DEF_TCOMP_P1_INDEX+3];
        //TComp_P1 <<= 8;
        //TComp_P1 += DF_Data[DEF_TCOMP_P1_INDEX+2];
        //TComp_P1 <<= 8;
        TComp_P1 = DF_Data[DEF_TCOMP_P1_INDEX+1];
        TComp_P1 <<= 8;
        TComp_P1 += DF_Data[DEF_TCOMP_P1_INDEX];
        
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
    
}

void Usr_DFData_To_DataFlash(void)
{

}





#endif





