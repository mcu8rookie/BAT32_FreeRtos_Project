#ifndef __USR_CONFIG_H__

#define __USR_CONFIG_H__


#if defined(__ICCARM__)

#define __WEAK	__WEAK __ATTRIBUTES

#elif defined(__CC_ARM)

#define __WEAK	__weak

#else

#error	"unsupported comiler!!!"

#endif


#define HW_VERSION_PART0    0
#define HW_VERSION_PART1    0
#define HW_VERSION_PART2    1

#define FW_VERSION_PART0    0
#define FW_VERSION_PART1    0
#define FW_VERSION_PART2    1

#define MCU_CORE            "\nMCU_Core: Arm Cortex-M0+.\n"
#define MCU_NAME            "MCU_Name: BAT32A237.\n"
#define MCU_SYSCLK          "MCU_SYSCLK: "
#define PROJ_NAME           "Project_Name: BAT32A237_FreeRTOS transplant.\n"

#define CFG_I2C_ADDR7B      0x50
#define CFG_I2C_ADDR_W      0xA0
#define CFG_I2C_ADDR_R      0xA1

#define CFG_SENSOR_I2C      1
#define CFG_SENSOR_UART     2
#define CFG_SENSOR_RS485    3
#define CFG_SENSOR_TYPE     CFG_SENSOR_RS485




#define CFG_UART_BR_2400    2400
#define CFG_UART_BR_9600    9600
#define CFG_UART_BR_19200   19200



#define CFG_UART0_BR_DEF    CFG_UART_BR_2400
#define CFG_UART1_BR_DEF    CFG_UART_BR_2400
#define CFG_UART2_BR_DEF    CFG_UART_BR_2400




#endif


