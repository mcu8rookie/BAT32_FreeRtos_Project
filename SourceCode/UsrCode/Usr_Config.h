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

#define DEF_SOFT_ARCH       DEF_MAINLOOP


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


#define FW_VERSION_PART0    28
#define FW_VERSION_PART1    0
#define FW_VERSION_PART2    40      // 20250806

#define MCU_CORE            "\nMCU_Core:            Arm Cortex-M0+."
#define MCU_Vender          "\nMCU_Vender:          Cmsemicon."
#if(defined(DEF_BOARD_TYPE)&&(DEF_BOARD_TYPE==DEF_BOARD_EVB_EN))
#define MCU_NAME            "\nMCU_Name:            BAT32A237KH64FB.      (KE24NA/32FP/40NB/48FA/64FB)"
#endif
#if(defined(DEF_BOARD_TYPE)&&(DEF_BOARD_TYPE==DEF_BOARD_PROJ1_EN))
#define MCU_NAME            "\nMCU_Name:            BAT32A237KH40NB.      (KE24NA/32FP/40NB/48FA/64FB)"
#endif
#if(defined(DEF_BOARD_TYPE)&&(DEF_BOARD_TYPE==DEF_BOARD_PROJ2_EN))
#define MCU_NAME            "\nMCU_Name:            BAT32A237KH40NB.      (KE24NA/32FP/40NB/48FA/64FB)"
#endif

#define LANGUAGE_NAME       "\nC_Language Version:  "

#define IDE_INFOR           "\nIDE_Name:            ARM-MDK V5.15.    (uVision V5.15)"
#define COMPILER_INFOR      "\nCompiler_Name:       Armcc.exe V5.05."

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
#define SENSOR_PT_TYPE              SENSOR_TYPE_CMP201


#define DEF_FUN_TIMESN_EN           (1)

#define DEF_FUN_TCOMP_EN           (1)

#define DEF_SRAW_FILTER_EN          (1)

//#define DEF_OVERRANGE_ALARM_EN      (1)

#define DEF_HUMCOMP_EN              (1)

#define DEF_PRESCOMP_EN             (1)

#define DEF_TEMPRATE_EN             (1)

#define DEF_LFL_EN                  (1)

#define DEF_ADC_EN                  (1)

#define DEF_HEAT_COMP2_EN           (0)

#define DEF_OVERRANGE_ALARM_EN      (1)

#define DEF_OVERTHVAL_EN            (1)

#define DEF_I2CRST1_EN              (1)

#define DEF_CONCEN_THRE_EN          (1)
#if(defined(DEF_CONCEN_THRE_EN)&&(DEF_CONCEN_THRE_EN==1))
#define DEF_ALARM5MIN_EN            (1)
#endif

#define DEF_JUDGE_OVER_DEWP_EN      (0)

#define DEF_DELTA_RAW_EN            (1)

#define DEF_DELTA_PPM_EN            (1)

#define DEBUG_HUMI_RATE_EN          (1)

#define DEF_ASC_EN                  (1)

#define DEF_HTHH_MODE_EN            (1)

// #define DEF_DBG_SRAW_0_EN           (0)     ////

#define DEF_HEAT_BOARD_EN           (1)

#define DEF_ASC_FAST_EN             (1)

#define DEF_HPC_FUNC_EN             (1)

#define DEF_TMPR_RATE_EN            (1)
#define DEF_HUMI_RATE_EN            (1)
#define DEF_PRES_RATE_EN            (1)


#define DEF_MOCK_TEST_EN            (0)

#if(defined(DEF_MOCK_TEST_EN)&&(DEF_MOCK_TEST_EN==1))

#define DEF_ASC_TEST_EN             (0)

#define DEF_HPC_TEST_EN             (0)


#if(defined(DEF_ASC_TEST_EN)&&(DEF_ASC_TEST_EN==1))

#define DEF_ASC_USR_EN              (1)
#define DEF_ASC_TEST_TMPR_VALUE     (200)
#define DEF_ASC_TEST_HUMI_VALUE     (500)
#define DEF_ASC_TEST_TMPR_RATE      (2)
#define DEF_ASC_TEST_HUMI_RATE      (2)

//#define DEF_ASC_TEST_PPM_TH_HIGH    (9000)
//#define DEF_ASC_TEST_PPM_TH_LOW     (1000)

#define DEF_ASC_TEST_PPM_VALUE      (5000)

#if 1 //((defined(DEF_GAS_TYPE))&&(DEF_GAS_TYPE == DEF_GAS_R454B))
// For R454B;115000;
#define DEF_ASC_TEST_PPM_TH_HIGH    (1150*6)
#define DEF_ASC_TEST_PPM_TH_LOW     (1150*4)
#endif

#if 0 //((defined(DEF_GAS_TYPE))&&(DEF_GAS_TYPE == DEF_GAS_R32))
// For R32;144000;
#define DEF_ASC_TEST_PPM_TH_HIGH    (1440*6)
#define DEF_ASC_TEST_PPM_TH_LOW     (1440*4)
#endif

#define DEF_ASC_FAST_TIME       (10)
#define DEF_ASC_NORM_TIME       (20)

#endif

#endif



#if(defined(DEF_LFL_EN)&&(DEF_LFL_EN==1))
#define DEF_GAS_R454B               (1)
#define DEF_GAS_R32                 (2)
#define DEF_GAS_R290                (3)
#define DEF_GAS_TYPE                DEF_GAS_R454B
#endif


#define DEF_YMDSN_YEAR1             (20)
#define DEF_YMDSN_YEAR2             (25)
#define DEF_YMDSN_CRC1              (1)

#define DEF_YMDSN_MONTH             (2)
#define DEF_YMDSN_DATE              (21)
#define DEF_YMDSN_CRC2              (2)

#define DEF_YMDSN_SN1               (1)
#define DEF_YMDSN_SN2               (2)
#define DEF_YMDSN_CRC3              (3)

#define DEF_YMDSN_SN3               (3)
#define DEF_YMDSN_SN4               (4)
#define DEF_YMDSN_CRC4              (4)




#endif


