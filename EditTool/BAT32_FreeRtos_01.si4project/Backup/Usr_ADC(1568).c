#ifndef __USR_ADC_C__
#define __USR_ADC_C__

#include <stdio.h>
#include "Usr_Config.h"
#include "Usr_ADC.h"

#include "BAT32A237.h"
#include "userdefine.h"
#include "adc.h"

#define DEF_ADC_STATE_UNINIT    (0)
#define DEF_ADC_STATE_INIT      (1)
#define DEF_ADC_STATE_START     (2)
#define DEF_ADC_STATE_PROC      (3)
#define DEF_ADC_STATE_FREE      (4)
#define DEF_ADC_STATE_STOP      (5)


uint8_t Usr_Adc_State;
uint32_t Usr_Adc_TimeCnt;
uint32_t Usr_Adc_StageHoldTime;
uint16_t Usr_Adc_Value;


void Usr_Adc_InitSetup(void)
{
    ADC_Init();
    
    Usr_Adc_State = DEF_ADC_STATE_INIT;
    
    Usr_Adc_TimeCnt = 0;
    Usr_Adc_StageHoldTime = 0;
    
    g_AdcIntTaken = 0;
    
    ADC_Start(ADC_CHANNEL_2);
    
    Usr_Adc_State = DEF_ADC_STATE_START;
    Usr_Adc_StageHoldTime = 20;
    
    //while(g_AdcIntTaken == 0);
    //g_AdcIntTaken = 0;
}

void Usr_Adc_MainLoop(void)
{
    switch(Usr_Adc_State)
    {
        case DEF_ADC_STATE_UNINIT:
        {
            Usr_Adc_InitSetup();
        }
        break;
        case DEF_ADC_STATE_INIT:
        {
            Usr_Adc_InitSetup();
        }
        break;
        case DEF_ADC_STATE_START:
        {
            if(g_AdcIntTaken == 1)
            {
                Usr_Adc_State = DEF_ADC_STATE_PROC;
            }
            else 
            {
                if(Usr_Adc_StageHoldTime == 0)
                {
                    Usr_Adc_State = DEF_ADC_STATE_INIT;
                }
            }
            
        }
        break;
        case DEF_ADC_STATE_PROC:
        {
            Usr_Adc_Value = 
            printf("");
        }
        break;
        case DEF_ADC_STATE_FREE:
        {
            
        }
        break;
        case DEF_ADC_STATE_STOP:
        {
            
        }
        break;
				
    }
    if(g_AdcIntTaken)
}


#endif


