#include "buzzer.h"


static void delay_us(uint32_t udelay);


static void delay_us(uint32_t udelay)
{
  uint32_t startval,tickn,delays,wait;
 
  startval = SysTick->VAL;
  tickn = HAL_GetTick();
  //sysc = 72000;  //SystemCoreClock / (1000U / uwTickFreq);
  //delays =udelay * 72; //sysc / 1000 * udelay;
  delays = udelay * 16; //sysCorCloc  = 16MHz 

  
  if(delays > startval)
    {
      while(HAL_GetTick() == tickn)
        {
 
        }
      //wait = 72000 + startval - delays;
      wait = 16000 + startval - delays;
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




/*******************************************
*
*Function Name: void BUZZER_KeySound(void)
*Function: Key be pressed carry out sound
*
*
*******************************************/
void BUZZER_KeySound(void)
{
      unsigned int m=200;//80
	


    while(m--){

		 HAL_GPIO_TogglePin(BEEP_GPIO,BEEP_GPIO_PIN);//BEEP=!BEEP;
         delay_us(300);//__delay_us(300);;//__delay_us(800);//delayUS(300);


	}
	 


}

void Buzzer_LongSound(void)
{
    unsigned int m=400;
	
//     for(m=0;m<200;m++){//m<50
//          BEEP=!BEEP;
//          __delay_us(600);//delayUS(99);
//     }

	 while(m--){

	   HAL_GPIO_TogglePin(BEEP_GPIO,BEEP_GPIO_PIN);//BEEP=!BEEP;
	  delay_us(300);//__delay_us(300);//delayUS(600);



	 }



}

void Buzzer_ResetSond(void)
{
     unsigned int m;
	
     for(m=0;m<40;m++){//m<50
          HAL_GPIO_TogglePin(BEEP_GPIO,BEEP_GPIO_PIN);//BEEP=!BEEP;
          delay_us(2);//__delay_us(2);//delayUS(99);
     }

}



