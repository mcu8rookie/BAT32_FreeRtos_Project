#ifndef __USR_DEBUG_H__
#define __USR_DEBUG_H__

#include"Usr_Config.h"

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "Usr_Task.h"


#define DBG_UART0 1
#define DBG_UART1 2
#define DBG_UART2 3

#define DBG_PRINT_UART      DBG_UART0
//#define DBG_PRINT_UART      DBG_UART1
//#define DBG_PRINT_UART      DBG_UART2


#define DBG_DEBUG_PRINTF_EN     1
#define DBG_INIT_PRINTF_EN      1
#define DBG_ERROR_PRINTF_EN     1
#define DBG_CUST_PRINTF_EN      1
#define DBG_TRANS_PRINTF_EN     1


#define DBG_PRINT_USE_SEMAPHORE_EN  1


#if(defined(DBG_DEBUG_PRINTF_EN)&&(DBG_DEBUG_PRINTF_EN == 1))

#if(defined(DBG_PRINT_USE_SEMAPHORE_EN)&&(DBG_PRINT_USE_SEMAPHORE_EN == 1))
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
#else
#define Debug_printf_Mut(...)   do{ printf(__VA_ARGS__);    }while(0)
#endif

#define Debug_printf(...)   do{ printf(__VA_ARGS__);    }while(0)

#else

#define Debug_printf(...)   

#endif

#if(defined(DBG_INIT_PRINTF_EN)&&(DBG_INIT_PRINTF_EN == 1))

#if(defined(DBG_PRINT_USE_SEMAPHORE_EN)&&(DBG_PRINT_USE_SEMAPHORE_EN == 1))
#define Init_printf_Mut(...)    \
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
#else
#define Init_printf_Mut(...)    do{ printf(__VA_ARGS__);    }while(0)
#endif

#define Init_printf(...)    do{ printf(__VA_ARGS__);    }while(0)

#else

#define Init_printf(...)   

#endif

#if(defined(DBG_ERROR_PRINTF_EN)&&(DBG_ERROR_PRINTF_EN == 1))

#if(defined(DBG_PRINT_USE_SEMAPHORE_EN)&&(DBG_PRINT_USE_SEMAPHORE_EN == 1))
#define Error_printf_Mut(...)   \
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
#else
#define Error_printf_Mut(...)   do{  printf(__VA_ARGS__);   }while(0)
#endif

#define Error_printf(...)   do{  printf(__VA_ARGS__);   }while(0)

#else

#define Error_printf(...)   

#endif

#if(defined(DBG_CUST_PRINTF_EN)&&(DBG_CUST_PRINTF_EN == 1))

#if(defined(DBG_PRINT_USE_SEMAPHORE_EN)&&(DBG_PRINT_USE_SEMAPHORE_EN == 1))
#define Cust_printf_Mut(...)    \
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
#else
#define Cust_printf_Mut(...)    do{ printf(__VA_ARGS__);   }while(0)
#endif

#define Cust_printf(...)    do{ printf(__VA_ARGS__);   }while(0)

#else

#define Cust_printf(...)   

#endif

#if(defined(DBG_TRANS_PRINTF_EN)&&(DBG_TRANS_PRINTF_EN == 1))

#if(defined(DBG_PRINT_USE_SEMAPHORE_EN)&&(DBG_PRINT_USE_SEMAPHORE_EN == 1))
#define Trans_printf_Mut(...)   \
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
#else
#define Trans_printf_Mut(...)   do{ printf(__VA_ARGS__);    }while(0)
#endif

#define Trans_printf(...)   do{ printf(__VA_ARGS__);    }while(0)

#else

#define Trans_printf(...)   

#endif






#endif

