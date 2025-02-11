#ifndef __USR_SOFT_I2C_H__
#define __USR_SOFT_I2C_H__

#include "stdint.h"


#define MCU_CLS_UNDEF           0
#define MCU_CLS_HT8             1
#define MCU_CLS_BAT32           2


//#define DEF_MCU_CLASS           MCU_CLS_HT8
#define DEF_MCU_CLASS           MCU_CLS_BAT32



#define IIC_BAUDRATE_100KHZ     1
#define IIC_BAUDRATE_400KHZ     2
#define IIC_BAUDRATE_TYPE       IIC_BAUDRATE_100KHZ

#define IIC_DELAY_CNT_100KHZ    5
#define IIC_DELAY_CNT_400KHZ    3



#if(defined(DEF_MCU_CLASS)&&(DEF_MCU_CLASS==MCU_CLS_HT8))
//#include "BH66F5250.h"

#include "BH67F2762.h"

#define IIC1_SCL_Pin            _pc4
#define IIC1_SDA_Pin            _pc5
#define IIC1_SCL_SetIn          _pcc4=1
#define IIC1_SCL_SetOut         _pcc4=0
#define IIC1_SDA_SetIn          _pcc5=1
#define IIC1_SDA_SetOut         _pcc5=0


// PGS4100: BH66F5250 -> CPS122;
#define IIC2_SCL_Pin            _pc1
#define IIC2_SDA_Pin            _pc0
#define IIC2_SCL_SetIn          _pcc1=1
#define IIC2_SCL_SetOut         _pcc1=0
#define IIC2_SDA_SetIn          _pcc0=1
#define IIC2_SDA_SetOut         _pcc0=0

#define IIC3_SCL_Pin            _pc3
#define IIC3_SDA_Pin            _pc4
#define IIC3_SCL_SetIn          _pcc3=1
#define IIC3_SCL_SetOut         _pcc3=0
#define IIC3_SDA_SetIn          _pcc4=1
#define IIC3_SDA_SetOut         _pcc4=0

#define IIC4_SCL_Pin            _pd5
#define IIC4_SDA_Pin            _pd4
#define IIC4_SCL_SetIn          _pdc5=1
#define IIC4_SCL_SetOut         _pdc5=0
#define IIC4_SDA_SetIn          _pdc4=1
#define IIC4_SDA_SetOut         _pdc4=0

#endif

#if(defined(DEF_MCU_CLASS)&&(DEF_MCU_CLASS==MCU_CLS_BAT32))

#define I2C_CHANNEL_NONE        0
#define I2C_CHANNEL_E703        1
#define I2C_CHANNEL_HDC3020     2
#define I2C_CHANNEL_CMP201      3
#define I2C_CHANNEL_HDC2010     4

#define IIC1_SCL_PORT           PORT1
#define IIC1_SCL_PIN            PIN5
#define IIC1_SDA_PORT           PORT1
#define IIC1_SDA_PIN            PIN4

#define IIC2_SCL_PORT           PORT3
#define IIC2_SCL_PIN            PIN0
#define IIC2_SDA_PORT           PORT5
#define IIC2_SDA_PIN            PIN0

#define IIC3_SCL_PORT           PORT7
#define IIC3_SCL_PIN            PIN5
#define IIC3_SDA_PORT           PORT7
#define IIC3_SDA_PIN            PIN4

#define IIC4_SCL_PORT           PORT6
#define IIC4_SCL_PIN            PIN0
#define IIC4_SDA_PORT           PORT6
#define IIC4_SDA_PIN            PIN1

#endif

extern unsigned char iic_tmp1;
extern unsigned char iic_tmp2;

extern unsigned char HTS_I2C_Address_7B;
extern unsigned char HTS_I2C_Address_8B_Rd;
extern unsigned char HTS_I2C_Address_8B_Wt;

#if((defined(SENSOR_HT_TYPE))&&(SENSOR_HT_TYPE == SENSOR_TYPE_HDC3020))
//extern unsigned char HDC3020_ReadFlag;
#endif



void Usr_Soft_IIC_Init(unsigned char nbr);

void iic_start_signal(unsigned char nbr);
void iic_stop_signal(unsigned char nbr);
unsigned char iic_wait_ack(unsigned char nbr);
unsigned char iic_send_8bit(unsigned char nbr,unsigned char arg);
unsigned char iic_receive_8bit(unsigned char nbr,unsigned char *parg,unsigned char fack);


unsigned char i2c_burst_read(unsigned char sn,unsigned char devID,unsigned char u8Addr, unsigned char *pu8Data, unsigned char u8Len);

unsigned char i2c_burst_write(unsigned char sn,unsigned char devID,unsigned char u8Addr, unsigned char *pu8Data, unsigned char u8Len);


#if 0
unsigned char BMP581_IIC_Write_NByte(unsigned char dev_addr, uint8_t reg_addr, const uint8_t *reg_data, uint32_t length);
unsigned char BMP581_IIC_Read_NByte(unsigned char dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint32_t length);
#endif


#endif

