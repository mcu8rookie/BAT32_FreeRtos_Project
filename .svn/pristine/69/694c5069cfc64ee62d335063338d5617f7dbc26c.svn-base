#ifndef __USR_HDC2010_C__
#define __USR_HDC2010_C__


//#include "Usr_Code.h"

//#include"Usr_IIC_Soft.h"

#include "Usr_ALSensor.h"

#if((defined(SENSOR_HT_TYPE))&&(SENSOR_HT_TYPE == SENSOR_TYPE_HDC2010))

#include "Usr_HDC2010.h"

unsigned char HDC2010_InitData[9] = 
{
	(HDC2010_INT_CONFIG_DRDY_EN_DISABLE | \
		HDC2010_INT_CONFIG_TH_EN_DISABLE | \
		HDC2010_INT_CONFIG_TL_EN_DISABLE | \
		HDC2010_INT_CONFIG_HH_EN_DISABLE | \
		HDC2010_INT_CONFIG_HL_EN_DISABLE),
	0x00U,
	0x00U,
	0x00U,
	0xFFU,
	0x00U,
	0xFFU,
	(HDC2010_CONFIG_SOFT_RES_DISABLE | \
		HDC2010_CONFIG_AMM_DISABLED | \
		HDC2010_CONFIG_HEAT_EN_DISABLE | \
		HDC2010_CONFIG_DRDY_INT_EN_DISABLE | \
		HDC2010_CONFIG_INT_POL_LOW | \
		HDC2010_CONFIG_INT_MODE_LEVEL),

	(HDC2010_MEAS_CONFIG_TRES_14BIT | \
		HDC2010_MEAS_CONFIG_HRES_14BIT | \
		HDC2010_MEAS_CONFIG_MEAS_CONF_HT | \
		HDC2010_MEAS_CONFIG_MEAS_TRIG_NA),
};


void HDC2010_ReadID(unsigned char *pdat)
{
    i2c_burst_read(I2C_CHANNEL_HDC2010,HTS_I2C_Address_7B,0xFC, pdat, 4);
}

unsigned char HDC2010_InitSetup(void)
{
	//return i2c_burst_write(3,HTS_I2C_Address_7B,0x07, HDC2010_InitData, 8);
	return i2c_burst_write(3,HTS_I2C_Address_7B,0x07, HDC2010_InitData, 8);
}

unsigned char HDC2010_ConvertStart(void)
{
	unsigned char tmpbuf[1];
	tmpbuf[0] = HDC2010_InitData[8]+1;
	
	//return i2c_burst_write(3,HTS_I2C_Address_7B,0x0F, &(HDC2010_InitData[8]), 1);
	return i2c_burst_write(3,HTS_I2C_Address_7B,0x0F, tmpbuf, 1);
}

unsigned char HDC2010_ConvertStop(void)
{
	unsigned char tmpbuf[1];
	tmpbuf[0] = HDC2010_InitData[8];
	
	//return i2c_burst_write(3,HTS_I2C_Address_7B,0x0F, &(HDC2010_InitData[8]), 1);
	return i2c_burst_write(3,HTS_I2C_Address_7B,0x0F, tmpbuf, 1);
}


unsigned char HDC2010_ReadHT(unsigned char *pdat)
{
	return i2c_burst_read(I2C_CHANNEL_HDC2010,HTS_I2C_Address_7B,0x00, pdat, 4);
}

#endif

#endif



