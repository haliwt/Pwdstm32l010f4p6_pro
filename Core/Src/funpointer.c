#include "funpointer.h"
#include "single_mode.h"
#include "run.h"
#include "led.h"
#include "eeprom.h"
#include "kmp.h"
#include "buzzer.h"

uint32_t fvirtualPwd[6];
uint32_t forigin_pwd[4]={1,2,3,4};
uint32_t freadFlag[1];
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

void TouchKey_Suspend_Handler(void)
{



}

static void OpenLock(void)
{
   
	  static unsigned char value;
	  static uint32_t    ReadAddress; 

	 for(run_t.eepromAddress =0; run_t.eepromAddress <11;run_t.eepromAddress++){ //2022.10.07 be changed ten password 
	  
	    switch(run_t.eepromAddress){
	
				 case 0:
					  ReadAddress = ADMINI;
				 break;
				 case 1:
					 ReadAddress = USER_1;
				  
			   break;
	
				 case 2:
					 ReadAddress = USER_2;
			   break;
	
			   case 3:
					 ReadAddress = USER_3;
			   break;
	
			   case 4:
					 ReadAddress = USER_4;
			   break;
	
			   case 5:
					ReadAddress = USER_5;
				break;
	
			   case 6:
					 ReadAddress = USER_6;
				break;
				
				case 7:
					ReadAddress = USER_7;
				  break;
	
				 case 8:
				 
				   ReadAddress = USER_8;
				 break;
	
				 case 9:
				 
					  ReadAddress = USER_9;
			   break;
	
				 case 10:
				   OK_LED_OFF();
						  ERR_LED_ON() ;
						    Fail_Buzzer_Sound();
				   return ;
				break;
	
		   }

      
	   if(run_t.eepromAddress <10){
	   	   if(run_t.Confirm_newPassword == 1){ //set save new password flag bit by administrator open lock
                ReadAddress = ADMINI;
           }
		   
		    EEPROM_Read_Byte(ReadAddress,freadFlag,1);
	
		   if(freadFlag[0] ==1){// has a been saved pwassword 

					EEPROM_Read_Byte(ReadAddress + 0X01,Readpwd,6);
				
					

                    if(run_t.Numbers_counter > 6){
 
                        value = BF_Search(fvirtualPwd,Readpwd);
					}
					else
					    value = CompareValue(Readpwd,pwd1);
					
					
					if(value==1)//if(strcmp(pwd1,pwd2)==0)
					{
						freadFlag[0]=0;
						//run_t.password_unlock=1;
						 OK_LED_ON();
						   ERR_LED_OFF() ;
						   run_t.Led_OK_flag=1;
						   run_t.Led_ERR_flag=0;
						  Buzzer_LongSound() ;
						return ;

					}
					else{
					
                     	freadFlag[0]=0;
						  // Fail = 1;
						  OK_LED_OFF();
						  ERR_LED_ON() ;
						  run_t.Led_OK_flag=0;
						   run_t.Led_ERR_flag=1;
						    Fail_Buzzer_Sound();
						   return ;
						
						
					}

			}
			else{ //don't has a empty space,default password is  "1,2,3,4" ,don't be write new  password

			     if(ReadAddress == ADMINI){

				    
                     if(run_t.Numbers_counter > 4){
 
                            value=0;
							    
                         //value = BF_Search(virtualPwd,origin_pwd);
					 }
                    else
					 value =CompareValue(forigin_pwd, pwd1);

				   if(value==1){
									   
						//run_t.password_unlock=1;	
						   OK_LED_ON();
						   ERR_LED_OFF() ;
				   run_t.Led_OK_flag=1;
						   run_t.Led_ERR_flag=0;
						  Buzzer_LongSound() ;
					
						return ;

					}
					else{
                           OK_LED_OFF();
						  ERR_LED_ON() ;
					run_t.Led_OK_flag=0;
						   run_t.Led_ERR_flag=1;
						    Fail_Buzzer_Sound();
					  
						 return ;
						
					}
				 }
				 //n_t.eepromAddress++ ;	
				 
			}

		 
	   	}
	 }
           

}

