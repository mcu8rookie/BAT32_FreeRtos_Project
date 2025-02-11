#ifndef __USR_CONFIG_H__

#define __USR_CONFIG_H__


#if defined(__ICCARM__)

#define __WEAK  __WEAK __ATTRIBUTES

#elif defined(__CC_ARM)

#define __WEAK  __weak

#else

#error  "unsupported comiler!!!"

#endif

#define DEF_MAINLOOP        1
#define DEF_FREERTOS        2

#define DEF_SOFT_ARCH       DEF_MAINLOOP
// #define DEF_SOFT_ARCH       DEF_FREERTOS


#define DEF_BOARD_EVB_EN    1
#define DEF_BOARD_PROJ1_EN  2
#define DEF_BOARD_PROJ2_EN  3

//#define DEF_BOARD_TYPE      DEF_BOARD_EVB_EN
#define DEF_BOARD_TYPE      DEF_BOARD_PROJ1_EN
//#define DEF_BOARD_TYPE      DEF_BOARD_PROJ2_EN



#define DEF_FREEMODBUS_EN   1


#define HW_VERSION_PART0    0
#define HW_VERSION_PART1    0
#define HW_VERSION_PART2    1

#define FW_VERSION_PART0    0
#define FW_VERSION_PART1    0
#define FW_VERSION_PART2    1

#define MCU_CORE            "\nMCU_Core:            Arm Cortex-M0+."
#define MCU_Vender          "\nMCU_Vender:          Cmsemicon."
#if(defined(DEF_BOARD_EVB_EN)&&(DEF_BOARD_EVB_EN==1))
#define MCU_NAME            "\nMCU_Name:            BAT32A237KH64FB.      (KE24NA/32FP/40NB/48FA/64FB)"
#endif
#if(defined(DEF_BOARD_PROJ1_EN)&&(DEF_BOARD_PROJ1_EN==1))
#define MCU_NAME            "\nMCU_Name:            BAT32A237KH40NB.      (KE24NA/32FP/40NB/48FA/64FB)"
#endif
#if(defined(DEF_BOARD_PROJ2_EN)&&(DEF_BOARD_PROJ2_EN==1))
#define MCU_NAME            "\nMCU_Name:            BAT32A237KH40NB.      (KE24NA/32FP/40NB/48FA/64FB)"
#endif

#define LANGUAGE_NAME       "\nC_Language Version:  "

#define IDE_INFOR           "\nIDE_Name:            ARM-MDK V5.15.    (uVision V5.15)"
#define COMPILER_INFOR      "\nCompiler_Name:       Armcc.exe V5.05."

#if(defined(DEF_SOFT_ARCH)&&(DEF_SOFT_ARCH==DEF_FREERTOS))
#define PROJ_NAME           "\nProject_Name:        BAT32A237_FreeRTOS transplant."
#endif
#if(defined(DEF_SOFT_ARCH)&&(DEF_SOFT_ARCH==DEF_MAINLOOP))
#define PROJ_NAME           "\nProject_Name:        BAT32A237_MainLoop transplant."
#endif

#define MCU_SYSCLK          "\nMCU_SYSCLK:          "




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


#define DEF_I2C_HARDWARE            1
#define DEF_I2C_SOFTWARE            2

#define DEF_I2C_HWSW                DEF_I2C_SOFTWARE





#if(defined(DEF_BOARD_TYPE)&&(DEF_BOARD_TYPE==DEF_BOARD_PROJ1_EN))
#define DEF_PGS7000_AGE_EN  1
#define DEF_PGS8000_AGE_EN  0
#endif

#if(defined(DEF_BOARD_TYPE)&&(DEF_BOARD_TYPE==DEF_BOARD_PROJ2_EN))
#define DEF_PGS7000_AGE_EN  1
#define DEF_PGS8000_AGE_EN  0
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
//#define SENSOR_PT_TYPE              SENSOR_TYPE_CMP201




#endif


