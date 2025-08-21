#ifndef __USR_DEBUG_H__
#define __USR_DEBUG_H__

#include "Usr_Config.h"
#include "stdio.h"
#include "Usr_Task.h"


#define DBG_DEBUG_PRINTF_EN     0
#define DBG_INIT_PRINTF_EN      1
#define DBG_ERROR_PRINTF_EN     0
#define DBG_CUST_PRINTF_EN      0
#define DBG_MODBUS_PRINTF_EN    0
#define DBG_E703_PRINTF_EN      0
#define DBG_DF_PRINTF_EN        0
#define DBG_I2CA_PRINTF_EN      0
#define DBG_ADC_PRINTF_EN       0





#if(defined(DBG_DEBUG_PRINTF_EN)&&(DBG_DEBUG_PRINTF_EN == 1))
    
#define NOS_printf(...)   do{ printf(__VA_ARGS__);    }while(0)
    
#else
    
#define NOS_printf(...)   
    
#endif


#if(defined(DBG_DEBUG_PRINTF_EN)&&(DBG_DEBUG_PRINTF_EN == 1))
    
    #define Debug_printf(...)   do{ printf(__VA_ARGS__);    }while(0)
    
#else

#define Debug_printf(...)   

#endif

#if(defined(DBG_INIT_PRINTF_EN)&&(DBG_INIT_PRINTF_EN == 1))
    
    #define Init_printf(...)    do{ printf(__VA_ARGS__);    }while(0)
    
#else

#define Init_printf(...)   

#endif

#if(defined(DBG_ERROR_PRINTF_EN)&&(DBG_ERROR_PRINTF_EN == 1))
    
    #define Error_printf(...)   do{  printf(__VA_ARGS__);   }while(0)
    
#else

#define Error_printf(...)   

#endif

#if(defined(DBG_CUST_PRINTF_EN)&&(DBG_CUST_PRINTF_EN == 1))
    
    #define Cust_printf(...)    do{ printf(__VA_ARGS__);   }while(0)
    
#else

#define Cust_printf(...)   

#endif

#if(defined(DBG_MODBUS_PRINTF_EN)&&(DBG_MODBUS_PRINTF_EN == 1))
    
    #define Modbus_printf(...)   do{ printf(__VA_ARGS__);    }while(0)
    
#else

#define Modbus_printf(...)   

#endif


#if(defined(DBG_E703_PRINTF_EN)&&(DBG_E703_PRINTF_EN == 1))
    
    #define E703_printf(...)   do{ printf(__VA_ARGS__);    }while(0)
    
#else

#define E703_printf(...)   

#endif




#if(defined(DBG_DF_PRINTF_EN)&&(DBG_DF_PRINTF_EN == 1))
    
    #define DF_printf(...)   do{ printf(__VA_ARGS__);    }while(0)
    
#else

#define DF_printf(...)   

#endif

#if(defined(DBG_I2CA_PRINTF_EN)&&(DBG_I2CA_PRINTF_EN == 1))
    
    #define I2CA_printf(...)   do{ printf(__VA_ARGS__);    }while(0)
    
#else

#define I2CA_printf(...)   

#endif



#if(defined(DBG_ADC_PRINTF_EN)&&(DBG_ADC_PRINTF_EN == 1))
    
    #define ADC_printf(...)   do{ printf(__VA_ARGS__);    }while(0)
    
#else

#define ADC_printf(...)   

#endif





#endif

