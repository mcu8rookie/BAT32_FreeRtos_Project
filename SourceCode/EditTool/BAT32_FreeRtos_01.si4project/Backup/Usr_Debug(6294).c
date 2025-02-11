#ifndef __USR_DEBUG_C__
#define __USR_DEBUG_C__

#include"Usr_Config.h"
#include"Usr_Debug.h"


#if 0
#define Debug_printf_Mut(...)   \
    do{ \
        if(pdPASS == xSemaphoreTake(Usr_SemaphoreHandle_Print,1000))    \
        {   \
            printf(__VA_ARGS__);    \
            xSemaphoreGive(Usr_SemaphoreHandle_Print);  \
        }   \
        else    \
        {   \
            printf("\nErr: xSemaphoreTake(): ");    \
            printf(__VA_ARGS__);    \
        }   \
    }while(0)
#endif

#endif


