#ifndef __USR_I2CA_SLAVE_C__
#define __USR_I2CA_SLAVE_C__


#include <stdint.h>

#include "Usr_Config.h"
#include "Usr_Debug.h"
#include "Usr_Psf.h"
#include "Usr_DataFlash.h"

#include "userdefine.h"
#include "BAT32A237.h"
#include "iica.h"

#include "Usr_Debug.h"

#include "Usr_I2CA_Slave.h"

#include"Usr_Main.h"

#include "User_SensorParam.h"

#if 0
//#define I2CA_SLAVE_ADDR_7B  (0x98>>1)
#define I2CA_SLAVE_ADDR_7B  (0x13)

#define I2CA_SLAVE_ADDR_WT  ((I2CA_SLAVE_ADDR_7B>>1)+0)
#define I2CA_SLAVE_ADDR_RD  ((I2CA_SLAVE_ADDR_7B>>1)+1)


#define I2CA_CMD_WT_DATA1   (0x01)
#define I2CA_CMD_WT_DATA2   (0x02)

#define I2CA_CMD_RD_DATA1   (0x11)
#define I2CA_CMD_RD_DATA2   (0x22)

#define DEF_I2CA_WT_FLG     (1)
#define DEF_I2CA_RD_FLG     (2)

#define DEF_I2CA_TX_MAX     (64)
#define DEF_I2CA_RX_MAX     (64)
#endif

uint8_t I2CA_WR_Flag;
uint8_t I2CA_Cmd_Flag;
uint16_t I2CA_Cmd_Code;

uint8_t I2CA_RX_Buff[DEF_I2CA_RX_MAX];
uint8_t I2CA_TX_Buff[DEF_I2CA_TX_MAX];

uint8_t I2CA_RX_Cnt;
uint8_t I2CA_RX_Buff2[DEF_I2CA_RX_MAX];


uint8_t YearMonthDateSN[12] = 
{
    DEF_YMDSN_YEAR1,
    DEF_YMDSN_YEAR2,
    DEF_YMDSN_CRC1,
    
    DEF_YMDSN_MONTH,
    DEF_YMDSN_DATE,
    DEF_YMDSN_CRC2,
    
    DEF_YMDSN_SN1,
    DEF_YMDSN_SN2,
    DEF_YMDSN_CRC3,
    
    DEF_YMDSN_SN3,
    DEF_YMDSN_SN4,
    DEF_YMDSN_CRC4,
    
};

void Usr_I2CA_InitSetup(void)
{
	IICA0_Init();

	//IICA->SVA0 = I2CA_SLAVE_ADDR_WT;

	g_iica0_master_status_flag = 0; /* iica0 master flag */

	g_iica0_slave_status_flag = 0;  /* iica0 slave flag */

	gp_iica0_rx_address = I2CA_RX_Buff;        /* iica0 receive buffer address */
	g_iica0_rx_len = DEF_I2CA_RX_MAX;             /* iica0 receive data length */
	g_iica0_rx_cnt = 0;             /* iica0 receive data count */
	g_iica0_rx_end = 0;             /* iica0 receive data end */

	gp_iica0_tx_address = I2CA_TX_Buff;        /* iica0 send buffer address */
	g_iica0_tx_len = 0;
	g_iica0_tx_cnt = 0;             /* iica0 send data count */
	g_iica0_tx_end = 0;             /* iica0 send data end */

	g_iica0_tx_count = 0;

	g_u16CurCmdCode = 0xFFFF;
	g_u8CmdEC05Type = 0;

	Psf_MeasurementFlag = 1;
}


uint8_t Usr_I2CA_isCmdCodeOK(uint16_t cmdCode)
{
	uint8_t ret = 0;

	if((cmdCode == 0xEC05)
		|| (cmdCode == 0x100F)
		|| (cmdCode == 0x3603)
		|| (cmdCode == 0x3606)
		|| (cmdCode == 0x3608)
		|| (cmdCode == 0x3615)
		|| ((cmdCode >= 0x1000) && (cmdCode <= 0x1009))
		|| ((cmdCode >= 0x1100) && (cmdCode <= 0x1115))
		|| ((cmdCode >= 0x1180) && (cmdCode <= 0x1195)))
	{
		ret = 1;
	}
		
	return ret;
}

uint8_t Usr_I2CA_isReadingCmd(uint16_t cmdCode)
{
	uint8_t ret = 0;

	if((cmdCode == 0x100F)
		|| (cmdCode == 0xEC05)
		|| ((cmdCode >= 0x1000) && (cmdCode <= 0x1009))
		|| ((cmdCode >= 0x1100) && (cmdCode <= 0x1115)))
	{
		ret = 1;
	}
		
	return ret;
}

	
uint8_t *Usr_I2CA_getBuffAddr(uint16_t cmdCode)
{
	uint8_t *pBuff = 0;	
		
	if(cmdCode == 0xEC05)
	{
		if(g_u8CmdEC05Type == 0)
		{
			pBuff = (uint8_t*)&g_tClientData;
		}
		else
		{
			pBuff = (uint8_t*)&g_tClientSN;
			g_u8CmdEC05Type = 0;
		}
	}
	else if( (cmdCode == 0x100F)
		|| ((cmdCode >= 0x1000) && (cmdCode <= 0x1009))
		|| ((cmdCode >= 0x1100) && (cmdCode <= 0x1115)))
	{
		uint8_t i = 0;
		tCmdVsAddrType tCmdVsAddr[] = 
		{
			{0x1000, (uint8_t*)&g_tSensor},
			{0x1001, (uint8_t*)&g_tSensor.TRawData},
			{0x1002, (uint8_t*)&g_tSensor.RawPPM},
			{0x1003, (uint8_t*)&g_tSensor.HumiCompVal},
			{0x1004, (uint8_t*)&g_tSensor.WarningFlag},
			{0x1005, (uint8_t*)&g_tSensor.HeaterRawData},
			{0x1006, (uint8_t*)&g_tSensor.T},
			{0x1007, (uint8_t*)&g_tSensor.WorkHour},
			{0x1008, (uint8_t*)&g_tSensor.T_Rate},
			{0x1009, (uint8_t*)&g_tSensor.ErrCode},
			{0x100F, (uint8_t*)&g_tSensor.FW_Ver_MSB},
			{0x1100, (uint8_t*)&g_tSensor.DeltaRawData},
			{0x1101, (uint8_t*)&g_tSensor.DeltaPPM},
			{0x1102, (uint8_t*)&g_tSensor.ConcentrationThres},
			{0x1103, (uint8_t*)&g_tSensor.RH_Coeff_P0_MSB},
			{0x1104, (uint8_t*)&g_tSensor.HumiCompSW},
			{0x1105, (uint8_t*)&g_tSensor.P_Coeff_P0_MSB},
			{0x1106, (uint8_t*)&g_tSensor.PressCompSW},
			{0x1107, (uint8_t*)&g_tSensor.HighRH_Time},
			{0x1108, (uint8_t*)&g_tSensor.SN_Date},
			{0x1109, (uint8_t*)&g_tSensor.T_Coeff_P0_MSB},
			{0x110A, (uint8_t*)&g_tSensor.LifeTimeNearThres},
			{0x110B, (uint8_t*)&g_tSensor.RH_Rate_Thres},
			{0x110C, (uint8_t*)&g_tSensor.CaliPPM0},
			{0x110D, (uint8_t*)&g_tSensor.CaliSRawData0},
			{0x110E, (uint8_t*)&g_tSensor.CoolTime},
			{0x110F, (uint8_t*)&g_tSensor.CaliTRawData},
			{0x1110, (uint8_t*)&g_tSensor.CaliP},
			{0x1111, (uint8_t*)&g_tSensor.CaliOffset},
			{0x1112, (uint8_t*)&g_tSensor.WorkDay},
			{0x1113, (uint8_t*)&g_tSensor.FilterNum},
			{0x1114, (uint8_t*)&g_tSensor.WarmUpTime},
			{0x1115, (uint8_t*)&g_tSensor.TSC_Coeff}
		};
		uint8_t size = sizeof(tCmdVsAddr)/sizeof(tCmdVsAddrType);
	
		for(i=0; i<size; i++)
		{
			if(cmdCode == tCmdVsAddr[i].cmd)
			{
				pBuff = tCmdVsAddr[i].addr;
				break;
			}
		}
	}

	return pBuff;
}

uint8_t Usr_I2CA_getWrCmdDataLen(uint16_t cmdCode)
{
	uint8_t cmdLen = 0;

	if(cmdCode == 0x3603)
	{
		cmdLen = 2;
	}
	else if(cmdCode == 0x3606)
	{
		cmdLen = 2;
	}
	else if(cmdCode == 0x3608)
	{
		cmdLen = 3+2;
	}
	else if((cmdCode >= 0x1180) && (cmdCode <= 0x1195))
	{
		tCmdVsLenType tCmdVsLen[] = 
		{
			{0x1180, 3+2},
			{0x1181, 3+2},
			{0x1182, 3+2},
			{0x1183, 48+2},
			{0x1184, 3+2},
			{0x1185, 18+2},
			{0x1186, 3+2},
			{0x1187, 9+2},
			{0x1188, 6+2},
			{0x1189, 24+2},
			{0x118A, 6+2},
			{0x118B, 3+2},
			{0x118C, 33+2},
			{0x118D, 33+2},
			{0x118E, 3+2},
			{0x118F, 3+2},
			{0x1190, 3+2},
			{0x1191, 3+2},
			{0x1192, 3+2},
			{0x1193, 3+2},
			{0x1194, 3+2},
			{0x1195, 3+2}
		};
		uint8_t size = sizeof(tCmdVsLen)/sizeof(tCmdVsLenType);
		uint8_t i = 0;

		for(i=0; i<size; i++)
		{
			if(cmdCode == tCmdVsLen[i].cmd)
			{
				cmdLen = tCmdVsLen[i].len;
				break;
			}
		}
	}

	return cmdLen;
}

uint8_t Usr_I2CA_getRdCmdDataLen(uint16_t cmdCode)
{
	uint8_t cmdLen = 0;

	if(Usr_I2CA_isReadingCmd(cmdCode))
	{
		tCmdVsLenType tCmdVsLen[] = 
		{
			{0xEC05, 18},
			{0x1000, 3},
			{0x1001, 9},
			{0x1002, 15},
			{0x1003, 6},
			{0x1004, 3},
			{0x1005, 3},
			{0x1006, 9},
			{0x1007, 6},
			{0x1008, 3},
			{0x1009, 3},
			{0x100F, 6},
			{0x1100, 3},
			{0x1101, 3},
			{0x1102, 3},
			{0x1103, 48},
			{0x1104, 3},
			{0x1105, 21},
			{0x1106, 3},
			{0x1107, 9},
			{0x1108, 6},
			{0x1109, 24},
			{0x110A, 6},
			{0x110B, 3},
			{0x110C, 33},
			{0x110D, 33},
			{0x110E, 3},
			{0x110F, 3},
			{0x1110, 3},
			{0x1111, 3},
			{0x1112, 3},
			{0x1113, 3},
			{0x1114, 3},
			{0x1115, 3}
		};
		uint8_t size = sizeof(tCmdVsLen)/sizeof(tCmdVsLenType);
		uint8_t i = 0;

		for(i=0; i<size; i++)
		{
			if(cmdCode == tCmdVsLen[i].cmd)
			{
				cmdLen = tCmdVsLen[i].len;
				break;
			}
		}
	}

	return cmdLen;
}


#if 1
uint8_t Usr_I2CA_StartMeasure(uint8_t *data, uint8_t dataLen)
{
    Psf_MeasurementFlag = 1;

	return 1;
}

uint8_t Usr_I2CA_ResetDevice(uint8_t *data, uint8_t dataLen)
{
    MCU_Reset_Flag = 1;
    Mcu_Timestamp  = 800;

	return 1;
}

uint8_t Usr_I2CA_Set_GasType(uint8_t *data, uint8_t dataLen)
{
	uint8_t ret = 0;

	if(data && (dataLen == 3))
	{
		uint8_t u8Crc = compute_crc8(&data[0], 2);
		uint16_t u16GasType = (data[0]<<8) | data[1];
		
		if(u8Crc == data[2])
		{
			if((u16GasType == 0x0018)
				|| (u16GasType == 0x0019)
				|| (u16GasType == 0x001B)
				|| (u16GasType == 0x001C)
				|| (u16GasType == 0x001D))
			{
				Psf_Gas_TypeCode = u16GasType;
				
				DF_Data[DEF_GASTYPE_INDEX+0] = data[1];
				DF_Data[DEF_GASTYPE_INDEX+1] = data[0];
				DF_UpdateReal_Flag = 1;
						
				ret = 1;
			}
		}
	}

	return ret;
}

uint8_t Usr_I2CA_Set_DeltaRawData(uint8_t *data, uint8_t dataLen)
{
	uint8_t ret = 0;

	if(data && (dataLen == 3))
	{
		uint8_t u8Crc = compute_crc8(&data[0], 2);
		uint8_t *pTemp = (uint8_t*)&g_tSensor.DeltaRawData;
		
		if(u8Crc == data[2])
		{
			Usr_Delta_Raw = (data[0]<<8) | data[1];
			
            DF_Data[DEF_DELTA_RAW_INDEX+0] = data[1];
            DF_Data[DEF_DELTA_RAW_INDEX+1] = data[0];
            DF_UpdateReal_Flag = 1;
					
			pTemp[0] = data[0];
			pTemp[1] = data[1];
			pTemp[2] = data[2];
			
			ret = 1;
		}
	}

	return ret;
}

uint8_t Usr_I2CA_Set_DeltaPPM(uint8_t *data, uint8_t dataLen)
{
	uint8_t ret = 0;

	if(data && (dataLen == 3))
	{
		uint8_t u8Crc = compute_crc8(&data[0], 2);
		uint8_t *pTemp = (uint8_t*)&g_tSensor.DeltaPPM;
		
		if(u8Crc == data[2])
		{
			Usr_Delta_PPM1 = (data[0]<<8) | data[1];
			
            DF_Data[DEF_DELTA_PPM_INDEX+0] = data[1];
            DF_Data[DEF_DELTA_PPM_INDEX+1] = data[0];
            DF_UpdateReal_Flag = 1;
					
			pTemp[0] = data[0];
			pTemp[1] = data[1];
			pTemp[2] = data[2];
			
			ret = 1;
		}
	}

	return ret;
}

uint8_t Usr_I2CA_Set_Concentration_Thres(uint8_t *data, uint8_t dataLen)
{
	uint8_t ret = 0;

	if(data && (dataLen == 3))
	{
		uint8_t u8Crc = compute_crc8(&data[0], 2);
		uint8_t *pTemp = (uint8_t*)&g_tSensor.ConcentrationThres;
		
		if(u8Crc == data[2])
		{
			Concen_Threshold = (data[0]<<8) | data[1];
			
            DF_Data[DEF_CONCEN_THRE_INDEX+0] = data[1];
            DF_Data[DEF_CONCEN_THRE_INDEX+1] = data[0];
            DF_UpdateReal_Flag = 1;
			
			pTemp[0] = data[0];
			pTemp[1] = data[1];
			pTemp[2] = data[2];
			
			ret = 1;
		}
	}

	return ret;
}

uint8_t Usr_I2CA_Set_HumiCoeff(uint8_t *data, uint8_t dataLen)
{
	uint8_t ret = 1;

	if(data && (dataLen == 48))
	{
		uint8_t i = 0;
		uint8_t u8Crc = 0;

		for(i=0; i<dataLen; i+=3)
		{
			u8Crc = compute_crc8(&data[i], 2);
			if(u8Crc != data[i+2])
			{
				ret = 0;
				break;
			}
		}
		
		if(ret)
		{
			uint8_t j = 0;
			uint8_t *pTemp1 = (uint8_t*)HumComp_M2_S;
			uint8_t *pTemp2 = (uint8_t*)&g_tSensor.RH_Coeff_P0_MSB;
			
			for(i=0; i<dataLen; i+=6)
			{
				pTemp1[j*4+0] = data[i+4];
				pTemp1[j*4+1] = data[i+3];
				pTemp1[j*4+2] = data[i+1];
				pTemp1[j*4+3] = data[i+0];
				
				DF_Data[DEF_HUMCOMP_PARAM_INDEX+j*4+0] = data[i+4];
				DF_Data[DEF_HUMCOMP_PARAM_INDEX+j*4+1] = data[i+3];
				DF_Data[DEF_HUMCOMP_PARAM_INDEX+j*4+2] = data[i+1];
				DF_Data[DEF_HUMCOMP_PARAM_INDEX+j*4+3] = data[i+0];
				
				j++;
				
				pTemp2[i+0] = data[i+0];
				pTemp2[i+1] = data[i+1];
				pTemp2[i+2] = data[i+2];
				pTemp2[i+3] = data[i+3];
				pTemp2[i+4] = data[i+4];
				pTemp2[i+5] = data[i+5];
			}
			
			DF_UpdateReal_Flag = 1;
		}
	}

	return ret;
}

uint8_t Usr_I2CA_Set_Humi_Comp_SW(uint8_t *data, uint8_t dataLen)
{
	uint8_t ret = 0;

	if(data && (dataLen == 3))
	{
		uint8_t u8Crc = compute_crc8(&data[0], 2);
		uint8_t *pTemp = (uint8_t*)&g_tSensor.HumiCompSW;
		
		if(u8Crc == data[2])
		{
			HumComp_Flag = (data[0]<<8) | data[1];
			
			DF_Data[DEF_HUMCOMP_FLAG_INDEX+0] = data[1];
			DF_Data[DEF_HUMCOMP_FLAG_INDEX+1] = data[0];
			DF_UpdateReal_Flag = 1;
			
			pTemp[0] = data[0];
			pTemp[1] = data[1];
			pTemp[2] = data[2];
			ret = 1;
		}
	}

	return ret;
}

uint8_t Usr_I2CA_Set_PressCoeff(uint8_t *data, uint8_t dataLen)
{
	uint8_t ret = 1;

	if(data && (dataLen == 18))
	{
		uint8_t i = 0;
		uint8_t u8Crc = 0;

		for(i=0; i<dataLen; i+=3)
		{
			u8Crc = compute_crc8(&data[i], 2);
			if(u8Crc != data[i+2])
			{
				ret = 0;
				break;
			}
		}
		
		if(ret)
		{
			uint8_t *pTemp1 = (uint8_t*)PresComp_K;
			uint8_t *pTemp2 = (uint8_t*)&g_tSensor.P_Coeff_P0_MSB;
			uint8_t j = 0;
			
			for(i=0; i<dataLen; i+=6)
			{
				pTemp1[j*4+0] = data[i+4];
				pTemp1[j*4+1] = data[i+3];
				pTemp1[j*4+2] = data[i+1];
				pTemp1[j*4+3] = data[i+0];
				
				DF_Data[DEF_PRESCOMP_PARAM_INDEX+j*4+0] = data[i+4];
				DF_Data[DEF_PRESCOMP_PARAM_INDEX+j*4+1] = data[i+3];
				DF_Data[DEF_PRESCOMP_PARAM_INDEX+j*4+2] = data[i+1];
				DF_Data[DEF_PRESCOMP_PARAM_INDEX+j*4+3] = data[i+0];
				
				j++;
				
				pTemp2[i+0] = data[i+0];
				pTemp2[i+1] = data[i+1];
				pTemp2[i+2] = data[i+2];
				pTemp2[i+3] = data[i+3];
				pTemp2[i+4] = data[i+4];
				pTemp2[i+5] = data[i+5];
			}
			
			DF_UpdateReal_Flag = 1;
		}
	}

	return ret;
}

uint8_t Usr_I2CA_Set_Press_Comp_SW(uint8_t *data, uint8_t dataLen)
{
	uint8_t ret = 0;

	if(data && (dataLen == 3))
	{
		uint8_t u8Crc = compute_crc8(&data[0], 2);
		uint8_t *pTemp = (uint8_t*)&g_tSensor.PressCompSW;
		
		if(u8Crc == data[2])
		{
			PresComp_Flag = (data[0]<<8) | data[1];
			
			DF_Data[DEF_PRESCOMP_FLAG_INDEX+0] = data[1];
			DF_Data[DEF_PRESCOMP_FLAG_INDEX+1] = data[0];
			DF_UpdateReal_Flag = 1;
			
			pTemp[0] = data[0];
			pTemp[1] = data[1];
			pTemp[2] = data[2];
			ret = 1;
		}
	}

	return ret;
}

uint8_t Usr_I2CA_Set_Aging_Time(uint8_t *data, uint8_t dataLen)
{
	uint8_t ret = 1;

	if(data && (dataLen == 9))
	{
		uint8_t i = 0;
		uint8_t u8Crc = 0;
		
		for(i=0; i<dataLen; i+=3)
		{
			u8Crc = compute_crc8(&data[i], 2);
			if(u8Crc != data[i+2])
			{
				ret = 0;
				break;
			}
		}

		if(ret)
		{
			uint8_t *pTemp = (uint8_t*)&g_tSensor.HighRH_Time;
			
			for(i=0; i<dataLen; i+=3)
			{
				pTemp[i+0] = data[i+0];
				pTemp[i+1] = data[i+1];
				pTemp[i+2] = data[i+2];
			}
		}
	}

	return ret;
}

uint8_t Usr_I2CA_Set_SerialNum(uint8_t *data, uint8_t dataLen)
{
	uint8_t ret = 1;

	if(data && (dataLen == 6))
	{
		uint8_t i = 0;
		uint8_t u8Crc = 0;
		uint8_t *pTemp = (uint8_t*)&g_tSensor.SN_Date;
		
		for(i=0; i<dataLen; i+=3)
		{
			u8Crc = compute_crc8(&data[i], 2);
			if(u8Crc != data[i+2])
			{
				ret = 0;
				break;
			}
		}

		if(ret)
		{
			for(i=0; i<dataLen; i++)
			{
				pTemp[i] = data[i];
			}
			
			TimeSn_Time = (data[0]<<16) | data[1];
			TimeSn_SN   = (data[3]<<16) | data[4];
			
			DF_Data[DEF_TIME_SN_INDEX+0] = data[1];
			DF_Data[DEF_TIME_SN_INDEX+1] = data[0];
			DF_Data[DEF_TIME_SN_INDEX+2] = data[4];
			DF_Data[DEF_TIME_SN_INDEX+3] = data[3];

			DF_UpdateReal_Flag = 1;
		}
	}

	return ret;
}

uint8_t Usr_I2CA_Set_T_CompCoeff(uint8_t *data, uint8_t dataLen)
{
	uint8_t ret = 1;

	if(data && (dataLen == 24))
	{
		uint8_t i = 0;
		uint8_t u8Crc = 0;
		
		for(i=0; i<dataLen; i+=3)
		{
			u8Crc = compute_crc8(&data[i], 2);
			if(u8Crc != data[i+2])
			{
				ret = 0;
				break;
			}
		}

		if(ret)
		{
			uint8_t *pTemp = (uint8_t*)&g_tSensor.T_Coeff_P0_MSB;
			
			for(i=0; i<dataLen; i++)
			{
				pTemp[i] = data[i];
			}
			
			TComp_P0 = (data[3]<<8)  | data[4];
			TComp_P1 = (data[9]<<8)  | data[10];
			TComp_P2 = (data[12]<<24) | (data[13]<<16) | (data[15]<<8) | data[16];
			TComp_P3 = (data[18]<<24) | (data[19]<<16) | (data[21]<<8) | data[22];
			
			DF_Data[DEF_TCOMP_P0_INDEX+0] = (uint8_t)TComp_P0;
			DF_Data[DEF_TCOMP_P0_INDEX+1] = (uint8_t)(TComp_P0>>8);

			DF_Data[DEF_TCOMP_P1_INDEX+0] = (uint8_t)TComp_P1;
			DF_Data[DEF_TCOMP_P1_INDEX+1] = (uint8_t)(TComp_P1>>8);

			DF_Data[DEF_TCOMP_P2_INDEX+0] = (uint8_t)TComp_P2;
			DF_Data[DEF_TCOMP_P2_INDEX+1] = (uint8_t)(TComp_P2>>8);
			DF_Data[DEF_TCOMP_P2_INDEX+2] = (uint8_t)(TComp_P2>>16);
			DF_Data[DEF_TCOMP_P2_INDEX+3] = (uint8_t)(TComp_P2>>24);

			DF_Data[DEF_TCOMP_P3_INDEX+0] = (uint8_t)TComp_P3;
			DF_Data[DEF_TCOMP_P3_INDEX+1] = (uint8_t)(TComp_P3>>8);
			DF_Data[DEF_TCOMP_P3_INDEX+2] = (uint8_t)(TComp_P3>>16);
			DF_Data[DEF_TCOMP_P3_INDEX+3] = (uint8_t)(TComp_P3>>24);

			DF_UpdateReal_Flag = 1;
		}
	}

	return ret;
}

uint8_t Usr_I2CA_Set_LifeTime_Thres(uint8_t *data, uint8_t dataLen)
{
	uint8_t ret = 1;

	if(data && (dataLen == 6))
	{
		uint8_t i = 0;
		uint8_t u8Crc = 0;
		uint8_t *pTemp = (uint8_t*)&g_tSensor.LifeTimeNearThres;
		
		for(i=0; i<dataLen; i+=3)
		{
			u8Crc = compute_crc8(&data[i], 2);
			if(u8Crc != data[i+2])
			{
				ret = 0;
				break;
			}
		}

		if(ret)
		{
			for(i=0; i<dataLen; i+=3)
			{
				pTemp[i+0] = data[i+0];
				pTemp[i+1] = data[i+1];
				pTemp[i+2] = data[i+2];
			}
		}
	}

	return ret;
}

uint8_t Usr_I2CA_Set_RH_Rate_Thres(uint8_t *data, uint8_t dataLen)
{
	uint8_t ret = 0;

	if(data && (dataLen == 3))
	{
		uint8_t u8Crc = 0;
		uint8_t *pTemp = (uint8_t*)&g_tSensor.RH_Rate_Thres;
		
		u8Crc = compute_crc8(&data[0], 2);
		if(u8Crc == data[2])
		{
			pTemp[0] = data[0];
			pTemp[1] = data[1];
			pTemp[2] = data[2];
			ret = 1;
		}
	}

	return ret;
}

uint8_t Usr_I2CA_Set_CaliPPM(uint8_t *data, uint8_t dataLen)
{
	uint8_t ret = 1;

	if(data && (dataLen == 33))
	{
		uint8_t i = 0;
		uint8_t u8Crc = 0;
		
		for(i=0; i<dataLen; i+=3)
		{
			u8Crc = compute_crc8(&data[i], 2);
			if(u8Crc != data[i+2])
			{
				ret = 0;
				break;
			}
		}
		
		if(ret)
		{
			uint8_t *pTemp = (uint8_t*)&g_tSensor.CaliPPM0;
			uint8_t j = 0;
			
			for(i=0; i<dataLen; i+=3)
			{
				Sens_TableY[j] = (data[i+0]<<8) | data[i+1];
				
				DF_Data[DEF_TABLEY_INDEX+j*2+0] = data[i+1];
				DF_Data[DEF_TABLEY_INDEX+j*2+1] = data[i+0];
				
				j++;

				pTemp[i+0] = data[i+0];
				pTemp[i+1] = data[i+1];
				pTemp[i+2] = data[i+2];
			}
			
			DF_UpdateReal_Flag = 1;
		}
	}

	return ret;
}

uint8_t Usr_I2CA_Set_CaliRawData(uint8_t *data, uint8_t dataLen)
{
	uint8_t ret = 1;

	if(data && (dataLen == 33))
	{
		uint8_t i = 0;
		uint8_t u8Crc = 0;
		
		for(i=0; i<dataLen; i+=3)
		{
			u8Crc = compute_crc8(&data[i], 2);
			if(u8Crc != data[i+2])
			{
				ret = 0;
				break;
			}
		}
		
		if(ret)
		{
			uint8_t *pTemp = (uint8_t*)&g_tSensor.CaliSRawData0;
			uint8_t j = 0;
			
			for(i=0; i<dataLen; i+=3)
			{
				Sens_TableX[j] = (data[i]<<8) | data[i+1];
				
				DF_Data[DEF_TABLEX_INDEX+j*2+0] = data[i+1];
				DF_Data[DEF_TABLEX_INDEX+j*2+1] = data[i+0];
				
				j++;
				
				pTemp[i+0] = data[i+0];
				pTemp[i+1] = data[i+1];
				pTemp[i+2] = data[i+2];
			}
			
			DF_UpdateReal_Flag = 1;
		}
	}

	return ret;
}

uint8_t Usr_I2CA_Set_CoolTime(uint8_t *data, uint8_t dataLen)
{
	uint8_t ret = 0;

	if(data && (dataLen == 3))
	{
		uint8_t u8Crc = compute_crc8(&data[0], 2);
		uint8_t *pTemp = (uint8_t*)&g_tSensor.CoolTime;
		
		if(u8Crc == data[2])
		{
			Sens_CoolTime = (data[0]<<8) | data[1];

			DF_Data[DEF_COOLTIME_INDEX+0] = data[1];
			DF_Data[DEF_COOLTIME_INDEX+1] = data[0];
			DF_UpdateReal_Flag = 1;
			
			pTemp[0] = data[0];
			pTemp[1] = data[1];
			pTemp[2] = data[2];
			ret = 1;
		}
	}

	return ret;
}

uint8_t Usr_I2CA_Set_CaliTRawData(uint8_t *data, uint8_t dataLen)
{
	uint8_t ret = 0;

	if(data && (dataLen == 3))
	{
		uint8_t u8Crc = compute_crc8(&data[0], 2);
		uint8_t *pTemp = (uint8_t*)&g_tSensor.CaliTRawData;
		
		if(u8Crc == data[2])
		{
			TComp_TRawBase = (data[0]<<8) | data[1];
			
			DF_Data[DEF_TRAWBASE_INDEX+0] = data[1];
			DF_Data[DEF_TRAWBASE_INDEX+1] = data[0];
			DF_UpdateReal_Flag = 1;
			
			pTemp[0] = data[0];
			pTemp[1] = data[1];
			pTemp[2] = data[2];
			ret = 1;
		}
	}

	return ret;
}

uint8_t Usr_I2CA_Set_CaliPressure(uint8_t *data, uint8_t dataLen)
{
	uint8_t ret = 0;

	if(data && (dataLen == 3))
	{
		uint8_t u8Crc = compute_crc8(&data[0], 2);
		uint8_t *pTemp = (uint8_t*)&g_tSensor.CaliP;
		
		if(u8Crc == data[2])
		{
			PresComp_PBase = (data[0]<<8) | data[1];
			
			DF_Data[DEF_PRESCOMP_PBASE_INDEX+0] = data[1];
			DF_Data[DEF_PRESCOMP_PBASE_INDEX+1] = data[0];
			DF_UpdateReal_Flag = 1;
			
			pTemp[0] = data[0];
			pTemp[1] = data[1];
			pTemp[2] = data[2];
			ret = 1;
		}
	}

	return ret;
}

uint8_t Usr_I2CA_Set_CaliOffset(uint8_t *data, uint8_t dataLen)
{
	uint8_t ret = 0;

	if(data && (dataLen == 3))
	{
		uint8_t u8Crc = compute_crc8(&data[0], 2);
		uint8_t *pTemp = (uint8_t*)&g_tSensor.CaliOffset;
		
		if(u8Crc == data[2])
		{
			Sens_DC_Y = (data[0]<<8) | data[1];
			
			DF_Data[DEF_DC_Y_INDEX+0] = data[1];
			DF_Data[DEF_DC_Y_INDEX+1] = data[0];
			DF_UpdateReal_Flag = 1;
			
			pTemp[0] = data[0];
			pTemp[1] = data[1];
			pTemp[2] = data[2];
			ret = 1;
		}
	}

	return ret;
}

uint8_t Usr_I2CA_Set_LifeTime(uint8_t *data, uint8_t dataLen)
{
	uint8_t ret = 0;

	if(data && (dataLen == 3))
	{
		uint8_t u8Crc = compute_crc8(&data[0], 2);
		uint8_t *pTemp = (uint8_t*)&g_tSensor.WorkDay;
		
		if(u8Crc == data[2])
		{
			pTemp[0] = data[0];
			pTemp[1] = data[1];
			pTemp[2] = data[2];
			ret = 1;
		}
	}

	return ret;
}

uint8_t Usr_I2CA_Set_FilterNum(uint8_t *data, uint8_t dataLen)
{
	uint8_t ret = 0;

	if(data && (dataLen == 3))
	{
		uint8_t u8Crc = compute_crc8(&data[0], 2);
		uint8_t *pTemp = (uint8_t*)&g_tSensor.FilterNum;
		
		if(u8Crc == data[2])
		{
            Sens_FilterCnt = (data[0]<<8) | data[1];
            
            if(Sens_FilterCnt > DEF_SRAW_FILTERMAX)
            {
                Sens_FilterCnt = DEF_SRAW_FILTERMAX;
            }
            else if(Sens_FilterCnt < 1)
            {
                Sens_FilterCnt = 1;
            }
            
            FilterIndex = 0;
            FilterTotal = 0;
			
			DF_Data[DEF_FILTERCNT_INDEX+0] = (uint8_t)Sens_FilterCnt;
			DF_Data[DEF_FILTERCNT_INDEX+1] = (uint8_t)(Sens_FilterCnt>>8);
			DF_UpdateReal_Flag = 1;
			
			pTemp[0] = (uint8_t)(Sens_FilterCnt>>8);
			pTemp[1] = (uint8_t)Sens_FilterCnt;
			pTemp[2] = compute_crc8(pTemp, 2);
			
			ret = 1;
		}
	}

	return ret;
}

uint8_t Usr_I2CA_Set_WarmUpTime(uint8_t *data, uint8_t dataLen)
{
	uint8_t ret = 0;

	if(data && (dataLen == 3))
	{
		uint8_t u8Crc = compute_crc8(&data[0], 2);
		uint8_t *pTemp = (uint8_t*)&g_tSensor.WarmUpTime;
		
		if(u8Crc == data[2])
		{
			Sens_PreHeatTime = (data[0]<<8) | data[1];
			
			DF_Data[DEF_PREHEATTIME_INDEX+0] = data[1];
			DF_Data[DEF_PREHEATTIME_INDEX+1] = data[0];
			DF_UpdateReal_Flag = 1;
			
			pTemp[0] = data[0];
			pTemp[1] = data[1];
			pTemp[2] = data[2];
			ret = 1;
		}
	}

	return ret;
}

uint8_t Usr_I2CA_Set_TSC_Coeff(uint8_t *data, uint8_t dataLen)
{
	uint8_t ret = 0;

	if(data && (dataLen == 3))
	{
		uint8_t u8Crc = compute_crc8(&data[0], 2);
		uint8_t *pTemp = (uint8_t*)&g_tSensor.TSC_Coeff;
		
		if(u8Crc == data[2])
		{
			TmpRate_P = (data[0]<<8) | data[1];
			
			DF_Data[DEF_TMPRATE_P_INDEX+0] = data[1];
			DF_Data[DEF_TMPRATE_P_INDEX+1] = data[0];
			DF_UpdateReal_Flag = 1;
			
			pTemp[0] = data[0];
			pTemp[1] = data[1];
			pTemp[2] = data[2];
			ret = 1;
		}
	}

	return ret;
}

tCmdVsFuncType IIC_Wr_Cmd_Func[] = 
{
	{0x3603, Usr_I2CA_StartMeasure},
	{0x3606, Usr_I2CA_ResetDevice},
	{0x3608, Usr_I2CA_Set_GasType},

	{0x1180, Usr_I2CA_Set_DeltaRawData},
	{0x1181, Usr_I2CA_Set_DeltaPPM},
	{0x1182, Usr_I2CA_Set_Concentration_Thres},
	{0x1183, Usr_I2CA_Set_HumiCoeff},
	{0x1184, Usr_I2CA_Set_Humi_Comp_SW},
	{0x1185, Usr_I2CA_Set_PressCoeff},
	{0x1186, Usr_I2CA_Set_Press_Comp_SW},
	{0x1187, Usr_I2CA_Set_Aging_Time},
	{0x1188, Usr_I2CA_Set_SerialNum},
	{0x1189, Usr_I2CA_Set_T_CompCoeff},
	{0x118A, Usr_I2CA_Set_LifeTime_Thres},
	{0x118B, Usr_I2CA_Set_RH_Rate_Thres},
	{0x118C, Usr_I2CA_Set_CaliPPM},
	{0x118D, Usr_I2CA_Set_CaliRawData},
	{0x118E, Usr_I2CA_Set_CoolTime},
	{0x118F, Usr_I2CA_Set_CaliTRawData},
	{0x1190, Usr_I2CA_Set_CaliPressure},
	{0x1191, Usr_I2CA_Set_CaliOffset},
	{0x1192, Usr_I2CA_Set_LifeTime},
	{0x1193, Usr_I2CA_Set_FilterNum},
	{0x1194, Usr_I2CA_Set_WarmUpTime},
	{0x1195, Usr_I2CA_Set_TSC_Coeff}	
};
void Usr_I2CA_MainLoop(void)
{
	if(g_u8CmdOK == 1)
	{
		uint8_t i = 0;
		uint8_t data[DEF_I2CA_RX_MAX] = {0};
		uint8_t dataLen = g_u16CurCmdLen-2;
		uint8_t size = sizeof(IIC_Wr_Cmd_Func)/sizeof(tCmdVsFuncType);
		uint16_t cmdCode = (I2CA_RX_Buff[0]<<8) | I2CA_RX_Buff[1];

		g_u8CmdOK = 0;

		for(i=0; i<dataLen; i++)
		{
			data[i] = I2CA_RX_Buff[i+2];
		}

		for(i=0; i<size; i++)
		{
			if(IIC_Wr_Cmd_Func[i].cmd == cmdCode)
			{
				IIC_Wr_Cmd_Func[i].pFunc(data, dataLen);
				break;
			}
		}
	}
}

#endif

#if 1   // CRC algorithm from Midea little board project;
#define CRC8_POLYNOMIAL 0x31
#define CRC8_INIT       0xFF

uint8_t sensirion_common_generate(const uint8_t *data,uint16_t count)
{
    uint16_t current_byte;
    uint8_t crc = CRC8_INIT;
    uint8_t crc_bit;
    /* calculates 8-Bit checksum with given polynomial */
    for(current_byte=0; current_byte<count; ++current_byte)
    {
        crc ^= (data[current_byte]);
        for(crc_bit=8; crc_bit>0; --crc_bit)
        {
            if(crc&0x80)
            {
                crc = (crc<<1)^CRC8_POLYNOMIAL;
            }
            else
            {
                crc = (crc<<1);
            }
        }
    }
    return crc;
}

#endif

#if 1   // CRC algorithm from HuangShiliang for Midea little board project;
static const uint8_t crc8_table[256] =
{
  0x00, 0x31, 0x62, 0x53, 0xc4, 0xf5, 0xa6, 0x97, 0xb9, 0x88, 0xdb, 0xea, 0x7d, 0x4c, 0x1f, 0x2e, 
  0x43, 0x72, 0x21, 0x10, 0x87, 0xb6, 0xe5, 0xd4, 0xfa, 0xcb, 0x98, 0xa9, 0x3e, 0x0f, 0x5c, 0x6d, 
  0x86, 0xb7, 0xe4, 0xd5, 0x42, 0x73, 0x20, 0x11, 0x3f, 0x0e, 0x5d, 0x6c, 0xfb, 0xca, 0x99, 0xa8, 
  0xc5, 0xf4, 0xa7, 0x96, 0x01, 0x30, 0x63, 0x52, 0x7c, 0x4d, 0x1e, 0x2f, 0xb8, 0x89, 0xda, 0xeb, 
  0x3d, 0x0c, 0x5f, 0x6e, 0xf9, 0xc8, 0x9b, 0xaa, 0x84, 0xb5, 0xe6, 0xd7, 0x40, 0x71, 0x22, 0x13, 
  0x7e, 0x4f, 0x1c, 0x2d, 0xba, 0x8b, 0xd8, 0xe9, 0xc7, 0xf6, 0xa5, 0x94, 0x03, 0x32, 0x61, 0x50, 
  0xbb, 0x8a, 0xd9, 0xe8, 0x7f, 0x4e, 0x1d, 0x2c, 0x02, 0x33, 0x60, 0x51, 0xc6, 0xf7, 0xa4, 0x95, 
  0xf8, 0xc9, 0x9a, 0xab, 0x3c, 0x0d, 0x5e, 0x6f, 0x41, 0x70, 0x23, 0x12, 0x85, 0xb4, 0xe7, 0xd6, 
  0x7a, 0x4b, 0x18, 0x29, 0xbe, 0x8f, 0xdc, 0xed, 0xc3, 0xf2, 0xa1, 0x90, 0x07, 0x36, 0x65, 0x54, 
  0x39, 0x08, 0x5b, 0x6a, 0xfd, 0xcc, 0x9f, 0xae, 0x80, 0xb1, 0xe2, 0xd3, 0x44, 0x75, 0x26, 0x17, 
  0xfc, 0xcd, 0x9e, 0xaf, 0x38, 0x09, 0x5a, 0x6b, 0x45, 0x74, 0x27, 0x16, 0x81, 0xb0, 0xe3, 0xd2, 
  0xbf, 0x8e, 0xdd, 0xec, 0x7b, 0x4a, 0x19, 0x28, 0x06, 0x37, 0x64, 0x55, 0xc2, 0xf3, 0xa0, 0x91, 
  0x47, 0x76, 0x25, 0x14, 0x83, 0xb2, 0xe1, 0xd0, 0xfe, 0xcf, 0x9c, 0xad, 0x3a, 0x0b, 0x58, 0x69, 
  0x04, 0x35, 0x66, 0x57, 0xc0, 0xf1, 0xa2, 0x93, 0xbd, 0x8c, 0xdf, 0xee, 0x79, 0x48, 0x1b, 0x2a, 
  0xc1, 0xf0, 0xa3, 0x92, 0x05, 0x34, 0x67, 0x56, 0x78, 0x49, 0x1a, 0x2b, 0xbc, 0x8d, 0xde, 0xef, 
  0x82, 0xb3, 0xe0, 0xd1, 0x46, 0x77, 0x24, 0x15, 0x3b, 0x0a, 0x59, 0x68, 0xff, 0xce, 0x9d, 0xac
};



// 使用CRC8表计算数据的CRC8值
//static uint8_t compute_crc8(uint8_t *data, uint16_t size) 
uint8_t compute_crc8(uint8_t *data, uint16_t size)
{
    //uint8_t crc = 0x00;  // 初始值设置为0
    uint8_t crc = 0xFF;  // 初始值设置为0
    
    while(size--) 
    {
        crc = crc8_table[crc ^ (*data)];
        data++;
    }
    return crc;
}
#endif



#if(defined(DEF_I2C_TYPE)&&(DEF_I2C_TYPE==DEF_I2C_TYPE_PSF))

#endif

#if(defined(DEF_I2C_TYPE)&&(DEF_I2C_TYPE==DEF_I2C_TYPE_MIDEA))

#if 0
#define DEF_PRODUCT_NBR     (0x12345678)
#define DEF_SERIAL_NBR1     (0x12345678)
#define DEF_SERIAL_NBR2     (0x9ABCDEF0)
#endif

uint8_t Usr_Product_Nbr[4] = 
{
    0x12,
    0x34,
    0x56,
    0x78
};

uint8_t Usr_Serial_Nbr1[8] = 
{
    0x12,
    0x34,
    0x56,
    0x78,
    0x9A,
    0xBC,
    0xDE,
    0xF0
};

uint8_t Usr_SnCrc1;
uint8_t Usr_SnCrc2;
uint8_t Usr_SnCrc3;
uint8_t Usr_SnCrc4;
uint8_t Usr_SnCrc5;
uint8_t Usr_SnCrc6;


uint8_t Usr_Md_Cmd1;
uint8_t Usr_Md_Cmd2;
uint16_t Usr_Md_CmdCode0;
uint16_t Usr_Md_CmdCode1;
uint16_t Usr_Md_CmdCode2;
uint8_t Usr_Md_State;

uint16_t g_u16CurCmdCode;
uint16_t g_u16CurCmdLen;

uint8_t g_u8CmdOK;

uint8_t g_u8CmdEC05Type;

uint8_t g_u8CmdBuf[2] = {0};

#endif


#endif



