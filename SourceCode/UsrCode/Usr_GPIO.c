#ifndef __USR_GPIO_C__
#define __USR_GPIO_C__

#include<stdint.h>

#include "BAT32A237.h"

#include"gpio.h"

#include"Usr_GPIO.h"

#include "Usr_I2C.h"




uint32_t Usr_GPIO_Timestamp;
uint32_t GPIO_Input_Temp;


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
    
    #if !defined(DBG_PRINT_UART)
    
    PORT_Init(Usr_DBGIO1_PORT,Usr_DBGIO1_PIN,OUTPUT);
    PORT_SetBit(Usr_DBGIO1_PORT,Usr_DBGIO1_PIN);
    
    PORT_Init(Usr_DBGIO2_PORT,Usr_DBGIO2_PIN,OUTPUT);
    PORT_SetBit(Usr_DBGIO2_PORT,Usr_DBGIO2_PIN);
    #endif
    
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
            
            #if !defined(DBG_PRINT_UART)
            PORT_SetBit(Usr_DBGIO2_PORT,Usr_DBGIO2_PIN);
            #endif
        }
        else
        {
            PORT_SetBit(Usr_LED1_PORT,Usr_LED1_PIN);
            PORT_ClrBit(Usr_LED2_PORT,Usr_LED2_PIN);
            tmp1 = 0;
            
            #if !defined(DBG_PRINT_UART)
            PORT_ClrBit(Usr_DBGIO2_PORT,Usr_DBGIO2_PIN);
            #endif
        }
        
    }
    
    while(0 == PORT_GetBit(Usr_KEY1_PORT, Usr_KEY1_PIN));
    
    
}



#endif


