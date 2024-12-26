#ifndef __USR_GPIO_C__
#define __USR_GPIO_C__

#include<stdint.h>

#include "BAT32A237.h"

#include"Usr_GPIO.h"



uint32_t Usr_GPIO_Timestamp;


void Usr_GPIO_InitSetup(void)
{
    PORT->P7    = 0x02U;
    PORT->PM7  &= ~(3<<1);          // P71/LED, P72/LED
    
    Usr_GPIO_Timestamp = 0;
}

void Usr_GPIO_MainLoop(void)
{
    if(Usr_GPIO_Timestamp == 0)
    {
        Usr_GPIO_Timestamp = 100;
        PORT->P7 ^= (1<<1);         // Toggle P71
        PORT->P7 ^= (1<<2);         // Toggle P72
    }
}



#endif


