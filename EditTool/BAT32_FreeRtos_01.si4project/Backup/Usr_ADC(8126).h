#ifndef __USR_ADC_H__
#define __USR_ADC_H__


extern uint8_t Usr_Adc_State;
extern uint32_t Usr_Adc_TimeCnt;
extern uint32_t Usr_Adc_StageHoldTime;
extern uint8_t Usr_Adc_ValueH;
extern uint16_t Usr_Adc_Value;

void Usr_Adc_InitSetup(void);

void Usr_Adc_MainLoop(void);



#endif



