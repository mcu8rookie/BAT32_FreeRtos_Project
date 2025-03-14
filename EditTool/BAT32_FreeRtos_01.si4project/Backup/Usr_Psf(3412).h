#ifndef __USR_PSF_H__
#define __USR_PSF_H__


#include "Usr_Config.h"
#include "stdint.h"

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

extern unsigned short Psf_Gas_Type;
extern unsigned short Psf_Gas_TypeCode;
extern unsigned short Psf_MeasurementFlag;


extern unsigned char Psf_State;
extern unsigned char Psf_Next_State;
extern unsigned int Psf_State_KeepTime;



extern unsigned char Sens_UpdateFlag;

extern int16_t Sens_SRaw;
extern int16_t Sens_DltSRaw;
extern int16_t Sens_SRawComp;

extern uint16_t ErrorData0;
extern uint16_t ErrorData1;
extern uint16_t ErrorData2;


extern uint16_t Sens_DC_Y;

extern int32_t Sens_CaliData;

extern int16_t Sens_Raw_After_Mems;
extern int16_t Sens_Raw_After_Filter;
extern int16_t Sens_Raw_After_TmpComp;
extern int16_t Sens_Raw_After_HtComp;


extern uint16_t Sens_PPM_After_Cali;
extern uint16_t Sens_PPM_After_HumComp;
extern uint16_t Sens_PPM_After_PrsComp;
extern uint16_t Sens_PPM_After_DCY;
extern uint16_t Sens_PPM_After_TmRtComp;
extern uint16_t Sens_PPM_After_All;

extern double Sens_LFL_dbl;
extern uint16_t Sens_LFL_U16;


extern int32_t Sens_PPM;
extern int32_t Sens_PPM_Dbl;


#if(defined(DEF_CONCEN_THRE_EN)&&(DEF_CONCEN_THRE_EN==1))
extern uint16_t Concen_Threshold;
extern uint8_t  Flag_Concen_Threshold;
#endif

extern uint16_t Tmpr_TRaw;

extern int16_t Tmpr_DltTRaw;

extern uint16_t TComp_TRawBase;
extern int32_t TComp_P0;
extern int32_t TComp_P1;
extern int32_t TComp_P2;
extern int32_t TComp_P3;

extern uint16_t Sens_CoolTime;
extern uint16_t Sens_PreHeatTime;
extern int16_t Sens_FilterCnt;

//#define DEF_TABLE_MAX   (16)
#define DEF_TABLE_MAX   (11)

extern uint16_t Sens_TableX[DEF_TABLE_MAX];
extern uint16_t Sens_TableY[DEF_TABLE_MAX];
extern int16_t Sens_TableX2[DEF_TABLE_MAX];
extern uint32_t Table_32Bit[DEF_TABLE_MAX];
extern uint8_t Sens_TableLen;
extern uint32_t PPM_RangeMax;


#define DEF_HUMCOMP_PARAM_MAX   (8)
extern float HumComp_M2_S[DEF_HUMCOMP_PARAM_MAX];
extern uint16_t HumComp_Flag;

extern double HumComp_Tmp0;
extern double HumComp_Tmp1;
extern double HumComp_Tmp2;

extern uint16_t Flag_HumiCompParameter;

extern double Usr_HumComp_K;
extern double Usr_HumComp_PPMC;
extern int16_t Usr_HumComp_PPMC_INT;


#if(defined(DEF_HUMCOMP_EN)&&(DEF_HUMCOMP_EN==1))
double Usr_HumComp_Calc_K1(double temp);
#endif

double Usr_HumComp_Calc_D(short T, unsigned short RH);


#if(defined(DEF_PRESCOMP_EN)&&(DEF_PRESCOMP_EN == 1))

#define DEF_PRESCOMP_PARAM_MAX  (3)

extern uint16_t PresComp_PBase;

extern float PresComp_K[DEF_PRESCOMP_PARAM_MAX];

extern uint16_t PresComp_Flag;

extern uint16_t Flag_PresCompParameter;

extern float delta_ppm_pressure;
extern int16_t dlt_ppm_pressure_int;

unsigned char Delta_Pressure_Compensation(double prsu);


#endif


#if(defined(DEF_TEMPRATE_EN)&&(DEF_TEMPRATE_EN == 1))

extern int16_t TmpRate_P;

double Usr_TmpRate_Comp(double arg);

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

#if(defined(DEBUG_HEAT_COMP2_EN)&&(DEBUG_HEAT_COMP2_EN == 1))

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

extern uint16_t Monitor_Raw1;


#endif


extern volatile uint16_t Flag_1Ms;


unsigned char Usr_DataBits(unsigned char typ, unsigned char* byt);

void Usr_TComp_Polynomial_Cubic(int16_t nbr, int16_t *out);


#define DEF_SRAW_FILTERMAX      (64)
#define DEF_SRAW_FILTERCNT      (4)


extern int16_t FilterBuff[DEF_SRAW_FILTERMAX];
extern int8_t FilterIndex;
extern int32_t FilterTotal;

int16_t Usr_SRaw_Filter(int16_t in);

uint8_t Usr_BrokenLine2(int16_t datain,int32_t *dataout,int16_t * Xcoordinates,uint32_t* Ycoordinates,uint8_t nbr);

#if((defined(DEF_OVERRANGE_ALARM_EN))&&(DEF_OVERRANGE_ALARM_EN == 1))
extern uint8_t Flag_Overrange_Ppm;
//extern uint8_t Flag_Overrange_Percentage;
extern uint32_t PPM_RangeMax;

void Usr_CheckRangeMax(void);

#endif

unsigned char FP32_IsNumerical(unsigned char *ptr);



#endif


