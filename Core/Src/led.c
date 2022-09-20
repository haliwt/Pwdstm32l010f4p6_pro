#include "led.h"
#include "run.h"
#include "gpio.h"
#include "buzzer.h"
#include "eeprom.h"
#include "adc.h"
#include "touchkey.h"


static void BackLight_Fun(void);
static void Buzzer_RunSound(void);
static void Fail_Buzzer_Sound(void);


uint16_t adcVale;
uint16_t adcx;
float temp;  


void DisplayLed_Handler(void)
{
            
         
        BackLight_Fun();
		if(run_t.fail_sound_flag ==1)
		       Fail_Buzzer_Sound();
		else
		    Buzzer_RunSound();
		Buzzer_InputNewPassword_two_short();

		  //erase EEPRO data 
		  if(run_t.clearEeprom==1){
			  run_t.clearEeprom = 0;
			  ClearEEPRO_Data();
			   run_t.gTimer_8s =0;
		       run_t.led_blank = 1;
			  //Buzzer_ShortSound();
			  Buzzer_LongSound();
			  run_t.inputDeepSleep_times =10;
			 
		  }
 
			 
   
 
	   if(run_t.panel_lock ==1){
			 ERR_LED_ON();   //WT.EDIT 2022.09.20
			 BACKLIGHT_2_OFF();
	         OK_LED_OFF();
			
			 
		   if(run_t.gTimer_input_error_times_60s > 5){
			   run_t.panel_lock =0;
			   run_t.error_times = 0;
		       ERR_LED_OFF(); //WT.EDIT 2022.09.20
 
		   }
 
 
	   }
	   if(run_t.gTimer_ADC >6){
	   	
              run_t.gTimer_ADC=0;
			
			     POWER_ON();
				adcx=Get_Adc_Average(10);
				//adcx =Get_Adc();
				temp=(float)adcx*(3.3/4096); //3.111
                // temp=(float)adcx*(2.7/4096);
		         temp = temp *1000; //31.11V
		        adcVale =(uint16_t)(temp);
				
				if(adcVale < 1500 ){ // low 3.3V is alarm
				    run_t.ADC_times++; //WT.EDIT 2022.09.09
				   if(run_t.ADC_times > 3 ){
				   	run_t.ADC_times = 4;
				      BAT_LED_ON();
				   }

				}
				else{
				    run_t.ADC_times = 0;
					BAT_LED_OFF();
					HAL_ADC_Stop(&hadc);  
                    
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
    uint8_t i;
	static uint16_t cnt;
	
	   if(run_t.BackLight ==1){
	
			  BACKLIGHT_2_ON();
			  
	  }
	
	   if(run_t.BackLight ==2 ){
	
			OK_LED_OFF();
			//BACKLIGHT_OFF() ;
			BACKLIGHT_2_OFF();
	
	   }
	
	  if(run_t.gTimer_8s >7 && run_t.factory_test !=1 && run_t.panel_lock ==0){
	  	  run_t.runTimer_newpassword_16s ++ ;
		  run_t.BackLight =0;
		  run_t.lock_fail=0;
		  run_t.gTimer_8s=0;
		  run_t.lock_fail=0;
		  HAL_ADC_Stop(&hadc);
		  BACKLIGHT_2_OFF();
		  OK_LED_OFF();
		  ERR_LED_OFF();
		  
		 run_t.led_blank =0;
         run_t.passwordsMatch =0 ;
	     run_t.powerOn =3;
        if(run_t.runTimer_newpassword_16s > 2){
        	   run_t.runTimer_newpassword_16s =0; 
		     run_t.Confirm_newPassword = 0;
		     run_t.adminiId=0;
		     run_t.password_unlock=0;
		     run_t.inputPwdTimes=0;
			 for(i=0;i<6;i++){ //WT.EDIT .2022.08.13
				*(pwd2 + i)=0;//pwd2[i]=0;

				*(pwd1+i)=0;//pwd1[i]=0;

		       }
			 
			 
	     }
		  POWER_OFF();
        
          
		  if(run_t.inputDeepSleep_times > 2){  //wait 20s  
			   run_t.inputDeepSleep_times =0;
			   run_t.adminiId =0;  //after a period of time auto turn off flag
			   run_t.Confirm_newPassword = 0; //after a period of time auto turn off flag
			   run_t.password_unlock=0;
			   run_t.unLock_times =0;
			   run_t.powerOn =3;
			   run_t.inputPwdTimes =0;//WT.EDIT 2022.08.13
          
               run_t.passwordsMatch =0 ;
               run_t.runInput_newpwd_times =0;
			   POWER_OFF();

			   BAT_LED_OFF();
				/*close tick timer low power Mode */
			   run_t.gTimer_10s=0;
			    run_t.lowPower_flag=0;
				HAL_SuspendTick();
				SysTick->CTRL = 0x00;//关闭定时器
                SysTick->VAL = 0x00;//清空val,清空定时器
				
				/* input low power mode "STOP"*/
		        HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON,PWR_STOPENTRY_WFI);//WFI ->wait for interrupt
		        SystemClock_Config();//Low power of low frequency 8MHz
			   
		  }
	
	
	  }
	
	  if(run_t.lock_fail==1 && run_t.panel_lock ==0 ){
		   cnt ++ ;
		   
		  OK_LED_OFF();
	
	  
		  if(cnt < 1001 ){
	
			  ERR_LED_OFF();
			  
		  }
		  else if(cnt > 1000 && cnt < 2001){
			  ERR_LED_ON();
		  }
		  if(cnt>2000) cnt = 0;
	
	  }
	 
	
	
	  if( run_t.adminiId==1 || run_t.led_blank	==1){	
	    
		 cnt ++ ;
		 run_t.lock_fail=0;
	
			 
		  if(run_t.inputDeepSleep_times < 1 ){ //30s
			   run_t.gTimer_8s=0;
			  
				  
		  }
		  if(run_t.adminiId ==1)run_t.passwordsMatch=0; //WT.EDIT 2022.08.19
		  if(cnt < 1001 ){
	
			  
               OK_LED_OFF();
			  
		  }
		  else if(cnt>1000 && cnt < 2001)
			  OK_LED_ON();
	
		  if(cnt>2000)cnt = 0;
		  
	  }
	
	  if(run_t.factory_test ==1){
		 run_t.getKey_saveNewPwd_flag = 0;
	      run_t.gTimer_8s=0;
		  BACKLIGHT_2_ON();
		  OK_LED_ON();
		  ERR_LED_ON();
		  BAT_LED_ON();
	
		if(run_t.gTimer_input_error_times_60s > 5){
			run_t.factory_test =0;
			run_t.gTimer_8s=10;
			  BACKLIGHT_2_OFF();
			  OK_LED_OFF();
			  ERR_LED_OFF();
			  BAT_LED_OFF();
	
	
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
   

	


		if(run_t.buzzer_flag ==1){
				  
			 run_t.buzzer_flag=0;
 
			 BUZZER_KeySound();
		   
	     }
		 
	


   
}

static void Fail_Buzzer_Sound(void)
{

	if(run_t.fail_sound_flag ==1){
	
		 run_t.fail_sound_flag = 0;
	
				Buzzer_ShortSound();//Buzzer_ReSound();//fail sound has two sound //WT.EDIT 2022.09.13
				BUZZER_OFF();
				HAL_Delay(200);
				Buzzer_ShortSound();//Buzzer_ReSound();//fail sound has two sound 
				BUZZER_OFF();
	
		}



}


void  Buzzer_InputNewPassword_two_short(void)
{
     


      if(run_t.buzzer_two_short ==1){
          run_t.buzzer_two_short =0;
          Buzzer_High_Sound();
          BUZZER_OFF();
        }


      if(run_t.buzzer_two_short ==2){
          run_t.buzzer_two_short =0;
          Buzzer_ReSound();
          BUZZER_OFF();
          HAL_Delay(400);
          Buzzer_ReSound();
          BUZZER_OFF();

        }


}
/************************************************************
 	*
 	* Function Name :void TouchKey_Led(void)
 	* 
 	* 
 	* 
*************************************************************/
void TouchKey_Led_Handler(void)
{
	  BACKLIGHT_2_ON(); 
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

    static unsigned char t0;

	if(htim->Instance==TIM2){
  
    t0++;
    if(t0>99){ //10*100 =1000ms "1s"
       t0=0;
	  run_t.gTimer_10s_start++;
	  run_t.gTimer_2s ++;
	   run_t.gTimer_1s ++;
	   
	   run_t.gTimer_8s++;
	   run_t.gTimer_10s ++;
	   run_t.gTimer_ADC ++;
	  
	   if(run_t.gTimer_10s_start>9){ //10s
		 run_t.gTimer_10s_start=0;
		 run_t.gTimer_input_error_times_60s++;
	     run_t.inputDeepSleep_times++;
		 run_t.runInput_newpwd_times++;
	    

	   }
	
    }  

	}
}


