/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    dma.h
* @brief   This file implements device driver for DTC module.
* @version 1.0.0  
* @date    2022/2/25
***********************************************************************************************************************/
#ifndef DMA_H
#define DMA_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Bit Position of DMACR
*/
#define SZ_Pos       6
#define RPTINT_Pos   5
#define CHNE_Pos     4
#define DAMOD_Pos    3
#define SAMOD_Pos    2
#define RPTSEL_Pos   1
#define MODE_Pos     0

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum {
   DMA_VECTOR_INTP0 	=  1U,  /* 外部中断INTP0 */
   DMA_VECTOR_INTP1 	=  2U,  /* 外部中断INTP1 */
   DMA_VECTOR_INTP2 	=  3U,  /* 外部中断INTP2 */
   DMA_VECTOR_INTP3 	=  4U,  /* 外部中断INTP3 */
   DMA_VECTOR_INTP4 	=  5U,  /* 外部中断INTP4 */
   DMA_VECTOR_INTP5 	=  6U,  /* 外部中断INTP5 */
   DMA_VECTOR_INTP6 	=  7U,  /* 外部中断INTP6 */
   DMA_VECTOR_INTP7 	=  8U,  /* 外部中断INTP7 */
   DMA_VECTOR_KEY    	=  9U,  /* 按键中断 */
   DMA_VECTOR_ADC   	= 10U,  /* A/D 转换结束 */
   DMA_VECTOR_SR0       = 11U,  /* UART0接收传送结束/SPI01传送结束或者缓冲器空/IIC01传送结束 */
   DMA_VECTOR_SPI01     = 11U,  /* UART0接收传送结束/SPI01传送结束或者缓冲器空/IIC01传送结束 */
   DMA_VECTOR_IIC01     = 11U,  /* UART0接收传送结束/SPI01传送结束或者缓冲器空/IIC01传送结束 */
   DMA_VECTOR_ST0       = 12U,  /* UART0发送传送结束/SPI00传送结束或者缓冲器空/IIC00传送结束 */
   DMA_VECTOR_SPI00     = 12U,  /* UART0发送传送结束/SPI00传送结束或者缓冲器空/IIC00传送结束 */
   DMA_VECTOR_IIC00     = 12U,  /* UART0发送传送结束/SPI00传送结束或者缓冲器空/IIC00传送结束 */
   DMA_VECTOR_SR1       = 13U,  /* UART1接收传送结束/SPI11传送结束或者缓冲器空/IIC11传送结束 */
   DMA_VECTOR_SPI11     = 13U,  /* UART1接收传送结束/SPI11传送结束或者缓冲器空/IIC11传送结束 */
   DMA_VECTOR_IIC11     = 13U,  /* UART1接收传送结束/SPI11传送结束或者缓冲器空/IIC11传送结束 */
   DMA_VECTOR_ST1       = 14U,  /* UART1发送传送结束/SPI10传送结束或者缓冲器空/IIC10传送结束 */
   DMA_VECTOR_SPI10     = 14U,  /* UART1发送传送结束/SPI10传送结束或者缓冲器空/IIC10传送结束 */
   DMA_VECTOR_IIC10     = 14U,  /* UART1发送传送结束/SPI10传送结束或者缓冲器空/IIC10传送结束 */
   DMA_VECTOR_SR2       = 15U,  /* UART2接收传送结束/SPI21传送结束或者缓冲器空/IIC21传送结束 */
   DMA_VECTOR_SPI21     = 15U,  /* UART2接收传送结束/SPI21传送结束或者缓冲器空/IIC21传送结束 */
   DMA_VECTOR_IIC21     = 15U,  /* UART2接收传送结束/SPI21传送结束或者缓冲器空/IIC21传送结束 */
   DMA_VECTOR_ST2       = 16U,  /* UART2发送传送结束/SPI20传送结束或者缓冲器空/IIC20传送结束 */
   DMA_VECTOR_SPI20     = 16U,  /* UART2发送传送结束/SPI20传送结束或者缓冲器空/IIC20传送结束 */
   DMA_VECTOR_IIC20     = 16U,  /* UART2发送传送结束/SPI20传送结束或者缓冲器空/IIC20传送结束 */
   DMA_VECTOR_IICA      = 17U,  /* IICA通信结束 */
   DMA_VECTOR_TM4_CH0   = 19U,  /* 定时器阵列单元0的通道0的计数结束或者捕获结束 */
   DMA_VECTOR_TM4_CH1   = 20U,  /* 定时器阵列单元0的通道1的计数结束或者捕获结束 */ 
   DMA_VECTOR_TM4_CH2   = 21U,  /* 定时器阵列单元0的通道2的计数结束或者捕获结束 */
   DMA_VECTOR_TM4_CH3   = 22U,  /* 定时器阵列单元0的通道3的计数结束或者捕获结束 */
   DMA_VECTOR_IT        = 23U,  /* 间隔定时器中断 */
   DMA_VECTOR_FLASH     = 24U,  /* Flash擦除/写入结束 */
   DMA_VECTOR_TMC_OVF   = 26U,  /* 定时器C的上溢 */
   DMA_VECTOR_TMM_IMFA0 = 27U,  /* 定时器M的比较匹配A0 */
   DMA_VECTOR_TMM_IMFB0 = 28U,  /* 定时器M的比较匹配B0 */
   DMA_VECTOR_TMM_IMFC0 = 29U,  /* 定时器M的比较匹配C0 */
   DMA_VECTOR_TMM_IMFD0 = 30U,  /* 定时器M的比较匹配D0 */
   DMA_VECTOR_TMM_IMFA1 = 31U,  /* 定时器M的比较匹配A1 */
   DMA_VECTOR_TMM_IMFB1 = 32U,  /* 定时器M的比较匹配B1 */
   DMA_VECTOR_TMM_IMFC1 = 33U,  /* 定时器M的比较匹配C1 */
   DMA_VECTOR_TMM_IMFD1 = 34U,  /* 定时器M的比较匹配D1 */
   DMA_VECTOR_TMB_IMFA  = 35U,  /* 定时器B的比较匹配A */
   DMA_VECTOR_TMB_IMFB  = 36U,  /* 定时器B的比较匹配B */
   DMA_VECTOR_TMA_UNF   = 37U,  /* 定时器A的下溢 */
   DMA_VECTOR_CMP0      = 38U,  /* 比较器0 */
   DMA_VECTOR_CMP1      = 39U   /* 比较器1 */

} dma_vector_t;

typedef enum {
	DMA_SIZE_BYTE, 				/*  8bits transfer */ 
	DMA_SIZE_HALF,  			/* 16bits transfer */
	DMA_SIZE_WORD   			/* 32bits transfer */
} dma_size_t;

typedef enum {
	DMA_MODE_NORMAL, 			/* Normal mode */ 
	DMA_MODE_REPEAT   			/* Repeat mode */
} dma_mode_t;

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
#if 1
void DMA_Start(dma_vector_t vect_num, uint8_t ctrl_data_num, dma_mode_t mode, dma_size_t size, uint16_t count, void *src_adr, void *dst_adr);
#else
void DMA_Start(dma_vector_t vect_num, uint8_t ctrl_data_num, DMAVEC_CTRL_Type ctrl_data);
#endif
void DMA_Enable(dma_vector_t vect_num);
void DMA_Stop(dma_vector_t vect_num);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
