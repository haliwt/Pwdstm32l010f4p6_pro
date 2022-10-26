#include "buzzer.h"
#include "gpio.h"
#include "run.h"
#include "delay.h"
#define CPU_FREQUENCY_MHZ 24 // STM32时钟主频


void Buzzer_ResetSond(void);



/*****************************************************************
  *
  *Function Name: void BUZZER_KeySound(void)
  *Function: Key be pressed carry out sound
  *Input Ref:NO
  *Return Ref:NO
  *
*****************************************************************/
void BUZZER_KeySound(void)
{
  //unsigned int m=300;//80
  unsigned int m=250;//150;//300;//200;//100
	while(m--){

  HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);//BEEP=!BEEP;
   delay_us(600);//4000//350//__delay_us(300);;//__delay_us(800);//delayUS(300);
  // delay_ms(1);//example @2
  //delay_us(650);//example @3 400

  }
}
/*****************************************************************
  *
  *Function Name: void BUZZER_KeySound(void)
  *Function: Key be pressed carry out sound
  *Input Ref:NO
  *Return Ref:NO
  *
*****************************************************************/
void Buzzer_LongSound(void)
{
    unsigned int m=800;//400
	while(m--){

	   HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);//BEEP=!BEEP;
	   delay_us(600);//__delay_us(300);//delayUS(600);
     //delay_us(300);
     
    }
}
/*****************************************************************
  *
  *Function Name: void Buzzer_ShortSound(void)
  *Function: short sound
  *Input Ref:NO
  *Return Ref:NO
  *
*****************************************************************/
void Buzzer_ShortSound(void)
{
    unsigned int m=400;
	

	 while(m--){

	   HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);//BEEP=!BEEP;
	  delay_us(300);//__delay_us(300);//delayUS(600);



	 }

}
/*****************************************************************
  *
  *Function Name: void Buzzer_ErrorSound(void)
  *Function: error sound
  *Input Ref:NO
  *Return Ref:NO
  *
*****************************************************************/
void Buzzer_ErrorSound(void)
{
	unsigned int m=200;//80
  
	while(m--){

  HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);//BEEP=!BEEP;
  delay_us(600);//4000//350//__delay_us(300);;//__delay_us(800);//delayUS(300);
 

  }


}

/*****************************************************************
  *
  *Function Name: void Buzzer_ErrorSound(void)
  *Function: high frequency 
  *Input Ref:NO
  *Return Ref:NO
  *
*****************************************************************/
void Buzzer_High_Sound(void)
{
     unsigned int m=800;
	
   //  for(m=0;m<100;m++){//m<50
      while(m--){
          HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);//BEEP=!BEEP;
          delay_us(400);//__delay_us(600);//delayUS(99);
         
          
     }
	  

}

void Buzzer_ReSound(void)
{
     unsigned int m=50;
  
      while(m--){
        HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);//BEEP=!BEEP;
        delay_us(800);//__delay_us(2);//delayUS(99);
        //  HAL_Delay(2);
        
     }

}



