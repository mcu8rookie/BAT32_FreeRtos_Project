#ifndef __USR_UART_C__
#define __USR_UART_C__

#include<stdint.h>

#include"Userdefine.h"
#include"sci.h"
#include"BAT32A237.h"
#include"Usr_Uart.h"

#include"gpio.h"
#include "Usr_GPIO.h"



static uint8_t uart1_tx_cbuf[1];
static uint8_t uart1_rx_cbuf[1];

static uint8_t uart2_tx_cbuf[1];
static uint8_t uart2_rx_cbuf[1];


#if 0
MD_STATUS Usr_UART1_Send(uint8_t ch)
{
    uart1_tx_cbuf[0] = ch;
    
    return UART1_Send(uart1_tx_cbuf, 1);
}
#else
MD_STATUS Usr_UART1_Send(uint8_t ch)
{
    SCI0->TXD1 = ch;
    while (SCI0->SSR02 & (_0040_SCI_UNDER_EXECUTE | _0020_SCI_VALID_STORED))
    {
        ;
    }
    return 0;
}
#endif


char Usr_UART1_Receive(void)
{   
    UART1_Receive(uart1_rx_cbuf, 1);

    return uart1_rx_cbuf[0];
}

#if 0
MD_STATUS Usr_UART2_Send(uint8_t ch)
{
    MD_STATUS rtn;
    
    uart2_tx_cbuf[0] = ch;
    
    rtn = UART2_Send(uart2_tx_cbuf, 1);

    if(rtn == MD_OK)
    {
        return 0;
    }
    Usr_DelayMs(5);
    
    return 1;
}
#else
MD_STATUS Usr_UART2_Send(uint8_t ch)
{
    SCI1->TXD2 = ch;
    //while (SCI1->SSR10 & (_0040_SCI_UNDER_EXECUTE | _0020_SCI_VALID_STORED))
    while (SCI1->SSR10 & (_0040_SCI_UNDER_EXECUTE | _0020_SCI_VALID_STORED))
    {
        ;
    }
    return 0;
}
#endif


char Usr_UART2_Receive(void)
{   
    UART2_Receive(uart2_rx_cbuf, 1);

    return uart2_rx_cbuf[0];
}



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
		
		return 0;
}

uint8_t Usr_Uart_Echo(uint8_t UartNbr)
{
    switch(UartNbr)
    {
        case 0:
        {
            // echo function;
            
            #if 0
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
            
            
            #if 1
            if(Uart0_St.rx_sta==1)
            {
                
                for(;Uart0_St.rx_sta == 1;)
                {
                    Uart0_St.tx_buff[Uart0_St.tx_len++] = Uart0_St.rx_buff[Uart0_St.rx_index++];
                    
                    if(Uart0_St.tx_len == USCI_TX_MAX)
                    {
                        Uart0_St.tx_len = 0;
                    }
                
                    if(Uart0_St.rx_index == USCI_RX_MAX)
                    {
                        Uart0_St.rx_index = 0;
                    }
                    
                    if(Uart0_St.rx_index == Uart0_St.rx_len)
                    {
                        Uart0_St.rx_sta = 0;
                    }
                    
                    Uart0_St.tx_sta = 1;
                }
            }
            
            if((Uart0_St.tx_sta ==1 ))
            {
                //UART0_Send(Uart0_St.tx_buff[Uart0_St.tx_index++]);
                
                SCI0->TXD0 = Uart0_St.tx_buff[Uart0_St.tx_index++];
                
                if(Uart0_St.tx_index == USCI_TX_MAX)
                {
                    Uart0_St.tx_index = 0;
                }
                
                if(Uart0_St.tx_index == Uart0_St.tx_len)
                {
                    Uart0_St.tx_sta = 0;
                }
                
                while (SCI0->SSR00 & (_0040_SCI_UNDER_EXECUTE | _0020_SCI_VALID_STORED))
                {
                    ;
                }
            }
            #endif
        }
        break;
        case 1:
        {
            // echo function;
            #if 0
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
            #endif
            
            
            #if 1
            if(Uart1_St.rx_sta==1)
            {
                
                for(;Uart1_St.rx_sta == 1;)
                {
                    Uart1_St.tx_buff[Uart1_St.tx_len++] = Uart1_St.rx_buff[Uart1_St.rx_index++];
                    
                    if(Uart1_St.tx_len == USCI_TX_MAX)
                    {
                        Uart1_St.tx_len = 0;
                    }
                
                    if(Uart1_St.rx_index == USCI_RX_MAX)
                    {
                        Uart1_St.rx_index = 0;
                    }
                    
                    if(Uart1_St.rx_index == Uart1_St.rx_len)
                    {
                        Uart1_St.rx_sta = 0;
                    }
                    
                    Uart1_St.tx_sta = 1;
                }
            }
            
            if(Uart1_St.tx_sta == 1)
            {
                //UART1_Send(Uart1_St.tx_buff+(Uart1_St.tx_index++),1);
                
                SCI0->TXD1 = Uart1_St.tx_buff[Uart1_St.tx_index++];
                
                if(Uart1_St.tx_index == USCI_TX_MAX)
                {
                    Uart1_St.tx_index = 0;
                }
                
                if(Uart1_St.tx_index == Uart1_St.tx_len)
                {
                    Uart1_St.tx_sta = 0;
                }
                
                while (SCI0->SSR02 & (_0040_SCI_UNDER_EXECUTE | _0020_SCI_VALID_STORED))
                {
                    ;
                }
            }
            #endif
        }
        break;
        case 2:
        {
            // echo function;
            #if 0
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
            #endif
            
            
            #if 1
            if(Uart2_St.rx_sta==1)
            {
                
                for(;Uart2_St.rx_sta == 1;)
                {
                    Uart2_St.tx_buff[Uart2_St.tx_len++] = Uart2_St.rx_buff[Uart2_St.rx_index++];
                    
                    if(Uart2_St.tx_len == USCI_TX_MAX)
                    {
                        Uart2_St.tx_len = 0;
                    }
                
                    if(Uart2_St.rx_index == USCI_RX_MAX)
                    {
                        Uart2_St.rx_index = 0;
                    }
                    
                    if(Uart2_St.rx_index == Uart2_St.rx_len)
                    {
                        Uart2_St.rx_sta = 0;
                    }
                    
                    Uart2_St.tx_sta = 1;
                }
            }
            
            if((Uart2_St.tx_sta ==1 ))
            {
                //UART2_Send(Uart2_St.tx_buff+(Uart2_St.tx_index++),1);
                
                SCI1->TXD2 = Uart2_St.tx_buff[Uart2_St.tx_index++];
                
                if(Uart2_St.tx_index == USCI_TX_MAX)
                {
                    Uart2_St.tx_index = 0;
                }
                
                if(Uart2_St.tx_index == Uart2_St.tx_len)
                {
                    Uart2_St.tx_sta = 0;
                }
                
                while (SCI1->SSR10 & (_0040_SCI_UNDER_EXECUTE | _0020_SCI_VALID_STORED))
                {
                    ;
                }
            }
            #endif
        }
        break;
        default:
        {
            
        }
        break;
    }
		
		return 0;
}




void Usr_Uart_InitSetup(void)
{
    Usr_Uart_Init(0,115200);
    //Usr_Uart_Init(1,115200);
    //Usr_Uart_Init(2,115200);
    
    Usr_Uart_Timestamp = 0;
    
}

void Usr_Uart_MainLoop(void)
{   
    
    Usr_Uart_Echo(0);
    //Usr_Uart_Echo(1);
    //Usr_Uart_Echo(2);
    
}



#endif


