#ifndef __USR_MAIN_H__
#define __USR_MAIN_H__

#define DEF_TEST_NONE       0
#define DEF_TEST_NULL       1

#define DEF_TEST_GPIO       2
#define DEF_TEST_UART       3
#define DEF_TEST_TIMER      4
#define DEF_TEST_I2C_MST    5
#define DEF_TEST_I2C_SLV    6
#define DEF_TEST_FREERTOS   7

#define DEF_TEST_FUNC       DEF_TEST_FREERTOS



extern uint8_t Flag_SysTick;
extern uint32_t Mcu_Timestamp;
extern uint32_t Mcu_ResetSource;
extern uint32_t Mcu_Name;
extern uint32_t Product_Name;
extern uint32_t Product_Verison;


#endif

