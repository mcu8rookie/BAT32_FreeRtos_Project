#ifndef __USR_UART_H__
#define __USR_UART_H__


#define USCI_TX_MAX 128
#define USCI_RX_MAX 128

struct USCI_ST
{
    unsigned char state;
    
    unsigned char tx_sta;
    unsigned char tx_index;
    unsigned char tx_len;
    unsigned char tx_buff[USCI_TX_MAX];
    
    unsigned char rx_sta;
    unsigned char rx_index;
    unsigned char rx_len;
    unsigned char rx_buff[USCI_RX_MAX];
};

extern struct USCI_ST Uart0_St;
extern struct USCI_ST Uart1_St;
extern struct USCI_ST Uart2_St;

extern uint32_t Usr_Uart_Timestamp;

void Uart_St_Init(struct USCI_ST* arg);

void Uart_St_Init_s(void);

uint8_t Usr_Uart_Init(uint8_t UartNbr,uint32_t bautrate);

uint8_t Usr_Uart_Echo(uint8_t UartNbr);


void Usr_Uart_InitSetup(void);

void Usr_Uart_MainLoop(void);


#endif


