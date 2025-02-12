#ifndef __USR_CMP201_C__
#define __USR_CMP201_C__


#include "Usr_Config.h"

//#include"Usr_IIC_Soft.h"

#include"Usr_Soft_I2C.h"

#include "Usr_CMP201.h"

typedef unsigned char u8;


#if(defined(SENSOR_PT_TYPE)&&(SENSOR_PT_TYPE == SENSOR_TYPE_CMP201))


volatile unsigned int CMP201_DlyCnt;



/*****************************************************************************
 *
 * Function : cmp201_burst_read
 *
 * @input : [u8Addr] -> register address
 *          [u8Len]  -> data length
 *
 * @output : [*pu8Data] -> data buffer 
 *
 * @return : 0 -> success
 *           other numbers(rc) -> receive wrong data
 *
 ****************************************************************************/
//


u8 cmp201_burst_read(u8 u8Addr, u8 *pu8Data, u8 u8Len)
{
    return(i2c_burst_read(I2C_CHANNEL_CMP201,CMP201_IIC_ADDR7B,u8Addr, pu8Data, u8Len));
}

/*****************************************************************************
 *
 * Function : cmp201_burst_write
 *
 * @input : [u8Addr]   -> register address 
 *          [*pu8Data] -> data buffer 
 *          [u8Len]    -> data length
 *
 * @output : N/A
 *
 * @return : 0 -> success
 *           other numbers(rc) -> receive wrong data
 *
 ****************************************************************************/
//
u8 cmp201_burst_write(u8 u8Addr, u8 *pu8Data, u8 u8Len)
{
    return(i2c_burst_write(I2C_CHANNEL_CMP201,CMP201_IIC_ADDR7B,u8Addr, pu8Data, u8Len));
}

/*****************************************************************************
 *
 * Function : cmp201_software_reset_process
 *
 * @input : N/A
 *
 * @output : N/A
 *
 * @return : 0 -> success
 *           others number -> error 
 *
 ****************************************************************************/
//
void cmp201_software_reset_process(void)
{
	u8 u8Data;
	
	u8Data = 0xB6;

	cmp201_burst_write(CMP201_REG_RESET, &u8Data, 1);
	
	//delay(100);	// wait 100msec
	
	CMP201_DlyCnt = 100+1;
	while(CMP201_DlyCnt>0);
}

/*****************************************************************************
 *
 * Function : cmp201_enable_PT_meas
 *
 * @input : N/A
 *
 * @output : N/A
 *
 * @return : 0 -> success
 *           others number -> error 
 *
 ****************************************************************************/
//
u8 cmp201_enable_PT_meas(void)
{
    u8 u8Data;
    
    u8Data = 0x33;
    
    return (cmp201_burst_write(CMP201_REG_PWR_CTRL, &u8Data, 1));
}

/*****************************************************************************
 *
 * Function : cmp201_initialization
 *
 * @input : N/A
 *
 * @output : N/A
 *
 * @return : 0 -> success
 *           others number -> error 
 *
 ****************************************************************************/
//
void cmp201_initialization(void)
{	
    u8 u8Data;
    
    cmp201_burst_read(CMP201_REG_REV_ID, &u8Data, 1);
	
    cmp201_burst_read(CMP201_REG_CHIP_ID, &u8Data, 1);
	
    u8Data = 0x00;
    cmp201_burst_write(CMP201_REG_FIFO_CONFIG_1, &u8Data, 1); 
	
    u8Data = 0x40;
    cmp201_burst_write(CMP201_REG_INT_CTRL, &u8Data, 1);
	
    u8Data = 0x77;
    cmp201_burst_write(CMP201_REG_OSR, &u8Data, 1);
	
    u8Data = 0x16;
    cmp201_burst_write(CMP201_REG_ODR, &u8Data, 1);
	
    u8Data = 0x00;
    cmp201_burst_write(CMP201_REG_FILTER, &u8Data, 1);
}


#endif

#endif


