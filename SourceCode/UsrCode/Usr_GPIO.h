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

#define Usr_HEATEN_PORT PORT5
#define Usr_HEATEN_PIN  PIN1


extern uint32_t Usr_GPIO_Timestamp;

void Usr_GPIO_InitSetup(void);


void Usr_GPIO_MainLoop(void);





#endif


