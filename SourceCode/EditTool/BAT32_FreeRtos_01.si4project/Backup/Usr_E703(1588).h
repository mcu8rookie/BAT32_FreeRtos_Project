#ifndef __USR_E307_H__
#define __USR_E307_H__


#include <stdint.h>

#define DEF_SENSOR_E703_EN      1
#define DEF_SENSOR_HDC3020_EN   1
#define DEF_SENSOR_CMP201_EN    1


#if(defined(DEF_SENSOR_E703_EN)&&(DEF_SENSOR_E703_EN==1))

#define DEF_REG_DATA_NUM             (80)
#define DEF_CM_DATA_NUM              (64)

#define DEF_USRDATA_ADDR            (0x6A)

typedef struct ADDR_DATA_TAG
{
    uint8_t addr;
    uint16_t data;
}ADDR_DATA_ST;

extern uint32_t Usr_E307_Timestamp;


extern ADDR_DATA_ST E703_RegData[DEF_REG_DATA_NUM];

extern ADDR_DATA_ST E703_CMData_Probe[DEF_CM_DATA_NUM];

extern const ADDR_DATA_ST E703_CMData_Init[DEF_CM_DATA_NUM];



uint8_t Usr_GetIndex_Reg(uint8_t addr);

uint8_t Usr_GetIndex_CM(uint8_t addr);

uint8_t Usr_E703_ReadReg(uint8_t addr,uint16_t *ptr);

uint8_t Usr_E703_WriteReg(uint8_t addr,uint16_t data);

uint8_t Usr_E703_ReadCM(uint8_t addr,uint16_t *ptr);

uint8_t Usr_E703_WriteCM(uint8_t addr,uint16_t data);


#endif

#if(defined(DEF_SENSOR_HDC3020_EN)&&(DEF_SENSOR_HDC3020_EN==1))

#endif

#if(defined(DEF_SENSOR_CMP201_EN)&&(DEF_SENSOR_CMP201_EN==1))

#endif




#endif


