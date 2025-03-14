#ifndef __USR_CMP201_H__
#define __USR_CMP201_H__


//#include "Usr_Code.h"
typedef unsigned char u8;
#if(defined(SENSOR_PT_TYPE)&&(SENSOR_PT_TYPE == SENSOR_TYPE_CMP201))


/* -----  I2C Slave Address  ----- */
#define CMP201_7BIT_I2C_ADDR    0x3A
// #define CMP201_7BIT_I2C_ADDR	0x3B


#define CMP201_IIC_ADDR7B       0x3A
#define CMP201_IIC_ADDR_Wit     ((CMP201_IIC_ADDR7B<<1)+0)
#define CMP201_IIC_ADDR_Rad     ((CMP201_IIC_ADDR7B<<1)+1)




/* --------------------------------------------------------------------- */
//
//#define polling_time                40          // sensor data polling time (unit: msec)

/* -----  Sensor Dara Resolution  ----- */
#define CMP201_PRESS_SENSITIVITY    (64)        // (unit : count/Pa)
#define CMP201_TEMP_SENSITIVITY     (65536)     // (unit : count/Celsius)

#define CMP201_P_CODE_TO_PA(pCode) 	((float)(pCode)/CMP201_PRESS_SENSITIVITY)
#define CMP201_T_CODE_TO_CELSIUS(tCode)  ((float)(tCode)/CMP201_TEMP_SENSITIVITY)

/* -----  Registers Address (RAM) ----- */
#define CMP201_REG_CHIP_ID		    0x00
#define CMP201_REG_REV_ID	 		0x01
#define CMP201_REG_ERR_MSG		    0x02
#define CMP201_REG_STATUS		    0x03
#define CMP201_REG_PRESS_XLSB	    0x04
#define CMP201_REG_PRESS_LSB	    0x05
#define CMP201_REG_PRESS_MSB	    0x06
#define CMP201_REG_TEMP_XLSB	    0x07
#define CMP201_REG_TEMP_LSB 	    0x08
#define CMP201_REG_TEMP_MSB 	    0x09
#define CMP201_REG_SENSOR_TIME_0    0x0C
#define CMP201_REG_SENSOR_TIME_1    0x0D
#define CMP201_REG_SENSOR_TIME_2    0x0E
#define CMP201_REG_INT_STATUS       0x11
#define CMP201_REG_FIFO_LENGTH_0    0x12
#define CMP201_REG_FIFO_LENGTH_1    0x13
#define CMP201_REG_FIFO_DATA        0x14
#define CMP201_REG_FIFO_WM_0        0x15
#define CMP201_REG_FIFO_WM_1        0x16
#define CMP201_REG_FIFO_CONFIG_0    0x17
#define CMP201_REG_FIFO_CONFIG_1    0x18
#define CMP201_REG_INT_CTRL         0x19
#define CMP201_REG_CONFIG           0x1A
#define CMP201_REG_PWR_CTRL         0x1B
#define CMP201_REG_OSR 	            0x1C
#define CMP201_REG_ODR 	            0x1D
#define CMP201_REG_FILTER           0x1F
#define CMP201_REG_PRIMIF           0x22
#define CMP201_REG_RESET            0x7E

/* -----  Registers Address (OTP) ----- */
#define CMP201_SERIAL_NUMBER        0x00	// 0x00 ~ 0x0C

/* -----  Sensor PID  ----- */
#define CMP201_PID		 	  0xA0

/* -----  Sensor Version  ----- */
#define CMP201_Ver		 	  0x80

/* CONF ERR bit */
#define CMP201_CONF_ERR__REG    CMP201_REG_ERR_MSG
#define CMP201_CONF_ERR__MSK	0x04
#define CMP201_CONF_ERR__POS	2

/* DRDY TEMP bit */
#define CMP201_DRDY_TEMP__REG	 CMP201_REG_STATUS
#define CMP201_DRDY_TEMP__MSK	 0x40
#define CMP201_DRDY_TEMP__POS	 6

/* DRDY PRESS bit */
#define CMP201_DRDY_PRESS__REG	 CMP201_REG_STATUS
#define CMP201_DRDY_PRESS__MSK	 0x20
#define CMP201_DRDY_PRESS__POS	 5

/* DRDY INT bit */
#define CMP201_DRDY_INT__REG	 CMP201_REG_INT_STATUS
#define CMP201_DRDY_INT__MSK	 0x10
#define CMP201_DRDY_INT__POS	 4

/* FFULL INT bit */
#define CMP201_FFULL_INT__REG	 CMP201_REG_INT_STATUS
#define CMP201_FFULL_INT__MSK	 0x02
#define CMP201_FFULL_INT__POS	 1

/* FWM INT bit */
#define CMP201_FWM_INT__REG	     CMP201_REG_INT_STATUS
#define CMP201_FWM_INT__MSK	     0x01
#define CMP201_FWM_INT__POS	     0

/* FIFO TEMP EN bit */
#define CMP201_FIFO_TEMP_EN__REG    CMP201_REG_FIFO_CONFIG_0
#define CMP201_FIFO_TEMP_EN__MSK    0x10
#define CMP201_FIFO_TEMP_EN__POS    4

/* FIFO PRESS EN bit */
#define CMP201_FIFO_PRESS_EN__REG    CMP201_REG_FIFO_CONFIG_0
#define CMP201_FIFO_PRESS_EN__MSK    0x08
#define CMP201_FIFO_PRESS_EN__POS    3

/* FIFO MODE bit */
#define CMP201_FIFO_MODE__REG    CMP201_REG_FIFO_CONFIG_0
#define CMP201_FIFO_MODE__MSK    0x02
#define CMP201_FIFO_MODE__POS    1

/* FIFO EN bit */
#define CMP201_FIFO_EN__REG    CMP201_REG_FIFO_CONFIG_0
#define CMP201_FIFO_EN__MSK    0x01
#define CMP201_FIFO_EN__POS    0

/* DATA SEL bit */
#define CMP201_DATA_SEL__REG    CMP201_REG_FIFO_CONFIG_1
#define CMP201_DATA_SEL__MSK    0x08
#define CMP201_DATA_SEL__POS    3

/* FIFO INT TYPE bit */
#define CMP201_FIFO_INT_TYPE__REG    CMP201_REG_INT_CTRL
#define CMP201_FIFO_INT_TYPE__MSK    0x80
#define CMP201_FIFO_INT_TYPE__POS    7

/* DRDY EN bit */
#define CMP201_DRDY_EN__REG    CMP201_REG_INT_CTRL
#define CMP201_DRDY_EN__MSK    0x40
#define CMP201_DRDY_EN__POS    6

/* FFULL EN bit */
#define CMP201_FFULL_EN__REG    CMP201_REG_INT_CTRL
#define CMP201_FFULL_EN__MSK    0x10
#define CMP201_FFULL_EN__POS    4

/* FWTM EN bit */
#define CMP201_FWTM_EN__REG    CMP201_REG_INT_CTRL
#define CMP201_FWTM_EN__MSK    0x08
#define CMP201_FWTM_EN__POS    3

/* INT LV bit */
#define CMP201_INT_LV__REG    CMP201_REG_INT_CTRL
#define CMP201_INT_LV__MSK    0x02
#define CMP201_INT_LV__POS    1

/* INT OD bit */
#define CMP201_INT_OD__REG    CMP201_REG_INT_CTRL
#define CMP201_INT_OD__MSK    0x01
#define CMP201_INT_OD__POS    0

/* I2C WDT SEL bit */
#define CMP201_I2C_WDT_SEL__REG    CMP201_REG_CONFIG
#define CMP201_I2C_WDT_SEL__MSK    0x04
#define CMP201_I2C_WDT_SEL__POS    2

/* I2C WDT EN bit */
#define CMP201_I2C_WDT_EN__REG    CMP201_REG_CONFIG
#define CMP201_I2C_WDT_EN__MSK    0x02
#define CMP201_I2C_WDT_EN__POS    1

/* SPI3 EN bit */
#define CMP201_SPI3_EN__REG    CMP201_REG_CONFIG
#define CMP201_SPI3_EN__MSK    0x01
#define CMP201_SPI3_EN__POS    0

/* PWR MODE bit */
#define CMP201_PWR_MODE__REG    CMP201_REG_PWR_CTRL
#define CMP201_PWR_MODE__MSK    0x30
#define CMP201_PWR_MODE__POS    4

/* TEMP EN bit */
#define CMP201_TEMP_EN__REG    CMP201_REG_PWR_CTRL
#define CMP201_TEMP_EN__MSK    0x02
#define CMP201_TEMP_EN__POS    1

/* PRESS EN bit */
#define CMP201_PRESS_EN__REG    CMP201_REG_PWR_CTRL
#define CMP201_PRESS_EN__MSK    0x01
#define CMP201_PRESS_EN__POS    0

typedef enum {
  CMP201_SLEEP_MODE 	= 0,
  CMP201_FORCED_MODE 	= 1,
  CMP201_NORMAL_MODE 	= 3,
} CMP201_PWR_MODE_Type;

typedef enum {
  CMP201_OSR_x1		= 0,
  CMP201_OSR_x2		= 1,
  CMP201_OSR_x4		= 2,
  CMP201_OSR_x8		= 3,
  CMP201_OSR_x16	= 4,
  CMP201_OSR_x32	= 5,
  CMP201_OSR_x64	= 6,
  CMP201_OSR_x128	= 7,
} CMP201_OSR_PT_Type;

typedef enum {
  CMP201_ODR_4ms	    = 0x00,
  CMP201_ODR_4_5ms	    = 0x01,
  CMP201_ODR_5ms	    = 0x02,
  CMP201_ODR_5_556ms    = 0x03,
  CMP201_ODR_6_25ms     = 0x04,
  CMP201_ODR_7ms	    = 0x05,
  CMP201_ODR_8ms	    = 0x06,
  CMP201_ODR_9ms	    = 0x07,
  CMP201_ODR_10ms	    = 0x08,
  CMP201_ODR_11_1ms	    = 0x09,
  CMP201_ODR_12_5ms	    = 0x0A,
  CMP201_ODR_14_286ms	= 0x0B,
  CMP201_ODR_16ms	    = 0x0C,
  CMP201_ODR_20ms	    = 0x0D,
  CMP201_ODR_25ms	    = 0x0E,
  CMP201_ODR_31_25ms    = 0x0F,
  CMP201_ODR_40ms       = 0x10,
  CMP201_ODR_50ms       = 0x11,
  CMP201_ODR_62_5ms     = 0x12,
  CMP201_ODR_80ms       = 0x13,
  CMP201_ODR_100ms      = 0x14,
  CMP201_ODR_125ms      = 0x15,
  CMP201_ODR_156_25ms   = 0x16,
  CMP201_ODR_200ms      = 0x17,
  CMP201_ODR_250ms      = 0x18,
  CMP201_ODR_312_5ms    = 0x19,
  CMP201_ODR_400ms      = 0x1A,
  CMP201_ODR_500ms      = 0x1B,
  CMP201_ODR_1000ms     = 0x1C,
  CMP201_ODR_2000ms     = 0x1D,
  CMP201_ODR_4000ms     = 0x1E,
  CMP201_ODR_8000ms     = 0x1F,
} CMP201_ODR_SEL_Type;

typedef enum {
  CMP201_FILTER_COE_T_0	     = 0,
  CMP201_FILTER_COE_T_1	     = 1,
  CMP201_FILTER_COE_T_3	     = 2,
  CMP201_FILTER_COE_T_7	     = 3,
  CMP201_FILTER_COE_T_15     = 4,
  CMP201_FILTER_COE_T_31     = 5,
  CMP201_FILTER_COE_T_63     = 6,
  CMP201_FILTER_COE_T_127    = 7,
} CMP201_IIR_COEF_T_Type;

typedef enum {
  CMP201_FILTER_COE_P_0	     = 0,
  CMP201_FILTER_COE_P_1	     = 1,
  CMP201_FILTER_COE_P_3	     = 2,
  CMP201_FILTER_COE_P_7	     = 3,
  CMP201_FILTER_COE_P_15     = 4,
  CMP201_FILTER_COE_P_31     = 5,
  CMP201_FILTER_COE_P_63     = 6,
  CMP201_FILTER_COE_P_127    = 7,
} CMP201_IIR_COEF_P_Type;

#define cmp201_get_bitslice(regvar, bitname)	\
  ((regvar & bitname##__MSK) >> bitname##__POS)

#define cmp201_set_bitslice(regvar, bitname, val)	\
  ((regvar & ~bitname##__MSK) | ((val<<bitname##__POS) & bitname##__MSK))




extern volatile unsigned int CMP201_DlyCnt;


u8 cmp201_burst_read(u8 u8Addr, u8 *pu8Data, u8 u8Len);

u8 cmp201_burst_write(u8 u8Addr, u8 *pu8Data, u8 u8Len);

void cmp201_software_reset_process(void);

u8 cmp201_enable_PT_meas(void);

void cmp201_initialization(void);

#endif

#endif

