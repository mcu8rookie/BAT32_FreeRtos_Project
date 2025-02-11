#ifndef __USR_DEBUG_H__
#define __USR_DEBUG_H__

#include"Usr_Config.h"


#define DEBUG_UART0 1
#define DEBUG_UART1 2
#define DEBUG_UART2 3

//#define DEBUG_PRINT_UART    DEBUG_UART0
//#define DEBUG_PRINT_UART    DEBUG_UART1
#define DEBUG_PRINT_UART    DEBUG_UART2


#define DBG_DEBUG_PRINTF_EN     1
#define DBG_INIT_PRINTF_EN      1
#define DBG_ERROR_PRINTF_EN     1
#define DBG_CUST_PRINTF_EN      1
#define DBG_TRANS_PRINTF_EN     1



#if(defined(DBG_DEBUG_PRINTF_EN)&&(DBG_DEBUG_PRINTF_EN == 1))
#define Debug_printf(...)   printf(__VA_ARGS__)
#else
#define Debug_printf(...)   
#endif

#if(defined(DBG_INIT_PRINTF_EN)&&(DBG_INIT_PRINTF_EN == 1))
#define Init_printf(...)   printf(__VA_ARGS__)
#else
#define Init_printf(...)   
#endif

#if(defined(DBG_ERROR_PRINTF_EN)&&(DBG_ERROR_PRINTF_EN == 1))
#define Error_printf(...)   printf(__VA_ARGS__)
#else
#define Error_printf(...)   
#endif

#if(defined(DBG_CUST_PRINTF_EN)&&(DBG_CUST_PRINTF_EN == 1))
#define Cust_printf(...)   printf(__VA_ARGS__)
#else
#define Cust_printf(...)   
#endif

#if(defined(DBG_TRANS_PRINTF_EN)&&(DBG_TRANS_PRINTF_EN == 1))
#define Trans_printf(...)   printf(__VA_ARGS__)
#else
#define Trans_printf(...)   
#endif






#endif

