#ifndef __USR_EXTSENS_C__
#define __USR_EXTSENS_C__

#include <stdint.h>
#include "Usr_ExtSens.h"

#include"Usr_Config.h"

#include"Usr_Soft_I2C.h"

#include "Usr_I2C.h"



#if(defined(DEF_SENSOR_E703_EN)&&(DEF_SENSOR_E703_EN==1))


ADDR_DATA_ST E703_RegData[DEF_REG_DATA_NUM];
ADDR_DATA_ST E703_CMData[DEF_CM_DATA_NUM];



uint8_t Usr_Init_E703_Data(void)
{
    uint8_t i;
    
    for(i=0;i<DEF_REG_DATA_NUM;i++)
    {
        
    }
    
    for(i=0;i<DEF_REG_DATA_NUM;i++)
    {
        
    }
    
    return 0;
}


uint8_t Usr_Is_RegsterAddr(uint8_t addr)
{
    // Odd number is wrong;
    if((addr&0x01) == 1)
    {
        return 0;
    }
    
    // For even number;
    if((addr>0x38)&&(addr<0x46))
    {
        return 0;
    }
    if((addr>0x4A)&&(addr<0x4E))
    {
        return 0;
    }
    if((addr>0xAA)&&(addr<0xE4))
    {
        return 0;
    }
    if(addr>0xF4)
    {
        return 0;
    }
    
    return 1;
}

uint8_t Usr_Is_CMAddr(uint8_t addr)
{
    // Odd number is wrong;
    if((addr&0x01) == 1)
    {
        return 0;
    }
    
    if(addr>0x7E)
    {
        return 0;
    }
    
    return 1;
}

uint8_t Usr_RegToCM_Addr(uint8_t addr)
{
    if(1==Usr_Is_RegsterAddr(addr))
    {
        if(addr<=0x1E)
        {
            return addr+0x1A;
        }
        if((addr>=0x50)&&(addr<=0x68))
        {
            return addr-0x50;
        }
        if((addr>=0x6A)&&(addr<=0xAA))
        {
            return addr-0x2E;
        }
    }
    
    return 0xFF;
    
}

uint8_t Usr_CMToReg_Addr(uint8_t addr)
{
    if(1==Usr_Is_CMAddr(addr))
    {
        if(addr<=0x18)
        {
            return addr+0x50;
        }
        if((addr>=0x1A)&&(addr<=0x3A))
        {
            return addr-0x1A;
        }
        if((addr>=0x3C)&&(addr<=0x7C))
        {
            return addr+0x2E;
        }
    }
    
    return 0xFF;
}


uint8_t Usr_E703_ReadReg(uint8_t addr,uint16_t *ptr)
{
    uint8_t i;
	
    if(1== Usr_Is_RegsterAddr(addr))
    {
        i2c20_wtbuf[0] = 0x38;
        
        for(i=0;i<10;i++)
        {
            i2c20_rdbuf[i] = 0xFF;
        }
        
        if(0 == i2c_burst_read(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_rdbuf, 2))
        {
            *ptr = i2c20_rdbuf[1];
            *ptr <<= 8;
            *ptr += i2c20_rdbuf[0];
            
					Debug_printf("\nI2C1: WT: 0x%02X,0x%02X,",DEF_E703_I2C_ADDR_WT,i2c20_wtbuf[0]);
        Debug_printf("\nI2C1: RD: 0x%02X,0x%02X,0x%02X,",DEF_E703_I2C_ADDR_RD,i2c20_rdbuf[0],i2c20_rdbuf[1]);
        Debug_printf("\nE703.11 ChipVersion: 0x%02X,0x%02X,\n",i2c20_rdbuf[0],i2c20_rdbuf[1]);
					
            return 1;
        }
        else
        {
            return 0;
        }
        
        
        
    }
    
    return 0;
}

uint8_t Usr_E703_ReadCM(uint8_t addr,uint16_t *ptr)
{
    return 0;
}


void Usr_E703_InitSetup(void)
{

}

void Usr_E703_MainLoop(void)
{

}


#endif

#if(defined(DEF_SENSOR_HDC3020_EN)&&(DEF_SENSOR_HDC3020_EN==1))

#endif

#if(defined(DEF_SENSOR_CMP201_EN)&&(DEF_SENSOR_CMP201_EN==1))

#endif



#endif


