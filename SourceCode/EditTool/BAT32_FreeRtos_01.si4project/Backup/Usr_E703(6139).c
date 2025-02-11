#ifndef __USR_E703_C__
#define __USR_E703_C__

#include <stdint.h>

#include <stdio.h>

#include "Usr_Config.h"

#include"Usr_Uart.h"

#include"gpio.h"

#include "Usr_Debug.h"

#include "Usr_E703.h"

#include "Usr_Soft_I2C.h"

#include "Usr_I2C.h"

#include "tima.h"

#include "Usr_Modbus.h"


unsigned short E703_RegBuff[DEF_REG_DATA_NUM];

unsigned short E703_CMBuff[DEF_CM_DATA_NUM];


#if(defined(DEF_SENSOR_E703_EN)&&(DEF_SENSOR_E703_EN==1))


uint16_t E703_CMD;
uint16_t E703_ADC_TC;
uint16_t E703_ADC_T;
uint16_t E703_ADC_S;
uint16_t E703_DSP_T;
uint16_t E703_DSP_S;
uint16_t E703_Status_sync;
uint16_t E703_Status;
uint16_t E703_ChipVersion;
uint16_t E703_CM_Status;


volatile uint32_t Usr_E307_Timestamp;
uint8_t Register_Lock = 1;
uint8_t CM_Usr_Lock = 1;
uint8_t CM_FCT_Lock = 1;



uint8_t Buff_U8[DEF_CM_DATA_NUM*2];
ADDR_DATA_ST E703_RegData[DEF_REG_DATA_NUM];
ADDR_DATA_ST E703_CMData_Probe[DEF_CM_DATA_NUM];
const ADDR_DATA_ST E703_CMData_Init[DEF_CM_DATA_NUM] = 
#if 0
{
    {0x00, 0x0001},
    {0x02, 0x0001},
    {0x04, 0x0001},
    {0x06, 0x0001},
    {0x08, 0x0001},
    {0x0A, 0x0001},
    {0x0C, 0x0001},
    {0x0E, 0x0001},
    {0x10, 0x0001},
    {0x12, 0x0001},
    {0x14, 0x0001},
    {0x16, 0x0001},
    {0x18, 0x0001},
    {0x1A, 0x0001},
    {0x1C, 0x0001},
    {0x1E, 0x0001},
    {0x20, 0x0001},
    {0x22, 0x0001},
    {0x24, 0x0001},
    {0x26, 0x0001},
    {0x28, 0x0001},
    {0x2A, 0x0001},
    {0x2C, 0x0001},
    {0x2E, 0x0001},
    {0x30, 0x0001},
    {0x32, 0x0001},
    {0x34, 0x0001},
    {0x36, 0x0001},
    {0x38, 0x0001},
    {0x3A, 0x0001},
    {0x3C, 0x0001},
    {0x3E, 0x0001},
    {0x40, 0x0001},
    {0x42, 0x0001},
    {0x44, 0x0001},
    {0x46, 0x0001},
    {0x48, 0x0001},
    {0x4A, 0x0001},
    {0x4C, 0x0001},
    {0x4E, 0x0001},
    {0x50, 0x0001},
    {0x52, 0x0001},
    {0x54, 0x0001},
    {0x56, 0x0001},
    {0x58, 0x0001},
    {0x5A, 0x0001},
    {0x5C, 0x0001},
    {0x5E, 0x0001},
    {0x60, 0x0001},
    {0x62, 0x0001},
    {0x64, 0x0001},
    {0x66, 0x0001},
    {0x68, 0x0001},
    {0x6A, 0x0001},
    {0x6C, 0x0001},
    {0x6E, 0x0001},
    {0x70, 0x0001},
    {0x72, 0x0001},
    {0x74, 0x0001},
    {0x76, 0x0001},
    {0x78, 0x0001},
    {0x7A, 0x0001},
    {0x7C, 0x0001},
    {0x7E, 0x0001},
};
#endif

#if 0
{
    {0x00, 0x0002},
    {0x02, 0x0002},
    {0x04, 0x0002},
    {0x06, 0x0002},
    {0x08, 0x0002},
    {0x0A, 0x0002},
    {0x0C, 0x0002},
    {0x0E, 0x0002},
    {0x10, 0x0002},
    {0x12, 0x0002},
    {0x14, 0x0002},
    {0x16, 0x0002},
    {0x18, 0x0002},
    {0x1A, 0x0002},
    {0x1C, 0x0002},
    {0x1E, 0x0002},
    {0x20, 0x0002},
    {0x22, 0x0002},
    {0x24, 0x0002},
    {0x26, 0x0002},
    {0x28, 0x0002},
    {0x2A, 0x0002},
    {0x2C, 0x0002},
    {0x2E, 0x0002},
    {0x30, 0x0002},
    {0x32, 0x0002},
    {0x34, 0x0002},
    {0x36, 0x0002},
    {0x38, 0x0002},
    {0x3A, 0x0002},
    {0x3C, 0x0002},
    {0x3E, 0x0002},
    {0x40, 0x0002},
    {0x42, 0x0002},
    {0x44, 0x0002},
    {0x46, 0x0002},
    {0x48, 0x0002},
    {0x4A, 0x0002},
    {0x4C, 0x0002},
    {0x4E, 0x0002},
    {0x50, 0x0002},
    {0x52, 0x0002},
    {0x54, 0x0002},
    {0x56, 0x0002},
    {0x58, 0x0002},
    {0x5A, 0x0002},
    {0x5C, 0x0002},
    {0x5E, 0x0002},
    {0x60, 0x0002},
    {0x62, 0x0002},
    {0x64, 0x0002},
    {0x66, 0x0002},
    {0x68, 0x0002},
    {0x6A, 0x0002},
    {0x6C, 0x0002},
    {0x6E, 0x0002},
    {0x70, 0x0002},
    {0x72, 0x0002},
    {0x74, 0x0002},
    {0x76, 0x0002},
    {0x78, 0x0002},
    {0x7A, 0x0002},
    {0x7C, 0x0002},
    {0x7E, 0x0002},
};
#endif

#if 0
{
    {0x00, 0x0003},
    {0x02, 0x0003},
    {0x04, 0x0003},
    {0x06, 0x0003},
    {0x08, 0x0003},
    {0x0A, 0x0003},
    {0x0C, 0x0003},
    {0x0E, 0x0003},
    {0x10, 0x0003},
    {0x12, 0x0003},
    {0x14, 0x0003},
    {0x16, 0x0003},
    {0x18, 0x0003},
    {0x1A, 0x0003},
    {0x1C, 0x0003},
    {0x1E, 0x0003},
    {0x20, 0x0003},
    {0x22, 0x0003},
    {0x24, 0x0003},
    {0x26, 0x0003},
    {0x28, 0x0003},
    {0x2A, 0x0003},
    {0x2C, 0x0003},
    {0x2E, 0x0003},
    {0x30, 0x0003},
    {0x32, 0x0003},
    {0x34, 0x0003},
    {0x36, 0x0003},
    {0x38, 0x0003},
    {0x3A, 0x0003},
    {0x3C, 0x0003},
    {0x3E, 0x0003},
    {0x40, 0x0003},
    {0x42, 0x0003},
    {0x44, 0x0003},
    {0x46, 0x0003},
    {0x48, 0x0003},
    {0x4A, 0x0003},
    {0x4C, 0x0003},
    {0x4E, 0x0003},
    {0x50, 0x0003},
    {0x52, 0x0003},
    {0x54, 0x0003},
    {0x56, 0x0003},
    {0x58, 0x0003},
    {0x5A, 0x0003},
    {0x5C, 0x0003},
    {0x5E, 0x0003},
    {0x60, 0x0003},
    {0x62, 0x0003},
    {0x64, 0x0003},
    {0x66, 0x0003},
    {0x68, 0x0003},
    {0x6A, 0x0003},
    {0x6C, 0x0003},
    {0x6E, 0x0003},
    {0x70, 0x0003},
    {0x72, 0x0003},
    {0x74, 0x0003},
    {0x76, 0x0003},
    {0x78, 0x0003},
    {0x7A, 0x0003},
    {0x7C, 0x0003},
    {0x7E, 0x0003},
};
#endif

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

#if 0
// From Claus's document;
{
    {0x00, 0xB197},     // SER0;
    {0x02, 0x0030},     // SER1;
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
    {0x7E, 0x2E54},     //CRC16;
};

#endif

































#if 1
// From HuangGong Sets1;
{
    {0x00, 0x51F8},  // ADDR=0x00, SER0
    {0x02, 0x00D1},  // ADDR=0x02, SER1
    {0x04, 0x00DE},  // ADDR=0x04, RATIO_DAC01
    {0x06, 0xE100},  // ADDR=0x06, RATIO_DAC23
    {0x08, 0x000A},  // ADDR=0x08, RATIO_DAC45
    {0x0A, 0xFFFF},  // ADDR=0x0A, ABS_V_DAC01
    {0x0C, 0xD2CC},  // ADDR=0x0C, ABS_V_DAC01
    {0x0E, 0xEEFA},  // ADDR=0x0E, ABS_V_DAC01
    {0x10, 0x0440},  // ADDR=0x10, ABS_I_DAC01
    {0x12, 0x0021},  // ADDR=0x12, ABS_I_DAC01
    {0x14, 0x0001},  // ADDR=0x14, ABS_I_DAC01
    {0x16, 0xD200},  // ADDR=0x16, G01
    {0x18, 0x2A00},  // ADDR=0x18, G2OFF
    {0x1A, 0x0ED3},  // ADDR=0x1A, CAL0
    {0x1C, 0x02B3},  // ADDR=0x1C, CAL1
    {0x1E, 0x8E00},  // ADDR=0x1E, FT_CRC8
    {0x20, 0x12D6},  // ADDR=0x20, CFG_EN
    {0x22, 0x6C06},  // ADDR=0x22, CFG_SPI_I2C
    {0x24, 0xF000},  // ADDR=0x24, CFG_PADS0
    {0x26, 0x099F},  // ADDR=0x26, CFG_PADS1
    {0x28, 0x100F},  // ADDR=0x28, CFG_PADS2
    {0x2A, 0x0001},  // ADDR=0x2A, CFG_PERIOD
    {0x2C, 0x0880},  // ADDR=0x2C, CFG_AODO
    {0x2E, 0x0000},  // ADDR=0x2E, CFG_SBC_INTF
    {0x30, 0x78D4},  // ADDR=0x30, CFG_ADC
    {0x32, 0x1452},  // ADDR=0x32, CFG_LP0
    {0x34, 0x029D},  // ADDR=0x34, CFG_LP1
    {0x36, 0x0C80},  // ADDR=0x36, CFG_AFE0
    {0x38, 0x0B47},  // ADDR=0x38, CFG_AFE1
    {0x3A, 0x1154},  // ADDR=0x3A, CFG_AFE2
    {0x3C, 0x0000},  // ADDR=0x3C, USER
    {0x3E, 0x0000},  // ADDR=0x3E, T_O
    {0x40, 0x1000},  // ADDR=0x40, T_F
    {0x42, 0x0000},  // ADDR=0x42, S_O
    {0x44, 0x0000},  // ADDR=0x44, S_F
    {0x46, 0x0000},  // ADDR=0x46, S0
    {0x48, 0x0000},  // ADDR=0x48, S1
    {0x4A, 0x0000},  // ADDR=0x4A, S2
    {0x4C, 0x0000},  // ADDR=0x4C, S3
    {0x4E, 0x0000},  // ADDR=0x4E, S4
    {0x50, 0x0000},  // ADDR=0x50, S5
    {0x52, 0x0000},  // ADDR=0x52, S6
    {0x54, 0x0000},  // ADDR=0x54, S7
    {0x56, 0x0000},  // ADDR=0x56, S8
    {0x58, 0x0000},  // ADDR=0x58, S9
    {0x5A, 0x0000},  // ADDR=0x5A, S10
    {0x5C, 0x0000},  // ADDR=0x5C, S11
    {0x5E, 0x0000},  // ADDR=0x5E, S12
    {0x60, 0x0000},  // ADDR=0x60, S13
    {0x62, 0x0000},  // ADDR=0x62, S14
    {0x64, 0x0000},  // ADDR=0x64, S15
    {0x66, 0x0F4D},  // ADDR=0x66, T0
    {0x68, 0xBC8E},  // ADDR=0x68, T1
    {0x6A, 0xFC54},  // ADDR=0x6A, T2
    {0x6C, 0x0000},  // ADDR=0x6C, T3
    {0x6E, 0x0000},  // ADDR=0x6E, ALARM_LO
    {0x70, 0x0000},  // ADDR=0x70, ALARM_HI
    {0x72, 0x0000},  // ADDR=0x72, AODO_O
    {0x74, 0x0000},  // ADDR=0x74, AODO_F
    {0x76, 0x0000},  // ADDR=0x76, LIMIT_LO
    {0x78, 0x0000},  // ADDR=0x78, LIMIT_HI
    {0x7A, 0x0000},  // ADDR=0x7A, ERR_MASK
    {0x7C, 0x0000},  // ADDR=0x7C, ERR_VAL_HI_LO
    {0x7E, 0xCCE2},  // ADDR=0x7E, CRC16
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
    
    if((addr>=0x20)&&(addr<=0x7E))
    //if((addr>=0x3C)&&(addr<=0x7E))
    {
        return 1;
    }
    
    return 0;
}

uint8_t Usr_GetIndex_Reg(uint8_t addr)
{
    uint8_t i;
    
    if(0 == Usr_Is_RegAddr(addr))
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
    
    if(0 == Usr_Is_CMAddr(addr))
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
    if(1 == Usr_Is_RegAddr(addr))
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


uint8_t Usr_E703_UnlockReg(void)
{
    
    #if 1
    if(Register_Lock == 1)
    {
        // Unlocking Register;
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
        #endif
    }
    
    Register_Lock = 0;
    
    return 0;
}

uint8_t Usr_E703_LockReg(void)
{
    
    #if 1
    if(Register_Lock == 0)
    {
        // Locking Register;
        // 0x62A2;
        i2c20_wtbuf[0] = 0x22;
        i2c20_wtbuf[1] = 0xA2;
        i2c20_wtbuf[2] = 0x62;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        #endif
    }
    
    Register_Lock = 1;
    
    return 0;
}

uint8_t Usr_E703_UnlockCMUsr(void)
{
    
    #if 1
    if(CM_Usr_Lock == 1)
    {
        // Unlocking CM_Usr area;
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
        #endif
    }
    
    CM_Usr_Lock = 0;
    
    return 0;
}

uint8_t Usr_E703_LockCMUsr(void)
{
    
    if(CM_Usr_Lock == 0)
    {
        #if 1
        
        // Locking CM_Usr area;
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
        #endif
    }
    
    CM_Usr_Lock = 1;
    
    return 0;
}


uint8_t Usr_E703_UnlockCMFCT(void)
{
    
    #if 1
    if(CM_FCT_Lock == 1)
    {
        // Unlocking CM_FCT;
        // 0x8218,0xF75F,0xB5B2;
        i2c20_wtbuf[0] = 0x4E;
        i2c20_wtbuf[1] = 0x18;
        i2c20_wtbuf[2] = 0x82;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
        i2c20_wtbuf[0] = 0x4E;
        i2c20_wtbuf[1] = 0x5F;
        i2c20_wtbuf[2] = 0xF7;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
        i2c20_wtbuf[0] = 0x4E;
        i2c20_wtbuf[1] = 0xB2;
        i2c20_wtbuf[2] = 0xB5;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        #endif
    }
    
    CM_FCT_Lock = 0;
    
    return 0;
}

uint8_t Usr_E703_LockCMFCT(void)
{
    
    if(CM_FCT_Lock == 0)
    {
        #if 1
        
        // Locking CM_FCT;
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
        #endif
    }
    
    CM_FCT_Lock = 1;
    
    return 0;
}



uint8_t Usr_E703_WriteReg(uint8_t addr,uint16_t data)   // OK;
{
    // uint8_t i;
    
    if(1 == Usr_Is_RegAddr(addr))
    {   
        #if 0
        // Unlocking Register;
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
        #endif
        
        Usr_E703_UnlockReg();
        
        i2c20_wtbuf[0] = addr;
        i2c20_wtbuf[1] = data;
        i2c20_wtbuf[2] = data>>8;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
        #if 0
        // Locking Register;
        // 0x62A2;
        i2c20_wtbuf[0] = 0x22;
        i2c20_wtbuf[1] = 0xA2;
        i2c20_wtbuf[2] = 0x62;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        #endif
        
        //Usr_E703_LockReg();
        
    }
    
    return 0;
}


uint8_t Usr_E703_ReadCM(uint8_t addr,uint16_t *ptr)     //
{
    uint8_t rtn = 0;
    uint8_t i;
    
    if(1 == Usr_Is_CMAddr(addr))
    {
        #if 0
        // Unlocking Register;
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
        #endif
        
        Usr_E703_UnlockReg();
        
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
        
        #if 0
        // Locking Register;
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
        #endif
        
        //Usr_E703_LockReg();
    }
    
    return rtn;
}


uint16_t Usr_E703_CRC(uint16_t crc_length, uint16_t crc_polynomial, uint16_t crc_value, uint16_t* data, uint32_t number_of_bits)
{
    uint16_t crc_bit;
    uint16_t data_bit;
    
    for (int i = 0; i < number_of_bits; i++)
    {
        crc_bit = (crc_value >> (crc_length - 1)) & 0x0001;
        data_bit = (data[i >> 4] >> (crc_length - 1 - (i % 16))) & 0x0001;
        if (crc_bit != data_bit)
        {
            crc_value = (crc_value << 1) ^ crc_polynomial;
        }
        else
        {
            crc_value = crc_value << 1;
        }
    }
    return crc_value & (~(0xFFFF << crc_length)); 
}


#define DEF_E703_WRITE_DELAY_TIME   1

uint8_t Usr_E703_WriteCMUsr(uint8_t addr,uint16_t data)
{
    //uint8_t rtn = 0;
    //uint8_t i;
    
    if(1 == Usr_Is_CMAddr_Usr(addr))
    {
        #if 0
        // Unlocking Regsiter;
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
        #endif
        Usr_E703_UnlockReg();
        
        #if 0
        // Unlocking CM_Usr area;
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
        #endif
        Usr_E703_UnlockCMUsr();
        
        i2c20_wtbuf[0] = 0x4A;
        i2c20_wtbuf[1] = data;
        i2c20_wtbuf[2] = data>>8;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
        i2c20_wtbuf[0] = 0x4E;
        i2c20_wtbuf[1] = addr;
        i2c20_wtbuf[2] = 0xA3;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
        
        #if(defined(DEF_SOFT_ARCH)&&(DEF_SOFT_ARCH==DEF_FREERTOS))
        vTaskDelay(DEF_E703_WRITE_DELAY_TIME);
        #endif
        
        
        #if(defined(DEF_SOFT_ARCH)&&(DEF_SOFT_ARCH==DEF_MAINLOOP))
        Usr_E307_Timestamp = DEF_E703_WRITE_DELAY_TIME;
        while(Usr_E307_Timestamp>0)
        {
            ;
        }
        #endif
        
        
        #if 0
        // Locking CM_Usr area;
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
        #endif
        //Usr_E703_LockCMUsr();
        
        #if 0
        // Locking Register;
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
        #endif
        //Usr_E703_LockReg();
    }
    
    return 0;
}

uint8_t Usr_E703_WriteCMFCT(uint8_t addr,uint16_t data)

{
    if(1 == Usr_Is_CMAddr_FCT(addr))
    {
        Usr_E703_UnlockReg();
        
        Usr_E703_UnlockCMFCT();
        
        i2c20_wtbuf[0] = 0x4A;
        i2c20_wtbuf[1] = data;
        i2c20_wtbuf[2] = data>>8;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
        i2c20_wtbuf[0] = 0x4E;
        i2c20_wtbuf[1] = addr;
        i2c20_wtbuf[2] = 0xA3;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
        
        #if(defined(DEF_SOFT_ARCH)&&(DEF_SOFT_ARCH==DEF_FREERTOS))
        vTaskDelay(DEF_E703_WRITE_DELAY_TIME);
        #endif
        
        
        #if(defined(DEF_SOFT_ARCH)&&(DEF_SOFT_ARCH==DEF_MAINLOOP))
        Usr_E307_Timestamp = DEF_E703_WRITE_DELAY_TIME;
        while(Usr_E307_Timestamp>0)
        {
            ;
        }
        #endif
        
        
        //Usr_E703_LockCMFCT();
        
        //Usr_E703_LockReg();
    }
    
    return 0;
}

uint8_t Usr_E703_WriteCM(uint8_t addr,uint16_t data)
{
    //uint8_t rtn = 0;
    //uint8_t i;
    
    if(1 == Usr_Is_CMAddr_Usr(addr))
    {
        #if 0
        // Unlocking Regsiter;
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
        #endif
        Usr_E703_UnlockReg();
        
        #if 0
        // Unlocking CM_Usr area;
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
        #endif
        Usr_E703_UnlockCMUsr();
        
        i2c20_wtbuf[0] = 0x4A;
        i2c20_wtbuf[1] = data;
        i2c20_wtbuf[2] = data>>8;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
        i2c20_wtbuf[0] = 0x4E;
        i2c20_wtbuf[1] = addr;
        i2c20_wtbuf[2] = 0xA3;
        i2c_burst_write(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_wtbuf+1,2);
        
        
        #if(defined(DEF_SOFT_ARCH)&&(DEF_SOFT_ARCH==DEF_FREERTOS))
        vTaskDelay(DEF_E703_WRITE_DELAY_TIME);
        #endif
        
        
        #if(defined(DEF_SOFT_ARCH)&&(DEF_SOFT_ARCH==DEF_MAINLOOP))
        Usr_E307_Timestamp = DEF_E703_WRITE_DELAY_TIME;
        while(Usr_E307_Timestamp>0)
        {
            ;
        }
        #endif
        
        
        #if 0
        // Locking CM_Usr area;
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
        #endif
        //Usr_E703_LockCMUsr();
        
        #if 0
        // Locking Register;
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
        #endif
        //Usr_E703_LockReg();
    }
    
    return 0;
}

uint16_t Usr_E703_CRC8_Init(void)
{
    #if 0
    Cover Addr0x00 to Addr0x1E;
    Polynomial CRC8: 0x07 (x8 + x2+ x1 + x0)
    Polynomial CRC16: 0x8005 (x16 + x15+ x2 + x0)
    The initial CRC value is 0xFF for CRC8 and 0xFFFF for CRC16 and its computed with no reflection.
    #endif
    
    
    //uint8_t crc8(uint8_t *data, uint_len length)
    {
        uint8_t i;
        uint8_t crc = 0xFF;        // Initial value
        uint16_t length = 15;
        uint8_t *data;
        
        for(i=0;i<DEF_CM_DATA_NUM;i++)
        {
            Buff_U8[i*2+0] = (uint8_t)E703_CMData_Init[i].data;
            Buff_U8[i*2+1] = (uint8_t)(E703_CMData_Init[i].data>>8);
        }
        data = Buff_U8;
        
        while(length--)
        {
            crc ^= *data++;        // crc ^= *data; data++;
            for ( i = 0; i < 8; i++ )
            {
                if ( crc & 0x80 )
                    crc = (crc << 1) ^ 0x07;
                else
                    crc <<= 1;
            }
        }
        return crc;
    }
}
uint16_t Usr_E703_CRC16_Init(void)
{
    #if 0
    Cover Addr0x00 to Addr0x7C;
    Polynomial CRC8: 0x07 (x8 + x2+ x1 + x0)
    Polynomial CRC16: 0x8005 (x16 + x15+ x2 + x0)
    The initial CRC value is 0xFF for CRC8 and 0xFFFF for CRC16 and its computed with no reflection.
    #endif
    
    //uint16_t crc16_ccitt_false(uint8_t *data, uint_len length)
    {
        uint8_t i;
        uint16_t crc = 0xffff;        //Initial value
        uint16_t length = 63;
        uint8_t *data;
        
        for(i=0;i<DEF_CM_DATA_NUM;i++)
        {
            Buff_U8[i*2+0] = (uint8_t)E703_CMData_Init[i].data;
            Buff_U8[i*2+1] = (uint8_t)(E703_CMData_Init[i].data>>8);
        }
        data = Buff_U8;
        
        while(length--)
        {
            crc ^= (uint16_t)(*data++) << 8; // crc ^= (uint6_t)(*data)<<8; data++;
            for (i = 0; i < 8; ++i)
            {
                if ( crc & 0x8000 )
                    //crc = (crc << 1) ^ 0x1021;
                    crc = (crc << 1) ^ 0x8005;
                else
                    crc <<= 1;
            }
        }
        return crc;
    }
}

void Usr_Read_All_Reg(void)
{
    uint8_t addr;
    uint16_t data;
    uint8_t i = 0;
    
    // Read All Registers;
    Init_printf("\n\nE703 Read all registers From Probe. ");
    for(addr = 0x00;addr<0xF0;addr+=2)
    {
        if(0 == Usr_Is_RegAddr(addr))
        {
            continue;
        }
        data = 0xFFFF;
        if(1 == Usr_E703_ReadReg(addr,&data))
        {
            // Debug_printf("\nE703.11 Reg[0x%02X], 0x%04X,",addr,data);
            E703_RegData[i].addr = addr;
            E703_RegData[i].data = data;
            i++;
        }
        else
        {
            Init_printf("\nE703.11 Register[0x%02X], Error1,",addr);
        }
    }
    
    {
        Init_printf("\nE703_RegData[DEF_REG_DATA_NUM] = \n{");
        for(i=0;i<DEF_REG_DATA_NUM;i++)
        {
            Init_printf("\n    {0x%02X, 0x%04X},",E703_RegData[i].addr,E703_RegData[i].data);
        }
        Init_printf("\n};\n");
        
    }
    
    #if 1
    for(i=0;i<DEF_REG_DATA_NUM;i++)
    {
        E703_RegBuff[i] = E703_RegData[i].data;
    }
    #endif
}

void Usr_Read_All_CM(void)
{
    uint8_t addr;
    uint16_t data;
    uint8_t i = 0;
    
    // Read All CM area;
    Init_printf("\n\nE703 Read all CM From Probe. ");
    i = 0;
    
    Usr_E703_UnlockReg();
    
    for(addr = 0x00;addr<0xF0;addr+=2)
    {   
        if(0 == Usr_Is_CMAddr(addr))
        {
            continue;
        }
        
        data = 0xFFFF;
        if(1 == Usr_E703_ReadCM(addr,&data))
        {
            //Debug_printf("\nE703.11 CM[0x%02X], 0x%04X,",addr,data);
            E703_CMData_Probe[i].addr = addr;
            E703_CMData_Probe[i].data = data;
            i++;
        }
        else
        {
            Init_printf("\nE703.11 CM[0x%02X], Error1,",addr);
        }
    }
    
    Usr_E703_LockReg();
    
    {
        Init_printf("\nE703_CMData[DEF_CM_DATA_NUM] = \n{");
        for(i=0;i<DEF_CM_DATA_NUM;i++)
        {
            Init_printf("\n    {0x%02X, 0x%04X},",E703_CMData_Probe[i].addr,E703_CMData_Probe[i].data);
        }
        Init_printf("\n};\n");
        
    }
    
    for(i=0;i<DEF_CM_DATA_NUM;i++)
    {
        Buff_U8[i*2+0] = (uint8_t)E703_CMData_Probe[i].data;
        Buff_U8[i*2+1] = (uint8_t)(E703_CMData_Probe[i].data>>8);
    }
    
    {
        uint16_t crc16 = 0;
        
        crc16 = Usr_E703_CRC(16,0x8005,0xFFFF,(uint16_t*)Buff_U8,63*16);
        
        Init_printf("\nCalculate the CRC16 of above data is 0x%04X.\n",crc16);
    }
    
    
    #if 1
    for(i=0;i<DEF_CM_DATA_NUM;i++)
    {
        E703_CMBuff[i] = E703_CMData_Probe[i].data;
    }
    #endif
}

void Usr_Read_All_Claus(void)
{
    unsigned char i;
    uint8_t tmp_crc8;
    uint16_t tmp_crc16;
    uint8_t tmp_index;
    uint16_t cm_crc;
    
    {
    Debug_printf("\nE703.11 CM Data From Claus parameters. \n{");
    for(i=0;i<DEF_CM_DATA_NUM;i++)
    {
        Debug_printf("\n    {0x%02X, 0x%04X},",E703_CMData_Init[i].addr,E703_CMData_Init[i].data);
        //Debug_printf("\n    {0x%02X, 0x%04X},",E703_CMData_Init[i].addr,1);
    }
    Debug_printf("\n};\n");
    
    }
    
    
    tmp_crc8 = Usr_E703_CRC8_Init();
    
    //tmp_crc16 = Usr_E703_CRC16_Init();
    
    tmp_crc16 = Usr_E703_CRC(16,0x8005,0xFFFF,(uint16_t*)Buff_U8,63*16);
    
    Debug_printf("\nThe CRC16 of above data is 0x%04X.\n",tmp_crc16);
    
    for(i=0;i<DEF_CM_DATA_NUM;i++)
    {
        Buff_U8[i*2+0] = (uint8_t)E703_CMData_Init[i].data;
        Buff_U8[i*2+1] = (uint8_t)(E703_CMData_Init[i].data>>8);
    }
    Debug_printf("\nCM data list for analysis CRC used online website.\n");
    for(i=0;i<DEF_CM_DATA_NUM*2;i++)
    {
        Debug_printf("%02X",Buff_U8[i]);
    }
    
    tmp_index = Usr_GetIndex_CM(0x1E);
    cm_crc = E703_CMData_Init[tmp_index].data;
    
    Debug_printf("\nCRC: CRC8 read from CM[0x1E] is 0x%04X. ",cm_crc);
    Debug_printf("\nCRC: CRC8 Calculate from CM[0x00] to CM[0x1C] is 0x%04X. ",tmp_crc8);
    
    tmp_index = Usr_GetIndex_CM(0x7E);
    cm_crc = E703_CMData_Init[tmp_index].data;
    
    Debug_printf("\nCRC: CRC16 read from CM[0x7E] is 0x%04X. ",cm_crc);
    Debug_printf("\nCRC: CRC16 Calculate from CM[0x00] to CM[0x7C] is 0x%04X. ",tmp_crc16);
}

void Usr_Write_CMUsr_Of_Claus(void)
{
    uint8_t addr;
    uint16_t data;
    uint8_t i = 0;
    uint8_t index;
    
    //for(i=0x20;i<0x7F;i++)
    for(i=0x20;i<0x7E;i++)
    {
        if(Usr_Is_CMAddr(i) == 1)
        {
            index = Usr_GetIndex_CM(i);
            addr = E703_CMData_Init[index].addr;
            data = E703_CMData_Init[index].data;
            Usr_E703_WriteCM(addr,data);
            Debug_printf("\nWrite CM[0x%02x] = 0x%04X. ",addr,data);
        }
    }
}

void Usr_Write_CMFCT_Of_Claus(void)
{
    uint8_t addr;
    uint16_t data;
    uint8_t i = 0;
    uint8_t index;
    
    for(i=0;i<0x20;i++)
    {
        if(Usr_Is_CMAddr(i) == 1)
        {
            index = Usr_GetIndex_CM(i);
            addr = E703_CMData_Init[index].addr;
            data = E703_CMData_Init[index].data;
            Usr_E703_WriteCM(addr,data);
            Debug_printf("\nWrite CM[0x%02x] = 0x%04X. ",addr,data);
        }
    }
    
}

void Usr_Write_All_Claus(void)
{
    #if 0
    uint8_t addr;
    uint16_t data;
    uint8_t i = 0;
    uint8_t index;
    
    for(i=0;i<0xF0;i++)
    {
        if(Usr_Is_CMAddr(i) == 1)
        {
            index = Usr_GetIndex_CM(i);
            addr = E703_CMData_Init[index].addr;
            data = E703_CMData_Init[index].data;
            Usr_E703_WriteCM(addr,data);
            Debug_printf("\nWrite Claus parameter CM[0x%02x] to 0x%04X. ",addr,data);
        }
    }
    #endif
    
    Usr_Write_CMUsr_Of_Claus();
    
    Usr_Write_CMFCT_Of_Claus();
}


uint8_t Usr_E703_ReadData(void)
{
    
    uint8_t rtn;
    uint16_t tmp1;
    
    
    rtn = Usr_E703_ReadReg(DEF_REGADDR_CMD,&tmp1);
    if(rtn == 1)
    {
        E703_CMD = tmp1;
    }
    
    rtn = Usr_E703_ReadReg(DEF_REGADDR_ADC_TC,&tmp1);
    if(rtn == 1)
    {
        E703_ADC_TC = tmp1;
    }
    
    rtn = Usr_E703_ReadReg(DEF_REGADDR_ADC_T,&tmp1);
    if(rtn == 1)
    {
        E703_ADC_T = tmp1;
    }
    
    rtn = Usr_E703_ReadReg(DEF_REGADDR_ADC_S,&tmp1);
    if(rtn == 1)
    {
        E703_ADC_S = tmp1;
    }
    
    rtn = Usr_E703_ReadReg(DEF_REGADDR_DSP_T,&tmp1);
    if(rtn == 1)
    {
        E703_DSP_T = tmp1;
    }
    
    rtn = Usr_E703_ReadReg(DEF_REGADDR_DSP_S,&tmp1);
    if(rtn == 1)
    {
        E703_DSP_S = tmp1;
    }
    
    rtn = Usr_E703_ReadReg(DEF_REGADDR_STATUS_SYNC,&tmp1);
    if(rtn == 1)
    {
        E703_Status_sync = tmp1;
    }
    
    rtn = Usr_E703_ReadReg(DEF_REGADDR_STATUS,&tmp1);
    if(rtn == 1)
    {
        E703_Status = tmp1;
    }
    
    rtn = Usr_E703_ReadReg(DEF_REGADDR_CHIPVERSION,&tmp1);
    if(rtn == 1)
    {
        E703_ChipVersion = tmp1;
    }
    
    rtn = Usr_E703_ReadReg(DEF_REGADDR_CM_STATUS,&tmp1);
    if(rtn == 1)
    {
        E703_CM_Status = tmp1;
    }
    
    return 0;
    
}



void Usr_E703_InitSetup(void)
{   
    unsigned char i;
    
    Init_printf("\nE703_Init;");
    
    Init_printf("\n1: First Read all Register and CM data;");
    
    Usr_Read_All_Reg();
    
    Usr_Read_All_CM();
    
    //Usr_Read_All_Claus();
    
    //Usr_E703_WriteCM(0x7E,0x5AB0);
    
    #if(defined(DEF_PARAM_UPDATE)&&(DEF_PARAM_UPDATE==1))
    Init_printf("\n2: Write Specified CM User data;");
    Usr_Write_CMUsr_Of_Claus();
    
    Init_printf("\n3: Read all CM data;");
    Usr_Read_All_CM();
    
    #endif
    
    #if(defined(DEF_PARAM_HOLD)&&(DEF_PARAM_HOLD==1))
    Init_printf("\n2: Write Specified CM User data, No this action;");
    
    Init_printf("\n3: Read all CM data, No this action;");
    #endif
    
    
    for(i=0;i<DEF_CM_DATA_NUM;i++)
    {
        Buff_U8[i*2+0] = (uint8_t)E703_CMData_Probe[i].data;
        Buff_U8[i*2+1] = (uint8_t)(E703_CMData_Probe[i].data>>8);
    }
    
    {
        uint16_t crc16 = 0;
        
        crc16 = Usr_E703_CRC(16,0x8005,0xFFFF,(uint16_t*)Buff_U8,63*16);
        
        #if(defined(DEF_PARAM_UPDATE)&&(DEF_PARAM_UPDATE==1))
        Init_printf("\n4: Write new CRC16 data;");
        Usr_E703_WriteCM(0x7E,crc16);
        Usr_E703_WriteCMUsr(0x7E,crc16);
        
        #endif
        
        
        #if(defined(DEF_PARAM_HOLD)&&(DEF_PARAM_HOLD==1))
        Init_printf("\n4: Write new CRC16 data, No this action;");
        #endif
        
        
        Init_printf("\nCalculate the CRC16 of above data is 0x%04X.\n",crc16);
    }
    
    
}


void Usr_E703_MainLoop(void)
{   
    static uint32_t E703_LoopCnt = 0;
    
    E703_LoopCnt++;
    
    //Debug_printf("\nE703_LoopCnt,%d, ",E703_LoopCnt);
    
    if(E703_LoopCnt == 1)
    {
        
        Init_printf("\n5: Second Read all Register and CM data;");
        
        Usr_E703_LockCMFCT();
        Usr_E703_LockCMUsr();
        Usr_E703_LockReg();
        
        Usr_Read_All_Reg();
        Usr_Read_All_CM();
        
        Usr_E703_ReadData();
        
        Init_printf("\nE703_ChipVersion,0x%04X,",E703_ChipVersion);
        
        Init_printf("\nE703_CMD,%d,",E703_CMD);
        Init_printf("\nE703_Status_sync,0x%04X,",E703_Status_sync);
        Init_printf("\nE703_Status,0x%04X,",E703_Status);
        Init_printf("\nE703_CM_Status,0x%04X,",E703_CM_Status);
        
    }
    
    #if 1
    Usr_E703_ReadData();
    
    E703_RegBuff[17] = E703_ADC_TC;
    E703_RegBuff[18] = E703_ADC_T;
    E703_RegBuff[19] = E703_ADC_S;
    E703_RegBuff[21] = E703_DSP_T;
    E703_RegBuff[22] = E703_DSP_S;
    
    #if 0
    Debug_printf("\tADC_TC,%d,",E703_ADC_TC);
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
    
    // Usr_Uart_Echo(0);
}


#endif

#if(defined(DEF_SENSOR_HDC3020_EN)&&(DEF_SENSOR_HDC3020_EN==1))

#endif

#if(defined(DEF_SENSOR_CMP201_EN)&&(DEF_SENSOR_CMP201_EN==1))

#endif



#endif



