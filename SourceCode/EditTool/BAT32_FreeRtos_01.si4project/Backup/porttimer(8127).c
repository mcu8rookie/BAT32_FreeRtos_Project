/*
 * FreeModbus Libary: BARE Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id$
 */

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

#include "BAT32A237.h"
#include "tima.h"

#include <stdint.h>
#include "Usr_Config.h"
#include "Usr_Modbus.h"

/* ----------------------- static functions ---------------------------------*/
//static void prvvTIMERExpiredISR( void );
void prvvTIMERExpiredISR( void );

/* ----------------------- Start implementation -----------------------------*/
BOOL
xMBPortTimersInit( USHORT usTim1Timerout50us )
{
    TMA0_IntervalTimer(TMA_COUNT_SOURCE_FCLK, 800);     // 50us;
    
    // return FALSE;
    return TRUE;
}


inline void
vMBPortTimersEnable(  )
{
    TMA->TA0 = 800 - 1;
    TMA0_Start();
    
    Usr_Mb_Timer_En = 1;
    
    Usr_Mb_Timer_Cnt = 0;
    
    /* Enable the timer with the timeout passed to xMBPortTimersInit( ) */
}

inline void
vMBPortTimersDisable(  )
{
    //TMA0_Stop();
    
    Usr_Mb_Timer_En = 0;
    
    Usr_Mb_Timer_Cnt = 0;
    
    /* Disable any pending timers. */
}

/* Create an ISR which is called whenever the timer has expired. This function
 * must then call pxMBPortCBTimerExpired( ) to notify the protocol stack that
 * the timer has expired.
 */
//static void prvvTIMERExpiredISR( void )
void prvvTIMERExpiredISR( void )
{
    ( void )pxMBPortCBTimerExpired(  );
}

