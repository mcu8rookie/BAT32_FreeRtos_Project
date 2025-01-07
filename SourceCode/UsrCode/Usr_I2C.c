#ifndef __USR_I2C_C__
#define __USR_I2C_C__

#include "userdefine.h"
#include "BAT32A237.h"
#include "iica.h"

#include "Usr_Debug.h"
#include "Usr_I2C.h"

unsigned char   i2c_cmdbuf[1];
unsigned char   i2c_wtbuf[32];
unsigned char   i2c_rdbuf[32];


unsigned char Usr_I2C_InitSetup(void)
{   
    IICA0_Init();
    
    return 0;
}

unsigned char Usr_I2C_MainLoop(void)
{
    
    Debug_printf_Mut("\nUsr_I2C_MainLoop();");
    
    
    Usr_Read_ChipVersion();
    
    return 0;
}

unsigned char Usr_I2C_AccessCmdData(unsigned char *cmdbuf,unsigned char cmdlen,unsigned char *rxbuff,unsigned char rxlen)
{   
    unsigned char chkbyte;
    MD_STATUS status;
    
    //status = IICA0_MasterSend(CFG_I2C_ADDR_W, cmdbuf, cmdlen, 20);
    status = IICA0_MasterSend(DEF_E703_I2C_ADDR_WT, cmdbuf, cmdlen, 20);
    
    while(g_iica0_tx_end == 0);
    
    status = IICA0_MasterReceive(DEF_E703_I2C_ADDR_RD, rxbuff, rxlen, 20);
    
    while(g_iica0_rx_end == 0);
    
    Debug_printf_Mut("\r\nI2C_Access;");
    
    return 0;
}

unsigned char Usr_Read_ChipVersion(void)
{   
    unsigned char chkbyte;
    
    //i2c_cmdbuf[0] = 0xD5;
    i2c_cmdbuf[0] = 0x38;
    
    Usr_I2C_AccessCmdData(i2c_cmdbuf,1,i2c_rdbuf,2);
    Debug_printf_Mut("\nChip Version : 0x%02X,0x%02X,",i2c_rdbuf[0],i2c_rdbuf[1]);
    
    i2c_cmdbuf[0] = 0x50;
    
    Usr_I2C_AccessCmdData(i2c_cmdbuf,1,i2c_rdbuf,2);
    Debug_printf_Mut("\nSerialNumber0: 0x%02X,0x%02X,",i2c_rdbuf[0],i2c_rdbuf[1]);
    
    i2c_cmdbuf[0] = 0x51;
    
    Usr_I2C_AccessCmdData(i2c_cmdbuf,1,i2c_rdbuf,2);
    Debug_printf_Mut("\nSerialNumber0: 0x%02X,0x%02X,",i2c_rdbuf[0],i2c_rdbuf[1]);
    
    return 0;
}



#endif



