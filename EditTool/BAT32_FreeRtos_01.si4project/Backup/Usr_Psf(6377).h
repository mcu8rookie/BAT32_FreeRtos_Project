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

extern uint16_t Sens_SRaw;
extern int16_t Sens_DltSRaw;
extern uint16_t Sens_SRawComp;

extern uint16_t Sens_DC_Y;

extern uint32_t Sens_CaliData;

extern uint16_t Sens_PPM_After_Cali;
extern uint16_t Sens_PPM_After_HumComp;
extern uint16_t Sens_PPM_After_PrsComp;
extern uint16_t Sens_ppm_After_TmRtComp;
extern uint16_t Sens_PPM_After_All;

extern uint16_t Sens_LFL;

extern int32_t Sens_PPM;
extern int32_t Sens_PPM_Dlt;


extern uint16_t Tmpr_TRaw;

extern int16_t Tmpr_DltTRaw;

extern uint16_t TComp_TRawBase;
extern int32_t TComp_P0;
extern int32_t TComp_P1;
extern int32_t TComp_P2;
extern int32_t TComp_P3;

extern uint16_t Sens_CoolTime;
extern uint16_t Sens_PreHeatTime;
extern uint16_t Sens_FilterCnt;

//#define DEF_TABLE_MAX   16
#define DEF_TABLE_MAX   11

extern uint16_t Sens_TableX[DEF_TABLE_MAX];
extern uint16_t Sens_TableY[DEF_TABLE_MAX];
extern uint32_t Table_32Bit[DEF_TABLE_MAX];
extern uint8_t Sens_TableLen;
extern uint32_t PPM_RangeMax;


#define DEF_HUMCOMP_PARAM_MAX   8
extern float HumComp_M2_S[DEF_HUMCOMP_PARAM_MAX];
extern uint16_t HumComp_Flag;

extern double HumComp_Tmp0;
extern double HumComp_Tmp1;
extern double HumComp_Tmp2;

extern uint16_t Flag_HumiCompParameter;

extern double Usr_HumComp_K;
extern double Usr_HumComp_PPMC;


#if(DEF_HUMCOMP_EN == DEF_HUMCOMP_EN)
double Usr_HumComp_Calc_K1(double temp);
#endif



extern volatile uint16_t Flag_1Ms;


unsigned char Usr_DataBits(unsigned char typ, unsigned char* byt);

void Usr_TComp_Polynomial_Cubic(uint16_t rawt, int16_t *out);

#define DEF_SRAW_FILTERMAX      (64)
#define DEF_SRAW_FILTERCNT      (4)


extern uint16_t FilterBuff[DEF_SRAW_FILTERMAX];
extern uint8_t FilterIndex;
extern uint32_t FilterTotal;

uint16_t Usr_SRaw_Filter(uint16_t in);

uint8_t Usr_BrokenLine2(uint16_t datain,uint32_t *dataout,uint16_t * Xcoordinates,uint32_t* Ycoordinates,uint8_t nbr);

#if((defined(DEF_OVERRANGE_ALARM_EN))&&(DEF_OVERRANGE_ALARM_EN == 1))

void Usr_CheckRangeMax(void);

#endif

unsigned char FP32_IsNumerical(unsigned char *ptr);



#endif


