#ifndef __USR_I2CA_SLAVE_H__
#define __USR_I2CA_SLAVE_H__

#if 1
//#define I2CA_SLAVE_ADDR_7B  (0x98>>1)
#define I2CA_SLAVE_ADDR_7B  (0x13)

#define I2CA_SLAVE_ADDR_WT  ((I2CA_SLAVE_ADDR_7B<<1)+0)
#define I2CA_SLAVE_ADDR_RD  ((I2CA_SLAVE_ADDR_7B<<1)+1)


#define I2CA_CMD_WT_DATA1   (0x01)
#define I2CA_CMD_WT_DATA2   (0x02)

#define I2CA_CMD_RD_DATA1   (0x11)
#define I2CA_CMD_RD_DATA2   (0x22)

#define DEF_I2CA_WT_FLG     (1)
#define DEF_I2CA_RD_FLG     (2)

#define DEF_I2CA_TX_MAX     (64)
#define DEF_I2CA_RX_MAX     (64)
#endif

#define DEF_I2C_TYPE_PSF   (1)
#define DEF_I2C_TYPE_MIDEA  (2)

//#define DEF_I2C_TYPE        DEF_I2C_TYPE_PSF
#define DEF_I2C_TYPE        DEF_I2C_TYPE_MIDEA

// IIC command list
#define IIC_CMD_GET_DELTA_SRAWDATA    0x1100
#define IIC_CMD_GET_DELTA_PPM         0x1101
#define IIC_CMD_GET_DAC_VALUE         0x1102
#define IIC_CMD_GET_HUMI_COEFF        0x1103
#define IIC_CMD_GET_HUMI_COMP_SW      0x1104
#define IIC_CMD_GET_PRESS_COEFF       0x1105
#define IIC_CMD_GET_PRESS_COMP_SW     0x1106
#define IIC_CMD_GET_AGING_TIME        0x1107
#define IIC_CMD_GET_SERIAL_NUM        0x1108
#define IIC_CMD_GET_T_COMP_COEFF      0x1109
#define IIC_CMD_GET_LIFETIME_THRES    0x110A
#define IIC_CMD_GET_RH_RATE_THRES     0x110B
#define IIC_CMD_GET_CALI_PPM          0x110C
#define IIC_CMD_GET_CALI_SRAWDATA     0x110D
#define IIC_CMD_GET_COOL_TIME         0x110E
#define IIC_CMD_GET_CALI_TRAWDATA     0x110F
#define IIC_CMD_GET_CALI_PRESS        0x1110
#define IIC_CMD_GET_CALI_OFFSET       0x1111
#define IIC_CMD_GET_LIFE_TIME         0x1112
#define IIC_CMD_GET_FILTER_NUM        0x1113
#define IIC_CMD_GET_WARMUP_TIME       0x1114
#define IIC_CMD_GET_TSC_COEFF         0x1115


typedef struct
{
	uint16_t cmd;
	uint8_t* addr; 
}tCmdVsAddrType;

typedef struct
{
	uint16_t cmd;
	uint8_t  len; 
}tCmdVsLenType;

typedef uint8_t (*IIC_Wr_Cmd_func_type)(uint8_t*, uint8_t);
	
typedef struct
{
	uint16_t cmd;
	IIC_Wr_Cmd_func_type pFunc; 
}tCmdVsFuncType;



extern uint8_t I2CA_WR_Flag;
extern uint8_t I2CA_Cmd_Flag;
extern uint16_t I2CA_Cmd_Code;

extern uint8_t I2CA_RX_Buff[DEF_I2CA_RX_MAX];
extern uint8_t I2CA_TX_Buff[DEF_I2CA_TX_MAX];

extern uint8_t I2CA_RX_Cnt;
extern uint8_t I2CA_RX_Buff2[DEF_I2CA_RX_MAX];

extern uint8_t YearMonthDateSN[12];

void Usr_I2CA_InitSetup(void);

uint8_t Usr_I2CA_isCmdCodeOK(uint16_t cmdCode);
uint8_t Usr_I2CA_isReadingCmd(uint16_t cmdCode);
uint8_t* Usr_I2CA_getBuffAddr(uint16_t cmdCode);
uint8_t Usr_I2CA_getWrCmdDataLen(uint16_t cmdCode);
uint8_t Usr_I2CA_getRdCmdDataLen(uint16_t cmdCode);

void Usr_I2CA_MainLoop(void);



#if(defined(DEF_I2C_TYPE)&&(DEF_I2C_TYPE==DEF_I2C_TYPE_PSF))

#endif

#if(defined(DEF_I2C_TYPE)&&(DEF_I2C_TYPE==DEF_I2C_TYPE_MIDEA))

#define DEF_PRODUCT_NBR     (0x12345678)
#define DEF_SERIAL_NBR1     (0x12345678)
#define DEF_SERIAL_NBR2     (0x9ABCDEF0)

extern uint8_t Usr_Product_Nbr[4];
extern uint8_t Usr_Serial_Nbr1[8];



extern uint8_t Usr_SnCrc1;
extern uint8_t Usr_SnCrc2;
extern uint8_t Usr_SnCrc3;
extern uint8_t Usr_SnCrc4;
extern uint8_t Usr_SnCrc5;
extern uint8_t Usr_SnCrc6;






extern uint8_t Usr_Md_Cmd1;
extern uint8_t Usr_Md_Cmd2;
extern uint16_t Usr_Md_CmdCode0;
extern uint16_t Usr_Md_CmdCode1;
extern uint16_t Usr_Md_CmdCode2;

extern uint8_t Usr_Md_State;

extern uint16_t g_u16CurCmdCode;
extern uint16_t g_u16CurCmdLen;

extern uint8_t g_u8CmdOK;

extern uint8_t g_u8CmdEC05Type;

extern uint8_t g_u8CmdBuf[2];

#endif


extern uint8_t sensirion_common_generate(const uint8_t *data,uint16_t count);
extern uint8_t compute_crc8(uint8_t *data, uint16_t size);


#endif



