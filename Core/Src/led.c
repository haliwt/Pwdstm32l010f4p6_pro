#include "led.h"
#include "run.h"
#include "gpio.h"
#include "buzzer.h"
#include "eeprom.h"
#include "adc.h"
#include "touchkey.h"


static void BackLight_Fun(void);
static void Buzzer_RunSound(void);

uint16_t adcx;
float temp;
uint16_t adcVale;



void DispLed_Fun(void)
{
           
         
          BackLight_Fun();
		  Buzzer_RunSound();

		  //erase EEPRO data 
		  if(run_t.clearEeprom==1){
               Buzzer_LongSound();
			   run_t.gTimer_8s =0;
			   run_t.retimes =10;
			   run_t.led_blank = 1;
			  run_t.clearEeprom = 0;
			  ClearEEPRO_Data();
			  Buzzer_LongSound();
			 
		  }
 
			 
   
 
	   if(run_t.panel_lock ==1){
			 ERR_LED_OFF();
			 BACKLIGHT_2_OFF();
			
			 
		   if(run_t.gTimer_60s > 59){
			   run_t.panel_lock =0;
			   run_t.error_times = 0;
 
		   }
 
 
	   }
	   if(run_t.gTimer_10s ==1){
	   	
            run_t.gTimer_10s=0;
			adcx=Get_Adc() ;  
			temp=(float)adcx*(3.3/4096); //3.111
	        temp = temp *10; //31.11V
	        adcVale =(uint16_t)temp;
			if(adcVale < 21){
			   BAT_LED_ON();

			}
			else{
				BAT_LED_OFF();

			}

	   }


}

/****************************************************************************
*
*Function Name:void BackLight_Fun(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
static void BackLight_Fun(void)
{
     
	static uint16_t cnt;
	
	   if(run_t.BackLight ==1 ){
	
			  
				//BACKLIGHT_ON() ;
				BACKLIGHT_2_ON();
			  
	  }
	
	   if(run_t.BackLight ==2 ){
	
			OK_LED_OFF();
			//BACKLIGHT_OFF() ;
			BACKLIGHT_2_OFF();
	
	   }
	
	  if(run_t.gTimer_8s >8){
		  run_t.BackLight =0;
		  run_t.lock_fail=0;
		  run_t.gTimer_8s=0;
		 // BACKLIGHT_OFF() ;
		  BACKLIGHT_2_OFF();
		  OK_LED_OFF();
		  ERR_LED_OFF();
		  BAT_LED_OFF();
		  run_t.led_blank =0;
          run_t.passwordsMatch =0 ;
	      run_t.powerOn =3;
		  POWER_OFF();
       
          
		  if(run_t.retimes > 2){  //wait 30s  
			   run_t.retimes =0;
			   run_t.adminiId =0;  //after a period of time auto turn off flag
			   run_t.Confirm = 0; //after a period of time auto turn off flag
			   run_t.password_unlock=0;
			   run_t.unLock_times =0;
			   run_t.Confirm =0 ; //permit new password be save to EEPROM flag
			   run_t.powerOn =3;
			   run_t.inputPwdTimes =0;//WT.EDIT 2022.08.13
			   POWER_OFF();

			   
				/*close tick timer low power Mode */
			  
			    run_t.lowPower_flag=1;
				HAL_SuspendTick();
				SysTick->CTRL = 0x00;//关闭定时器
                SysTick->VAL = 0x00;//清空val,清空定时器
				
				/* input low power mode "STOP"*/
		        HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON,PWR_STOPENTRY_WFI);//WFI ->wait for interrupt
		        SystemClock_Config();//Low power of low frequency 8MHz
			   
		  }
	
	
	  }
	
	  if(run_t.lock_fail==1){
		   cnt ++ ;
		   
		  OK_LED_OFF();
	
	  
		  if(cnt < 2000 ){
	
			  ERR_LED_ON();
			  
		  }
		  else if(cnt > 1999 && cnt < 4001)
			  ERR_LED_OFF();
	
		  if(cnt>4000) cnt = 0;
	
	  }
	 
	
	
	  if( run_t.adminiId==1 || run_t.led_blank	==1){
	
		 cnt ++ ;
		 run_t.lock_fail=0;
	
			 
		  if(run_t.retimes < 2 ){ //30s
			   run_t.gTimer_8s=0;
			  
				  
		  }
		
		  if(cnt < 2000 ){
	
			  OK_LED_ON();
			  
		  }
		  else if(cnt>1999 && cnt < 4001)
			  OK_LED_OFF();
	
		  if(cnt>4000)cnt = 0;
		  
	  }
	
	  if(run_t.factory_test ==1){
		  run_t.getKey = 0;
	      run_t.gTimer_8s=0;
		  //BACKLIGHT_ON() ;
		  BACKLIGHT_2_ON();
		  OK_LED_ON();
		  ERR_LED_ON();
		  BAT_LED_ON();
	
		if(run_t.gTimer_60s > 60){
			run_t.getKey = 0;
			run_t.factory_test =0;
			BAT_LED_OFF();
			 run_t.gTimer_8s=10;
	
	
		}
	
	
	
	  }

}
/****************************************************************************
*
*Function Name:void Buzzer_Sound(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
static void Buzzer_RunSound(void)
{
    unsigned char  i;

	if(run_t.buzzer_flag ==1){
			  
		 run_t.buzzer_flag=0;

		 BUZZER_KeySound();
	   
         i=1;
	              
	}

   

	

   if(i==1){
   	
      HAL_Delay(100);//__delay_ms(200);//300
      
    			 run_t.getSpecial_1_key++;//n0++;
				 run_t.getSpecial_2_key++;//n1++;
				 run_t.getNumbers_key++;//n2++;
                  i=0;
     
       run_t.passwordsMatch =0;
      
   }
}

/****************************************************************************
*
*Function Name:void HAL_TIM_PeriodElapsedHalfCpltCallback(TIM_HandleTypeDef *htim)
*Function : half -> 16bit, TIM2 timing time is 10ms 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

    static unsigned char t0,tm1;

	if(htim->Instance==TIM2){
  
    t0++;
    if(t0>99){ //10*100 =1000ms "1s"
       t0=0;
	   tm1++;
	  run_t.gTimer_2s ++;
	   run_t.gTimer_1s ++;
	   run_t.gTimer_60s++;
	   run_t.gTimer_8s++;
	 
	  
	   if(tm1>9){ //10s
		 tm1=0;
		 run_t.gTimer_10s ++;
	     run_t.retimes++;
		 
	    

	   }
	
    }  

	}
}


