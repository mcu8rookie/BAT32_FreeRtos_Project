#ifndef __USR_I2C_C__
#define __USR_I2C_C__

#include "userdefine.h"
#include "BAT32A237.h"
#include "iica.h"
#include "sci.h"

#include "Usr_Debug.h"
#include "Usr_I2C.h"

unsigned char   i2c_cmdbuf[1];
unsigned char   i2c_wtbuf[32];
unsigned char   i2c_rdbuf[32];

unsigned char   i2c20_cmdbuf[1];
unsigned char   i2c20_wtbuf[32];
unsigned char   i2c20_rdbuf[32];

unsigned char   i2c00_cmdbuf[1];
unsigned char   i2c00_wtbuf[32];
unsigned char   i2c00_rdbuf[32];

unsigned char   i2c01_cmdbuf[1];
unsigned char   i2c01_wtbuf[32];
unsigned char   i2c01_rdbuf[32];



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
    //Debug_printf_Mut("\nChip Version : 0x%02X,0x%02X,",i2c_rdbuf[0],i2c_rdbuf[1]);
    Debug_printf("\nChip Version : 0x%02X,0x%02X,",i2c_rdbuf[0],i2c_rdbuf[1]);
    
    i2c_cmdbuf[0] = 0x50;
    
    Usr_I2C_AccessCmdData(i2c_cmdbuf,1,i2c_rdbuf,2);
    //Debug_printf_Mut("\nSerialNumber0: 0x%02X,0x%02X,",i2c_rdbuf[0],i2c_rdbuf[1]);
    Debug_printf("\nSerialNumber0: 0x%02X,0x%02X,",i2c_rdbuf[0],i2c_rdbuf[1]);
    
    i2c_cmdbuf[0] = 0x51;
    
    Usr_I2C_AccessCmdData(i2c_cmdbuf,1,i2c_rdbuf,2);
    //Debug_printf_Mut("\nSerialNumber0: 0x%02X,0x%02X,",i2c_rdbuf[0],i2c_rdbuf[1]);
    Debug_printf("\nSerialNumber0: 0x%02X,0x%02X,",i2c_rdbuf[0],i2c_rdbuf[1]);
    
    return 0;
}

#if 0
unsigned char HDC3020_ReadID(unsigned char *pdat)
{   
    HDC3020_ReadFlag = 1;
    
    unsigned char buff[1] = {0x81};
    i2c_burst_write(3,HTS_I2C_Address_7B,0x37, buff, 1);
    i2c_burst_read(3,HTS_I2C_Address_7B,0x00, pdat, 3);
    
    HDC3020_ReadFlag = 0;
    
    return 0;
}
#endif


void Usr_I2C20_InitSetup(void)
{
    #if 0
    IIC20_Init();
    #endif
    
    #if 0
    IIC00_Init();
    #endif
    
    #if 1
    IIC01_Init();
    #endif
}

void Usr_I2C20_MainLoop(void)
{
    #if 0
    i2c20_wtbuf[0] = 0x38;
    
    g_iic20_tx_end = 0;
    IIC20_MasterSend(DEF_E703_I2C_ADDR_WT, i2c20_wtbuf, 2);
    while(g_iic20_tx_end == 0);
    
    g_iic20_rx_end = 0;
    IIC20_MasterReceive(DEF_E703_I2C_ADDR_WT, i2c20_rdbuf, 3);
    while(g_iic20_rx_end == 0);
    #endif
    
    
    #if 0
    i2c00_wtbuf[0] = 0x81;
    i2c00_wtbuf[1] = 0x37;
    
    g_iic00_tx_end = 0;
    IIC00_MasterSend(DEF_E703_I2C_ADDR_WT, i2c00_wtbuf, 2);
    while(g_iic00_tx_end == 0);
    
    g_iic00_rx_end = 0;
    IIC00_MasterReceive(0x89, i2c00_rdbuf, 3);
    while(g_iic00_rx_end == 0);
    
    Debug_printf_Mut("\nI2C00 Read: 0x%02X,0x%02X,0x%02X,",i2c00_rdbuf[0],i2c00_rdbuf[1],i2c00_rdbuf[2]);
    #endif
    
    
    #if 1
    i2c01_wtbuf[0] = 0x81;
    i2c01_wtbuf[1] = 0x37;
    
    g_iic01_tx_end = 0;
    IIC01_MasterSend(DEF_E703_I2C_ADDR_WT, i2c01_wtbuf, 2);
    while(g_iic01_tx_end == 0);
    
    g_iic01_rx_end = 0;
    IIC01_MasterReceive(0x89, i2c01_rdbuf, 3);
    while(g_iic01_rx_end == 0);
    
    Debug_printf_Mut("\nI2C01 Read: 0x%02X,0x%02X,0x%02X,",i2c00_rdbuf[0],i2c00_rdbuf[1],i2c00_rdbuf[2]);
    #endif
}



#endif



