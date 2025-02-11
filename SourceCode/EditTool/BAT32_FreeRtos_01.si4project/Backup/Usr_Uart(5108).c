#ifndef __USR_UART_C__
#define __USR_UART_C__

#include<stdint.h>

#include"Userdefine.h"
#include"sci.h"
#include"BAT32A237.h"
#include"Usr_Uart.h"

uint32_t Usr_Uart_Timestamp;


struct USCI_ST Uart0_St;
struct USCI_ST Uart1_St;
struct USCI_ST Uart2_St;

void Uart_St_Init(struct USCI_ST* arg)
{   
    arg->state = 0;
    arg->tx_sta = 0;
    arg->tx_index = 0;
    arg->tx_len = 0;
    //arg->buff[USCI_TX_MAX];
    
    arg->rx_sta = 0;
    arg->rx_index = 0;
    arg->rx_len = 0;
    //arg->buff[USCI_RX_MAX];
}

void Uart_St_Init_s(void)
{   
    Uart_St_Init(&Uart0_St);
    Uart_St_Init(&Uart1_St);
    Uart_St_Init(&Uart2_St);
}

uint8_t Usr_Uart_Init(uint8_t UartNbr,uint32_t bautrate)
{
    MD_STATUS status;
    
    switch(UartNbr)
    {
        case 0:
        {
            #if 1
            // Setup Uart0;
            status = UART0_Init(SystemCoreClock, 115200);
            
            if(status == MD_ERROR)
            {
                while(1); // The baud rate cannot get at the current system clock frequency.
            }
            
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
        }
        break;
        case 1:
        {
            
            #if 1
            // Setup Uart1;
            status = UART1_Init(SystemCoreClock, 115200);
            if(status == MD_ERROR)
            {
                while(1); // The baud rate cannot get at the current system clock frequency.    
            }
            
            {   
                //SCI0->SO0 |= _0004_SCI_CH2_DATA_OUTPUT_1;
                //SCI0->SOE0 |= _0004_SCI_CH2_OUTPUT_ENABLE;
                //SCI0->SS0 |= _0008_SCI_CH3_START_TRG_ON | _0004_SCI_CH2_START_TRG_ON;
                
                //SCI0->SO0 |= _0001_SCI_CH0_DATA_OUTPUT_1;
                //SCI0->SOL0 &= (uint16_t)~_0001_SCI_CHANNEL0_INVERTED;
                //SCI0->SOE0 |= _0001_SCI_CH0_OUTPUT_ENABLE;
                
                INTC_ClearPendingIRQ(ST1_IRQn); /* clear INTST1 interrupt flag */
                INTC_ClearPendingIRQ(SR1_IRQn); /* clear INTSR1 interrupt flag */
                
                NVIC_ClearPendingIRQ(ST1_IRQn); /* clear INTST1 interrupt flag */
                NVIC_ClearPendingIRQ(SR1_IRQn); /* clear INTSR1 interrupt flag */
                
                INTC_EnableIRQ(ST1_IRQn);       /* enable INTST1 interrupt */
                INTC_EnableIRQ(SR1_IRQn);       /* enable INTSR1 interrupt */
                
                NVIC_EnableIRQ(ST1_IRQn); 
                NVIC_EnableIRQ(SR1_IRQn); 
            }
            #endif
        }
        break;
        case 2:
        {
            // Setup Uart2;
            status = UART2_Init(SystemCoreClock, 115200);
            if(status == MD_ERROR)
            {
                while(1); // The baud rate cannot get at the current system clock frequency.    
            }
            
            {   
                //SCI0->SO0 |= _0004_SCI_CH2_DATA_OUTPUT_1;
                //SCI0->SOE0 |= _0004_SCI_CH2_OUTPUT_ENABLE;
                //SCI0->SS0 |= _0008_SCI_CH3_START_TRG_ON | _0004_SCI_CH2_START_TRG_ON;
                
                //SCI0->SO0 |= _0001_SCI_CH0_DATA_OUTPUT_1;
                //SCI0->SOL0 &= (uint16_t)~_0001_SCI_CHANNEL0_INVERTED;
                //SCI0->SOE0 |= _0001_SCI_CH0_OUTPUT_ENABLE;
                
                INTC_ClearPendingIRQ(ST2_IRQn); /* clear INTST1 interrupt flag */
                INTC_ClearPendingIRQ(SR2_IRQn); /* clear INTSR1 interrupt flag */
                
                NVIC_ClearPendingIRQ(ST2_IRQn); /* clear INTST1 interrupt flag */
                NVIC_ClearPendingIRQ(SR2_IRQn); /* clear INTSR1 interrupt flag */
                
                INTC_EnableIRQ(ST2_IRQn);       /* enable INTST1 interrupt */
                INTC_EnableIRQ(SR2_IRQn);       /* enable INTSR1 interrupt */
                
                NVIC_EnableIRQ(ST2_IRQn); 
                NVIC_EnableIRQ(SR2_IRQn); 
            }
        }
        break;
        default:
        {
            
        }
        break;
    }
}

uint8_t Usr_Uart_Echo(uint8_t UartNbr)
{
    switch(UartNbr)
    {
        case 0:
        {
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
        }
        break;
        case 1:
        {
            // echo function;
            
            if((Uart1_St.rx_sta==1))
            {
                UART1_Send(Uart1_St.rx_buff+(Uart1_St.rx_index++),1);
                
                if(Uart1_St.rx_index == USCI_RX_MAX)
                {
                    Uart1_St.rx_index = 0;
                }
                if(Uart1_St.rx_index == Uart1_St.rx_len)
                {
                    Uart1_St.rx_sta = 0;
                }
            }
        }
        break;
        case 2:
        {
            // echo function;
            
            if((Uart2_St.rx_sta==1))
            {
                UART2_Send(Uart2_St.rx_buff+(Uart2_St.rx_index++),1);
                
                if(Uart2_St.rx_index == USCI_RX_MAX)
                {
                    Uart2_St.rx_index = 0;
                }
                if(Uart2_St.rx_index == Uart2_St.rx_len)
                {
                    Uart2_St.rx_sta = 0;
                }
            }
        }
        break;
        default:
        {
            
        }
        break;
    }
}




void Usr_Uart_InitSetup(void)
{
    MD_STATUS status;
    
    #if 1
    // Setup Uart0;
    status = UART0_Init(SystemCoreClock, 115200);
    
    if(status == MD_ERROR)
    {
        while(1); // The baud rate cannot get at the current system clock frequency.
    }
    
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
    
    #if 1
    // Setup Uart1;
    status = UART1_Init(SystemCoreClock, 115200);
    if(status == MD_ERROR)
    {
        while(1); // The baud rate cannot get at the current system clock frequency.    
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


