#include "User_SensorParam.h"
#include "Usr_Psf.h"



extern uint16_t TimeSn_Time;
extern uint16_t TimeSn_SN;

extern uint8_t compute_crc8(uint8_t *data, uint16_t size);


tSensorType g_tSensor;

tClientDataType g_tClientData;

tClientSnType g_tClientSN;


void setSensorParam(uint8_t* paramAddr, uint16_t paramVal)
{
	paramAddr[0] = (uint8_t)(paramVal>>8);
	paramAddr[1] = (uint8_t)paramVal;
	paramAddr[2] = compute_crc8(paramAddr, 2);
}

void initSensorParam(void)
{
	setSensorParam((uint8_t*)&g_tSensor.FW_Ver_MSB, FW_VERSION_PART0);
	setSensorParam((uint8_t*)&g_tSensor.FW_Ver_LSB, (FW_VERSION_PART1<<8) | FW_VERSION_PART2);
	
	setSensorParam((uint8_t*)&g_tSensor.DeltaRawData, Usr_Delta_Raw);
	setSensorParam((uint8_t*)&g_tSensor.DeltaPPM, Usr_Delta_PPM1);
	setSensorParam((uint8_t*)&g_tSensor.ConcentrationThres, Concen_Threshold);
	
	setSensorParam((uint8_t*)&g_tSensor.RH_Coeff_P0_MSB, *((uint16_t*)&HumComp_M2_S[0]+1));
	setSensorParam((uint8_t*)&g_tSensor.RH_Coeff_P0_LSB, *((uint16_t*)&HumComp_M2_S[0]));
	setSensorParam((uint8_t*)&g_tSensor.RH_Coeff_P1_MSB, *((uint16_t*)&HumComp_M2_S[1]+1));
	setSensorParam((uint8_t*)&g_tSensor.RH_Coeff_P1_LSB, *((uint16_t*)&HumComp_M2_S[1]));
	setSensorParam((uint8_t*)&g_tSensor.RH_Coeff_P2_MSB, *((uint16_t*)&HumComp_M2_S[2]+1));
	setSensorParam((uint8_t*)&g_tSensor.RH_Coeff_P2_LSB, *((uint16_t*)&HumComp_M2_S[2]));
	setSensorParam((uint8_t*)&g_tSensor.RH_Coeff_P3_MSB, *((uint16_t*)&HumComp_M2_S[3]+1));
	setSensorParam((uint8_t*)&g_tSensor.RH_Coeff_P3_LSB, *((uint16_t*)&HumComp_M2_S[3]));
	setSensorParam((uint8_t*)&g_tSensor.RH_Coeff_P4_MSB, *((uint16_t*)&HumComp_M2_S[4]+1));
	setSensorParam((uint8_t*)&g_tSensor.RH_Coeff_P4_LSB, *((uint16_t*)&HumComp_M2_S[4]));
	setSensorParam((uint8_t*)&g_tSensor.RH_Coeff_P5_MSB, *((uint16_t*)&HumComp_M2_S[5]+1));
	setSensorParam((uint8_t*)&g_tSensor.RH_Coeff_P5_LSB, *((uint16_t*)&HumComp_M2_S[5]));
	setSensorParam((uint8_t*)&g_tSensor.RH_Coeff_P6_MSB, *((uint16_t*)&HumComp_M2_S[6]+1));
	setSensorParam((uint8_t*)&g_tSensor.RH_Coeff_P6_LSB, *((uint16_t*)&HumComp_M2_S[6]));
	setSensorParam((uint8_t*)&g_tSensor.RH_Coeff_P7_MSB, *((uint16_t*)&HumComp_M2_S[7]+1));
	setSensorParam((uint8_t*)&g_tSensor.RH_Coeff_P7_LSB, *((uint16_t*)&HumComp_M2_S[7]));
	
	setSensorParam((uint8_t*)&g_tSensor.HumiCompSW, HumComp_Flag);
	
	setSensorParam((uint8_t*)&g_tSensor.P_Coeff_P0_MSB, *((uint16_t*)&PresComp_K[0]+1));
	setSensorParam((uint8_t*)&g_tSensor.P_Coeff_P0_LSB, *((uint16_t*)&PresComp_K[0]));
	setSensorParam((uint8_t*)&g_tSensor.P_Coeff_P1_MSB, *((uint16_t*)&PresComp_K[1]+1));
	setSensorParam((uint8_t*)&g_tSensor.P_Coeff_P1_LSB, *((uint16_t*)&PresComp_K[1]));
	setSensorParam((uint8_t*)&g_tSensor.P_Coeff_P2_MSB, *((uint16_t*)&PresComp_K[2]+1));
	setSensorParam((uint8_t*)&g_tSensor.P_Coeff_P2_LSB, *((uint16_t*)&PresComp_K[2]));
	
	setSensorParam((uint8_t*)&g_tSensor.PressCompSW, PresComp_Flag);
	
	setSensorParam((uint8_t*)&g_tSensor.SN_Date, TimeSn_Time);
	setSensorParam((uint8_t*)&g_tSensor.SN_Num, TimeSn_SN);

	setSensorParam((uint8_t*)&g_tSensor.T_Coeff_P0_MSB, *((uint16_t*)&g_TCompCoeff.P0+1));
	setSensorParam((uint8_t*)&g_tSensor.T_Coeff_P0_LSB, *((uint16_t*)&g_TCompCoeff.P0));
	setSensorParam((uint8_t*)&g_tSensor.T_Coeff_P1_MSB, *((uint16_t*)&g_TCompCoeff.P1+1));
	setSensorParam((uint8_t*)&g_tSensor.T_Coeff_P1_LSB, *((uint16_t*)&g_TCompCoeff.P1));
	setSensorParam((uint8_t*)&g_tSensor.T_Coeff_P2_MSB, *((uint16_t*)&g_TCompCoeff.P2+1));
	setSensorParam((uint8_t*)&g_tSensor.T_Coeff_P2_LSB, *((uint16_t*)&g_TCompCoeff.P2));
	setSensorParam((uint8_t*)&g_tSensor.T_Coeff_P3_MSB, *((uint16_t*)&g_TCompCoeff.P3+1));
	setSensorParam((uint8_t*)&g_tSensor.T_Coeff_P3_LSB, *((uint16_t*)&g_TCompCoeff.P3));

	setSensorParam((uint8_t*)&g_tSensor.CaliPPM0, Sens_TableY[0]);
	setSensorParam((uint8_t*)&g_tSensor.CaliPPM1, Sens_TableY[1]);
	setSensorParam((uint8_t*)&g_tSensor.CaliPPM2, Sens_TableY[2]);
	setSensorParam((uint8_t*)&g_tSensor.CaliPPM3, Sens_TableY[3]);
	setSensorParam((uint8_t*)&g_tSensor.CaliPPM4, Sens_TableY[4]);
	setSensorParam((uint8_t*)&g_tSensor.CaliPPM5, Sens_TableY[5]);
	setSensorParam((uint8_t*)&g_tSensor.CaliPPM6, Sens_TableY[6]);
	setSensorParam((uint8_t*)&g_tSensor.CaliPPM7, Sens_TableY[7]);
	setSensorParam((uint8_t*)&g_tSensor.CaliPPM8, Sens_TableY[8]);
	setSensorParam((uint8_t*)&g_tSensor.CaliPPM9, Sens_TableY[9]);
	setSensorParam((uint8_t*)&g_tSensor.CaliPPM10, Sens_TableY[10]);
	
	setSensorParam((uint8_t*)&g_tSensor.CaliSRawData0, Sens_TableX[0]);
	setSensorParam((uint8_t*)&g_tSensor.CaliSRawData1, Sens_TableX[1]);
	setSensorParam((uint8_t*)&g_tSensor.CaliSRawData2, Sens_TableX[2]);
	setSensorParam((uint8_t*)&g_tSensor.CaliSRawData3, Sens_TableX[3]);
	setSensorParam((uint8_t*)&g_tSensor.CaliSRawData4, Sens_TableX[4]);
	setSensorParam((uint8_t*)&g_tSensor.CaliSRawData5, Sens_TableX[5]);
	setSensorParam((uint8_t*)&g_tSensor.CaliSRawData6, Sens_TableX[6]);
	setSensorParam((uint8_t*)&g_tSensor.CaliSRawData7, Sens_TableX[7]);
	setSensorParam((uint8_t*)&g_tSensor.CaliSRawData8, Sens_TableX[8]);
	setSensorParam((uint8_t*)&g_tSensor.CaliSRawData9, Sens_TableX[9]);
	setSensorParam((uint8_t*)&g_tSensor.CaliSRawData10, Sens_TableX[10]);
	

	setSensorParam((uint8_t*)&g_tSensor.CoolTime, Sens_CoolTime);
	setSensorParam((uint8_t*)&g_tSensor.CaliTRawData, g_TCompCoeff.baseTRaw);
	setSensorParam((uint8_t*)&g_tSensor.CaliP, PresComp_PBase);
	setSensorParam((uint8_t*)&g_tSensor.CaliOffset, Sens_DC_Y);
	setSensorParam((uint8_t*)&g_tSensor.FilterNum, Sens_FilterCnt);
	setSensorParam((uint8_t*)&g_tSensor.WarmUpTime, Sens_PreHeatTime);
	setSensorParam((uint8_t*)&g_tSensor.TSC_Coeff, TmpRate_P);

	setSensorParam((uint8_t*)&g_tClientSN.ProductNum_MSB, FW_VERSION_PART0);
	setSensorParam((uint8_t*)&g_tClientSN.ProductNum_LSB, (FW_VERSION_PART1<<8) | FW_VERSION_PART2);
	
	setSensorParam((uint8_t*)&g_tClientSN.SN4, 0);
	setSensorParam((uint8_t*)&g_tClientSN.SN3, 0);
	setSensorParam((uint8_t*)&g_tClientSN.SN2, TimeSn_Time);
	setSensorParam((uint8_t*)&g_tClientSN.SN1, TimeSn_SN);
}

