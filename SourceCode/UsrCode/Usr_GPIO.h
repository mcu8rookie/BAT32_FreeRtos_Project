#ifndef __USR_GPIO_H__
#define __USR_GPIO_H__


#define Usr_LED1_PORT   PORT7
#define Usr_LED1_PIN    PIN1

#define Usr_LED2_PORT   PORT7
#define Usr_LED2_PIN    PIN2


#define Usr_KEY1_PORT   PORT7
#define Usr_KEY1_PIN    PIN0

#define Usr_LDOEN_PORT  PORT1
#define Usr_LDOEN_PIN   PIN7

#define Usr_HTMNBD_PORT PORT5
#define Usr_HTMNBD_PIN  PIN1

#define Usr_DBGIO1_PORT PORT1
#define Usr_DBGIO1_PIN  PIN1

#define Usr_DBGIO2_PORT PORT1
#define Usr_DBGIO2_PIN  PIN2


//For PGS8000;
#define Usr_VHT_EN1_PORT    PORT1
#define Usr_VHT_EN1_PIN     PIN2

#define Usr_VHT_EN2_PORT    PORT1
#define Usr_VHT_EN2_PIN     PIN1

#define Usr_VHT_EN3_PORT    PORT1
#define Usr_VHT_EN3_PIN     PIN0

#define Usr_VHT_EN4_PORT    PORT14
#define Usr_VHT_EN4_PIN     PIN7

#define Usr_RS485_DIR_PORT  PORT7
#define Usr_RS485_DIR_PIN   PIN0



extern uint32_t Usr_GPIO_Timestamp;

#define DEF_HEATVOLTAGE_0D0V    0
#define DEF_HEATVOLTAGE_1D2V    1
#define DEF_HEATVOLTAGE_1D8V    2
#define DEF_HEATVOLTAGE_3D3V    3
#define DEF_HEATVOLTAGE_4D5V    4

extern uint8_t Usr_HeatVoltage_State0;
extern uint8_t Usr_HeatVoltage_State1;

void Usr_HeatVoltage_Set(uint8_t voltage);


void Usr_GPIO_InitSetup(void);


void Usr_GPIO_MainLoop(void);





#endif


