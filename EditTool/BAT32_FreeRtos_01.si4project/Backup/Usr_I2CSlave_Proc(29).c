#ifndef __USR_I2CSLAVE_PROC_C__
#define __USR_I2CSLAVE_PROC_C__

#include <stdint.h>

#include "userdefine.h"
#include "BAT32A237.h"
#include "iica.h"

#include"Usr_Config.h"
#include"Usr_Main.h"
#include "Usr_Psf.h"

#include "Usr_I2CA_Slave.h"
#include "Usr_ALSensor.h"

#include"gpio.h"
#include"Usr_GPIO.h"

#include "Usr_DataFlash.h"


#include "Usr_I2CSlave_Proc.h"

//#define MD_RD_SN_CMDCODE1   0x3615
//#define MD_RD_SN_CMDCODE2   0xEC05
//#define MD_RD_SN_CMDLEN        18

uint8_t MD_SN[MD_RD_SN_CMDLEN];

static uint8_t crc_tmp;

void MD_SN_Update(void)
{   // Read Product SN;
    //g_iica0_tx_cnt = 18;
    
    MD_SN[0] = 0;
    MD_SN[1] = FW_VERSION_PART0;
    crc_tmp = compute_crc8(MD_SN,2);
    MD_SN[2] = crc_tmp;
    
    MD_SN[3] = FW_VERSION_PART1;
    MD_SN[4] = FW_VERSION_PART2;
    crc_tmp = compute_crc8(MD_SN+3,2);
    MD_SN[5] = crc_tmp;
    
    MD_SN[6] = 0;
    MD_SN[7] = 0;
    crc_tmp = compute_crc8(MD_SN+6,2);
    MD_SN[8] = crc_tmp;
    
    MD_SN[9] = 0;
    MD_SN[10] = 0;
    crc_tmp = compute_crc8(MD_SN+9,2);
    MD_SN[11] = crc_tmp;
    
    MD_SN[12] = TimeSn_Time>>8;
    MD_SN[13] = TimeSn_Time;
    crc_tmp = compute_crc8(MD_SN+12,2);
    MD_SN[14] = crc_tmp;
    
    MD_SN[15] = TimeSn_SN>>8;
    MD_SN[16] = TimeSn_SN;
    crc_tmp = compute_crc8(MD_SN+15,2);
    MD_SN[17] = crc_tmp;
}


//#define MD_RD_DATA_CMDCODE1   0xEC05
//#define MD_RD_DATA_CMDLEN        18

uint8_t MD_DATA[MD_RD_SN_CMDLEN];

void MD_DATA_Update(void)
{   // Read Datas;
    //g_iica0_tx_cnt = 18;
    
    #if 1
    MD_DATA[0] = Sens_LFL_U16_Cust>>8;
    MD_DATA[1] = Sens_LFL_U16_Cust;
    crc_tmp = compute_crc8(MD_DATA+0,2);
    MD_DATA[2] = crc_tmp;
    #endif
    
    MD_DATA[3] = ErrorData1_Cust>>8;
    MD_DATA[4] = ErrorData1_Cust;
    crc_tmp = compute_crc8(MD_DATA+3,2);
    MD_DATA[5] = crc_tmp;
    
    MD_DATA[6] = Psf_Gas_TypeCode_Cust>>8;
    MD_DATA[7] = Psf_Gas_TypeCode_Cust;
    crc_tmp = compute_crc8(MD_DATA+6,2);
    MD_DATA[8] = crc_tmp;
    
    MD_DATA[9] = TH_Sensor_Temperature_out_Cust>>8;
    MD_DATA[10] = TH_Sensor_Temperature_out_Cust;
    crc_tmp = compute_crc8(MD_DATA+9,2);
    MD_DATA[11] = crc_tmp;
    
    MD_DATA[12] = TH_Sensor_Humidity_out_Cust>>8;
    MD_DATA[13] = TH_Sensor_Humidity_out_Cust;
    crc_tmp = compute_crc8(MD_DATA+12,2);
    MD_DATA[14] = crc_tmp;
    
    #if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))
    MD_DATA[15] = ASC_Adjust_Total>>8;
    MD_DATA[16] = ASC_Adjust_Total;
    crc_tmp = compute_crc8(MD_DATA+15,2);
    MD_DATA[17] = crc_tmp;
    #else
    MD_DATA[15] = 0>>8;
    MD_DATA[16] = 0;
    crc_tmp = compute_crc8(MD_DATA+15,2);
    MD_DATA[17] = crc_tmp;
    #endif
}




#endif




