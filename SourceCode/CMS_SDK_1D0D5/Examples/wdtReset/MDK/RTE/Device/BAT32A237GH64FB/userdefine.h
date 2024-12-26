/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    userdefine.h
* @brief   This file includes user definition.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/
#ifndef _USER_DEF_H
#define _USER_DEF_H

/***********************************************************************************************************************
User definitions
***********************************************************************************************************************/
#ifndef __TYPEDEF__

typedef unsigned short 	MD_STATUS;
/* Status list definition */
#define MD_STATUSBASE        (0x00U)
#define MD_OK                (MD_STATUSBASE + 0x00U) /* register setting OK */
#define MD_SPT               (MD_STATUSBASE + 0x01U) /* IIC stop */
#define MD_NACK              (MD_STATUSBASE + 0x02U) /* IIC no ACK */
#define MD_BUSY1             (MD_STATUSBASE + 0x03U) /* busy 1 */
#define MD_BUSY2             (MD_STATUSBASE + 0x04U) /* busy 2 */
#define MD_OVERRUN           (MD_STATUSBASE + 0x05U) /* IIC OVERRUN occur */

/* Error list definition */
#define MD_ERRORBASE         (0x80U)
#define MD_ERROR             (MD_ERRORBASE + 0x00U)  /* error */
#define MD_ARGERROR          (MD_ERRORBASE + 0x01U)  /* error agrument input error */
#define MD_ERROR1            (MD_ERRORBASE + 0x02U)  /* error 1 */
#define MD_ERROR2            (MD_ERRORBASE + 0x03U)  /* error 2 */
#define MD_ERROR3            (MD_ERRORBASE + 0x04U)  /* error 3 */
#define MD_ERROR4            (MD_ERRORBASE + 0x05U)  /* error 4 */
#define MD_ERROR5            (MD_ERRORBASE + 0x06U)  /* error 5 */
#endif

#define TRMW   *((volatile uint8_t *)(0x40021C08))
#define TRMR   *((volatile uint8_t *)(0x40021C0C))
#define TRMT   *((volatile uint8_t *)(0x40021C10))

/***********************************************************************************************************************
Macro definitions for Clock
***********************************************************************************************************************/
#define CPU_CLOCK_FREQ 12000000UL//12MHz clock frequency


/***********************************************************************************************************************
Macro definitions for CAN
***********************************************************************************************************************/
#define CAN0_USE

#define CAN_REC_MASK1 0x1fffffffU
#define CAN_REC_MASK2 0x1fffffffU
#define CAN_REC_MASK3 0x1fffffffU
#define CAN_REC_MASK4 0x1fffffffU

/***********************************************************************************************************************
Macro definitions of SCI usage:
Each channel of SCI has three functions: UART, SPI, and IIC. You can only choose one function to use.
***********************************************************************************************************************/
/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
#define USE_SCI_UART0_TX      /*! Using CH0 of SCI0 as UART Transmitter */
//#define USE_SCI_SPI00         /*! Using CH0 of SCI0 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC00         /*! Using CH0 of SCI0 as IIC Transmitter or Receiver */

/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
#define USE_SCI_UART0_RX      /*! Using CH1 of SCI0 as UART Receiver */
//#define USE_SCI_SPI01         /*! Using CH1 of SCI0 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC01         /*! Using CH1 of SCI0 as IIC Transmitter or Receiver */

/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
//#define USE_SCI_UART1_TX      /*! Using CH2 of SCI0 as UART Transmitter */
#define USE_SCI_SPI10         /*! Using CH2 of SCI0 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC10         /*! Using CH2 of SCI0 as IIC Transmitter or Receiver */

/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
//#define USE_SCI_UART1_RX      /*! Using CH3 of SCI0 as UART Receiver */
#define USE_SCI_SPI11         /*! Using CH3 of SCI0 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC11         /*! Using CH3 of SCI0 as IIC Transmitter or Receiver */

/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
//#define USE_SCI_UART2_TX      /*! Using CH0 of SCI1 as UART Transmitter */
//#define USE_SCI_SPI20         /*! Using CH0 of SCI1 as SPI Transmitter or Receiver */
#define USE_SCI_IIC20         /*! Using CH0 of SCI1 as IIC Transmitter or Receiver */

/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
//#define USE_SCI_UART2_RX      /*! Using CH1 of SCI1 as UART Receiver */
//#define USE_SCI_SPI21         /*! Using CH1 of SCI1 as SPI Transmitter or Receiver */
#define USE_SCI_IIC21         /*! Using CH1 of SCI1 as IIC Transmitter or Receiver */

/* ToDo: You can define the following MACRO and USE_SCI_UART2_TX or USE_SCI_UART2_RX MACROs to use Infra-Red transmitter or receiver */
//#define USE_IRDA              /*! Enable Infra-Red transmission with UART2 */

/***********************************************************************************************************************
DMA Control Data Set definitions
***********************************************************************************************************************/
#define SPI00_WITH_DMA
#define CTRL_DATA_SPI00 0

//#define SPI01_WITH_DMA
//#define CTRL_DATA_SPI01 2

#define SPI10_WITH_DMA
#define CTRL_DATA_SPI10 4

#define SPI11_WITH_DMA
#define CTRL_DATA_SPI11 6

//#define SPI20_WITH_DMA
//#define CTRL_DATA_SPI20 8

//#define SPI21_WITH_DMA
//#define CTRL_DATA_SPI21 10

#define ADC_WITH_DMA
#define CTRL_DATA_ADC   12

#define DAC_WITH_DMA
#define CTRL_DATA_DAC   14

/** @addtogroup Peripherals_Port_Setting_Definations
  * @{
  */

/* ================================================================================================================== */
/* ================                                       TM40                                       ================ */
/* ================================================================================================================== */
/**
  * @brief TM40 TI00~3 and TO00~3 Port Setting (Alternative to fixed ports)
  */

#define TI00_PORT_SETTING() do{ \
        PORT->PM0  |=  (1 << 0);    /* P00 is used as TI00 input */ \
        PORT->PMC0 &= ~(1 << 0);    /* P00 is digital function */ \
}while(0)

#define TI01_PORT_SETTING() do{ \
        PORT->PM1  |=  (1 << 6);    /* P16 is used as TI01 input */ \
}while(0)

#define TI02_PORT_SETTING() do{ \
        PORT->PM1  |=  (1 << 7);    /* P17 is used as TI02 input */ \
}while(0)

#define TI03_PORT_SETTING() do{ \
        PORT->PM3  |=  (1 << 1);    /* P31 is used as TI03 input */ \
}while(0)

#define TO00_PORT_SETTING() do{ \
        PORT->P0   &= ~(1 << 1);    /* P01 output low level */ \
        PORT->PM0  &= ~(1 << 1);    /* P01 is used as TO00 output */ \
        PORT->PMC0 &= ~(1 << 1);    /* P01 is digital function */ \
}while(0)

#define TO01_PORT_SETTING() do{ \
        PORT->P1   &= ~(1 << 6);    /* P16 output low level */ \
        PORT->PM1  &= ~(1 << 6);    /* P16 is used as TO01 output */ \
}while(0)

#define TO02_PORT_SETTING() do{ \
        PORT->P1   &= ~(1 << 7);    /* P17 output low level */ \
        PORT->PM1  &= ~(1 << 7);    /* P17 is used as TO02 output */ \
}while(0)

#define TO03_PORT_SETTING() do{ \
        PORT->P3   &= ~(1 << 1);    /* P31 output low level */ \
        PORT->PM3  &= ~(1 << 1);    /* P31 is used as TO03 output */ \
}while(0)
/* ================================================================================================================== */
/* ================                                      TMA                                         ================ */
/* ================================================================================================================== */

/**
  * @brief TAIO Port Setting (Alternative to 4 group ports)
  */

/* ToDo: You can allocate the TAIO to P01, P31, P41, or P06 with PIOR11 and PIOR10 register */
#define TAIO_PORT_SETTING() do{ \
        PORT->PIOR1 |=  (0 << 0);    /* allocate TAIO to P01 */ \
        PORT->P0    &= ~(1 << 1);    /* P01 output low level */ \
        PORT->PM0   &= ~(1 << 1);    /* P01 is used as TAIO output */ \
        PORT->POM0  &= ~(1 << 1);    /* P01 is push-pull output mode */ \
}while(0)

/* ToDo: You can allocate the TAIO to P01, P31, P41, or P06 with PIOR11 and PIOR10 register */
#define TAI_PORT_SETTING() do{ \
        PORT->PIOR1 |=  (0 << 0);    /* allocate TAIO to P01 */ \
        PORT->PM0   |=  (1 << 1);    /* P01 is used as TAIO input */ \
}while(0)

/* ToDo: You can allocate the TAO to P30, P50, or P00 with PIOR13 and PIOR12 register */
#define TAO_PORT_SETTING() do{ \
        PORT->PIOR1 |=  (0 << 2);    /* allocate TAO to P30 */ \
        PORT->P3    &= ~(1 << 0);    /* P30 output low level */ \
        PORT->PM3   &= ~(1 << 0);    /* P30 is used as TAO output */ \
        PORT->POM3  &= ~(1 << 0);    /* P30 is push-pull output mode */ \
}while(0)

/* ================================================================================================================== */
/* ================                                      TMB                                         ================ */
/* ================================================================================================================== */

/**
  * @brief TMB Port Setting（Alternative to fixed port)
  */

#define TBCLK0_PORT_SETTING() do{ \
        PORT->PM0   |=  (1 << 0);    /* P00 is used as TBCLK0 input */ \
}while(0)

#define TBCLK1_PORT_SETTING() do{ \
        PORT->PM0   |=  (1 << 1);    /* P01 is used as TBCLK1 input */ \
}while(0)

#define TBI0_PORT_SETTING() do{ \
        PORT->PM5   |=  (1 << 0);    /* P50 is used as TBIO0 input */ \
}while(0)

#define TBI1_PORT_SETTING() do{ \
        PORT->PM5   |=  (1 << 1);    /* P51 is used as TBIO1 input */ \
}while(0)

#define TBO0_PORT_SETTING() do{ \
        PORT->P5    &= ~(1 << 0);    /* P50 output low level */ \
        PORT->PM5   &= ~(1 << 0);    /* P50 is used as TBIO0 output */ \
        PORT->POM5  &= ~(1 << 0);    /* P50 is push-pull output mode */ \
}while(0)

#define TBO1_PORT_SETTING() do{ \
        PORT->P5    &= ~(1 << 1);    /* P51 output low level */ \
        PORT->PM5   &= ~(1 << 1);    /* P51 is used as TBIO1 output */ \
        PORT->POM5  &= ~(1 << 1);    /* P51 is push-pull output mode */ \
}while(0)

/* ================================================================================================================== */
/* ================                                      TMM                                         ================ */
/* ================================================================================================================== */

/**
  * @brief TMM Port Setting（Alternative to 3 group ports)
  */

#define TMCLK_PORT_SETTING() do{ \
        PORT->PM1   |=  (1 << 7);    /* P17 is used as TMCLK input */ \
}while(0)

#define TMIA0_PORT_SETTING() do{ \
        PORT->PM1   |=  (1 << 7);    /* P17 is used as TMIOA0 input */ \
}while(0)

/* ToDo: You can allocate the TMIOB0 to P14, P12, or P15 with PIOR37 and PIOR36 register */
#define TMIB0_PORT_SETTING() do{ \
        PORT->PM1   |=  (1 << 4);    /* P14 is used as TMIOB0 input */ \
}while(0)

#define TMIC0_PORT_SETTING() do{ \
        PORT->PM1   |=  (1 << 6);    /* P16 is used as TMIOC0 input */ \
}while(0)

/* ToDo: You can allocate the TMIOD0 to P15, P15, or P14 with PIOR37 and PIOR36 register */
#define TMID0_PORT_SETTING() do{ \
        PORT->PM1   |=  (1 << 5);    /* P15 is used as TMIOD0 input */ \
}while(0)

/* ToDo: You can allocate the TMIOA1 to P12, P11, or P13 with PIOR37 and PIOR36 register */
#define TMIA1_PORT_SETTING() do{ \
        PORT->PM1   |=  (1 << 2);    /* P12 is used as TMIOA1 input */ \
}while(0)

/* ToDo: You can allocate the TMIOB1 to P10, P10, or P12 with PIOR37 and PIOR36 register */
#define TMIB1_PORT_SETTING() do{ \
        PORT->PM1   |=  (1 << 0);    /* P10 is used as TMIOB1 input */ \
}while(0)

/* ToDo: You can allocate the TMIOC1 to P13, P14, or P11 with PIOR37 and PIOR36 register */
#define TMIC1_PORT_SETTING() do{ \
        PORT->PM1   |=  (1 << 3);    /* P13 is used as TMIOC1 input */ \
}while(0)

/* ToDo: You can allocate the TMIOD1 to P11, P13, or P10 with PIOR37 and PIOR36 register */
#define TMID1_PORT_SETTING() do{ \
        PORT->PM1   |=  (1 << 1);    /* P11 is used as TMIOD1 input */ \
}while(0)

#define TMOA0_PORT_SETTING() do{ \
        PORT->P1    &= ~(1 << 7);    /* P17 output low level */ \
        PORT->PM1   &= ~(1 << 7);    /* P17 is used as TMIOA0 output */ \
        PORT->POM1  &= ~(1 << 7);    /* P17 is push-pull output mode */ \
}while(0)

#define TMOB0_PORT_SETTING() do{ \
        PORT->P1    &= ~(1 << 4);    /* P14 output low level */ \
        PORT->PM1   &= ~(1 << 4);    /* P14 is used as TMIOB0/U+ output */ \
        PORT->POM1  &= ~(1 << 4);    /* P14 is push-pull output mode */ \
}while(0)

#define TMOC0_PORT_SETTING() do{ \
        PORT->P1    &= ~(1 << 6);    /* P16 output low level */ \
        PORT->PM1   &= ~(1 << 6);    /* P16 is used as TMIOC0 output */ \
        PORT->POM1  &= ~(1 << 6);    /* P16 is push-pull output mode */ \
}while(0)

#define TMOD0_PORT_SETTING() do{ \
        PORT->P1    &= ~(1 << 5);    /* P15 output low level */ \
        PORT->PM1   &= ~(1 << 5);    /* P15 is used as TMIOD0/U- output */ \
        PORT->POM1  &= ~(1 << 5);    /* P15 is push-pull output mode */ \
}while(0)

#define TMOA1_PORT_SETTING() do{ \
        PORT->P1    &= ~(1 << 2);    /* P12 output low level */ \
        PORT->PM1   &= ~(1 << 2);    /* P12 is used as TMIOA1/V+ output */ \
        PORT->POM1  &= ~(1 << 2);    /* P12 is push-pull output mode */ \
}while(0)

#define TMOB1_PORT_SETTING() do{ \
        PORT->P1    &= ~(1 << 0);    /* P10 output low level */ \
        PORT->PM1   &= ~(1 << 0);    /* P10 is used as TMIOB1/W+ output */ \
        PORT->POM1  &= ~(1 << 0);    /* P10 is push-pull output mode */ \
        PORT->PMC1  &= ~(1 << 0);    /* P10 is digital function */ \
}while(0)

#define TMOC1_PORT_SETTING() do{ \
        PORT->P1    &= ~(1 << 3);    /* P13 output low level */ \
        PORT->PM1   &= ~(1 << 3);    /* P13 is used as TMIOC1/V- output */ \
        PORT->POM1  &= ~(1 << 3);    /* P13 is push-pull output mode */ \
}while(0)

#define TMOD1_PORT_SETTING() do{ \
        PORT->P1    &= ~(1 << 1);    /* P11 output low level */ \
        PORT->PM1   &= ~(1 << 1);    /* P11 is used as TMIOD1/W- output */ \
        PORT->POM1  &= ~(1 << 1);    /* P11 is push-pull output mode */ \
        PORT->PMC1  &= ~(1 << 1);    /* P11 is digital function */ \
}while(0)

#define MTR_PORT_UP_SET() do{ \
        PORT->P1    |=  (1 << 4);    /* TMIOB0/U+ output H level */ \
}while(0)

#define MTR_PORT_UP_CLR() do{ \
        PORT->P1    &= ~(1 << 4);    /* TMIOB0/U+ output L level */ \
}while(0)

#define MTR_PORT_VP_SET() do{ \
        PORT->P1    |=  (1 << 2);    /* TMIOA1/V+ output H level */ \
}while(0)

#define MTR_PORT_VP_CLR() do{ \
        PORT->P1    &= ~(1 << 2);    /* TMIOA1/V+ output L level */ \
}while(0)

#define MTR_PORT_WP_SET() do{ \
        PORT->P1    |=  (1 << 0);    /* TMIOB1/W+ output H level */ \
}while(0)

#define MTR_PORT_WP_CLR() do{ \
        PORT->P1    &= ~(1 << 0);    /* TMIOB1/W+ output L level */ \
}while(0)

#define MTR_PORT_UN_SET() do{ \
        PORT->P1    |=  (1 << 5);    /* TMIOD0/U- output H level */ \
}while(0)

#define MTR_PORT_UN_CLR() do{ \
        PORT->P1    &= ~(1 << 5);    /* TMIOD0/U- output L level */ \
}while(0)

#define MTR_PORT_VN_SET() do{ \
        PORT->P1    |=  (1 << 3);    /* TMIOC1/V- output H level */ \
}while(0)

#define MTR_PORT_VN_CLR() do{ \
        PORT->P1    &= ~(1 << 3);    /* TMIOC1/V- output L level */ \
}while(0)

#define MTR_PORT_WN_SET() do{ \
        PORT->P1    |=  (1 << 1);    /* TMIOD1/W- output H level */ \
}while(0)

#define MTR_PORT_WN_CLR() do{ \
        PORT->P1    &= ~(1 << 1);    /* TMIOD1/W- output L level */ \
}while(0)

/* ================================================================================================================== */
/* ================                                      RTC1HZ                                      ================ */
/* ================================================================================================================== */

/**
  * @brief RTC1HZ Port Setting（Alternative to fixed port)
  */

#define RTC1HZ_PORT_SETTING() do{ \
        PORT->P3   &= ~(1 << 0);    /* P30 output low level */ \
        PORT->PM3  &= ~(1 << 0);    /* P30 is used as RTC1HZ output */ \
        PORT->POM3 &= ~(1 << 0);    /* P30 is push-pull output mode */ \
}while(0)

/* ================================================================================================================== */
/* ================                                      CLKBUZ                                      ================ */
/* ================================================================================================================== */

/**
  * @brief CLKBUZ Port Setting（Alternative to 2 group ports)
  */

#if 1
/* ToDo: You can allocate the CLKBUZ0 to P140 or P31 with PIOR03 register */
#define CLKBUZ0_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 3);   /* allocate CLKBUZ0 to P140 */ \
        PORT->P14   &= ~(1 << 0);   /* P140 output low level */ \
        PORT->PM14  &= ~(1 << 0);   /* P140 is used as CLKBUZ0 output */ \
}while(0)
#else
/* ToDo: You can allocate the CLKBUZ0 to P140 or P31 with PIOR03 register */
#define CLKBUZ0_PORT_SETTING() do{ \
        PORT->PIOR0 |=  (1 << 3);   /* allocate CLKBUZ0 to P31 */ \
        PORT->P3    &= ~(1 << 1);   /* P31 output low level */ \
        PORT->PM3   &= ~(1 << 1);   /* P31 is used as CLKBUZ0 output */ \
}while(0)
#endif

#if 1
/* ToDo: You can allocate the CLKBUZ1 to P141 or P55 with PIOR04 register */
#define CLKBUZ1_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 4);   /* allocate CLKBUZ1 to P141 */ \
        PORT->P14   &= ~(1 << 1);   /* P141 output low level */ \
        PORT->PM14  &= ~(1 << 1);   /* P141 is used as CLKBUZ1 output */ \
}while(0)
#else
/* ToDo: You can allocate the CLKBUZ1 to P141 or P55 with PIOR04 register */
#define CLKBUZ1_PORT_SETTING() do{ \
        PORT->PIOR0 |=  (1 << 4);   /* allocate CLKBUZ1 to P55 */ \
        PORT->P5    &= ~(1 << 5);   /* P55 output low level */ \
        PORT->PM5   &= ~(1 << 5);   /* P55 is used as CLKBUZ1 output */ \
}while(0)
#endif

/* ================================================================================================================== */
/* ================                                        ADC                                       ================ */
/* ================================================================================================================== */

/**
  * @brief ADC Port Setting (Alternate to fixed ports)
  */

/* ToDo: Please comment out the following unused ANIx setting according to your application needs. */
#define ADC_PORT_SETTING() do{ \
        PORT->PMC2 |= (1 << 0);   /* Set ANI0(P20) pin: It is necessary for ADC_VREF_AVREFP_AVREFM, used as AVREFP */ \
        PORT->PMC2 |= (1 << 1);   /* Set ANI1(P21) pin: It is necessary for ADC_VREF_AVREFP_AVREFM, used as AVREFM */ \
        PORT->PMC2 |= (1 << 2);   /* Set ANI2(P22) pin */ \
        PORT->PMC2 |= (1 << 3);   /* Set ANI3(P23) pin */ \
        PORT->PMC2 |= (1 << 4);   /* Set ANI4(P24) pin */ \
        PORT->PMC2 |= (1 << 5);   /* Set ANI5(P25) pin */ \
        PORT->PMC2 |= (1 << 6);   /* Set ANI6(P26) pin */ \
        PORT->PMC2 |= (1 << 7);   /* Set ANI7(P27) pin */ \
        PORT->PMC1 |= (1 << 1);   /* Set ANI8(P11) pin */ \
        PORT->PMC1 |= (1 << 0);   /* Set ANI9(P10) pin */ \
        PORT->PMC0 |= (1 << 3);   /* Set ANI10(P03) pin */ \
        PORT->PMC0 |= (1 << 2);   /* Set ANI11(P02) pin */ \
        PORT->PMC14|= (1 << 7);   /* Set ANI12(P147) pin */ \
        PORT->PMC0 |= (1 << 4);   /* Set ANI13(P04) pin */ \
        PORT->PMC12|= (1 << 0);   /* Set ANI14(P120) pin */ \
        PORT->PMC14|= (1 << 6);   /* Set ANI15(P146) pin */ \
}while(0)

/* ================================================================================================================== */
/* ================                                        DAC                                       ================ */
/* ================================================================================================================== */

/**
  * @brief DAC Port Setting (Alternate to fixed ports)
  */

#define DAC0_PORT_SETTING() do{ \
        PORT->PMC2 |= (1 << 2);   /* Set ANO0(P22) pin */ \
}while(0)

#define DAC1_PORT_SETTING() do{ \
        PORT->PMC2 |= (1 << 3);   /* Set ANO1(P23) pin */ \
}while(0)

/* ================================================================================================================== */
/* ================                                        CMP                                       ================ */
/* ================================================================================================================== */

/**
  * @brief CMP Port Setting (Analog input alternate to fixed ports, digital output alternate to 2 group ports)
  */

#if 1
/* ToDo: You can allocate the VCOUT0 to P120 or P71 with PIOR20 register */
#define VCOUT0_PORT_SETTING() do { \
        PORT->PIOR3 |=  (1 << 1);  /* VCOUT0 output enable */ \
        PORT->PIOR2 &= ~(1 << 0);  /* allocate VCOUT0 to P120 */ \
        PORT->P12   &= ~(1 << 0);  /* P120 output low level */ \
        PORT->PM12  &= ~(1 << 0);  /* VCOUT0 output to P120 */ \
        PORT->PMC12 &= ~(1 << 0);  /* P120 is digital function */ \
}while(0)
#else
/* ToDo: You can allocate the VCOUT0 to P120 or P71 with PIOR20 register */
#define VCOUT0_PORT_SETTING() do { \
        PORT->PIOR3 |=  (1 << 1);  /* VCOUT0 output enable */ \
        PORT->PIOR2 |=  (1 << 0);  /* allocate VCOUT0 to P71 */ \
        PORT->P7    &= ~(1 << 1);  /* P71 output low level */ \
        PORT->PM7   &= ~(1 << 1);  /* VCOUT0 output to P71 */ \
}while(0)
#endif

#if 1
/* ToDo: You can allocate the VCOUT1 to P31 or P70 with PIOR21 register */
#define VCOUT1_PORT_SETTING() do { \
        PORT->PIOR3 |=  (1 << 2);  /* VCOUT1 output enable */ \
        PORT->PIOR2 &= ~(1 << 1);  /* allocate VCOUT1 to P31 */ \
        PORT->P3    &= ~(1 << 1);  /* P31 output low level */ \
        PORT->PM3   &= ~(1 << 1);  /* VCOUT1 output to P31 */ \
}while(0)
#else
#define VCOUT1_PORT_SETTING() do { \
        PORT->PIOR3 |=  (1 << 2);  /* VCOUT1 output enable */ \
        PORT->PIOR2 |=  (1 << 1);  /* allocate VCOUT1 to P70 */ \
        PORT->P7    &= ~(1 << 0);  /* P70 output low level */ \
        PORT->PM7   &= ~(1 << 0);  /* VCOUT1 output to P70 */ \
}while(0)
#endif

/* ToDo: Please comment out the VREF0 setting if don't used VREF0 as negative(-) side input of CMP */
#define CMP0_PORT_SETTING() do{ \
        PORT->PMC2  |= (1 << 2);  /* Set VCIN0(P22) pin */ \
        PORT->PMC14 |= (1 << 7);  /* Set VREF0(P147) pin */ \
        VCOUT0_PORT_SETTING();    /* ToDo: Please delete me if you don't output VCOUT0 signal to port */ \
}while(0)

/* ToDo: Please comment out the VCINxx setting if don't used it as positive(+) side input of CMP */
#define CMP1_PORT_SETTING() do{ \
        PORT->PMC0  |= (1 << 2);  /* Set VCIN10(P02) pin */ \
        PORT->PMC0  |= (1 << 3);  /* Set VCIN11(P03) pin */ \
        PORT->PMC2  |= (1 << 0);  /* Set VCIN12(P20) pin */ \
        PORT->PMC2  |= (1 << 1);  /* Set VCIN13(P21) pin */ \
        VCOUT1_PORT_SETTING();    /* ToDo: Please delete me if you don't output VCOUT1 signal to port */ \
}while(0)

/* ================================================================================================================== */
/* ================                                        PGA                                       ================ */
/* ================================================================================================================== */

/**
  * @brief PGA Port Setting (Alternate to fixed ports)
  */

#define PGA0O_PORT_SETTING() do { \
        PORT->PMC2 |= (1 << 0);   /* PGA0O output to P20 */ \
}while(0)

#define PGA1O_PORT_SETTING() do { \
        PORT->PMC2 |= (1 << 1);   /* PGA1O output to P21 */ \
}while(0)

#define PGA0IN_PORT_SETTING() do { \
        PORT->PMC2 |= (1 << 2);  /* PGA0IN input from P22 */ \
}while(0)

#define PGA0GND_PORT_SETTING() do { \
        PORT->PMC2 |= (1 << 3);  /* PGA0GND input from P23 */ \
}while(0)

#define PGA1IN_PORT_SETTING() do { \
        PORT->PMC2 |= (1 << 4);  /* PGA1IN input from P24 */ \
}while(0)

#define PGA1GND_PORT_SETTING() do { \
        PORT->PMC2 |= (1 << 5);  /* PGA1GND input from P25 */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       SCI0                                       ================ */
/* ================================================================================================================== */
/* ToDo: You can allocate the TXD0, RXD0, SCLK00, SDI00, SDO00, SCL00 and SDA00 to the following ports with PIOR register */
/* PIOR35  PIOR34  PIOR01 :  TXD0  RXD0  SCLK00  SDO00  SDI00  SCL00  SDA00
 *    0       0       0   :  P51   P50   P30     P51    P50    P30    P50   # default setting
 *    0       0       1   :  P17   P16   P55     P17    P16     -      -
 *    0       1       X   :  P40   P137   -       -      -      -      -
 *    1       X       X   :  P12   P11    -       -      -      -      -
*/
/**
  * @brief UART0 Port Setting（Alternative to 4 group ports) 
  */

#if 1
/* ToDo: You can allocate the TXD0 to P51, P17, P40 or P12 with PIOR35, PIOR43 and PIOR01 register */
#define TXD0_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 1);    /* allocate TXD0 to P51 */ \
        PORT->P5    |=  (1 << 1);    /* P51 output high level */ \
        PORT->PM5   &= ~(1 << 1);    /* P51 is used as TXD0 output */ \
        PORT->POM5  &= ~(1 << 1);    /* P51 is push-pull output mode */ \
}while(0)

/* ToDo: You can allocate the RXD0 to P50, P16, P137 or P11 with PIOR35, PIOR43 and PIOR01 register */
#define RXD0_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 1);    /* allocate RXD0 to P50 */ \
        PORT->PM5   |=  (1 << 0);    /* P50 is used as RXD0 input */ \
}while(0)

#else
/* ToDo: You can allocate the TXD0 to P51, P17, P40 or P12 with PIOR35, PIOR43 and PIOR01 register */
#define TXD0_PORT_SETTING() do{ \
        PORT->PIOR0 |=  (1 << 1);    /* allocate TXD0 to P17 */ \
        PORT->P1    |=  (1 << 7);    /* P17 output high level */ \
        PORT->PM1   &= ~(1 << 7);    /* P17 is used as TXD0 output */ \
        PORT->POM1  &= ~(1 << 7);    /* P17 is push-pull output mode */ \
}while(0)

/* ToDo: You can allocate the RXD0 to P50, P16, P137 or P11 with PIOR35, PIOR43 and PIOR01 register */
#define RXD0_PORT_SETTING() do{ \
        PORT->PIOR0 |=  (1 << 1);    /* allocate RXD0 to P16 */ \
        PORT->PM1   |=  (1 << 6);    /* P16 is used as RXD0 input */ \
}while(0)
#endif

/**
  * @brief SPI00 Port Setting（Alternative to 2 group ports)
  */

#define SS00_PORT_SETTING() do{ \
        PORT->PM6  |=  (1 << 2);     /* P62 is used as SS00 input */ \
}while(0)

#define SS00_PORT_SET() do{ \
        PORT->P6  |=  (1 << 2);      /* P62 output high level */ \
}while(0)

#define SS00_PORT_CLR() do{ \
        PORT->P6  &= ~(1 << 2);      /* P62 output low level */ \
}while(0)

/* ToDo: You can allocate the SCLK00 to P30 or P55 with PIOR01 register */
#define SCLKI00_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 1);     /* allocate SCLKI00 to P30 */ \
        PORT->PM3   |=  (1 << 0);     /* P30 is used as SCLK00 input */ \
}while(0)

/* ToDo: You can allocate the SCLK00 to P30 or P55 with PIOR01 register */
#define SCLKO00_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 1);    /* allocate SCLKI00 to P30 */ \
        PORT->P3    |=  (1 << 0);    /* P30 output high level */ \
        PORT->PM3   &= ~(1 << 0);    /* P30 is used as SCLK00 output */ \
        PORT->POM3  &= ~(1 << 0);    /* P30 is push-pull output mode */ \
}while(0)

/* ToDo: You can allocate the SDO00 to P51 or P17 with PIOR01 register */
#define SDO00_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 1);    /* allocate SDO00 to P51 */ \
        PORT->P5    |=  (1 << 1);    /* P51 output high level */ \
        PORT->PM5   &= ~(1 << 1);    /* P51 is used as SDO00 output */ \
        PORT->POM5  &= ~(1 << 1);    /* P51 is push-pull output mode */ \
}while(0)

/* ToDo: You can allocate the SDI00 to P50 or P16 with PIOR01 register */
#define SDI00_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 1);    /* allocate SDI00 to P50 */ \
        PORT->PM5   |=  (1 << 0);    /* P50 is used as SDI00 input */ \
}while(0)

/**
  * @brief IIC00 Port Setting（Alternative to fixed port)
  */

#define SCL00_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 1);    /* allocate SCL00 to P30 */ \
        PORT->P3    |=  (1 << 0);    /* P30 output high level */ \
        PORT->PM3   &= ~(1 << 0);    /* P30 is used as SCL00 output */ \
        PORT->POM3  |=  (1 << 0);    /* P30 is N-ch open-drain output mode */ \
}while(0)

#define SDA00_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 1);    /* allocate SDA00 to P50 */ \
        PORT->P5    |=  (1 << 0);    /* P50 output high level */ \
        PORT->PM5   &= ~(1 << 0);    /* P50 is used as SDA00 inout */ \
        PORT->POM5  |=  (1 << 0);    /* P50 is N-ch open-drain output mode */ \
}while(0)

/**
  * @brief SPI01 Port Setting (Alternative to fixed port)
  */

/* ToDo: You can allocate the SS01 to any desired pins */
#define SS01_PORT_SETTING() do{ \
        PORT->P6   |=  (1 << 2);     /* P62 output high level */ \
        PORT->PM6  &= ~(1 << 2);     /* P62 is used as SS01 output */ \
}while(0)

/* ToDo: You can allocate the SS01 to any desired pins */
#define SS01_PORT_SET() do{ \
        PORT->P6  |=  (1 << 2);      /* P62 output high level */ \
}while(0)

/* ToDo: You can allocate the SS01 to any desired pins */
#define SS01_PORT_CLR() do{ \
        PORT->P6  &= ~(1 << 2);      /* P62 output low level */ \
}while(0)

#define SCLKI01_PORT_SETTING() do{ \
        PORT->PM7  |=  (1 << 5);    /* P75 is used as SCLK00 input */ \
}while(0)

#define SCLKO01_PORT_SETTING() do{ \
        PORT->P7   |=  (1 << 5);    /* P75 output high level */ \
        PORT->PM7  &= ~(1 << 5);    /* P75 is used as SCLK00 output */ \
}while(0)

#define SDO01_PORT_SETTING() do{ \
        PORT->P7   |=  (1 << 3);    /* P73 output high level */ \
        PORT->PM7  &= ~(1 << 3);    /* P73 is used as SDO01 output */ \
}while(0)

#define SDI01_PORT_SETTING() do{ \
        PORT->PM7  |=  (1 << 4);    /* P74 is used as SDI01 input */ \
}while(0)

/**
  * @brief IIC01 Port Setting (Alternative to fixed port)
  */

#define SCL01_PORT_SETTING() do{ \
        PORT->P7   |=  (1 << 5);    /* P75 output high level */ \
        PORT->PM7  &= ~(1 << 5);    /* P75 is used as SCL01 output */ \
}while(0)

#define SDA01_PORT_SETTING() do{ \
        PORT->P7   |=  (1 << 4);    /* P74 output high level */ \
        PORT->PM7  &= ~(1 << 4);    /* P74 is used as SDA01 inout */ \
        PORT->POM7 |=  (1 << 4);    /* P74 is N-ch open-drain output mode */ \
}while(0)

/**
  * @brief UART1 Port Setting (Alternative to fixed port)
  */

#define TXD1_PORT_SETTING() do{ \
        PORT->P0   |=  (1 << 2);    /* P02 output high level */ \
        PORT->PM0  &= ~(1 << 2);    /* P02 is used as TXD1 output */ \
        PORT->POM0 &= ~(1 << 2);    /* P02 is push-pull output mode */ \
        PORT->PMC0 &= ~(1 << 2);    /* P02 digital function */ \
}while(0)

#define RXD1_PORT_SETTING() do{ \
        PORT->PM0  |=  (1 << 1);    /* P01 is used as RXD1 input */ \
        PORT->PMC0 &= ~(1 << 1);    /* P01 digital function */ \
}while(0)

/**
  * @brief SPI10 Port Setting (Alternative to fixed port)
  */

/* ToDo: You can allocate the SS10 to any desired pins */
#define SS10_PORT_SETTING() do{ \
        PORT->P6   |=  (1 << 2);     /* P62 output high level */ \
        PORT->PM6  &= ~(1 << 2);     /* P62 is used as SS10 output */ \
}while(0)

/* ToDo: You can allocate the SS10 to any desired pins */
#define SS10_PORT_SET() do{ \
        PORT->P6  |=  (1 << 2);      /* P62 output high level */ \
}while(0)

/* ToDo: You can allocate the SS10 to any desired pins */
#define SS10_PORT_CLR() do{ \
        PORT->P6  &= ~(1 << 2);      /* P62 output low level */ \
}while(0)

#define SCLKI10_PORT_SETTING() do{ \
        PORT->PM0  |=  (1 << 4);    /* P04 is used as SCLK10 input */ \
        PORT->PMC0 &= ~(1 << 4);    /* P04 is digital function */ \
}while(0)

#define SCLKO10_PORT_SETTING() do{ \
        PORT->P0   |=  (1 << 4);    /* P04 output high level */ \
        PORT->PM0  &= ~(1 << 4);    /* P04 is used as SCLK10 output */ \
        PORT->POM0 &= ~(1 << 4);    /* P04 is push-pull output mode */ \
        PORT->PMC0 &= ~(1 << 4);    /* P04 is digital function */ \
}while(0)

#define SDO10_PORT_SETTING() do{ \
        PORT->P0   |=  (1 << 2);    /* P02 output high level */ \
        PORT->PM0  &= ~(1 << 2);    /* P02 is used as SDO10 output */ \
        PORT->POM0 &= ~(1 << 2);    /* P02 is push-pull output mode */ \
        PORT->PMC0 &= ~(1 << 2);    /* P02 is digital function */ \
}while(0)

#define SDI10_PORT_SETTING() do{ \
        PORT->PM0  |=  (1 << 3);    /* P03 is used as SDI10 input */ \
        PORT->PMC0 &= ~(1 << 3);    /* P03 is digital function */ \
}while(0)

/**
  * @brief IIC10 Port Setting (Alternative to fixed port)
  */

#define SCL10_PORT_SETTING() do{ \
        PORT->P0   |=  (1 << 4);    /* P04 output  */ \
        PORT->PM0  &= ~(1 << 4);    /* P04 is used as SCL10 output */ \
        PORT->POM0 |=  (1 << 4);    /* P04 is N-ch open-drain output mode */ \
        PORT->PMC0 &= ~(1 << 4);    /* P04 is digital function */ \
}while(0)

#define SDA10_PORT_SETTING() do{ \
        PORT->P0   |=  (1 << 3);    /* P03 output high level */ \
        PORT->PM0  &= ~(1 << 3);    /* P03 is used as SDA10 inout */ \
        PORT->POM0 |=  (1 << 3);    /* P03 is N-ch open-drain output mode */ \
        PORT->PMC0 &= ~(1 << 3);    /* P03 is digital function */ \
}while(0)

/**
  * @brief SPI11 Port Setting (Alternative to fixed port)
  */

/* ToDo: You can allocate the SS11 to any desired pins */
#define SS11_PORT_SETTING() do{ \
        PORT->P6   |=  (1 << 2);     /* P62 output high level */ \
        PORT->PM6  &= ~(1 << 2);     /* P62 is used as SS11 output */ \
}while(0)

/* ToDo: You can allocate the SS11 to any desired pins */
#define SS11_PORT_SET() do{ \
        PORT->P6  |=  (1 << 2);      /* P62 output high level */ \
}while(0)

/* ToDo: You can allocate the SS11 to any desired pins */
#define SS11_PORT_CLR() do{ \
        PORT->P6  &= ~(1 << 2);      /* P62 output low level */ \
}while(0)

#define SCLKI11_PORT_SETTING() do{ \
        PORT->PM1  |=  (1 << 0);    /* P10 is used as SCLK11 input */ \
        PORT->PMC1 &= ~(1 << 0);    /* P10 is digital function */ \
}while(0)

#define SCLKO11_PORT_SETTING() do{ \
        PORT->P1   |=  (1 << 0);    /* P10 output high level */ \
        PORT->PM1  &= ~(1 << 0);    /* P10 is used as SCLK11 output */ \
        PORT->POM1 &= ~(1 << 0);    /* P10 is push-pull output mode */ \
        PORT->PMC1 &= ~(1 << 0);    /* P10 is digital function */ \
}while(0)

#define SDO11_PORT_SETTING() do{ \
        PORT->P1   |=  (1 << 2);    /* P12 output high level */ \
        PORT->PM1  &= ~(1 << 2);    /* P12 is used as SDO11 output */ \
        PORT->POM1 &= ~(1 << 2);    /* P12 is push-pull output mode */ \
        PORT->PMC1 &= ~(1 << 2);    /* P12 is digital function */ \
}while(0)

#define SDI11_PORT_SETTING() do{ \
        PORT->PM1  |=  (1 << 1);    /* P11 is used as SDI11 input */ \
        PORT->PMC1 &= ~(1 << 1);    /* P11 is digital function */ \
}while(0)

/**
  * @brief IIC11 Port Setting (Alternative to fixed port)
  */

#define SCL11_PORT_SETTING() do{ \
        PORT->P1   |=  (1 << 0);    /* P10 output high level */ \
        PORT->PM1  &= ~(1 << 0);    /* P10 is used as SCL11 output */ \
        PORT->POM1 |=  (1 << 0);    /* P10 is N-ch open-drain output mode */ \
        PORT->PMC1 &= ~(1 << 0);    /* P10 digital function */ \
}while(0)

#define SDA11_PORT_SETTING() do{ \
        PORT->P1   |=  (1 << 1);    /* P11 output high level */ \
        PORT->PM1  &= ~(1 << 1);    /* P11 is used as SDA11 inout */ \
        PORT->POM1 |=  (1 << 1);    /* P11 is N-ch open-drain output mode */ \
        PORT->PMC1 &= ~(1 << 1);    /* P11 is digital function */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       SCI1                                       ================ */
/* ================================================================================================================== */
/* PIOR01 : TXD2  RXD2
 *    0     P13   P14
 *    1     P77   P76
 */

/**
  * @brief UART2 Port Setting（Alternative to 2 group ports for 64pin product) 
  */

#if 1
/* ToDo: You can allocate the TXD2 to P13 or P77 with PIOR01 register */
#define TXD2_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 1);    /* allocate TXD2 to P13 */ \
        PORT->P1    |=  (1 << 3);    /* P13 output high level */ \
        PORT->PM1   &= ~(1 << 3);    /* P13 is used as TXD2 output */ \
        PORT->POM1  &= ~(1 << 3);    /* P13 is push-pull output mode */ \
        PORT->PMC1  &= ~(1 << 3);    /* P13 is digital function */ \
}while(0)

/* ToDo: You can allocate the RXD2 to P14 or P76 with PIOR01 register */
#define RXD2_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 1);    /* allocate RXD2 to P14 */ \
        PORT->PM1   |=  (1 << 4);    /* P14 is used as RXD2 input */ \
        PORT->PMC1  &= ~(1 << 4);    /* P14 is digital function */ \
}while(0)

#else
/* ToDo: You can allocate the TXD2 to P13 or P77 with PIOR01 register */
#define TXD2_PORT_SETTING() do{ \
        PORT->PIOR0 |=  (1 << 1);    /* allocate TXD2 to P77 */ \
        PORT->P7    |=  (1 << 7);    /* P77 output high level */ \
        PORT->PM7   &= ~(1 << 7);    /* P77 is used as TXD2 output */ \
        PORT->POM7  &= ~(1 << 7);    /* P77 is push-pull output mode */ \
}while(0)

/* ToDo: You can allocate the RXD2 to P14 or P76 with PIOR01 register */
#define RXD2_PORT_SETTING() do{ \
        PORT->PIOR0 |=  (1 << 1);    /* allocate RXD2 to P76 */ \
        PORT->PM7   |=  (1 << 4);    /* P76 is used as RXD2 input */ \
}while(0)
#endif

/**
  * @brief SPI20 Port Setting（Alternative to fixed port)
  */

/* ToDo: You can allocate the SS20 to any desired pins */
#define SS20_PORT_SETTING() do{ \
        PORT->P6   |=  (1 << 3);     /* P63 output high level */ \
        PORT->PM6  &= ~(1 << 3);     /* P63 is used as SS20 output */ \
}while(0)

/* ToDo: You can allocate the SS20 to any desired pins */
#define SS20_PORT_SET() do{ \
        PORT->P6  |=  (1 << 3);      /* P63 output high level */ \
}while(0)

/* ToDo: You can allocate the SS20 to any desired pins */
#define SS20_PORT_CLR() do{ \
        PORT->P6  &= ~(1 << 3);      /* P63 output low level */ \
}while(0)

#define SCLKI20_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 1);    /* allocate SCLK20 to P15 */ \
        PORT->PM1   |=  (1 << 5);    /* P15 is used as SCLK20 input */ \
}while(0)

#define SCLKO20_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 1);    /* allocate SCLK20 to P15 */ \
        PORT->P1    |=  (1 << 5);    /* P15 output high level */ \
        PORT->PM1   &= ~(1 << 5);    /* P15 is used as SCLK20 output */ \
        PORT->POM1  &= ~(1 << 5);    /* P15 is push-pull output mode */ \
}while(0)

#define SDO20_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 1);    /* allocate SDO20 to P15 */ \
        PORT->P1    |=  (1 << 3);    /* P13 output high level */ \
        PORT->PM1   &= ~(1 << 3);    /* P13 is used as SDO20 output */ \
        PORT->POM1  &= ~(1 << 3);    /* P13 is push-pull output mode */ \
}while(0)

#define SDI20_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 1);    /* allocate SDI20 to P14 */ \
        PORT->PM1   |=  (1 << 4);    /* P14 is used as SDI20 input */ \
}while(0)

/**
  * @brief IIC20 Port Setting（Alternative to fixed port)
  */

#define SCL20_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 1);    /* allocate SCL20 to P15 */ \
        PORT->P1    |=  (1 << 5);    /* P15 output high level */ \
        PORT->PM1   &= ~(1 << 5);    /* P15 is used as SCL20 output */ \
        PORT->POM1  |=  (1 << 5);    /* P15 is N-ch open-drain output mode */ \
}while(0)

#define SDA20_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 1);    /* allocate SDA20 to P14 */ \
        PORT->P1    |=  (1 << 4);    /* P14 output high level */ \
        PORT->PM1   &= ~(1 << 4);    /* P14 is used as SDA20 inout */ \
        PORT->POM1  |=  (1 << 4);    /* P14 is N-ch open-drain output mode */ \
}while(0)

/**
  * @brief SPI21 Port Setting (Alternative to fixed port)
  */

/* ToDo: You can allocate the SS21 to any desired pins */
#define SS21_PORT_SETTING() do{ \
        PORT->P6   |=  (1 << 3);     /* P63 output high level */ \
        PORT->PM6  &= ~(1 << 3);     /* P63 is used as SS21 output */ \
}while(0)

/* ToDo: You can allocate the SS21 to any desired pins */
#define SS21_PORT_SET() do{ \
        PORT->P6  |=  (1 << 3);      /* P63 output high level */ \
}while(0)

/* ToDo: You can allocate the SS21 to any desired pins */
#define SS21_PORT_CLR() do{ \
        PORT->P6  &= ~(1 << 3);      /* P63 output low level */ \
}while(0)

#define SCLKI21_PORT_SETTING() do{ \
        PORT->PM7  |=  (1 << 0);    /* P70 is used as SCLK21 input */ \
}while(0)

#define SCLKO21_PORT_SETTING() do{ \
        PORT->P7   |=  (1 << 0);    /* P70 output high level */ \
        PORT->PM7  &= ~(1 << 0);    /* P70 is used as SCLK21 output */ \
}while(0)

#define SDO21_PORT_SETTING() do{ \
        PORT->P7   |=  (1 << 2);    /* P72 output high level */ \
        PORT->PM7  &= ~(1 << 2);    /* P72 is used as SDO21 output */ \
}while(0)

#define SDI21_PORT_SETTING() do{ \
        PORT->PM7  |=  (1 << 1);    /* P71 is used as SDI21 input */ \
}while(0)

/**
  * @brief IIC21 Port Setting (Alternative to fixed port)
  */

#define SCL21_PORT_SETTING() do{ \
        PORT->P7   |=  (1 << 0);    /* P70 output high level */ \
        PORT->PM7  &= ~(1 << 0);    /* P70 is used as SCL21 output */ \
}while(0)

#define SDA21_PORT_SETTING() do{ \
        PORT->P7   |=  (1 << 1);    /* P71 output high level */ \
        PORT->PM7  &= ~(1 << 1);    /* P71 is used as SDA21 inout */ \
        PORT->POM7 |=  (1 << 1);    /* P71 is N-ch open-drain output mode */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       IICA                                       ================ */
/* ================================================================================================================== */

/**
  * @brief IICA0 Port Setting（Alternative to 2 group ports)
  */

#if 1
/* ToDo: You can allocate the SCLA0 to P60 or P14 with PIOR02 register */
#define SCLA0_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 2);    /* allocate SCLA0 to P60 */ \
        PORT->P6    &= ~(1 << 0);    /* P60 output low level */ \
        PORT->PM6   &= ~(1 << 0);    /* P60 is used as SCLA0 output */ \
}while(0)

/* ToDo: You can allocate the SDAA0 to P61 or P15 with PIOR02 register */
#define SDAA0_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 2);    /* allocate SDAA0 to P66 */ \
        PORT->P6    &= ~(1 << 1);    /* P61 output low level */ \
        PORT->PM6   &= ~(1 << 1);    /* P61 is used as SDAA0 inout */ \
}while(0)

#else
/* ToDo: You can allocate the SCLA0 to P60 or P14 with PIOR02 register */
#define SCLA0_PORT_SETTING() do{ \
        PORT->PIOR0 |=  (1 << 2);    /* allocate SCLA0 to P14 */ \
        PORT->P1    &= ~(1 << 4);    /* P14 output low level */ \
        PORT->PM1   &= ~(1 << 4);    /* P14 is used as SCLA0 output */ \
        PORT->POM1  |=  (1 << 4);    /* P14 is N-ch open-drain output mode */ \
}while(0)

/* ToDo: You can allocate the SDAA0 to P61 or P15 with PIOR02 register */
#define SDAA0_PORT_SETTING() do{ \
        PORT->PIOR0 |=  (1 << 2);    /* allocate SDAA0 to P15 */ \
        PORT->P1    &= ~(1 << 5);    /* P15 output low level */ \
        PORT->PM1   &= ~(1 << 5);    /* P15 is used as SDAA0 inout */ \
        PORT->POM1  |=  (1 << 5);    /* P15 is N-ch open-drain output mode */ \
}while(0)
#endif

/* ================================================================================================================== */
/* ================                                       CAN0                                       ================ */
/* ================================================================================================================== */

/**
  * @brief CAN0 Port Setting（Alternative to 2 group ports)
  */

#if 1
/* ToDo: You can allocate the CTXD0 to P02 or P51 with PIOR33 register */
#define CTXD0_PORT_SETTING() do{ \
        PORT->PIOR3 &= ~(1 << 3);    /* allocate CTXD0 to P02 */ \
        PORT->P0    |=  (1 << 2);    /* P02 output high level */ \
        PORT->PM0   &= ~(1 << 2);    /* P02 is used as CTXD0 output */ \
        PORT->PMC0  &= ~(1 << 2);    /* P02 is digital function */ \
}while(0)

/* ToDo: You can allocate the CRXD0 to P03 or P50 with PIOR33 register */
#define CRXD0_PORT_SETTING() do{ \
        PORT->PIOR3 &= ~(1 << 3);    /* allocate CRXD0 to P03 */ \
        PORT->PM0   |=  (1 << 3);    /* P03 is used as CRXD0 input */ \
        PORT->PMC0  &= ~(1 << 3);    /* P03 is digital function */ \
}while(0)

#else
/* ToDo: You can allocate the CTXD0 to P02 or P51 with PIOR33 register */
#define CTXD0_PORT_SETTING() do{ \
        PORT->PIOR3 |=  (1 << 3);    /* allocate CTXD0 to P51 */ \
        PORT->P5    |=  (1 << 1);    /* P51 output high level */ \
        PORT->PM5   &= ~(1 << 1);    /* P51 is used as CTXD0 output */ \
}while(0)

/* ToDo: You can allocate the CRXD0 to P03 or P50 with PIOR33 register */
#define CRXD0_PORT_SETTING() do{ \
        PORT->PIOR3 |=  (1 << 3);    /* allocate CRXD0 to P50 */ \
        PORT->PM5   |=  (1 << 0);    /* P50 is used as CRXD0 input */ \
}while(0)

#endif

/* ================================================================================================================== */
/* ================                                       INTP                                       ================ */
/* ================================================================================================================== */
/**
  * @brief INTP Port Setting 
  */
#define INTP0_PORT_SETTING() do{ \
        PORT->PM13  |=  (1 << 6);   /* P136 is used as INTP0 input */ \
}while(0)

/* ToDo: You can allocate the INTP1 to P50 or P52 with PIOR00 register */
#define INTP1_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 0);    /* allocate INTP1 to P50 */ \
        PORT->PM5   |=  (1 << 0);    /* P50 is used as INTP1 input */ \
}while(0)

/* ToDo: You can allocate the INTP2 to P51 or P53 with PIOR00 register */
#define INTP2_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 0);    /* allocate INTP2 to P51 */ \
        PORT->PM5   |=  (1 << 1);    /* P51 is used as INTP2 input */ \
}while(0)

/* ToDo: You can allocate the INTP3 to P30 or P54 with PIOR00 register */
#define INTP3_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 0);    /* allocate INTP3 to P30 */ \
        PORT->PM3   |=  (1 << 0);    /* P30 is used as INTP3 input */ \
}while(0)

/* ToDo: You can allocate the INTP4 to P31 or P55 with PIOR00 register */
#define INTP4_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 0);    /* allocate INTP4 to P31 */ \
        PORT->PM3   |=  (1 << 1);    /* P31 is used as INTP4 input */ \
}while(0)

/* ToDo: You can allocate the INTP5 to P16 or P12 with PIOR04 register */
#define INTP5_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 4);    /* allocate INTP5 to P16 */ \
        PORT->PM1   |=  (1 << 6);    /* P16 is used as INTP5 input */ \
}while(0)

#define INTP6_PORT_SETTING() do{ \
        PORT->PM14  |=  (1 << 0);   /* P140 is used as INTP6 input */ \
}while(0)

#define INTP7_PORT_SETTING() do{ \
        PORT->PM14  |=  (1 << 1);   /* P141 is used as INTP7 input */ \
}while(0)

/* ToDo: You can allocate the INTP8 to P74 or P42 with PIOR00 register */
#define INTP8_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 0);    /* allocate INTP8 to P74 */ \
        PORT->PM7   |=  (1 << 4);    /* P74 is used as INTP8 input */ \
}while(0)

/* ToDo: You can allocate the INTP9 to P75 or P43 with PIOR00 register */
#define INTP9_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 0);    /* allocate INTP9 to P75 */ \
        PORT->PM7   |=  (1 << 5);    /* P75 is used as INTP9 input */ \
}while(0)

/* ToDo: You can allocate the INTP10 to P76 or P05 with PIOR01 register */
#define INTP10_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 0);    /* allocate INTP10 to P76 */ \
        PORT->PM7   |=  (1 << 6);    /* P76 is used as INTP10 input */ \
}while(0)

/* ToDo: You can allocate the INTP11 to P77 or P06 with PIOR01 register */
#define INTP11_PORT_SETTING() do{ \
        PORT->PIOR0 &= ~(1 << 0);    /* allocate INTP11 to P77 */ \
        PORT->PM7   |=  (1 << 7);    /* P77 is used as INTP11 input */ \
}while(0)

/** @} */ /* End of group Peripherals_Port_Setting_Definations */

#endif
