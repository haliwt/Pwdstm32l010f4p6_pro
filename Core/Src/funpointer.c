#include "funpointer.h"
#include "single_mode.h"
#include "run.h"
#include "led.h"


static void OpenLock(void);

void(*Led_Working_Handler)(void);
void(*ReadPassword_Handler)(void);

void Led_Response_Handler(void(*led_doing_handler)(void))
{
   Led_Working_Handler = led_doing_handler;

}


void ReadPwd_Handler(void(*readpwd_mode)(void))
{
	ReadPassword_Handler = readpwd_mode;
}

void CheckPassword_Suspend_Handler(void)
{

  if(run_t.passwordsMatch ==1 && run_t.inputNewPassword_Enable==0 ){
		  
		  run_t.passwordsMatch=0;
          run_t.gTimer_8s=0;
          OpenLock();
    }



}

static void OpenLock(void)
{
     uint8_t i;
     static uint8_t Fail;
	     
    ReadPassword_EEPROM_SaveData();
		 
		
		  if(Fail == 1){//unlock is fail 
	
			OK_LED_OFF();
			ERR_LED_ON();
			
			run_t.Numbers_counter = 0;
			 run_t.password_unlock=0;	
			run_t.eepromAddress=0;
			run_t.passwordsMatch = 0;
			Fail ++;
			run_t.error_times ++ ; //input times 5 ,
			if(run_t.error_times > 4){
				run_t.gTimer_10s_start=0;
				run_t.gTimer_input_error_times_60s =0;
				run_t.panel_lock=1;
				run_t.gTimer_8s=0;//WT.EDIT 2022.09.28
					
			}
			run_t.Confirm_newPassword =0;
			run_t.inputNewPassword_Enable =0;
			 run_t.lock_fail=1;
			run_t.fail_sound_flag=1;
			run_t.buzzer_flag =0; //WT.EDIT 2022.10.19
			run_t.buzzer_two_short=0;//WT.EDIT 2022.10.19
			run_t.clear_inputNumbers_newpassword=0; //WT.EDIT 2022.10.14
	
			run_t.Numbers_counter =0; //WT.EDIT 2022.10.14
		 
			   for(i=0;i<6;i++){
				   pwd1[i]=0;
				   Readpwd[i]=0;
				   pwd2[i]=0;
			
				}
			  
			
		  }
	
		 if(run_t.password_unlock ==1){ //unlock 
	
			 if(run_t.Confirm_newPassword ==1){ //prepare new password 
				
				ERR_LED_OFF();
				run_t.inputNewPassword_Enable =1; //Input Administrator password is OK
				run_t.motor_return_homePosition= 0;
				run_t.Numbers_counter =0 ;
				run_t.eepromAddress=0;
				run_t.passwordsMatch = 0;
				run_t.password_unlock=3; //motor don't need run to moved .
				run_t.gTimer_motor_transience_100ms=0;//run_t.gTimer_2s =0;
				run_t.inputDeepSleep_times =0;
				run_t.error_times=0;
				run_t.lock_fail=0;
				run_t.gTimer_8s =0;
				run_t.inputNewPwd_times=0;
			 
			
			}
			else{ //runing open lock 
		      OK_LED_ON();
			  ERR_LED_OFF();
				
			 }
	
            }

}

