#ifndef __USR_EXTSENS_C__
#define __USR_EXTSENS_C__


#include <stdint.h>

#include <stdio.h>

#include "Usr_Config.h"

#include "Usr_Debug.h"

#include "Usr_E703.h"

#include "Usr_Soft_I2C.h"

#include "Usr_I2C.h"



#if(defined(DEF_SENSOR_E703_EN)&&(DEF_SENSOR_E703_EN==1))

uint32_t Usr_E307_Timestamp;




ADDR_DATA_ST E703_RegData[DEF_REG_DATA_NUM];
ADDR_DATA_ST E703_CMData_Probe[DEF_CM_DATA_NUM];
const ADDR_DATA_ST E703_CMData_Init[DEF_CM_DATA_NUM] = 
#if 0
{   // M3;
    {0x00, 0x59D6},
    {0x02, 0x0023},
    {0x04, 0x00EC},
    {0x06, 0xE700},
    {0x08, 0x0000},
    {0x0A, 0x0000},
    {0x0C, 0x0000},
    {0x0E, 0x0000},
    {0x10, 0x0000},
    {0x12, 0x0000},
    {0x14, 0x0000},
    {0x16, 0x184B},
    {0x18, 0x2E00},
    {0x1A, 0x0FF3},
    {0x1C, 0x02B6},
    {0x1E, 0xE000},
    {0x20, 0x1214},
    {0x22, 0x6C06},
    {0x24, 0x4000},
    {0x26, 0x099F},
    {0x28, 0x100F},
    {0x2A, 0x0000},
    {0x2C, 0x0880},
    {0x2E, 0x0000},
    {0x30, 0x48A0},
    {0x32, 0x2E56},
    {0x34, 0x04B4},
    {0x36, 0x0C80},
    {0x38, 0x0000},
    {0x3A, 0x1154},
    {0x3C, 0x0000},
    {0x3E, 0x0000},
    {0x40, 0x1000},
    {0x42, 0x0000},
    {0x44, 0x0000},
    {0x46, 0x0000},
    {0x48, 0x0000},
    {0x4A, 0x0000},
    {0x4C, 0x0000},
    {0x4E, 0x0000},
    {0x50, 0x0000},
    {0x52, 0x0000},
    {0x54, 0x0000},
    {0x56, 0x0000},
    {0x58, 0x0000},
    {0x5A, 0x0000},
    {0x5C, 0x0000},
    {0x5E, 0x0000},
    {0x60, 0x0000},
    {0x62, 0x0000},
    {0x64, 0x0000},
    {0x66, 0x0F4D},
    {0x68, 0xBC8E},
    {0x6A, 0x0000},
    {0x6C, 0x0000},
    {0x6E, 0x0000},
    {0x70, 0x0000},
    {0x72, 0x0000},
    {0x74, 0x0000},
    {0x76, 0x0000},
    {0x78, 0x0000},
    {0x7A, 0x0000},
    {0x7C, 0x0000},
    {0x7E, 0xEEAC},
};
#endif

#if 0
{   // M4
    {0x00, 0x75CA},
    {0x02, 0x0022},
    {0x04, 0x00D9},
    {0x06, 0xE800},
    {0x08, 0x0000},
    {0x0A, 0x0000},
    {0x0C, 0x0000},
    {0x0E, 0x0000},
    {0x10, 0x0000},
    {0x12, 0x0000},
    {0x14, 0x0000},
    {0x16, 0x144A},
    {0x18, 0x2E00},
    {0x1A, 0x0FF3},
    {0x1C, 0x02AB},
    {0x1E, 0xD600},
    {0x20, 0x1214},
    {0x22, 0x6C06},
    {0x24, 0x4000},
    {0x26, 0x099F},
    {0x28, 0x100F},
    {0x2A, 0x0000},
    {0x2C, 0x0880},
    {0x2E, 0x0000},
    {0x30, 0x48A0},
    {0x32, 0x2E56},
    {0x34, 0x04B4},
    {0x36, 0x0C80},
    {0x38, 0x0000},
    {0x3A, 0x1154},
    {0x3C, 0x0000},
    {0x3E, 0x0000},
    {0x40, 0x1000},
    {0x42, 0x0000},
    {0x44, 0x0000},
    {0x46, 0x0000},
    {0x48, 0x0000},
    {0x4A, 0x0000},
    {0x4C, 0x0000},
    {0x4E, 0x0000},
    {0x50, 0x0000},
    {0x52, 0x0000},
    {0x54, 0x0000},
    {0x56, 0x0000},
    {0x58, 0x0000},
    {0x5A, 0x0000},
    {0x5C, 0x0000},
    {0x5E, 0x0000},
    {0x60, 0x0000},
    {0x62, 0x0000},
    {0x64, 0x0000},
    {0x66, 0x0F4D},
    {0x68, 0xBC8E},
    {0x6A, 0xFC54},
    {0x6C, 0x0000},
    {0x6E, 0x0000},
    {0x70, 0x0000},
    {0x72, 0x0000},
    {0x74, 0x0000},
    {0x76, 0x0000},
    {0x78, 0x0000},
    {0x7A, 0x0000},
    {0x7C, 0x0000},
    {0x7E, 0x8FC2},
};
#endif

#if 1
// From Claus's document;
{
    {0x00, 0xB197},	// SER0;
    {0x02, 0x0030},	// SER1;
    {0x04, 0x07D9},
    {0x06, 0xE500},
    {0x08, 0x0003},
    {0x0A, 0x0000},	
    {0x0C, 0x0000},
    {0x0E, 0x0000},
    {0x10, 0x0000},
    {0x12, 0x0000},
    {0x14, 0x0000},
    {0x16, 0x1E54},
    {0x18, 0x2E00},
    {0x1A, 0x0FD3},
    {0x1C, 0x029B},
    {0x1E, 0x4E00},
    {0x20, 0x12D6},
    {0x22, 0x6C06},
    {0x24, 0xF000},
    {0x26, 0x099F},
    {0x28, 0x100F},
    {0x2A, 0x0001},
    {0x2C, 0x0880},
    {0x2E, 0x0000},
    {0x30, 0x78D4},
    {0x32, 0x1452},
    {0x34, 0x029D},
    {0x36, 0x0C80},
    {0x38, 0x1B87},
    {0x3A, 0x1154},
    {0x3C, 0x0000},
    {0x3E, 0x0000},
    {0x40, 0x1000},
    {0x42, 0x0000},
    {0x44, 0x0000},
    {0x46, 0x0000},
    {0x48, 0x0000},
    {0x4A, 0x0000},
    {0x4C, 0x0000},
    {0x4E, 0x0000},
    {0x50, 0x0000},
    {0x52, 0x0000},
    {0x54, 0x0000},
    {0x56, 0x0000},
    {0x58, 0x0000},
    {0x5A, 0x0000},
    {0x5C, 0x0000},
    {0x5E, 0x0000},
    {0x60, 0x0000},
    {0x62, 0x0000},
    {0x64, 0x0000},
    {0x66, 0x0F4D},
    {0x68, 0xBC8E},
    {0x6A, 0xFC54},
    {0x6C, 0x0000},
    {0x6E, 0x0000},
    {0x70, 0x0000},
    {0x72, 0x0000},
    {0x74, 0x0000},
    {0x76, 0x0000},
    {0x78, 0x0000},
    {0x7A, 0x0000},
    {0x7C, 0x0000},
    {0x7E, 0x2E54},	//CRC16;
};

#endif


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


uint8_t Usr_Is_RegAddr(uint8_t addr)
{
    // Odd number is wrong;
    if((addr&0x01) == 1)
    {
        return 0;
    }
    
    // For even number;
    if((addr==0x20)||(addr==0x24))
    {
        return 0;
    }
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
    if(addr>0xE4)
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

uint8_t Usr_Is_CMAddr_FCT(uint8_t addr)
{
    // Odd number is wrong;
    if((addr&0x01) == 1)
    {
        return 0;
    }
    
    if(addr>0x2E)
    {
        return 0;
    }
    
    return 1;
}

uint8_t Usr_Is_CMAddr_Usr(uint8_t addr)
{
    // Odd number is wrong;
    if((addr&0x01) == 1)
    {
        return 0;
    }
    
    if((addr>=0x3C)&&(addr<=0x7E))
    {
        return 1;
    }
    
    return 0;
}

uint8_t Usr_GetIndex_Reg(uint8_t addr)
{
    uint8_t i;
    
    if(1 == Usr_Is_RegAddr(addr))
    {
        return 0xFF;
    }
    
    for(i=0;i<DEF_REG_DATA_NUM;i++)
    {
        if(E703_RegData[i].addr == addr)
        {
            break;
        }
    }
    
    return i;
}

uint8_t Usr_GetIndex_CM(uint8_t addr)
{
    uint8_t i;
    
    if(1 == Usr_Is_CMAddr(addr))
    {
        return 0xFF;
    }
    
    for(i=0;i<DEF_CM_DATA_NUM;i++)
    {
        if(E703_CMData_Init[i].addr == addr)
        {
            break;
        }
    }
    
    return i;
}



uint8_t Usr_RegToCM_Addr(uint8_t addr)
{
    if(1==Usr_Is_RegAddr(addr))
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


uint8_t Usr_E703_ReadReg(uint8_t addr,uint16_t *ptr)    // OK;
{
    uint8_t i;
    
    if(1 == Usr_Is_RegAddr(addr))
    {
        i2c20_wtbuf[0] = addr;
        
        for(i=0;i<10;i++)
        {
            i2c20_rdbuf[i] = 0xFF;
        }
        
        if(0 == i2c_burst_read(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_rdbuf, 2))
        {
            *ptr = i2c20_rdbuf[1];
            *ptr <<= 8;
            *ptr += i2c20_rdbuf[0];
            
            return 1;
        }
        else
        {
            return 0;
        }
    }
    
    return 0;
}

uint8_t Usr_E703_WriteReg(uint8_t addr,uint16_t data)   // OK;
{
    // uint8_t i;
    
    if(1 == Usr_Is_RegAddr(addr))
    {   
        // Unlocking;
        // 0xF75A,0x0CC7,0xD21E;
        i2c20_wtbuf[0] = 0x22;
        i2c20_wtbuf[1] = 0x5A;
        i2c20_wtbuf[2] = 0xF7;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
        i2c20_wtbuf[0] = 0x22;
        i2c20_wtbuf[1] = 0xC7;
        i2c20_wtbuf[2] = 0x0C;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
        i2c20_wtbuf[0] = 0x22;
        i2c20_wtbuf[1] = 0x1E;
        i2c20_wtbuf[2] = 0xD2;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
        i2c20_wtbuf[0] = addr;
        i2c20_wtbuf[1] = data;
        i2c20_wtbuf[2] = data>>8;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
        // Locking;
        // 0x62A2;
        i2c20_wtbuf[0] = 0x22;
        i2c20_wtbuf[1] = 0xA2;
        i2c20_wtbuf[2] = 0x62;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
    }
    
    return 0;
}


uint8_t Usr_E703_ReadCM(uint8_t addr,uint16_t *ptr)     //
{
    uint8_t rtn = 0;
    uint8_t i;
    
    if(1 == Usr_Is_CMAddr(addr))
    {
        // Unlocking;
        // 0xF75A,0x0CC7,0xD21E;
        i2c20_wtbuf[0] = 0x22;
        i2c20_wtbuf[1] = 0x5A;
        i2c20_wtbuf[2] = 0xF7;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
        i2c20_wtbuf[0] = 0x22;
        i2c20_wtbuf[1] = 0xC7;
        i2c20_wtbuf[2] = 0x0C;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
        i2c20_wtbuf[0] = 0x22;
        i2c20_wtbuf[1] = 0x1E;
        i2c20_wtbuf[2] = 0xD2;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
        
        i2c20_wtbuf[0] = 0x4E;
        i2c20_wtbuf[1] = addr;
        i2c20_wtbuf[2] = 0x4C;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
        
        i2c20_wtbuf[0] = 0x48;
        for(i=0;i<10;i++)
        {
            i2c20_rdbuf[i] = 0xFF;
        }
        if(0 == i2c_burst_read(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_rdbuf, 2))
        {
            *ptr = i2c20_rdbuf[1];
            *ptr <<= 8;
            *ptr += i2c20_rdbuf[0];
            
            rtn = 1;
        }
        else
        {
            rtn = 0;
        }
        
        
        // Locking;
        // 0x62A2;
        i2c20_wtbuf[0] = 0x22;
        i2c20_wtbuf[1] = 0xA2;
        i2c20_wtbuf[2] = 0x62;
        if(0 == i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2))
        {
            
        }
        else
        {
            
        }
    }
    
    return rtn;
}

uint8_t Usr_E703_WriteCM(uint8_t addr,uint16_t data)
{
    uint8_t rtn = 0;
    uint8_t i;
    
    if(1 == Usr_Is_CMAddr_Usr(addr))
    {
        // Unlocking;
        // 0xF75A,0x0CC7,0xD21E;
        i2c20_wtbuf[0] = 0x22;
        i2c20_wtbuf[1] = 0x5A;
        i2c20_wtbuf[2] = 0xF7;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
        i2c20_wtbuf[0] = 0x22;
        i2c20_wtbuf[1] = 0xC7;
        i2c20_wtbuf[2] = 0x0C;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
        i2c20_wtbuf[0] = 0x22;
        i2c20_wtbuf[1] = 0x1E;
        i2c20_wtbuf[2] = 0xD2;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
        // Unlocking;
        // 0x98BD,0x25BF,0x36D8;
        i2c20_wtbuf[0] = 0x4E;
        i2c20_wtbuf[1] = 0xBD;
        i2c20_wtbuf[2] = 0x98;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
        i2c20_wtbuf[0] = 0x4E;
        i2c20_wtbuf[1] = 0xBF;
        i2c20_wtbuf[2] = 0x25;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
        i2c20_wtbuf[0] = 0x4E;
        i2c20_wtbuf[1] = 0xD8;
        i2c20_wtbuf[2] = 0x36;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
        
        i2c20_wtbuf[0] = 0x4A;
        i2c20_wtbuf[1] = data;
        i2c20_wtbuf[2] = data>>8;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
        i2c20_wtbuf[0] = 0x4E;
        i2c20_wtbuf[1] = addr;
        i2c20_wtbuf[2] = 0xA3;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
        
        #if(defined(DEF_SOFT_ARCH)&&(DEF_SOFT_ARCH==DEF_FREERTOS))
        vTaskDelay(20);
        #endif
        
        
        #if(defined(DEF_SOFT_ARCH)&&(DEF_SOFT_ARCH==DEF_MAINLOOP))
        Usr_E307_Timestamp = 20;
        while(Usr_E307_Timestamp>0)
        {
            ;
        }
        #endif
        
        
        // Locking;
        // 0x62A2;
        i2c20_wtbuf[0] = 0x4E;
        i2c20_wtbuf[1] = 0x00;
        i2c20_wtbuf[2] = 0x00;
        if(0 == i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2))
        {
            
        }
        else
        {
            
        }
        
        // Locking;
        // 0x62A2;
        i2c20_wtbuf[0] = 0x22;
        i2c20_wtbuf[1] = 0xA2;
        i2c20_wtbuf[2] = 0x62;
        if(0 == i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2))
        {
            
        }
        else
        {
            
        }
        
    }
    
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


