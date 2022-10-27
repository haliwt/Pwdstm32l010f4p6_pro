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
		    run_t.Led_OK_flag=0;
			run_t.Led_ERR_flag =1;
			
			for(i=0;i<6;i++){
				   pwd1[i]=0;
				   Readpwd[i]=0;
				   pwd2[i]=0;
			
			}
			  
			
		  }
	
		 if(run_t.password_unlock ==1){ //unlock 
	
		      OK_LED_ON();
			  ERR_LED_OFF();
			  run_t.Led_OK_flag=1;
			  run_t.Led_ERR_flag =0;
			  for(i=0;i<6;i++){
				   pwd1[i]=0;
				   Readpwd[i]=0;
				   pwd2[i]=0;
			
			}
				
			}
	
           

}

