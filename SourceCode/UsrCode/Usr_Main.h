#ifndef __USR_MAIN_H__
#define __USR_MAIN_H__



extern unsigned char MCU_Reset_Flag;


extern uint8_t Flag_SysTick;
extern uint32_t Mcu_Timestamp;
extern uint32_t Mcu_ResetSource;
extern uint32_t Mcu_Name;
extern uint32_t Product_Name;
extern uint32_t Product_Verison;

extern uint16_t TimeSn_Time;
extern uint16_t TimeSn_SN;

extern uint32_t Mcu_Time1s_Cnt;


extern volatile unsigned int DlyMsCnt;
void Sample_DelayMs(unsigned int ms);



#endif

