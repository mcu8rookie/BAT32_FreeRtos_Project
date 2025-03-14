#ifndef __USR_I2C_C__
#define __USR_I2C_C__

#include "stdio.h"

#include "userdefine.h"
#include "BAT32A237.h"
#include "iica.h"
#include "sci.h"

#include "Usr_Debug.h"
#include "Usr_I2C.h"

#include"gpio.h"
#include"Usr_GPIO.h"

#include"Usr_Soft_I2C.h"


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

#define DEF_HT_VID                  0x3000
#define DEF_HT_PID                  0x3020

unsigned int ALSensor_TH_VID;
unsigned int ALSensor_TH_PID;

unsigned char   hdc3020_cmdbuf[1];
unsigned char   hdc3020_wtbuf[32];
unsigned char   hdc3020_rdbuf[32];

unsigned char CMP201_ChipID;


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
    // unsigned char chkbyte;
    // MD_STATUS status;
    
    //status = IICA0_MasterSend(CFG_I2C_ADDR_W, cmdbuf, cmdlen, 20);
    IICA0_MasterSend(DEF_E703_I2C_ADDR_WT, cmdbuf, cmdlen, 20);
    
    while(g_iica0_tx_end == 0);
    
    IICA0_MasterReceive(DEF_E703_I2C_ADDR_RD, rxbuff, rxlen, 20);
    
    while(g_iica0_rx_end == 0);
    
    Debug_printf_Mut("\r\nI2C_Access;");
    
    return 0;
}

unsigned char Usr_Read_ChipVersion(void)
{   
    // unsigned char chkbyte;
    
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
    //Debug_printf_Mut("\nSerialNumber1: 0x%02X,0x%02X,",i2c_rdbuf[0],i2c_rdbuf[1]);
    Debug_printf("\nSerialNumber1: 0x%02X,0x%02X,",i2c_rdbuf[0],i2c_rdbuf[1]);
    
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


void Usr_I2CS_InitSetup(void)
{
    
    #if 0
    IIC20_Init();
    #endif
    
    #if 0
    IIC00_Init();
    #endif
    
    #if 0
    IIC01_Init();
    #endif
    
    
    #if(DEF_I2C_HWSW == DEF_I2C_SOFTWARE)
    Usr_Soft_IIC_Init(I2C_CHANNEL_E703);
    Usr_Soft_IIC_Init(I2C_CHANNEL_HDC3020);
    Usr_Soft_IIC_Init(I2C_CHANNEL_CMP201);
    #endif
    
    
    
}

unsigned char HDC3020_ReadID(unsigned char *pdat)
{   
    HDC3020_ReadFlag = 1;
    
    unsigned char buff[1] = {0x81};
    i2c_burst_write(I2C_CHANNEL_HDC3020,DEF_HDC3020_I2C_ADDR_7B,0x37, buff, 1);
    i2c_burst_read(I2C_CHANNEL_HDC3020,DEF_HDC3020_I2C_ADDR_7B,0x00, pdat, 2);
    
    HDC3020_ReadFlag = 0;
    
    return 0;
}


void Usr_I2C20_MainLoop(void)
{
    unsigned char i;
    
    #if 0
    i2c20_wtbuf[0] = 0x38;
    
    g_iic20_tx_end = 0;
    IIC20_MasterSend(DEF_E703_I2C_ADDR_WT, i2c20_wtbuf, 1);
    while(g_iic20_tx_end == 0);
    
    g_iic20_rx_end = 0;
    IIC20_MasterReceive(DEF_E703_I2C_ADDR_RD, i2c20_rdbuf, 2);
    while(g_iic20_rx_end == 0);
    
    Debug_printf("\nI2C20: WT: 0x%02X,0x%02X,",DEF_E703_I2C_ADDR_WT,i2c20_wtbuf[0]);
    Debug_printf("\nI2C20: RD: 0x%02X,0x%02X,0x%02X,",DEF_E703_I2C_ADDR_RD,i2c20_rdbuf[0],i2c20_rdbuf[1]);
    Debug_printf("\nE703.11 ChipVersion: 0x%02X,0x%02X,\n",i2c20_rdbuf[0],i2c20_rdbuf[1]);
    
    if((i2c20_rdbuf[0] == 0x20)&&(i2c20_rdbuf[1] == 0x00))
    {
        
        #if !defined(DBG_PRINT_UART)
            PORT_ToggleBit(Usr_DBGIO1_PORT,Usr_DBGIO1_PIN);
        #endif
    }
    
    
    #if 1
    i2c20_wtbuf[0] = 0x50;
    
    g_iic20_tx_end = 0;
    IIC20_MasterSend(DEF_E703_I2C_ADDR_WT, i2c20_wtbuf, 1);
    while(g_iic20_tx_end == 0);
    
    g_iic20_rx_end = 0;
    IIC20_MasterReceive(DEF_E703_I2C_ADDR_RD, i2c20_rdbuf, 2);
    while(g_iic20_rx_end == 0);
    
    Debug_printf("\nI2C20: WT:0x%02X,0x%02X,",DEF_E703_I2C_ADDR_WT,i2c20_wtbuf[0]);
    Debug_printf("\nI2C20: RD:0x%02X,0x%02X,0x%02X,",DEF_E703_I2C_ADDR_RD,i2c20_rdbuf[0],i2c20_rdbuf[1]);
    Debug_printf("\nSerialNumber0: 0x%02X,0x%02X,\n",i2c20_rdbuf[0],i2c20_rdbuf[1]);
    #endif
    
    #if 1
    i2c20_wtbuf[0] = 0x51;
    
    g_iic20_tx_end = 0;
    IIC20_MasterSend(DEF_E703_I2C_ADDR_WT, i2c20_wtbuf, 1);
    while(g_iic20_tx_end == 0);
    
    g_iic20_rx_end = 0;
    IIC20_MasterReceive(DEF_E703_I2C_ADDR_RD, i2c20_rdbuf, 2);
    while(g_iic20_rx_end == 0);
    
    Debug_printf("\nI2C20: WT:0x%02X,0x%02X,",DEF_E703_I2C_ADDR_WT,i2c20_wtbuf[0]);
    Debug_printf("\nI2C20: RD:0x%02X,0x%02X,0x%02X,",DEF_E703_I2C_ADDR_RD,i2c20_rdbuf[0],i2c20_rdbuf[1]);
    Debug_printf("\nSerialNumber1: 0x%02X,0x%02X,\n",i2c20_rdbuf[0],i2c20_rdbuf[1]);
    #endif
    
    
    #if 1
    i2c20_wtbuf[0] = 0x06;
    //i2c20_wtbuf[0] = 0x1A;
    
    g_iic20_tx_end = 0;
    IIC20_MasterSend(DEF_E703_I2C_ADDR_WT, i2c20_wtbuf, 1);
    while(g_iic20_tx_end == 0);
    
    g_iic20_rx_end = 0;
    IIC20_MasterReceive(DEF_E703_I2C_ADDR_RD, i2c20_rdbuf, 2);
    while(g_iic20_rx_end == 0);
    
    Debug_printf("\nI2C20: WT:0x%02X,0x%02X,",DEF_E703_I2C_ADDR_WT,i2c20_wtbuf[0]);
    Debug_printf("\nI2C20: RD:0x%02X,0x%02X,0x%02X,",DEF_E703_I2C_ADDR_RD,i2c20_rdbuf[0],i2c20_rdbuf[1]);
    Debug_printf("\nRead Data is: 0x%02X,0x%02X,\n",i2c20_rdbuf[0],i2c20_rdbuf[1]);
    #endif
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
    
    
    #if 0
    i2c01_wtbuf[0] = 0x81;
    i2c01_wtbuf[1] = 0x37;
    
    g_iic01_tx_end = 0;
    IIC01_MasterSend(DEF_E703_I2C_ADDR_WT, i2c01_wtbuf, 2);
    while(g_iic01_tx_end == 0);
    
    g_iic01_rx_end = 0;
    IIC01_MasterReceive(DEF_E703_I2C_ADDR_RD, i2c01_rdbuf, 3);
    while(g_iic01_rx_end == 0);
    
    Debug_printf_Mut("\nI2C01 Read: 0x%02X,0x%02X,0x%02X,",i2c00_rdbuf[0],i2c00_rdbuf[1],i2c00_rdbuf[2]);
    #endif
    
    
    #if(DEF_I2C_HWSW == DEF_I2C_SOFTWARE)
    {
        i2c20_wtbuf[0] = 0x38;
        
        for(i=0;i<10;i++)
        {
            i2c20_rdbuf[i] = 0xFF;
        }
        
        //g_iic20_tx_end = 0;
        //IIC20_MasterSend(DEF_E703_I2C_ADDR_WT, i2c20_wtbuf, 1);
        //while(g_iic20_tx_end == 0);
        
        //g_iic20_rx_end = 0;
        //IIC20_MasterReceive(DEF_E703_I2C_ADDR_RD, i2c20_rdbuf, 2);
        //while(g_iic20_rx_end == 0);
        
        i2c_burst_read(I2C_CHANNEL_E703,DEF_E703_I2C_ADDR_7B,i2c20_wtbuf[0],i2c20_rdbuf, 2);
        
        Debug_printf("\nI2C1: WT: 0x%02X,0x%02X,",DEF_E703_I2C_ADDR_WT,i2c20_wtbuf[0]);
        Debug_printf("\nI2C1: RD: 0x%02X,0x%02X,0x%02X,",DEF_E703_I2C_ADDR_RD,i2c20_rdbuf[0],i2c20_rdbuf[1]);
        Debug_printf("\nE703.11 ChipVersion: 0x%02X,0x%02X,\n",i2c20_rdbuf[0],i2c20_rdbuf[1]);
        
        if((i2c20_rdbuf[0] == 0x20)&&(i2c20_rdbuf[1] == 0x00))
        {
            #if !defined(DBG_PRINT_UART)
            PORT_ToggleBit(Usr_DBGIO1_PORT,Usr_DBGIO1_PIN);
            #endif
        }
    }
    
    {
        
        for(i=0;i<10;i++)
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
            
            #if !defined(DBG_PRINT_UART)
                PORT_ToggleBit(Usr_DBGIO2_PORT,Usr_DBGIO2_PIN);
            #endif
        }
        
        Debug_printf("\nI2C2: WT: 0x%02X,0x%02X,",DEF_HDC3020_I2C_ADDR_WT,0x81);
        Debug_printf("\nI2C2: RD: 0x%02X,0x%02X,0x%02X,",DEF_E703_I2C_ADDR_RD,hdc3020_rdbuf[0],hdc3020_rdbuf[1]);
        Debug_printf("\nHDC3020 ChipID: 0x%02X,0x%02X,\n",hdc3020_rdbuf[0],hdc3020_rdbuf[1]);
        
        if((i2c20_rdbuf[0] == 0x20)&&(i2c20_rdbuf[1] == 0x00))
        {
            #if !defined(DBG_PRINT_UART)
            PORT_ToggleBit(Usr_DBGIO1_PORT,Usr_DBGIO1_PIN);
            #endif
        }
    }
    
    {
        CMP201_ChipID = 0xFF;
        
        /*****  check sensor ID *****/
        #define CMP201_REG_CHIP_ID          0x00
        i2c_burst_read(I2C_CHANNEL_CMP201,DEF_CMP201_I2C_ADDR_7B,CMP201_REG_CHIP_ID,&CMP201_ChipID, 1);
        
        if(CMP201_ChipID == 0xA0)
        {
            
            #if !defined(DBG_PRINT_UART)
            PORT_ToggleBit(Usr_HEATEN_PORT,Usr_HEATEN_PIN);
            #endif
        }
        
        Debug_printf("\nI2C3: WT: 0x%02X,0x%02X,",DEF_CMP201_I2C_ADDR_WT,CMP201_REG_CHIP_ID);
        Debug_printf("\nI2C3: RD: 0x%02X,0x%02X,",DEF_E703_I2C_ADDR_RD,CMP201_ChipID);
        Debug_printf("\nCMP201 ChipID: 0x%02X,\n",CMP201_ChipID);
        
    }
    
    
    #endif
    
    
}



#endif



