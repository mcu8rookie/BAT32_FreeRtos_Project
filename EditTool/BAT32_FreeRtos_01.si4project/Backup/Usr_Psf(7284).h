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
extern unsigned char Psf_Current_State;
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


unsigned char Usr_DataBits(unsigned char typ, unsigned char* byt);

void Usr_TComp_Polynomial_Cubic(uint16_t rawt, int16_t *out);


#endif


