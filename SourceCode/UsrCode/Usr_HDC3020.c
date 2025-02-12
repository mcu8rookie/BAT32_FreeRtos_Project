#ifndef __USR_HDC3020_C__
#define __USR_HDC3020_C__

//#include "Usr_Code.h"

//#include "Usr_IIC_Soft.h"

#include"Usr_Config.h"
#include"Usr_Soft_I2C.h"
#include "Usr_I2C.h"
#include "Usr_HDC3020.h"


#if((defined(SENSOR_HT_TYPE))&&(SENSOR_HT_TYPE == SENSOR_TYPE_HDC3020))


unsigned char HDC3020_ReadFlag = 0;

#if 0
unsigned char HDC3020_ReadID(unsigned char *pdat)
{   
    HDC3020_ReadFlag = 1;
    
    unsigned char buff[1] = {0x81};
    i2c_burst_write(I2C_CHANNEL_HDC3020,DEF_HDC3020_I2C_ADDR_7B,0x37, buff, 1);
    i2c_burst_read(I2C_CHANNEL_HDC3020,DEF_HDC3020_I2C_ADDR_7B,0x00, pdat, 3);
    
    HDC3020_ReadFlag = 0;
    
    return 0;
}
#endif

unsigned char HDC3020_ConvertStart(void)
{   
    unsigned char buff[1] = {0x00};
    
    return i2c_burst_write(I2C_CHANNEL_HDC3020,DEF_HDC3020_I2C_ADDR_7B,0x24, buff, 1);
}


unsigned char HDC3020_ReadTH(unsigned char *pdat)
{   
    unsigned char rtn;
    
    HDC3020_ReadFlag = 1;
    
    rtn = i2c_burst_read(I2C_CHANNEL_HDC3020,DEF_HDC3020_I2C_ADDR_7B,0x00, pdat, 6);
    
    HDC3020_ReadFlag = 0;
    
    return rtn;
}



#endif


#endif



