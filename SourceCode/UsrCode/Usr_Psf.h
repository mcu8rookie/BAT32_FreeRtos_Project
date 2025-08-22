#ifndef __USR_PSF_H__
#define __USR_PSF_H__


#include "Usr_Config.h"
#include "stdint.h"

#include "BAT32A237.h"
#include"gpio.h"
#include"Usr_GPIO.h"


#define PSF_STATE_INIT      1
#define PSF_STATE_PREHEAT   2
#define PSF_STATE_E703      3
#define PSF_STATE_COOL      4

#define PSF_STATE_INIT_KEEPTIME     0
#define PSF_STATE_PREHEAT_KEEPTIME  100
#define PSF_STATE_E703_KEEPTIME     0
#define PSF_STATE_COOL_KEEPTIME     1000


#define PSF_GASTYPE_DEFAULT (0xFFFF)

#define PSF_GASTYPE_R32     (0x18)
#define PSF_GASTYPE_R454B   (0x19)
#define PSF_GASTYPE_R454C   (0x1B)
#define PSF_GASTYPE_R454A   (0x1C)
#define PSF_GASTYPE_R455A   (0x1D)

#define PSF_GASTYPE_MAX     (PSF_GASTYPE_R455A)

extern uint16_t Psf_Gas_Type;
extern uint16_t Psf_Gas_TypeCode;
extern uint16_t Psf_MeasurementFlag;


extern uint8_t Psf_State;
extern uint8_t Psf_Next_State;
extern unsigned int Psf_State_KeepTime;



extern uint8_t Sens_UpdateFlag;

extern int16_t Sens_SRaw;
extern int16_t Sens_DltSRaw;

extern uint16_t ErrorData0;
extern uint16_t ErrorData1;
extern uint16_t ErrorData2;


extern uint16_t Sens_DC_Y;

extern int16_t Sens_Raw_After_Mems;
extern int16_t Sens_Raw_After_Filter;
extern int16_t Sens_Raw_After_TmpComp;
extern int16_t Sens_Raw_After_HtComp;
extern int16_t Sens_Raw_After_All;


extern uint16_t Sens_PPM_After_Cali;

#if(defined(DEF_MBREG_M2_EN)&&(DEF_MBREG_M2_EN==1))
extern int32_t Sens_PPM_After_Cali_S32;
extern uint16_t Reg778_Flags;
#endif

extern uint16_t Sens_PPM_After_PrsComp;
extern uint16_t Sens_PPM_After_All;
extern int32_t Sens_PPM_After_All_I32;

extern uint16_t Sens_LFL_U16;


#if(defined(DEF_CONCEN_THRE_EN)&&(DEF_CONCEN_THRE_EN==1))
extern uint16_t Concen_Threshold;
extern uint8_t Flag_Concen_Threshol_Alarm;
extern uint8_t Flag_Concen_Threshold_En;
extern uint16_t Donot_Alarm_5s;
extern uint16_t Concentration_Alarm_HoldTime;
#endif

extern int16_t Tmpr_DltTRaw;

extern uint16_t Sens_CoolTime;
extern uint16_t Sens_PreHeatTime;
extern uint16_t Sens_FilterCnt;

//#define DEF_TABLE_MAX   (16)
#define DEF_TABLE_MAX   (11)

extern uint16_t Sens_TableX[DEF_TABLE_MAX];
extern uint16_t Sens_TableY[DEF_TABLE_MAX];
extern int16_t Sens_TableX2[DEF_TABLE_MAX];
extern uint32_t Table_32Bit[DEF_TABLE_MAX];
extern uint8_t Sens_TableLen;
extern int32_t PPM_RangeMax;


#define DEF_HUMCOMP_PARAM_MAX   (8)
extern float HumComp_M2_S[DEF_HUMCOMP_PARAM_MAX];
extern uint16_t HumComp_Flag;
extern uint16_t HumComp_Flag2;



extern uint16_t Flag_HumiCompParameter;
extern uint16_t Flag_HumiCompParameter2;

extern int16_t Usr_HumComp_PPMC_INT;

extern int16_t Usr_Delta_Raw;
extern int16_t Usr_Delta_PPM1;

#if(defined(DEF_DBG_SRAW_0_EN)&&(DEF_DBG_SRAW_0_EN==1))
extern uint16_t Dbg_SRaw0_Cnt1;
extern uint16_t Dbg_SRaw0_Cnt2;
#endif


#if(defined(DEF_HUMCOMP_EN)&&(DEF_HUMCOMP_EN==1))
float Usr_HumComp_Calc_K1(float T);
float Usr_HumComp_Calc_D(float T);
#endif


#if(defined(DEF_HUMICOMP_M2_EN)&&(DEF_HUMICOMP_M2_EN==1))

extern double Usr_HumiComp_Param[6];

double HumiComp_PartA_Function(double t, double hr, double p);

double HumiComp_PartB_Function(double ah, double *pCoeff);

double HumiComp_PartC_Function(double ah, double *pCoeff);

double HumiComp_PartD_Function(double x85c, double k, double t, double *pCoeff);

double Humidity_Compensation_AH(double t, double hr, double p);

#endif

#if(defined(DEF_PRESCOMP_EN)&&(DEF_PRESCOMP_EN == 1))

#define DEF_PRESCOMP_PARAM_MAX  (3)

extern uint16_t PresComp_PBase;

extern float PresComp_K[DEF_PRESCOMP_PARAM_MAX];

extern uint16_t PresComp_Flag;

extern uint16_t Flag_PresCompParameter;

extern int16_t dlt_ppm_pressure_int;

float Delta_Pressure_Compensation(int prsu);


#endif


#if(defined(DEF_TEMPRATE_EN)&&(DEF_TEMPRATE_EN == 1))

extern int16_t TmpRate_P;

float Usr_TmpRate_Comp(float arg);

#endif

#if((defined(DEF_HTHH_MODE_EN))&&(DEF_HTHH_MODE_EN==1))

#define DEF_HIGH_TMPR1   (80.0f)
#define DEF_HIGH_HUMI1   (0.7f)

#define DEF_HIGH_TMPR2   (60.0f)
#define DEF_HIGH_HUMI2   (0.85f)

//extern double High_Tmpr;
//extern double High_Humi;

extern uint8_t Flag_HighTmprHighHumi;

#endif


#if(defined(DEF_ADC_EN)&&(DEF_ADC_EN == 1))

extern uint16_t Monitor_Raw1;

#endif

#if(defined(DEF_HEAT_COMP2_EN)&&(DEF_HEAT_COMP2_EN == 1))

extern uint8_t Flag_HtComp_2;

extern uint16_t HtComp_TRaw_Base_2;
extern uint16_t HtComp_HtRaw_Base_2;
extern int16_t HtComp_Kh_2;
extern int16_t HtComp_SP_2;
extern int16_t HtComp_Ks_2;

extern int16_t HtComp_Delta_TRaw_2;
extern uint16_t HtComp_HtRaw_Base_rt_2;
extern uint16_t HtComp_HtRaw_Base_min_2;
extern uint16_t HtComp_HtRaw_Base_max_2;

extern int16_t Delta_Ht_Raw_2;
extern int16_t Delta_Ht_Comp_2;
extern int16_t HtComp_CompTotal_2;

extern int32_t Dlt_P;

extern int32_t Dlt_P0;

extern uint16_t HtComp_DP0;

#endif

#if(1)  // (defined(DEF_JUDGE_OVER_DEWP_EN)&&(DEF_JUDGE_OVER_DEWP_EN==1))

extern uint8_t Flag_Over_Dewp;

unsigned char IsHumidityLargerThanDewRH(float T);

#endif



extern volatile uint16_t Flag_1Ms;



#if(defined(DEF_FUN_TCOMP_EN)&&(DEF_FUN_TCOMP_EN==1))

#pragma pack(push)
#pragma pack(1)

typedef struct
{
	float P0;
	float P1;
	float P2;
	float P3;
	
	uint8_t flag;
	uint16_t baseTRaw;
}TempCompCoeffType;
extern TempCompCoeffType g_TCompCoeff;

#pragma pack(pop)


float calcTempCompRawData(float nbr);

#endif

#define DEF_SRAW_FILTERMAX      (64)
#define DEF_SRAW_FILTERCNT      (4)


extern int16_t FilterBuff[DEF_SRAW_FILTERMAX];
extern int8_t FilterIndex;
extern int32_t FilterTotal;

int16_t Usr_SRaw_Filter(int16_t in);

uint8_t calibrateTargetGas(int16_t datain,int32_t *dataout,int16_t * Xcoordinates,uint32_t* Ycoordinates,uint8_t nbr);

#if((defined(DEF_OVERRANGE_ALARM_EN))&&(DEF_OVERRANGE_ALARM_EN == 1))
extern uint8_t Flag_Overrange_Ppm;
//extern uint8_t Flag_Overrange_Percentage;
extern int32_t PPM_RangeMax;

void Usr_CheckRangeMax(void);

#endif

uint8_t FP32_IsNumerical(uint8_t *ptr);


#if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))

// SelfMonitor FunctionSwitch;

//#define ASC_ARRAYLEN       (2)     // When SelfMoni2 function, also known as Drift function.
#define ASC_ARRAYLEN       (10)     // When ASC function, full title is Automatic Self-Calibration function.


extern uint16_t SelfMoni2_DriftFault;

extern int32_t ASC_Average_Array[ASC_ARRAYLEN];

extern uint8_t ASC_Average_Index;

extern uint16_t ASC_TimeCnt;
extern uint16_t ASC_TimeCnt_Th;

extern uint8_t LFL_LeakSignal_Rt;

extern uint16_t LFL_Leakage_Flag;

extern int32_t ASC_PPM_Total;
extern int32_t  ASC_PPM_Cnt;
extern int32_t  ASC_PPM_Average;

void Usr_ASC_MainLoop(void);

#endif


#if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))

extern uint16_t ASC_Func_En;

extern uint16_t ASC_Usr_En;
extern uint16_t ASC_Param_En;

extern uint16_t ASC_PPM_HighTh;
extern uint16_t ASC_PPM_LowTh;

extern int32_t ASC_PPM_HighTh_S32;
extern int32_t ASC_PPM_LowTh_S32;


extern uint16_t ASC_Adjust_Cnt;

#define DEF_ASC_ADJUST_VALUE_MAX        (6)

extern int16_t ASC_Adjust_Value[DEF_ASC_ADJUST_VALUE_MAX];
extern int32_t ASC_Adjust_Total;

#define DEF_TMPR_BUFFLEN    (2)
extern int16_t ASC_Tmpr_Rt;
extern int16_t ASC_Tmpr[DEF_TMPR_BUFFLEN];
extern uint8_t ASC_Tmpr_Index;
extern int16_t ASC_Tmpr_Min;
extern int16_t ASC_Tmpr_Max;
extern int16_t ASC_Tmpr_Min30M;
extern int16_t ASC_Tmpr_Max30M;
extern int16_t ASC_Tmpr_Rate;
extern int16_t ASC_Tmpr_RateTh;
extern int16_t ASC_Tmpr_RateMax30M;
extern int16_t ASC_Tmpr_Thre;

#define DEF_HUMI_BUFFLEN    (2)
extern int16_t ASC_Humi_Rt;
extern int16_t ASC_Humi[DEF_HUMI_BUFFLEN];
extern uint8_t ASC_Humi_Index;
extern int16_t ASC_Humi_Min;
extern int16_t ASC_Humi_Max;
extern int16_t ASC_Humi_Min30M;
extern int16_t ASC_Humi_Max30M;
extern int16_t ASC_Humi_Rate;
extern int16_t ASC_Humi_RateTh;
extern int16_t ASC_Humi_RateMax30M;
extern int16_t ASC_Humi_Thre;

#define DEF_ASC_DELTDIRC_BUFFLEN    (2)

extern uint16_t ASC_DeltDire_Cnt;
extern int32_t ASC_DeltDire_Buff[DEF_ASC_DELTDIRC_BUFFLEN];
extern int8_t ASC_Dlt_Direct_Current;
extern int8_t ASC_Dlt_Direct_Last;
extern uint16_t ASC_Dlt_SameDire_Cnt;
extern uint16_t ASC_Dlt_SameDire_Cnt30M;
extern int32_t ASC_Dlt_Threshold;
extern int32_t ASC_Dlt_Value;
#endif


#if(defined(DEF_ASC_FAST_EN)&&(DEF_ASC_FAST_EN==1))
extern uint8_t ASC_Stage;
extern uint16_t ASC_Fast_DataCnt;
extern uint8_t ASC_Init_Error;
extern int32_t ASC_Init_Value;

extern uint8_t ASC_Fast_FailCnt;
extern uint8_t ASC_Fast_SuccCnt;
extern uint16_t ASC_Fast_ProcCnt;
extern int16_t ASC_Fast_Value;
extern uint8_t ASC_Fast_Rslt;
#endif


#if((defined(DEBUG_HUMI_RATE_EN))&&(DEBUG_HUMI_RATE_EN==1))
//#define EEPROM_HUMI_RATE_THRE_ADDSTART      208 //0xD0;
#define DEF_RH_BUFF_LEN       3
extern uint16_t ExtSens_RH_Rate;
extern uint16_t ExtSens_RH_Thre;
extern uint16_t ExtSens_RH_Buff[DEF_RH_BUFF_LEN];
extern uint8_t ExtSens_RH_BufIdx;
extern uint8_t Flag_RH_Rate_Exceed;
extern uint8_t Flag_RH_Rate_En;
extern uint16_t ExtSens_RH_Total;
extern uint8_t ExtSens_RH_TolIdx;
extern uint16_t ExtSens_RH_Max;
extern uint16_t ExtSens_RH_Min;
#endif

extern uint16_t Sens_LFL_U16_Cust;
extern uint16_t ErrorData1_Cust;
extern uint16_t Psf_Gas_TypeCode_Cust;
extern int16_t TH_Sensor_Temperature_out_Cust;
extern uint16_t TH_Sensor_Humidity_out_Cust;

extern uint16_t Conc_For_Custom;
//extern int16_t Tmpr_For_Custom;
extern uint16_t Tmpr_For_Custom;
extern uint16_t Humi_For_Custom;



#if(defined(DEF_HEAT_BOARD_EN)&&(DEF_HEAT_BOARD_EN == 1))

#define HeatBoard_Heat()    do{PORT_SetBit(Usr_HTMNBD_PORT,Usr_HTMNBD_PIN);;}while(0)
#define HeatBoard_Cool()    do{PORT_ClrBit(Usr_HTMNBD_PORT,Usr_HTMNBD_PIN);;}while(0)
extern volatile unsigned char HeatBoard_Flag;
extern volatile unsigned char HeatBoard_ParamFlag;
extern unsigned int HeatBoard_Duty;
extern unsigned int HeatBoard_Period;
extern unsigned int HeatBoard_Cnt;
extern unsigned int HeatBoard_PreTime;
#endif

#if(defined(DEF_HPC_FUNC_EN)&&(DEF_HPC_FUNC_EN==1))

#if(defined(DEF_HPC_TEST_EN)&&(DEF_HPC_TEST_EN==1))

#define DEF_HPC_TMPR                (10)
#define DEF_HPC_HUMI                (501)
#define DEF_HPC_HUMIRATE            (601)

#endif


extern uint8_t HPC_Func_En;
extern int16_t HPC_Tmpr;
extern uint16_t HPC_Humi;
extern uint8_t HPC_PreHeat_Flag;
extern uint8_t HPC_Heat_Flag;
extern int16_t HPC_HumiRate;
extern uint16_t HPC_HoldCount;
extern uint8_t HPC_PWM_Data;

void HPC_InitSetup(unsigned char arg);

void HPC_MainLoop(void);

#endif

#if(defined(DEF_TMPR_RATE_EN)&&(DEF_TMPR_RATE_EN==1))
extern int8_t TR_Data_Cnt;
extern int32_t TR_Tmpr[2];
extern int32_t TR_Tmpr_Delt;
extern int32_t TR_Tmpr_Interval;
extern int32_t TR_Tmpr_Rate;
#endif

#if(defined(DEF_HUMI_RATE_EN)&&(DEF_HUMI_RATE_EN==1))
extern int8_t HR_Data_Cnt;
extern int32_t HR_Humi[2];
extern int32_t HR_Humi_Delt;
extern int32_t HR_Humi_Interval;
extern int32_t HR_Humi_Rate;
#endif

#if(defined(DEF_PRES_RATE_EN)&&(DEF_PRES_RATE_EN==1))
extern int8_t PR_Data_Cnt;
extern int32_t PR_Pres[2];
extern int32_t PR_Pres_Delt;
extern int32_t PR_Pres_Interval;
extern int32_t PR_Pres_Rate;
#endif

int32_t Usr_DataRate_DltPerMin(int32_t data1,int32_t data2,int32_t *rate);




#endif


