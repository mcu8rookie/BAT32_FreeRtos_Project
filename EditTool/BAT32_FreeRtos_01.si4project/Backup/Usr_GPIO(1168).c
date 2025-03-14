#ifndef __USR_GPIO_C__
#define __USR_GPIO_C__

#include<stdint.h>

#include "BAT32A237.h"

#include"gpio.h"

#include"Usr_GPIO.h"

#include "Usr_I2C.h"

#include"Usr_Uart.h"



uint32_t Usr_GPIO_Timestamp;
uint32_t GPIO_Input_Temp;

uint8_t Usr_HeatVoltage_State0;
uint8_t Usr_HeatVoltage_State1;

void Usr_HeatVoltage_Set(uint8_t voltage)
{
    
    switch(voltage)
    {   
        case DEF_HEATVOLTAGE_0D0V:
        {
            PORT_ClrBit(Usr_VHT_EN1_PORT,Usr_VHT_EN1_PIN);
            PORT_ClrBit(Usr_VHT_EN2_PORT,Usr_VHT_EN2_PIN);
            PORT_ClrBit(Usr_VHT_EN3_PORT,Usr_VHT_EN3_PIN);
            PORT_ClrBit(Usr_VHT_EN4_PORT,Usr_VHT_EN4_PIN);
            
            //Usr_HeatVoltage_State0 = voltage;
        }
        break;
        case DEF_HEATVOLTAGE_1D2V:
        {
            PORT_ClrBit(Usr_VHT_EN1_PORT,Usr_VHT_EN1_PIN);
            PORT_ClrBit(Usr_VHT_EN2_PORT,Usr_VHT_EN2_PIN);
            PORT_ClrBit(Usr_VHT_EN3_PORT,Usr_VHT_EN3_PIN);
            PORT_ClrBit(Usr_VHT_EN4_PORT,Usr_VHT_EN4_PIN);
            
            PORT_SetBit(Usr_VHT_EN4_PORT,Usr_VHT_EN4_PIN);
            
            //Usr_HeatVoltage_State0 = voltage;
        }
        break;
        case DEF_HEATVOLTAGE_1D8V:
        {
            PORT_ClrBit(Usr_VHT_EN1_PORT,Usr_VHT_EN1_PIN);
            PORT_ClrBit(Usr_VHT_EN2_PORT,Usr_VHT_EN2_PIN);
            PORT_ClrBit(Usr_VHT_EN3_PORT,Usr_VHT_EN3_PIN);
            PORT_ClrBit(Usr_VHT_EN4_PORT,Usr_VHT_EN4_PIN);
            
            PORT_SetBit(Usr_VHT_EN3_PORT,Usr_VHT_EN3_PIN);
            
            //Usr_HeatVoltage_State0 = voltage;
        }
        break;
        case DEF_HEATVOLTAGE_3D3V:
        {
            PORT_ClrBit(Usr_VHT_EN1_PORT,Usr_VHT_EN1_PIN);
            PORT_ClrBit(Usr_VHT_EN2_PORT,Usr_VHT_EN2_PIN);
            PORT_ClrBit(Usr_VHT_EN3_PORT,Usr_VHT_EN3_PIN);
            PORT_ClrBit(Usr_VHT_EN4_PORT,Usr_VHT_EN4_PIN);
            
            PORT_SetBit(Usr_VHT_EN1_PORT,Usr_VHT_EN1_PIN);
            
            //Usr_HeatVoltage_State0 = voltage;
        }
        break;
        case DEF_HEATVOLTAGE_4D5V:
        {
            PORT_ClrBit(Usr_VHT_EN1_PORT,Usr_VHT_EN1_PIN);
            PORT_ClrBit(Usr_VHT_EN2_PORT,Usr_VHT_EN2_PIN);
            PORT_ClrBit(Usr_VHT_EN3_PORT,Usr_VHT_EN3_PIN);
            PORT_ClrBit(Usr_VHT_EN4_PORT,Usr_VHT_EN4_PIN);
            
            PORT_SetBit(Usr_VHT_EN2_PORT,Usr_VHT_EN2_PIN);
            
            //Usr_HeatVoltage_State0 = voltage;
        }
        break;
        default:
        
        break;
    }
}

void Usr_GPIO_InitSetup(void)
{
    //PORT->P7    = 0x02U;
    //PORT->PM7  &= ~(3<<1);          // P71/LED, P72/LED
    
    
    PORT_Init(Usr_KEY1_PORT,Usr_KEY1_PIN,PULLUP_INPUT);
    
    PORT_Init(Usr_LED1_PORT,Usr_LED1_PIN,OUTPUT);
    PORT_Init(Usr_LED2_PORT,Usr_LED2_PIN,OUTPUT);
    
    PORT_Init(Usr_LDOEN_PORT,Usr_LDOEN_PIN,OUTPUT);
    PORT_SetBit(Usr_LDOEN_PORT,Usr_LDOEN_PIN);
    
    PORT_Init(Usr_HEATEN_PORT,Usr_HEATEN_PIN,OUTPUT);
    PORT_SetBit(Usr_HEATEN_PORT,Usr_HEATEN_PIN);
    
    #if(defined(DBG_PRINT_UART)&&(DBG_PRINT_UART>0))
    #else
    PORT_Init(Usr_DBGIO1_PORT,Usr_DBGIO1_PIN,OUTPUT);
    PORT_SetBit(Usr_DBGIO1_PORT,Usr_DBGIO1_PIN);
    
    PORT_Init(Usr_DBGIO2_PORT,Usr_DBGIO2_PIN,OUTPUT);
    PORT_SetBit(Usr_DBGIO2_PORT,Usr_DBGIO2_PIN);
    #endif
    
    #if(defined(DEF_BOARD_TYPE)&&(DEF_BOARD_TYPE==DEF_BOARD_PROJ1_EN))
    
    #endif
    
    
    #if(defined(DEF_BOARD_TYPE)&&(DEF_BOARD_TYPE==DEF_BOARD_PROJ2_EN))
    PORT_Init(Usr_VHT_EN1_PORT,Usr_VHT_EN1_PIN,OUTPUT);
    PORT_ClrBit(Usr_VHT_EN1_PORT,Usr_VHT_EN1_PIN);
    
    PORT_Init(Usr_VHT_EN2_PORT,Usr_VHT_EN2_PIN,OUTPUT);
    PORT_ClrBit(Usr_VHT_EN2_PORT,Usr_VHT_EN2_PIN);
    
    PORT_Init(Usr_VHT_EN3_PORT,Usr_VHT_EN3_PIN,OUTPUT);
    PORT_ClrBit(Usr_VHT_EN3_PORT,Usr_VHT_EN3_PIN);
    
    PORT_Init(Usr_VHT_EN4_PORT,Usr_VHT_EN4_PIN,OUTPUT);
    PORT_ClrBit(Usr_VHT_EN4_PORT,Usr_VHT_EN4_PIN);
    
    PORT_Init(Usr_RS485_DIR_PORT,Usr_RS485_DIR_PIN,OUTPUT);
    PORT_ClrBit(Usr_RS485_DIR_PORT,Usr_RS485_DIR_PIN);
    #endif
    
    
    
    #if(defined(DEF_BOARD_TYPE)&&(DEF_BOARD_TYPE==DEF_BOARD_PROJ2_EN))
    //Usr_HeatVoltage_Set(DEF_HEATVOLTAGE_0D0V);
    //Usr_HeatVoltage_Set(DEF_HEATVOLTAGE_1D2V);
    //Usr_HeatVoltage_Set(DEF_HEATVOLTAGE_1D8V);
    //Usr_HeatVoltage_Set(DEF_HEATVOLTAGE_3D3V);
    Usr_HeatVoltage_Set(DEF_HEATVOLTAGE_4D5V);
    
    PORT_SetBit(Usr_RS485_DIR_PORT,Usr_RS485_DIR_PIN);
    #endif
    
    PORT_ClrBit(Usr_HEATEN_PORT,Usr_HEATEN_PIN);
    
    Usr_GPIO_Timestamp = 0;
}

void Usr_GPIO_MainLoop(void)
{
    static uint8_t tmp1 = 0;
    
    if(Usr_GPIO_Timestamp == 0)
    {
        Usr_GPIO_Timestamp = 1000;
        //PORT->P7 ^= (1<<1);         // Toggle P71
        //PORT->P7 ^= (1<<2);         // Toggle P72
        
        if(tmp1 == 0)
        {
            PORT_ClrBit(Usr_LED1_PORT,Usr_LED1_PIN);
            PORT_SetBit(Usr_LED2_PORT,Usr_LED2_PIN);
            tmp1 = 1;
            
        }
        else
        {
            PORT_SetBit(Usr_LED1_PORT,Usr_LED1_PIN);
            PORT_ClrBit(Usr_LED2_PORT,Usr_LED2_PIN);
            tmp1 = 0;
            
        }
        
        
        #if 0
        Usr_HeatVoltage_Set(Usr_HeatVoltage_State0);
        
        if(Usr_HeatVoltage_State0++>5)
        {
            Usr_HeatVoltage_State0 = 0;
        }
        #endif
    }
    
    while(0 == PORT_GetBit(Usr_KEY1_PORT, Usr_KEY1_PIN));
    
    
}



#endif


