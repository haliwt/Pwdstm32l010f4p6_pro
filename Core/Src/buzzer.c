#include "buzzer.h"
#include "gpio.h"

#define CPU_FREQUENCY_MHZ 24 // STM32时钟主频

static void delay_us(uint32_t udelay);
void Buzzer_ResetSond(void);

#if 0

static void delay_us(uint32_t udelay)
{
  uint32_t startval,tickn,delays,wait;
 
  startval = SysTick->VAL;
  tickn = HAL_GetTick();
  //sysc = 72000;  //SystemCoreClock / (1000U / uwTickFreq);
  //delays =udelay * 72; //sysc / 1000 * udelay;
  delays = udelay * 24; //sysCorCloc  = 16MHz 

  
  if(delays > startval)
    {
      while(HAL_GetTick() == tickn)
        {
 
        }
      //wait = 72000 + startval - delays;
      wait = 24000 + startval - delays;
      while(wait < SysTick->VAL)
        {
 
        }
    }
  else
    {
      wait = startval - delays;
      while(wait < SysTick->VAL && HAL_GetTick() == tickn)
        {
 
        }
    }
}

#endif 
static void delay_us(uint32_t delay)
{ 
   
    int last, curr, val;
    int temp;

    while (delay != 0)
    { 
   
        temp = delay > 900 ? 900 : delay;
        last = SysTick->VAL;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        { 
   
            do
            { 
   
                val = SysTick->VAL;
            }
            while ((val < last) && (val >= curr));
        }
        else
        { 
   
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            { 
   
                val = SysTick->VAL;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;
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
void BUZZER_KeySound(void)
{
  unsigned int m=300;//80
  //unsigned int m=200;//80
	while(m--){

  HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);//BEEP=!BEEP;
  delay_us(500);//4000//350//__delay_us(300);;//__delay_us(800);//delayUS(300);
  //  delay_us(300);

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
    unsigned int m=700;//400
	while(m--){

	   HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);//BEEP=!BEEP;
	   delay_us(500);//__delay_us(300);//delayUS(600);
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
    unsigned int m=200;
	

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
	//unsigned int m=150;//80
  unsigned int m=80;//80
	while(m--){

  HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);//BEEP=!BEEP;
  delay_us(500);//4000//350//__delay_us(300);;//__delay_us(800);//delayUS(300);
  //  delay_us(300);

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
     unsigned int m=100;
	
   //  for(m=0;m<100;m++){//m<50
      while(m--){
          HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);//BEEP=!BEEP;
          delay_us(200);//__delay_us(600);//delayUS(99);
          //HAL_Delay(1);
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



