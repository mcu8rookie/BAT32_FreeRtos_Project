#ifndef __USR_I2C_C__
#define __USR_I2C_C__

#include "Usr_Debug.h"
#include "userdefine.h"
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
    
    Debug_printf("\r\n");
    
    //Usr_Read_Fw();
    
    //Usr_Read_Raw();
    
    //Usr_Read_Cali();
    
    Usr_Read_Fw();
    
    return 0;
}

unsigned char Usr_I2C_AccessCmdData(unsigned char *cmdbuf,unsigned char cmdlen,unsigned char *rxbuff,unsigned char rxlen)
{   
    unsigned char chkbyte;
    MD_STATUS status;
    
    status = IICA0_MasterSend(CFG_I2C_ADDR_W, cmdbuf, cmdlen, 20);
    
    while(g_iica0_tx_end == 0);
    
    status = IICA0_MasterReceive(CFG_I2C_ADDR_R, rxbuff, rxlen, 20);
    
    while(g_iica0_rx_end == 0);
    
    chkbyte = Usr_CalculateCheck_I2C(rxbuff,rxlen-1);	
    
    if(chkbyte == rxbuff[rxlen-1])
    {
        //Debug_printf("\r\nI2C_Access;   chkbyte OK;");
    }
    else
    {
        Debug_printf("\r\nI2C_Access;   chkbyte NG;");
    }
    
    return 0;
}

unsigned char Usr_Read_Fw(void)
{   
    unsigned char chkbyte;
    
    i2c_cmdbuf[0] = 0xD5;
    
    Usr_I2C_AccessCmdData(i2c_cmdbuf,1,i2c_rdbuf,3);
    
    return 0;
}



#endif



