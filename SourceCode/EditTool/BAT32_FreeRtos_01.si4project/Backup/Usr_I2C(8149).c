#ifndef __USR_I2C_C__
#define __USR_I2C_C__

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
    
    Debug_printf("\r\n");
    
    //Usr_Read_Fw();
    
    //Usr_Read_Raw();
    
    //Usr_Read_Cali();
    
    
    
    return 0;
}


#endif



