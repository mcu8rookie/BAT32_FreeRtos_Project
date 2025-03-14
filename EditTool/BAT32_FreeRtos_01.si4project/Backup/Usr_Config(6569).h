#ifndef __USR_CONFIG_H__

#define __USR_CONFIG_H__


#if defined(__ICCARM__)

#define __WEAK  __WEAK __ATTRIBUTES

#elif defined(__CC_ARM)

#define __WEAK  __weak

#else

#error	"unsupported comiler!!!"

#endif


#define HW_VERSION_PART0    0
#define HW_VERSION_PART1    0
#define HW_VERSION_PART2    1

#define FW_VERSION_PART0    0
#define FW_VERSION_PART1    0
#define FW_VERSION_PART2    1

#define MCU_CORE            "\nMCU_Core:            Arm Cortex-M0+.\n"
#define MCU_Vender          "\nMCU_Vender:          Cmsemicon."
#define MCU_NAME            "\nMCU_Name:            BAT32A23740NB.  (24NA/32FP/40NB/48FA/64FB)\n"

#define IDE_INFOR           "\nIDE:                 ARM-MDK5.15.    (uVision V5.15)"
#define COMPILER_INFOR      "\nCompiler:            Armcc.exe V5.05."

#define C_STD_VERSION       "\n__STDC__VERSION__"__STDC_VERSION__

#define PROJ_NAME           "Project_Name: BAT32A237_FreeRTOS transplant.\n"



#define DEF_TEST_NONE       0
#define DEF_TEST_NULL       1

#define DEF_MAINLOOP        2
#define DEF_FREERTOS        3


#define DEF_BOARD_EVB_EN    1
#define DEF_BOARD_PROJ_EN   1



//#define DEF_SOFT_ARCH       DEF_MAINLOOP
#define DEF_SOFT_ARCH       DEF_FREERTOS



#if(defined(DEF_BOARD_EVB_EN)&&(DEF_BOARD_EVB_EN==1))

#endif

#if(defined(DEF_BOARD_PROJ_EN)&&(DEF_BOARD_PROJ_EN==1))

#endif



//#define SENSOR_TYPE_SHT41           1   // Sensirion temperature and humidity sensor;
#define SENSOR_TYPE_HDC2010         2   // TI temperature and humidity sensor;
#define SENSOR_TYPE_HDC3020         3   // TI temperature and humidity sensor;

//#define SENSOR_TYPE_CPS122          4   // Consensic temperature and barometic pressure sensor;
#define SENSOR_TYPE_CMP201          5   // Coretronic temperature and barometric pressure sensor;

//#define SENSOR_HT_TYPE              SENSOR_TYPE_SHT41
//#define SENSOR_HT_TYPE              SENSOR_TYPE_HDC2010
#define SENSOR_HT_TYPE              SENSOR_TYPE_HDC3020

//#define SENSOR_PT_TYPE              SENSOR_TYPE_CPS122
#define SENSOR_PT_TYPE              SENSOR_TYPE_CMP201


#define DEF_I2C_HARDWARE        1
#define DEF_I2C_SOFTWARE        2

#define DEF_I2C_HWSW            DEF_I2C_SOFTWARE


#endif


