/*
 * FreeModbus Libary: BARE Demo Application
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id$
 */

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

#include "Usr_Modbus.h"

#include "Usr_E703.h"

/* ----------------------- Defines ------------------------------------------*/
//#define REG_INPUT_START 1000
//#define REG_INPUT_NREGS 4

/* ----------------------- Static variables ---------------------------------*/
//static USHORT   usRegInputStart = REG_INPUT_START;
//static USHORT   usRegInputBuf[REG_INPUT_NREGS];

/* ----------------------- Start implementation -----------------------------*/
int
main_disable( void )
{
    eMBErrorCode    eStatus;
    
    eStatus = eMBInit( MB_RTU, 0x0A, 0, 38400, MB_PAR_EVEN );
    
    /* Enable the Modbus Protocol Stack. */
    eStatus = eMBEnable(  );
    
    for( ;; )
    {
        ( void )eMBPoll(  );
        
        /* Here we simply count the number of poll cycles. */
        usRegInputBuf[0]++;
    }
}

eMBErrorCode
eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    int             iRegIndex;

    if( ( usAddress >= REG_INPUT_START )
        && ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
    {
        iRegIndex = ( int )( usAddress - usRegInputStart );
        while( usNRegs > 0 )
        {
            *pucRegBuffer++ =
                ( unsigned char )( usRegInputBuf[iRegIndex] >> 8 );
            *pucRegBuffer++ =
                ( unsigned char )( usRegInputBuf[iRegIndex] & 0xFF );
            iRegIndex++;
            usNRegs--;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }

    return eStatus;
}

eMBErrorCode
eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs,
                 eMBRegisterMode eMode )
{
    //return MB_ENOREG;
    unsigned char i;
    
    if(eMode == MB_REG_READ)
    {   
        if((usAddress>=1024)&&(usAddress<=1101))
        {
            for(i=0;i<usNRegs;i++)
            {   
                *(pucRegBuffer+i*2) = E703_RegBuff[usAddress-1024 + i]>>8;
                *(pucRegBuffer+i*2+1) = E703_RegBuff[usAddress-1024 + i];
            }
        }
        else if((usAddress>=1280)&&(usAddress<=1343))
        {
            for(i=0;i<usNRegs;i++)
            {   
                *(pucRegBuffer+i*2) = E703_CMBuff[usAddress-1280 + i]>>8;
                *(pucRegBuffer+i*2+1) = E703_CMBuff[usAddress-1280 + i];
            }
        }
        
    }
    
    if(eMode == MB_REG_WRITE)
    {   
        uint8_t ea;
        uint16_t ma;
        uint16_t val;
        #if 0
        for(i=0;i<usNRegs;i++)
        {   
            usRegHoldingBuf[usAddress+i] = *(pucRegBuffer+i*2);
            usRegHoldingBuf[usAddress+i] <<= 8;
            usRegHoldingBuf[usAddress+i] += *(pucRegBuffer+i*2+1);
        }
        #endif
        
        if((usAddress>=1024)&&(usAddress<=1101))
        {
            
            if(Usr_MbToE703_Addr(usAddress,&ea) == 1)
            {
                val = *(pucRegBuffer);
                val <<= 8;
                val += *(pucRegBuffer+1);
                
                E703_RegBuff[usAddress-1024] = val;
                
                Usr_E703_WriteReg(ea,val);
            }
            
        }
        else if((usAddress>=1280)&&(usAddress<=1343))
        {
            
            if(Usr_MbToE703_Addr(usAddress,&ea) == 1)
            {
                val = *(pucRegBuffer);
                val <<= 8;
                val += *(pucRegBuffer+1);
                
                E703_CMBuff[usAddress-1024] = val;
                
                Usr_E703_WriteReg(ea,val);
            }
            
        }
    }
    
    return MB_ENOERR;
}


eMBErrorCode
eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,
               eMBRegisterMode eMode )
{
    return MB_ENOREG;
}

eMBErrorCode
eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
    return MB_ENOREG;
}
