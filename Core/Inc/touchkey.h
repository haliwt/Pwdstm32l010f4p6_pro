#ifndef   __TOUCHKEY_H_
#define   __TOUCHKEY_H_
#include "main.h"

//IO Direction setup
//#define I2C_SDA_IO_IN()      {GPIOB->MODER&=0XFFFF3FFF;GPIOB->MODER|=0<<14;}  //0x00 input mode
//#define I2C_SDA_IO_OUT()     {GPIOB->MODER&=0XFFFF3FFF;GPIOB->MODER|=1<<14;}   //0x01 output  mode 


#define I2C_SDA         GPIO_PIN_10
#define I2C_SCL         GPIO_PIN_4
#define I2C_GPIO        GPIOA



#define I2C_SDA_SetHigh()            HAL_GPIO_WritePin(I2C_GPIO,I2C_SDA,GPIO_PIN_SET)    // output high level
#define I2C_SDA_SetLow()             HAL_GPIO_WritePin(I2C_GPIO,I2C_SDA,GPIO_PIN_RESET)    // output low level

#define I2C_SCL_SetHigh()            HAL_GPIO_WritePin(I2C_GPIO,I2C_SCL,GPIO_PIN_SET)    // output high level
#define I2C_SCL_SetLow()             HAL_GPIO_WritePin(I2C_GPIO,I2C_SCL,GPIO_PIN_RESET)    // output low level
//#define EE_IIC_SDA(val)              HAL_GPIO_WritePin(I2C_GPIO, I2C_SDA,val)                    //SDA Êä³ö¸ß»òÕßµÍ 

#define I2C_SDA_ReadData()           HAL_GPIO_ReadPin(I2C_GPIO,I2C_SDA)




#define SC12B_ADDR    0x40         //ASEL 引脚悬空，设备的地址 ->write address

#define SC12B_READ_ADDR        0X41

typedef enum
{
    UNDONE = 0x00,
    DONE   = 0x01
}Complete_Status; 

extern uint8_t  SC_Data[2];






#if 0

#define IO_OUT          0         								//定义 IO口输出方向值
#define IO_IN           1        		              //定义 IO口输入方向值
#define IO_HIGH         1         								//定义 IO口高电平值
#define IO_LOW          0        		              //定义 IO口低电平值





#define OUTPUT0_REG          0x08  //Touch of status register output address
//#define OUTPUT1_REG          0x09 //Touch of status register output address CH[11:0]

#define SAMP0_REG            0x0A  //touch of value be save reg output address
//#define SAMP1_REG             0x0B 


#define SenSet0_REG         0x00                //SC12B为对应CIN3 通道灵敏度的设置地址 


#define SenSet0_REG                  0x00    //CIN4 channel sensitivity of address
#define SenSetCom_REG                0x01    //others channel CINx sensitivity  of address 
#define CTRL0_REG                    0x02    //CTRL0 control register setup of address
#define CTRL1_REG                    0x03    //CTRL1  control register setup of address
#define OUPUT_REG                    0x08    //output register state output of address
#define SAMP_REG                     0x0A    //touch data be save value output address 

#define RTM0                         0 
#define RTM1                         1
#define RTM2                         2
#define RTM3                         3


#define KVF_STOP_CORREC              (1<<2)  //touch is avail ,touch don't need calibration 
#define KVF_50S_CORREC              (0<<2)  //touch is avail ,50s start  calibration
#define HOLD             (1<<3)  //base line  ,don't need  calibration
#define NOTHOLD         (0<<3)    //base line ,continue calibration
#define SLPCYC_LGT       (0<<5)   //infint maxmium 
#define SLPCYC_0R5T       (1<<5)   //to sleep for sample interval 60ms 
#define SLPCYC_0R5T       (1<<5)   //to sleep for sample interval 60ms 
#define SLPCYC_5R5T       (6<<5)   //to sleep for sample interval 660ms 
#define SLPCYC_6R5T       (7<<5)   //to sleep for sample interval 780ms 

#define FAST_T0_SLEEP      (1<<4)    //fast input sleep 


#define TOUCH_KEY_SPEC_1              0x40    //'*' 
#define TOUCH_KEY_6                   0x80
#define TOUCH_KEY_7   

extern unsigned char  SC_Data[2];


typedef enum
{
    UNDONE = 0x00,
    DONE   = 0x01
}Complete_Status;  


typedef enum 
{
   SPECIAL_1 =0x4000,KEY_1=0x1000, KEY_2=0x400, KEY_3=0x100, KEY_4=0x40, KEY_5=0x10,
   KEY_6= 0x8000, KEY_7=0x2000, KEY_8=0x800, KEY_9=0x200, KEY_0=0x80, SPECIAL_2=0x20

}TouchKey_Numbers;




void KEY_Initial(void);


void SC12B_Init_Function(void);





void ICman_Init_SET(unsigned char SC_ADDR);  //IC->SC12B Initialize funciton

unsigned char  I2C_SimpleRead_From_Device(unsigned char *dat8);



Complete_Status I2C_Simple_Read_From_Device(unsigned char deviceAddr,unsigned char* target,unsigned char len);
Complete_Status I2C_Read_From_Device(unsigned char deviceAddr,unsigned char REG,unsigned char* target,unsigned char len);



#endif 

void ICman_Init_SET(unsigned char SC_ADDR);  //IC->SC12B Initialize funciton

uint8_t I2C_SimpleRead_From_Device(uint8_t *dat8);



Complete_Status I2C_Simple_Read_From_Device(unsigned char deviceAddr,unsigned char* target,unsigned char len);
Complete_Status I2C_Read_From_Device(unsigned char deviceAddr,unsigned char REG,unsigned char* target,unsigned char len);





#endif 

