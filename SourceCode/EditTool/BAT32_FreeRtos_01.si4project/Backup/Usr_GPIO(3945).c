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
    
    
    PORT_Init(PORT7,PIN0,INPUT);
    
    PORT_Init(PORT7,PIN1,OUTPUT);
    PORT_Init(PORT7,PIN2,OUTPUT);
    
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
            PORT_ClrBit(PORT7,PIN1);
            PORT_SetBit(PORT7,PIN2);
            tmp1 = 1;
        }
        else
        {
            PORT_SetBit(PORT7,PIN1);
            PORT_ClrBit(PORT7,PIN2);
            tmp1 = 0;
        }
    }
    
    while(PORT_GetBit(PORT7, PIN0));
    
    
}



#endif


