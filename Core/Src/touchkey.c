#include "touchkey.h"
#include "i2c.h"
uint8_t  SC_Data[2];



# if 0
static void I2C_Start(void);
static void I2C_Stop(void);
void I2C_Respond(unsigned char acksig);
static unsigned char I2C_Receive8bit(void);
unsigned char SendByteAndGetNACK(unsigned char dataToSend);



/**
 * @brief 
 * 
 */
void SC12B_Init_Function(void)
{
   
   // CMCON  = 0x07;          //关闭比较器功能 ->PORTA 
    CMCON0 = 0x07 ; //PIC16F684
    ANSELbits.ANS5 = 0;
    ANSELbits.ANS6=0;     //

  //  TRISCbits.TRISC1 = 0;
  //  TRISCbits.TRISC2= 0;

}
/**
 * @brief 
 * 
 */

/*****************************************************************************
									* I2C 时钟延时函数 
									* 要保证波特率在100K以内最好
									如果太快，可以把以下函数Delay内的变量稍微加大
******************************************************************************/
void I2C_Delay(void)
{
		unsigned char a;
		for(a = 20; a>0; a--){

            asm("NOP");

			};//a =5
}

static void I2C_Start(void)
{
        SDA_OUT_OR_IN = IO_OUT;
		SCL_OUT_OR_IN = IO_OUT;
		SDA = IO_HIGH;
		SCL = IO_HIGH;
		I2C_Delay();
		SDA = IO_LOW;
		I2C_Delay();
		SCL = IO_LOW;
		I2C_Delay();

}

static void I2C_Stop(void)
{
        SCL = IO_LOW;
		SDA_OUT_OR_IN = IO_OUT;
		SDA = IO_LOW;
		I2C_Delay();
		SCL = IO_HIGH;
		I2C_Delay();
		SDA = IO_HIGH;
}

/*****************************************************************************
						* 发送一个字节数据，并获取应答
******************************************************************************/
unsigned char SendByteAndGetNACK(unsigned char dataToSend)
{
		unsigned char i;
		SDA_OUT_OR_IN = IO_OUT;
		for (i = 0; i < 8; i++) {
			SCL = IO_LOW;
			I2C_Delay();
			SDA = (dataToSend>>7) &0x01;
			I2C_Delay();
			SCL = IO_HIGH;
			I2C_Delay();
			dataToSend <<= 1;
		}
		SCL = IO_LOW;
		SDA_OUT_OR_IN = IO_IN;
		I2C_Delay();
		SCL = IO_HIGH;
	  I2C_Delay();
		i= 250;
		while(i--)
		{
			if(!SDA_IN){ SCL = IO_LOW; return 0;}
		}
		SCL = IO_LOW;
		return (1);
}


/*****************************************************************************
						* 读取一个字节信号，并下发应答命令.
******************************************************************************/
void I2C_Respond(unsigned char ACKSignal)
{
		SDA_OUT_OR_IN = IO_OUT;
		SDA = IO_LOW;
		SCL = IO_LOW;
		SDA = ACKSignal;
		I2C_Delay();
		SCL = IO_HIGH;
		I2C_Delay();
		SCL = IO_LOW;
}

/*****************************************************************************
									* 读取一个字节函数
******************************************************************************/
unsigned char I2C_Receive8Bit(void)
{
		unsigned char i,buffer = 0;
		SDA_OUT_OR_IN = IO_IN;
		SCL = IO_LOW;
		for (i = 0; i < 8; i++)
		{
			I2C_Delay();
			SCL = IO_HIGH;
			buffer = (buffer<<1)|SDA_IN;
			I2C_Delay();
			SCL = IO_LOW;
		}		
		return (buffer);
}

/****
 * 
 * Function Name :
 * Function : IC SC12B read register value 
 * Input Ref: deviceAddr  ->device address ,reg -register address,dat16 -> read of address value
 * 
*/


/*****************************************************************************
				* SC系列B版本芯片 写寄存器参数运用函数
deviceAddr 设置器件地址 REG 设置寄存器地址 DAT8 写入数据内容的地址
******************************************************************************/
Complete_Status I2C_Write_To_Device(unsigned char deviceAddr,unsigned char REG,unsigned char*DAT8)
{
				I2C_Start();

                if (SendByteAndGetNACK((deviceAddr<<1) & ~0x01)) {
					I2C_Stop();
				return UNDONE;
			}
			if (SendByteAndGetNACK(REG)) {
					I2C_Stop();
					return UNDONE;
			}
			if (SendByteAndGetNACK(*DAT8)) {
					I2C_Stop();
					return UNDONE;
			}
			I2C_Stop();
			return DONE;
}

/*****************************************************************************
					*SC系列B系列芯片初始化功能函数，如无特殊运用，无需初始化
					如需对那个型号芯片初始化，只需将对应地址写入即可，
					对应的设定参数在初始化函数里面修改
******************************************************************************/
void ICman_Init_SET(unsigned char SC_ADDR)
{
		 unsigned char databuf;
		 #ifdef SPECIAL_APP		
		 //灵敏度从低到高 0x04  0 0x15    0x25  0x36  0x47  0x58  0x68  0x79 
     //               0x8A  0x9B  0xAC  0xBC  0xCD  0xDE  0xEF  0xFF 	
				databuf = 0xFF;
				while(I2C_Write_To_Device(SC_ADDR,SenSet0_REG,&databuf) !=DONE);	
				//databuf = 0x79;
				//while(I2C_Write_To_Device(SC_ADDR,SenSetCOM_REG,&databuf) !=DONE);	
			 //////////非必要，不建议修改，不用直接注释掉/////////////////////////////
			 //databuf = SLPCYC_3R5T | SLOW_TO_SLEEP | NOTHOLD | KVF_50S_CORREC | RTM3;
			 //while(I2C_Write_To_Device(SC_ADDR,CTRL0_REG,&databuf)!=DONE);	
				
				//////////无必要，不建议修改，不用直接注释掉/////////////////////////
				//databuf =0b1000;
				//while(I2C_Write_To_Device(SC_ADDR,CTRL1_REG,&databuf)!=DONE);	
				
		 #endif
}


/***************************************************************************************************************************
	SC系列B版本芯片 简易读取按键值函数（默认直接读取）
	此函数只有初始化配置默认的情况下，直接调用，如果在操作前有写入或者其他读取不能调用默认
**********************************************************************************************************************************/
Complete_Status I2C_Simple_Read_From_Device(unsigned char deviceAddr,unsigned char* target,unsigned char len)
{
			unsigned char i;
			unsigned char *p;
			p = target;
			I2C_Start();
			if (SendByteAndGetNACK((deviceAddr<<1) | 0x01)) {
					I2C_Stop();
					return UNDONE;
			}
			for(i = 0; i < len; i++)
			{
			 		*p= I2C_Receive8Bit();
			 		 p++;
				 	if(i < len-1)
			  			I2C_Respond(0);
			 		else 
			 	 			I2C_Respond(1);
			}
			I2C_Stop();
			return DONE;
}
/*******************************************************************************************************************************
* SC系列B版本芯片
deviceAddr 设置器件地址, REG 设置寄存器地址, target 读取地址对应数据内容。
**************************************************************************************************************************************/
Complete_Status I2C_Read_From_Device(unsigned char deviceAddr,unsigned char REG,unsigned char* target,unsigned char len)
{
	   unsigned char i;
		unsigned char *p;
	  p = target;
		I2C_Start();
		if (SendByteAndGetNACK((deviceAddr<<1) & ~0x01)) {
				I2C_Stop();
				return UNDONE;
		}
		if (SendByteAndGetNACK(REG)) {
			I2C_Stop();
			return UNDONE;
		}
		I2C_Stop();
		I2C_Start();
		if (SendByteAndGetNACK((deviceAddr<<1) | 0x01)) {
			I2C_Stop();
			return UNDONE;
		}
		for(i = 0; i < len; i++)
		{
			 	*p= I2C_Receive8Bit();
			 	p++;
				if(i < len-1)
			  	 I2C_Respond(0);
			  else 
			 	 	 I2C_Respond(1);
		}
		I2C_Stop();
		return DONE;
}


#endif 


uint8_t SC12B_I2C_ReadData(void)
{
    uint8_t reval;
    
    reval = HAL_I2C_Master_Receive(&hi2c1,SC12B_READ_ADDR ,SC_Data,2,1000);
    return reval;
    
}





