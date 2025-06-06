#ifndef __USR_INTERRUPT_C__
#define __USR_INTERRUPT_C__

#include<stdint.h>
#include "BAT32A237.h"
#include"Usr_Config.h"
#include"Usr_Main.h"
#include"Usr_GPIO.h"
#include"Usr_Interrupt.h"
#include"Usr_Uart.h"
#include "gpio.h"

#include "Usr_ALSensor.h"
#include "Usr_CMP201.h"

#include "Usr_Psf.h"

#include "Usr_Adc.h"


/***********************************************************************************************************************
* Function Name: SysTick Handler
* Description  : Decreament the g_ticks value
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/


void SysTick_Handler(void)
// void SysTick_Handler_UsrPart(void)
{   // 1 ms;
    //WDT->WDTE = 0xAC;
    
    Mcu_Timestamp++;
    Flag_SysTick = 1;
    
    if((Mcu_Timestamp%1000) == 0)
    {   // 1 s;
        Mcu_Time1s_Cnt++;
    }
    
    Flag_1Ms++;
    
    if(Usr_GPIO_Timestamp > 0)
    {
        Usr_GPIO_Timestamp--;
    }
    
    if(Usr_Uart_Timestamp > 0)
    {
        Usr_Uart_Timestamp--;
    }
    
    #include "Usr_E703.h"
    #if(defined(DEF_SENSOR_E703_EN)&&(DEF_SENSOR_E703_EN==1))
    if(Usr_E307_Timestamp > 0)
    {
        Usr_E307_Timestamp--;
    }
    #endif
    
    if(DlyMsCnt>0)
    {
        DlyMsCnt--;
    }
    
    #if((defined(SENSOR_HT_TYPE))&&(SENSOR_HT_TYPE > 0))
    //if(TH_DelayMs > 0)
    {
      //  TH_DelayMs--;
    }
    if(ALSensor_TH_HoleTime > 0)
    {
        ALSensor_TH_HoleTime--;
    }
    #endif
    
    #if(defined(SENSOR_PT_TYPE)&&(SENSOR_PT_TYPE == SENSOR_TYPE_CMP201))
    if(CMP201_DlyCnt > 0)
    {
        CMP201_DlyCnt--;
    }
    if(ALSensor_CMP201_HoleTime>0)
    {
        ALSensor_CMP201_HoleTime--;
    }
    #endif
    
    if(Psf_State_KeepTime > 0)
    {
        Psf_State_KeepTime--;
    }
    
    if(Usr_Adc_StageHoldTime>0)
    {
        Usr_Adc_StageHoldTime--;
    }
    
    if(Flag_HeatMems == 1)
    {
        if(Usr_Adc_ValidTime<65535)
        {
            Usr_Adc_ValidTime++;
        }
    }
    
    #if(defined(DEF_HEAT_BOARD_EN)&&(DEF_HEAT_BOARD_EN == 1))
    HeatBoard_Cnt++;
    
    if(Flag_HeatBoard == 1)
    {
        if(HeatBoard_Duty == HeatBoard_Cnt)
        {
            HeatBoard_Cool();
        }
        else if(HeatBoard_Period == HeatBoard_Cnt)
        {
            HeatBoard_Heat();
            HeatBoard_Cnt = 0;
        }
        
    }
    else if(Flag_HeatBoard == 2)
    {
        HeatBoard_Heat();
    }
    else
    {
        HeatBoard_Cool();
    }
    #endif
    
    // PORT_ToggleBit(Usr_HTMNBD_PORT,Usr_HTMNBD_PIN);
}

#if 0
SVC_Handler               ; SVCall Handler
PendSV_Handler            ; PendSV Handler
SysTick_Handler           ; SysTick Handler
#endif

#endif


