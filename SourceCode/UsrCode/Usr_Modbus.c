#ifndef __USR_MODBUS_C__
#define __USR_MODBUS_C__

#include <stdint.h>
#include "Usr_Config.h"
#include "Usr_Modbus.h"
#include "Usr_E703.h"


/* ----------------------- Static variables ---------------------------------*/
uint16_t   usRegInputStart = REG_INPUT_START;
uint16_t   usRegInputBuf[REG_INPUT_NREGS];

#if 1
unsigned short   usRegHoldingStart = REG_HOLDING_START;
unsigned short   usRegHoldingBuf[REG_HOLDING_NREGS];
#endif

uint8_t Usr_Mb_En;

uint8_t Usr_Mb_Timer_En;
uint8_t Usr_Mb_Timer_Cnt;

uint8_t Usr_Mb_Comm_Tx_En;
uint8_t Usr_Mb_Comm_Rx_En;

uint8_t Usr_MbToE703_Addr(uint16_t mi,uint8_t *ei)
{
    if((mi>=1024)&&(mi<=1101))
    {
        if((mi>=1024)&&(mi<=1039))
        {
            *ei = (mi-1024)*2;
            
            return 1;
        }
        else if(mi>=1040)
        {
            *ei = 0x22;
            
            return 1;
        }
        else if((mi>=1041)&&(mi<=1050))
        {
            *ei = (mi-1041+0x13)*2;
            
            return 1;
        }
        else if((mi>=1051)&&(mi<=1053))
        {
            *ei = (mi-1051+0x23)*2;
            
            return 1;
        }
        else if((mi>=1054)&&(mi<=1100))
        {
            *ei = (mi-1054+0x27)*2;
            
            return 1;
        }
        else if(mi>=1101)
        {
            *ei = 0xE4;
            
            return 1;
        }
    }
    else if((mi>=1280)&&(mi<=1343))
    {
        *ei = (mi-1280)*2;
        
        return 1;
    }
    
    return 0;
    
}

uint8_t Usr_E703RegToMb_Addr(uint8_t ei,uint16_t *mi)
{
    if(Usr_Is_RegAddr(ei) == 1)
    {
        if(ei<=0x1E)
        {   
            *mi = ei/2+1024;
            
            return 1;
        }
        else if(ei==0x22)
        {
            *mi = 1040;
            
            return 1;
        }
        else if((ei>=0x026)&&(ei<=0x4A))
        {   
            *mi = (ei-0x26)/2+1041;
            
            return 1;
        }
        else if((ei>=0x04E)&&(ei<=0xAA))
        {   
            *mi = (ei-0x4E)/2+1054;
            
            return 1;
        }
        else if(ei==0xE4)
        {
            *mi = 1101;
            
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
    
}

uint8_t Usr_E703CMToMb_Addr(uint8_t ei,uint16_t *mi)
{   
    if(Usr_Is_CMAddr(ei) == 1)
    {
        if(ei<=0x7E)
        {
            *mi = ei/2+1280;
            
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}



#endif



