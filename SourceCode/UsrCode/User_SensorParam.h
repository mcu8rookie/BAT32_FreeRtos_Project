#ifndef __USER_SENSOR_PARAM_H
#define __USER_SENSOR_PARAM_H

#include "stdint.h"

#pragma pack(push)
#pragma pack(1)

typedef struct
{
	uint16_t RH_Rate;
	uint8_t  RH_RateCRC;

	uint16_t TRawData;
	uint8_t  TRawDataCRC;
	
	uint16_t SRawDataNoT;
	uint8_t  SRawDataNoTCRC;
	
	uint16_t SRawData;
	uint8_t  SRawDataCRC;
	
	//uint16_t RawPPM;
	//uint8_t  RawPPMCRC;

	//uint16_t TempPPM;
	//uint8_t  TempPPMCRC;

    uint16_t RawPPM_MSB;
    uint8_t  RawPPM_MSB_CRC;
    
    uint16_t RawPPM_LSB;
    uint8_t  RawPPM_LSB_CRC;
    
	uint16_t FinalPPM_MSB;
	uint8_t  FinalPPM_MSB_CRC;
	
	uint16_t FinalPPM_LSB;
	uint8_t  FinalPPM_LSB_CRC;
	
	uint16_t FinalLFL;
	uint8_t  FinalLFLCRC;
	
	uint16_t HumiCompVal;
	uint8_t  HumiCompValCRC;
	
	uint16_t PressCompVal;
	uint8_t  PressCompValCRC;
	
	uint16_t WarningFlag;
	uint8_t  WarningFlagCRC;
	
	uint16_t HeaterRawData;
	uint8_t  HeaterRawDataCRC;

	int16_t T;
	uint8_t T_CRC;

	uint16_t RH;
	uint8_t  RH_CRC;

	uint16_t P;
	uint8_t  P_CRC;

	uint16_t WorkHour;
	uint8_t  WorkHourCRC;

	uint16_t WorkSec;
	uint8_t  WorkSecCRC;

	uint16_t T_Rate;
	uint8_t  T_RateCRC;
	
	uint16_t ErrCode;
	uint8_t  ErrCode_CRC;
	
	uint16_t FW_Ver_MSB;
	uint8_t  FW_Ver_MSB_CRC;
	
	uint16_t FW_Ver_LSB;
	uint8_t  FW_Ver_LSB_CRC;
	
	uint16_t DeltaRawData;
	uint8_t  DeltaRawDataCRC;
	
	uint16_t DeltaPPM;
	uint8_t  DeltaPPMCRC;
	
	uint16_t ConcentrationThres;
	uint8_t  ConcentrationThres_DataCRC;
	
	uint16_t RH_Coeff_P0_MSB;
	uint8_t  RH_Coeff_P0_MSB_CRC;
	
	uint16_t RH_Coeff_P0_LSB;
	uint8_t  RH_Coeff_P0_LSB_CRC;
	
	uint16_t RH_Coeff_P1_MSB;
	uint8_t  RH_Coeff_P1_MSB_CRC;
	
	uint16_t RH_Coeff_P1_LSB;
	uint8_t  RH_Coeff_P1_LSB_CRC;
	
	uint16_t RH_Coeff_P2_MSB;
	uint8_t  RH_Coeff_P2_MSB_CRC;
	
	uint16_t RH_Coeff_P2_LSB;
	uint8_t  RH_Coeff_P2_LSB_CRC;
	
	uint16_t RH_Coeff_P3_MSB;
	uint8_t  RH_Coeff_P3_MSB_CRC;
	
	uint16_t RH_Coeff_P3_LSB;
	uint8_t  RH_Coeff_P3_LSB_CRC;
	
	uint16_t RH_Coeff_P4_MSB;
	uint8_t  RH_Coeff_P4_MSB_CRC;
	
	uint16_t RH_Coeff_P4_LSB;
	uint8_t  RH_Coeff_P4_LSB_CRC;
	
	uint16_t RH_Coeff_P5_MSB;
	uint8_t  RH_Coeff_P5_MSB_CRC;
	
	uint16_t RH_Coeff_P5_LSB;
	uint8_t  RH_Coeff_P5_LSB_CRC;
	
	uint16_t RH_Coeff_P6_MSB;
	uint8_t  RH_Coeff_P6_MSB_CRC;
	
	uint16_t RH_Coeff_P6_LSB;
	uint8_t  RH_Coeff_P6_LSB_CRC;
	
	uint16_t RH_Coeff_P7_MSB;
	uint8_t  RH_Coeff_P7_MSB_CRC;
	
	uint16_t RH_Coeff_P7_LSB;
	uint8_t  RH_Coeff_P7_LSB_CRC;
	
	uint16_t HumiCompSW;
	uint8_t  HumiCompSW_CRC;
	
	uint16_t P_Coeff_P0_MSB;
	uint8_t  P_Coeff_P0_MSB_CRC;
	
	uint16_t P_Coeff_P0_LSB;
	uint8_t  P_Coeff_P0_LSB_CRC;
	
	uint16_t P_Coeff_P1_MSB;
	uint8_t  P_Coeff_P1_MSB_CRC;
	
	uint16_t P_Coeff_P1_LSB;
	uint8_t  P_Coeff_P1_LSB_CRC;
	
	uint16_t P_Coeff_P2_MSB;
	uint8_t  P_Coeff_P2_MSB_CRC;
	
	uint16_t P_Coeff_P2_LSB;
	uint8_t  P_Coeff_P2_LSB_CRC;
	
	uint16_t PressCompSW;
	uint8_t  PressCompSW_CRC;
	
	uint16_t HighRH_Time;
	uint8_t  HighRH_Time_CRC;
	
	uint16_t HighT_Time;
	uint8_t  HighT_Time_CRC;
	
	uint16_t LowT_Time;
	uint8_t  LowT_Time_CRC;
	
	uint16_t SN_Date;
	uint8_t  SN_Date_CRC;
	
	uint16_t SN_Num;
	uint8_t  SN_Num_CRC;
	
	uint16_t T_Coeff_P0_MSB;
	uint8_t  T_Coeff_P0_MSB_CRC;
	
	uint16_t T_Coeff_P0_LSB;
	uint8_t  T_Coeff_P0_LSB_CRC;
	
	uint16_t T_Coeff_P1_MSB;
	uint8_t  T_Coeff_P1_MSB_CRC;
	
	uint16_t T_Coeff_P1_LSB;
	uint8_t  T_Coeff_P1_LSB_CRC;
	
	uint16_t T_Coeff_P2_MSB;
	uint8_t  T_Coeff_P2_MSB_CRC;
	
	uint16_t T_Coeff_P2_LSB;
	uint8_t  T_Coeff_P2_LSB_CRC;
	
	uint16_t T_Coeff_P3_MSB;
	uint8_t  T_Coeff_P3_MSB_CRC;
	
	uint16_t T_Coeff_P3_LSB;
	uint8_t  T_Coeff_P3_LSB_CRC;
	
	uint16_t LifeTimeNearThres;
	uint8_t  LifeTimeNearThres_CRC;
	
	uint16_t LifeTimeOutThres;
	uint8_t  LifeTimeOutThres_CRC;
	
	uint16_t RH_Rate_Thres;
	uint8_t  RH_Rate_Thres_CRC;
	
	uint16_t CaliPPM0;
	uint8_t  CaliPPM0_CRC;
	
	uint16_t CaliPPM1;
	uint8_t  CaliPPM1_CRC;
	
	uint16_t CaliPPM2;
	uint8_t  CaliPPM2_CRC;
	
	uint16_t CaliPPM3;
	uint8_t  CaliPPM3_CRC;
	
	uint16_t CaliPPM4;
	uint8_t  CaliPPM4_CRC;
	
	uint16_t CaliPPM5;
	uint8_t  CaliPPM5_CRC;
	
	uint16_t CaliPPM6;
	uint8_t  CaliPPM6_CRC;
	
	uint16_t CaliPPM7;
	uint8_t  CaliPPM7_CRC;
	
	uint16_t CaliPPM8;
	uint8_t  CaliPPM8_CRC;
	
	uint16_t CaliPPM9;
	uint8_t  CaliPPM9_CRC;
	
	uint16_t CaliPPM10;
	uint8_t  CaliPPM10_CRC;
	
	uint16_t CaliSRawData0;
	uint8_t  CaliSRawData0_CRC;
	
	uint16_t CaliSRawData1;
	uint8_t  CaliSRawData1_CRC;
	
	uint16_t CaliSRawData2;
	uint8_t  CaliSRawData2_CRC;
	
	uint16_t CaliSRawData3;
	uint8_t  CaliSRawData3_CRC;
	
	uint16_t CaliSRawData4;
	uint8_t  CaliSRawData4_CRC;
	
	uint16_t CaliSRawData5;
	uint8_t  CaliSRawData5_CRC;
	
	uint16_t CaliSRawData6;
	uint8_t  CaliSRawData6_CRC;
	
	uint16_t CaliSRawData7;
	uint8_t  CaliSRawData7_CRC;
	
	uint16_t CaliSRawData8;
	uint8_t  CaliSRawData8_CRC;
	
	uint16_t CaliSRawData9;
	uint8_t  CaliSRawData9_CRC;
	
	uint16_t CaliSRawData10;
	uint8_t  CaliSRawData10_CRC;
	
	uint16_t CoolTime;
	uint8_t  CoolTime_CRC;
	
	uint16_t CaliTRawData;
	uint8_t  CaliTRawData_CRC;
	
	uint16_t CaliP;
	uint8_t  CaliP_CRC;
	
	uint16_t CaliOffset;
	uint8_t  CaliOffset_CRC;
	
	uint16_t WorkDay;
	uint8_t  WorkDay_CRC;
	
	uint16_t FilterNum;
	uint8_t  FilterNum_CRC;
	
	uint16_t WarmUpTime;
	uint8_t  WarmUpTime_CRC;
	
	uint16_t TSC_Coeff;
	uint8_t  TSC_Coeff_CRC;

	uint16_t ASC_EN_Flag;
	uint8_t  ASC_EN_CRC;

	uint16_t ASC_MaxPPM;
	uint8_t  ASC_MaxPPM_CRC;

	uint16_t ASC_MinPPM;
	uint8_t  ASC_MinPPM_CRC;

	uint16_t ASC_TRateThres;
	uint8_t  ASC_TRateThres_CRC;

	uint16_t ASC_HRateThres;
	uint8_t  ASC_HRateThres_CRC;

	uint16_t ASC_Temp;
	uint8_t  ASC_Temp_CRC;

	uint16_t ASC_Humidity;
	uint8_t  ASC_Humidity_CRC;

	uint16_t ASC_Max_TRate_30M;
	uint8_t  ASC_Max_TRate_30M_CRC;

	uint16_t ASC_Max_HRate_30M;
	uint8_t  ASC_Max_HRate_30M_CRC;

	uint16_t ASC_TRate;
	uint8_t  ASC_TRate_CRC;

	uint16_t ASC_HRate;
	uint8_t  ASC_HRate_CRC;
	
	uint16_t ASC_AdjustCnt;
	uint8_t  ASC_AdjustCnt_CRC;

	uint16_t ASC_AdjustVal1;
	uint8_t  ASC_AdjustVal1_CRC;

	uint16_t ASC_AdjustVal2;
	uint8_t  ASC_AdjustVal2_CRC;

	uint16_t ASC_AdjustVal3;
	uint8_t  ASC_AdjustVal3_CRC;

	uint16_t ASC_AdjustVal4;
	uint8_t  ASC_AdjustVal4_CRC;

	uint16_t ASC_AdjustVal5;
	uint8_t  ASC_AdjustVal5_CRC;

	uint16_t ASC_AdjustVal6;
	uint8_t  ASC_AdjustVal6_CRC;
}tSensorType;
extern tSensorType g_tSensor;

typedef struct
{
	uint16_t FinalLFL;
	uint8_t  FinalLFL_CRC;
	
	uint16_t ErrCode;
	uint8_t  ErrCode_CRC;
	
	uint16_t GasType;
	uint8_t  GasType_CRC;

	uint16_t T;
	uint8_t T_CRC;

	uint16_t RH;
	uint8_t  RH_CRC;

	uint16_t ASC_Val;
	uint8_t  ASC_Val_CRC;	
}tClientDataType;
extern tClientDataType g_tClientData;

typedef struct
{
	uint16_t ProductNum_MSB;
	uint8_t  ProductNum_MSB_CRC;
	
	uint16_t ProductNum_LSB;
	uint8_t  ProductNum_LSB_CRC;
	
	uint16_t SN4;
	uint8_t  SN4_CRC;
	
	uint16_t SN3;
	uint8_t  SN3_CRC;
	
	uint16_t SN2;
	uint8_t  SN2_CRC;
	
	uint16_t SN1;
	uint8_t  SN1_CRC;
}tClientSnType;
extern tClientSnType g_tClientSN;

#pragma pack(pop)


void setSensorParam(uint8_t* paramAddr, uint16_t paramVal);

void initSensorParam(void);




#endif


