#ifndef __USR_UART_C__
#define __USR_UART_C__

#include<stdint.h>

#include"Userdefine.h"
#include"sci.h"
#include"BAT32A237.h"
#include"Usr_Uart.h"

uint32_t Usr_Uart_Timestamp;


struct USCI_ST Uart0_St,Uart1_St,Uart2_St;



void Usr_Uart_InitSetup(void)
{
    MD_STATUS status;
    
    status = UART0_Init(SystemCoreClock, 115200);
    
    if(status == MD_ERROR)
    {
        while(1); // The baud rate cannot get at the current system clock frequency.
    }
    
    
    #if 1
    {   
        //SCI0->SO0 |= _0004_SCI_CH2_DATA_OUTPUT_1;
        //SCI0->SOE0 |= _0004_SCI_CH2_OUTPUT_ENABLE;
        //SCI0->SS0 |= _0008_SCI_CH3_START_TRG_ON | _0004_SCI_CH2_START_TRG_ON;
        
        //SCI0->SO0 |= _0001_SCI_CH0_DATA_OUTPUT_1;
        //SCI0->SOL0 &= (uint16_t)~_0001_SCI_CHANNEL0_INVERTED;
        //SCI0->SOE0 |= _0001_SCI_CH0_OUTPUT_ENABLE;
        
        INTC_ClearPendingIRQ(ST0_IRQn); /* clear INTST1 interrupt flag */
        INTC_ClearPendingIRQ(SR0_IRQn); /* clear INTSR1 interrupt flag */
        
        NVIC_ClearPendingIRQ(ST0_IRQn); /* clear INTST1 interrupt flag */
        NVIC_ClearPendingIRQ(SR0_IRQn); /* clear INTSR1 interrupt flag */
        
        INTC_EnableIRQ(ST0_IRQn);       /* enable INTST1 interrupt */
        INTC_EnableIRQ(SR0_IRQn);       /* enable INTSR1 interrupt */
        
        NVIC_EnableIRQ(ST0_IRQn); 
        NVIC_EnableIRQ(SR0_IRQn); 
    }
    #endif
    
    Usr_Uart_Timestamp = 0;
}

void Usr_Uart_MainLoop(void)
{	
    #if 0
		static uint8_t tmp = 0x30;
    if(Usr_Uart_Timestamp == 0)
    {
        Usr_Uart_Timestamp = 1000;
        UART0_Send(tmp);
        tmp++;
        if(tmp>0x40)
        {
            tmp = 0x30;
        }
    }
    #endif
    
    #if 1
    // echo function;
    
    if((Uart0_St.rx_sta==1))
    {
        UART0_Send(Uart0_St.rx_buff[Uart0_St.rx_index++]);
        
        if(Uart0_St.rx_index == USCI_RX_MAX)
        {
            Uart0_St.rx_index = 0;
        }
        if(Uart0_St.rx_index == Uart0_St.rx_len)
        {
            Uart0_St.rx_sta = 0;
        }
    }
    
    
    #endif
    
    
}



#endif

