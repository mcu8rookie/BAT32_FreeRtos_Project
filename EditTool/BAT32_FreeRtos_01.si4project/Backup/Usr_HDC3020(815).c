#ifndef __USR_HDC3020_C__
#define __USR_HDC3020_C__

//#include "Usr_Code.h"

//#include "Usr_IIC_Soft.h"

#include <stdint.h>
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

/*
 *  ======== HDC3020_CRC_A ========
 *  Calculate CRC values
 */
uint8_t HDC3020_CRC_A(uint8_t msg[], uint8_t msglen){
 uint8_t crc = 0xFF;
 uint8_t byte;
 uint8_t bit;
 for (byte = 0; byte < msglen; byte++){
  crc ^= msg[byte];
  for (bit = 0; bit < 8; bit++){
   if (crc & 0x80) 
    crc = (crc << 1) ^ 0x31;
   else
    crc = (crc << 1);
  }
 }
 return crc;
}

/*
 *  ======== HDC3020_CRC ========
 *  Calculate CRC value for 2 bytes
 */
uint8_t HDC3020_CRC(uint8_t msg1, uint8_t msg2){
 uint8_t msg[2] = {msg1, msg2};
 return HDC3020_CRC_A(msg, 2);
}



#endif


#endif



