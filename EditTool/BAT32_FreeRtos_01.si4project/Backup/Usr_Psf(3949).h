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


extern unsigned char Psf_State;
extern unsigned char Psf_Next_State;
extern unsigned int Psf_State_KeepTime;

extern unsigned char Sens_UpdateFlag;

extern uint16_t Sens_SRaw;
extern int16_t Sens_DltSRaw;
extern uint16_t Sens_SRawComp;

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


extern volatile uint16_t Flag_1Ms;


unsigned char Usr_DataBits(unsigned char typ, unsigned char* byt);

void Usr_TComp_Polynomial_Cubic(uint16_t rawt, int16_t *out);

#define DEF_SRAW_FILTERMAX      64
#define DEF_SRAW_FILTERCNT      4


extern uint16_t FilterBuff[DEF_SRAW_FILTERMAX];
extern uint8_t FilterIndex;
extern uint32_t FilterTotal;

uint16_t Usr_SRaw_Filter(uint16_t in);



#endif


