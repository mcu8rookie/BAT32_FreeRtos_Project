#ifndef __USR_E703_H__
#define __USR_E703_H__


#include <stdint.h>

#define DEF_PARAM_UPDATE        1
#define DEF_PARAM_HOLD          0


#define DEF_SENSOR_E703_EN      1
#define DEF_SENSOR_HDC3020_EN   1
#define DEF_SENSOR_CMP201_EN    1




#if(defined(DEF_SENSOR_E703_EN)&&(DEF_SENSOR_E703_EN==1))

#define DEF_REG_DATA_NUM             (78)
#define DEF_CM_DATA_NUM              (64)

#define DEF_USRDATA_ADDR            (0x6A)

#define DEF_REGADDR_CMD             (0x22)
#define DEF_REGADDR_ADC_TC          (0x26)
#define DEF_REGADDR_ADC_T           (0x28)
#define DEF_REGADDR_ADC_S           (0x2A)
#define DEF_REGADDR_DSP_AODO        (0x2C)
#define DEF_REGADDR_DSP_T           (0x2E)
#define DEF_REGADDR_DSP_S           (0x30)
#define DEF_REGADDR_STATUS_SYNC     (0x32)
#define DEF_REGADDR_HW_DIAG         (0x34)
#define DEF_REGADDR_STATUS          (0x36)
#define DEF_REGADDR_CHIPVERSION     (0x38)
#define DEF_REGADDR_CM_STATUS       (0x46)
#define DEF_REGADDR_CM_RD           (0x48)
#define DEF_REGADDR_CM_WD           (0x4A)
#define DEF_REGADDR_CM_CMD          (0x4E)


typedef struct ADDR_DATA_TAG
{
    uint8_t addr;
    uint16_t data;
}ADDR_DATA_ST;

extern uint16_t E703_CMD;
extern uint16_t E703_ADC_TC;
extern uint16_t E703_ADC_T;
extern uint16_t E703_ADC_S;
extern uint16_t E703_DSP_T;
extern uint16_t E703_DSP_S;
extern uint16_t E703_Status_sync;
extern uint16_t E703_Status;
extern uint16_t E703_ChipVersion;
extern uint16_t E703_CM_Status;


extern volatile uint32_t Usr_E307_Timestamp;


extern ADDR_DATA_ST E703_RegData[DEF_REG_DATA_NUM];

extern ADDR_DATA_ST E703_CMData_Probe[DEF_CM_DATA_NUM];

extern const ADDR_DATA_ST E703_CMData_Init[DEF_CM_DATA_NUM];

extern unsigned short E703_RegBuff[DEF_REG_DATA_NUM];

extern unsigned short E703_CMBuff[DEF_CM_DATA_NUM];


uint8_t Usr_Is_RegAddr(uint8_t addr);

uint8_t Usr_Is_CMAddr(uint8_t addr);

uint8_t Usr_GetIndex_Reg(uint8_t addr);

uint8_t Usr_GetIndex_CM(uint8_t addr);

uint8_t Usr_E703_ReadReg(uint8_t addr,uint16_t *ptr);

uint8_t Usr_E703_WriteReg(uint8_t addr,uint16_t data);

uint8_t Usr_E703_ReadCM(uint8_t addr,uint16_t *ptr);

uint8_t Usr_E703_WriteCM(uint8_t addr,uint16_t data);

uint16_t Usr_E703_CRC8_Init(void);

uint16_t Usr_E703_CRC16_Init(void);

void Usr_E703_InitSetup(void);

void Usr_E703_MainLoop(void);


#endif

#if(defined(DEF_SENSOR_HDC3020_EN)&&(DEF_SENSOR_HDC3020_EN==1))

#endif

#if(defined(DEF_SENSOR_CMP201_EN)&&(DEF_SENSOR_CMP201_EN==1))

#endif




#endif


