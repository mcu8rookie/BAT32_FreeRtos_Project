/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    gpio.h
* @brief   This file implements device driver for GPIO module.
* @version 1.0.0
* @date    2022/2/25
***********************************************************************************************************************/
#ifndef GPIO_H
#define GPIO_H
#ifndef __CORE_CM0PLUS_H_GENERIC
#include "core_cm0plus.h"
#endif

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum {
	PORT0 = 0,
	PORT1,
	PORT2,
	PORT3,
	PORT4,
	PORT5,
	PORT6,
	PORT7,
	PORT8,
	PORT9,
	PORT10,
	PORT11,
	PORT12,
	PORT13,
	PORT14,
	
}PORT_TypeDef;

typedef enum {
	PIN0 = 0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	
}PIN_TypeDef;

typedef enum {
	INPUT = 0,
	PULLUP_INPUT,
	TTL_INPUT,
	ANALOG_INPUT,
	OUTPUT,
	OPENDRAIN_OUTPUT,
	
}PIN_ModeDef;

#define PIN_MASK_0                 ((uint8_t)(0x01))  /*!< Pin 0 selected    */
#define PIN_MASK_1                 ((uint8_t)(0x02))  /*!< Pin 1 selected    */
#define PIN_MASK_2                 ((uint8_t)(0x04))  /*!< Pin 2 selected    */
#define PIN_MASK_3                 ((uint8_t)(0x08))  /*!< Pin 3 selected    */
#define PIN_MASK_4                 ((uint8_t)(0x10))  /*!< Pin 4 selected    */
#define PIN_MASK_5                 ((uint8_t)(0x20))  /*!< Pin 5 selected    */
#define PIN_MASK_6                 ((uint8_t)(0x40))  /*!< Pin 6 selected    */
#define PIN_MASK_7                 ((uint8_t)(0x80))  /*!< Pin 7 selected    */


/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void GPIO_Output_Enable(__IO uint8_t *port, uint8_t pinMsk);
void GPIO_Input_Enable(__IO uint8_t *port, uint8_t pinMsk);
void GPIO_PullUp_Enable(__IO uint8_t *port, uint8_t pinMsk);
void GPIO_PullUp_Disable(__IO uint8_t *port, uint8_t pinMsk);
void GPIO_Nch_OpenDrain(__IO uint8_t *port, uint8_t pinMsk);
void GPIO_Ttl_Input(__IO uint8_t *port, uint8_t pinMsk);
void GPIO_Set_Value(__IO uint8_t *port, uint8_t value);
uint8_t GPIO_Get_Value(__IO uint8_t *port);

void PORT_Init(PORT_TypeDef PORTx,PIN_TypeDef PINx,PIN_ModeDef MODEx);
//void PORT_SetBit(PORT_TypeDef PORTx,PIN_TypeDef PINx);
//void PORT_ClrBit(PORT_TypeDef PORTx,PIN_TypeDef PINx);
//void PORT_ToggleBit(PORT_TypeDef PORTx,PIN_TypeDef PINx);
//uint8_t PORT_GetBit(PORT_TypeDef PORTx,PIN_TypeDef PINx);

/*****************************************************************************
 ** \brief	 PORT_SetBit
 **			 
 ** \param [in] PORTx : PORT_TypeDef
 **				PINx: PIN_TypeDef
 ** \return  none
 ** \note	 
*****************************************************************************/
#define   PORT_SetBit(PORTx,PINx)  do{\
											*((uint8_t*)((uint8_t*)&PORT->P0+PORTx)) |= (1<<PINx);\
										   }while(0)
/*****************************************************************************
 ** \brief	 PORT_ClrBit
 **			 
 ** \param [in] PORTx : PORT_TypeDef
 **				PINx: PIN_TypeDef
 ** \return  none
 ** \note	 
*****************************************************************************/
#define   PORT_ClrBit(PORTx,PINx)  do{\
											*((uint8_t*)((uint8_t*)&PORT->P0+PORTx)) &= ~(1<<PINx);\
										   }while(0)
/*****************************************************************************
 ** \brief	 PORT_ToggleBit
 **			 
 ** \param [in] PORTx : PORT_TypeDef
 **				PINx: PIN_TypeDef
 ** \return  none
 ** \note	 
*****************************************************************************/
#define   PORT_ToggleBit(PORTx,PINx)  do{\
											*((uint8_t*)((uint8_t*)&PORT->P0+PORTx)) ^= (1<<PINx);\
										   }while(0)
/*****************************************************************************
 ** \brief	 PORT_GetBit
 **	
 ** \param [in] PORTx : PORT_TypeDef
 **				PINx: PIN_TypeDef
 ** \return  PORT Bit
 ** \note	 
*****************************************************************************/
#define   PORT_GetBit(PORTx,PINx)  (*((uint8_t*)((uint8_t*)&PORT->P0+PORTx)) & (1<<PINx))
											
#endif
