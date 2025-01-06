#ifndef __USR_GPIO_C__
#define __USR_GPIO_C__

#include<stdint.h>

#include "BAT32A237.h"

#include"Usr_GPIO.h"

#include"gpio.h"



uint32_t Usr_GPIO_Timestamp;
uint32_t GPIO_Input_Temp;


void Usr_GPIO_InitSetup(void)
{
    //PORT->P7    = 0x02U;
    //PORT->PM7  &= ~(3<<1);          // P71/LED, P72/LED
    
    
    PORT_Init(Usr_KEY1_PORT,Usr_KEY1_PIN,PULLUP_INPUT);
    
    PORT_Init(Usr_LED1_PORT,Usr_LED1_PIN,OUTPUT);
    PORT_Init(Usr_LED2_PORT,Usr_LED2_PIN,OUTPUT);
    
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
    }
    
    while(0 == PORT_GetBit(Usr_KEY1_PORT, Usr_KEY1_PIN));
    
    
}



#endif


