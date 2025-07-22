#ifndef __USR_ADC_C__
#define __USR_ADC_C__

#include <stdint.h>
#include <stdio.h>

#include "Usr_Config.h"
#include "Usr_Debug.h"
#include "Usr_ADC.h"

#include "BAT32A237.h"
#include "userdefine.h"
#include "adc.h"

#include "Usr_Psf.h"
#include "User_SensorParam.h"

#define DEF_ADC_STATE_UNINIT    (0)
#define DEF_ADC_STATE_INIT      (1)
#define DEF_ADC_STATE_START     (2)
#define DEF_ADC_STATE_PROC      (3)
#define DEF_ADC_STATE_FREE      (4)
#define DEF_ADC_STATE_STOP      (5)

//#define DEF_ADC_CHANNEL         (ADC_CHANNEL_2)
#define DEF_ADC_CHANNEL         (ADC_CHANNEL_5)

uint8_t Usr_Adc_State;
uint32_t Usr_Adc_TimeCnt;
uint32_t Usr_Adc_StageHoldTime;
volatile uint8_t Usr_Adc_ValueH;
volatile uint16_t Usr_Adc_Value;
volatile uint16_t Usr_Adc_ValidTime;
uint16_t Flag_HeatMems;


void Usr_Adc_InitSetup(void)
{
    ADC_Init();
    
    Usr_Adc_State = DEF_ADC_STATE_INIT;
    
    Usr_Adc_TimeCnt = 0;
    Usr_Adc_StageHoldTime = 0;
    
    gp_u1_adc_buf = &Usr_Adc_ValueH;
    gp_u2_adc_buf = &Usr_Adc_Value;
    
    g_AdcIntTaken = 0;
    
    ADC_Start(DEF_ADC_CHANNEL);
    //ADC_Start(ADC_CHANNEL_5);
    
    Usr_Adc_State = DEF_ADC_STATE_START;
    Usr_Adc_StageHoldTime = 10;
    
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
            if(g_AdcIntTaken > 0)
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
            
            g_AdcIntTaken = 0;
            Usr_Adc_State = DEF_ADC_STATE_FREE;
            Usr_Adc_StageHoldTime = 10;
            
            if(Usr_Adc_ValidTime>20)
            {
                Monitor_Raw1 = Usr_Adc_Value;
                setSensorParam((uint8_t*)&g_tSensor.HeaterRawData, Monitor_Raw1);
            }
            
            ADC_printf("\nUsr_Adc_Value, %d,\tUsr_Adc_ValueH, %d,",Usr_Adc_Value,Usr_Adc_ValueH);
            ADC_printf("\tUsr_Adc_Value, %d,\tMonitor_Raw1, %d,",Usr_Adc_Value,Monitor_Raw1);
            
            // ADC_Stop();
        }
        break;
        case DEF_ADC_STATE_FREE:
        {
            if(Usr_Adc_StageHoldTime == 0)
            {
                ADC_Start(DEF_ADC_CHANNEL);
                //ADC_Start(ADC_CHANNEL_5);
                
                g_AdcIntTaken = 0;
                Usr_Adc_State = DEF_ADC_STATE_START;
                Usr_Adc_StageHoldTime = 20;
            }
        }
        break;
        case DEF_ADC_STATE_STOP:
        {
            
        }
        break;
        
    }
}


#endif


