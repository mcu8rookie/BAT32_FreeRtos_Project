#ifndef __USR_HDC3020_H__
#define __USR_HDC3020_H__


//#include "Usr_Code.h"

#if((defined(SENSOR_HT_TYPE))&&(SENSOR_HT_TYPE == SENSOR_TYPE_HDC3020))

#define HDC3020_IIC_ADDR7B          0x44

#define HDC3020_IIC_ADDR_Wit        ((HDC3020_IIC_ADDR7B<<1)+0)
#define HDC3020_IIC_ADDR_Rad        ((HDC3020_IIC_ADDR7B<<1)+1)

#define DEF_HT_VID                  0x3000
#define DEF_HT_PID                  0x3020

extern unsigned char HDC3020_ReadFlag;


unsigned char HDC3020_ReadID(unsigned char *pdat);

unsigned char HDC3020_ConvertStart(void);

unsigned char HDC3020_ReadTH(unsigned char *pdat);



#endif

#endif


