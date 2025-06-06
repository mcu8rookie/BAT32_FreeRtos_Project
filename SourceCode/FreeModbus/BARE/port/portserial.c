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

#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

#include "BAT32A237.h"
#include <stdint.h>
#include "Usr_Config.h"
#include "Usr_Modbus.h"

#include "userdefine.h"
#include "sci.h"

#include"Usr_Uart.h"



/* ----------------------- static functions ---------------------------------*/
static void prvvUARTTxReadyISR( void );
static void prvvUARTRxISR( void );

/* ----------------------- Start implementation -----------------------------*/
void
vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{
    /* If xRXEnable enable serial receive interrupts. If xTxENable enable
     * transmitter empty interrupts.
     */
    if(xRxEnable == TRUE)
    {
        Usr_Mb_Comm_Rx_En = 1;
        
        INTC_ClearPendingIRQ(SR0_IRQn); /* clear INTSR1 interrupt flag */
        
        NVIC_ClearPendingIRQ(SR0_IRQn); /* clear INTSR1 interrupt flag */
        
        INTC_EnableIRQ(SR0_IRQn);       /* enable INTSR1 interrupt */
        
        NVIC_EnableIRQ(SR0_IRQn); 
    }
    else
    {
        Usr_Mb_Comm_Rx_En = 0;
        
        INTC_ClearPendingIRQ(SR0_IRQn); /* clear INTSR1 interrupt flag */
        
        NVIC_ClearPendingIRQ(SR0_IRQn); /* clear INTSR1 interrupt flag */
        
        INTC_DisableIRQ(SR0_IRQn);       /* enable INTSR1 interrupt */
        
        NVIC_DisableIRQ(SR0_IRQn); 
    }
    
    if(xTxEnable == TRUE)
    {
        Usr_Mb_Comm_Tx_En = 1;
        
        INTC_ClearPendingIRQ(ST0_IRQn); /* clear INTST1 interrupt flag */
        
        NVIC_ClearPendingIRQ(ST0_IRQn); /* clear INTST1 interrupt flag */
        
        INTC_EnableIRQ(ST0_IRQn);       /* enable INTST1 interrupt */
        
        NVIC_EnableIRQ(ST0_IRQn); 
    }
    else
    {
        Usr_Mb_Comm_Tx_En = 0;
        
        INTC_ClearPendingIRQ(ST0_IRQn); /* clear INTST1 interrupt flag */
        
        NVIC_ClearPendingIRQ(ST0_IRQn); /* clear INTST1 interrupt flag */
        
        INTC_DisableIRQ(ST0_IRQn);       /* enable INTST1 interrupt */
        
        NVIC_DisableIRQ(ST0_IRQn); 
    }
    
}

BOOL
xMBPortSerialInit( UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity )
{
    
    //Usr_Uart_Init(0,115200);
    
    #if(defined(DBG_PRINT_UART)&&(DBG_PRINT_UART==DBG_UART0))
    //Usr_Uart_Init(0,Usr_Uart_Baudrate);
    #endif
    
    //return FALSE;
    return TRUE;
}

BOOL
xMBPortSerialPutByte( CHAR ucByte )
{
    /* Put a byte in the UARTs transmit buffer. This function is called
     * by the protocol stack if pxMBFrameCBTransmitterEmpty( ) has been
     * called. */
    
    UART0_Send(ucByte);
    
    return TRUE;
}

BOOL
xMBPortSerialGetByte( CHAR * pucByte )
{
    /* Return the byte in the UARTs receive buffer. This function is called
     * by the protocol stack after pxMBFrameCBByteReceived( ) has been called.
     */
    
    *pucByte = UART0_Receive();
    
    return TRUE;
}

/* Create an interrupt handler for the transmit buffer empty interrupt
 * (or an equivalent) for your target processor. This function should then
 * call pxMBFrameCBTransmitterEmpty( ) which tells the protocol stack that
 * a new character can be sent. The protocol stack will then call 
 * xMBPortSerialPutByte( ) to send the character.
 */
static void prvvUARTTxReadyISR( void )
{
    pxMBFrameCBTransmitterEmpty(  );
}

/* Create an interrupt handler for the receive interrupt for your target
 * processor. This function should then call pxMBFrameCBByteReceived( ). The
 * protocol stack will then call xMBPortSerialGetByte( ) to retrieve the
 * character.
 */
static void prvvUARTRxISR( void )
{
    pxMBFrameCBByteReceived(  );
}
