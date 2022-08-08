#include "eeprom.h"






#define PEKEY1        			0x89ABCDEF                //FLASH_PEKEYR
#define PEKEY2       			0x02030405                //FLASH_PEKEYR 
#define EN_INT             		 __enable_irq();         //system open globle interrupt 
#define DIS_INT             	__disable_irq();        //system close globle interrupt

/******************************************************************************
	*
	*Function Name ：void EEPROM_EraseData(uint32_t start, uint32_t NumberSectors)         
	*Function：from EEPROM  erase data 
	*Input Ref: Address：                       
	*           *Buffer： to save data                    
	*           len： to read data length                         
	*Return ：NO 
	*
*******************************************************************************/
void EEPROM_EraseData(void)
{
   uint8_t i;

   HAL_FLASHEx_DATAEEPROM_Unlock();
   for(i=0;i<0x80;i++){

	 HAL_FLASHEx_DATAEEPROM_Erase(DATA_EEPROM_START_ADDR + i);

   }
	HAL_FLASHEx_DATAEEPROM_Lock();


}



/******************************************************************************
	*
	*Function Name ：void EEPROM_Read_Byte(uint16_t Addr,uint8_t *Buffer,uint16_t Length)                    
	*Function：from EEPROM read data 
	*Input Ref: Address：                       
	*           *Buffer： to save data                    
	*           len： to read data length                         
	*Return ：NO 
	*
*******************************************************************************/
void EEPROM_Read_Byte(uint16_t Addr,uint8_t *Buffer,uint8_t Length)
{
   uint8_t *wAddr;  
    HAL_FLASHEx_DATAEEPROM_Unlock();
    wAddr=(uint8_t *)(DATA_EEPROM_BASE+Addr);  
    while(Length--){  
        *Buffer++=*wAddr++;  
        //  HAL_FLASHEx_DATAEEPROM_Lock();
    } 
	HAL_FLASHEx_DATAEEPROM_Lock();

}

/****************************************************************************************************
	*
	*Function Name :void EEPROM_Write_Byte(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite) 
	*Function : To stm32l010f4 to write data form EEPROM 
	*Input Ref: WriteAddr ->to write address ,*pBuffer ->to write data ,
				NumTowrie -> data of length
	*Return Ref :NO
	*
*****************************************************************************************************/
void EEPROM_Write_Byte(uint32_t WriteAddr,uint32_t *pBuffer,uint8_t NumToWrite)  
{  
    uint8_t t;  
    HAL_FLASHEx_DATAEEPROM_Unlock();      
    for(t = 0;t < NumToWrite;t++)  
    {  
        HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE,DATA_EEPROM_BASE + WriteAddr + t,*(pBuffer + t));  
    }  
    HAL_FLASHEx_DATAEEPROM_Unlock();  
}  











