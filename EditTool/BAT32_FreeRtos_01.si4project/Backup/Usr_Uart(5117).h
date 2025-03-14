#ifndef __USR_UART_H__
#define __USR_UART_H__


#include"Usr_Config.h"

#include"Usr_Debug.h"

#include "Usr_Task.h"


#define DBG_UART0       1
#define DBG_UART1       2
#define DBG_UART2       3

#define DBG_PRINT_UART      DBG_UART0
//#define DBG_PRINT_UART      DBG_UART1
//#define DBG_PRINT_UART      DBG_UART2



/*

UART0_TXD ---> P12;
UART0_RXD ---> P11;

UART1_TXD ---> P02;
UART1_RXD ---> P03;

UART2_TXD ---> P13;
UART2_RXD ---> P14;

*/


#if((defined(DBG_PRINT_UART))\
        &&(DBG_PRINT_UART == DBG_UART0))

#define DebugUart_Send      UART0_Send
#define DebugUart_Receive   UART0_Receive

#endif

#if((defined(DBG_PRINT_UART))\
        &&(DBG_PRINT_UART == DBG_UART1))
        
//#define DebugUart_Send      Usr_UART1_Send
//#define DebugUart_Receive   Usr_UART1_Receive

#define DebugUart_Send      Usr_UART1_Send
#define DebugUart_Receive   Usr_UART1_Receive


#endif

#if((defined(DBG_PRINT_UART))\
        &&(DBG_PRINT_UART == DBG_UART2))

//#define DebugUart_Send      Usr_UART2_Send
//#define DebugUart_Receive   Usr_UART2_Receive

#define DebugUart_Send      Usr_UART2_Send
#define DebugUart_Receive   Usr_UART2_Receive


#endif

#if 0
MD_STATUS Usr_UART1_Send(uint8_t ch);

char Usr_UART1_Receive(void);


MD_STATUS Usr_UART2_Send(uint8_t ch);

char Usr_UART2_Receive(void);


// Uart0 shall configure as RS485; connect to UsrIOT;
// Direct pin is Pin10;

// Uart1 shall configure as RS485; connect to Sensor;
// Direct pin is Pin70;

void USCI_PinInit(void);

void RS485_UsrIot_Direct(unsigned char arg);

void RS485_Sensor_Direct(unsigned char arg);
#endif


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



#if(defined(DEF_TASK_UART_EN)&&(DEF_TASK_UART_EN==1))

extern const char *const Task_Uart_Name;
extern const configSTACK_DEPTH_TYPE Task_Uart1_StackDepth;
extern uint32_t Task_Uart_Arg;
extern uint32_t *Task_Uart_ArgPtr;
extern UBaseType_t Task_Uart_Priority;
extern TaskHandle_t Task_Uart_Handle;

void Usr_Task_Uart(void *TaskParameter);

void Task_Uart_InitSetup(void);

void Task_Uart_MainLoop(void);



#endif


#endif


