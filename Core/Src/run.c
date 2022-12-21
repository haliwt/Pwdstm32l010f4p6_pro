#include "run.h"
#include "eeprom.h"
#include "led.h"
#include "buzzer.h"
#include "motor.h"
#include "kmp.h"
#include "single_mode.h"
#include "funpointer.h"

RUN_T run_t;
unsigned char Fail;
uint32_t readFlag[1]={0};
uint32_t pwd1[6];
uint32_t pwd2[6];
uint32_t origin_pwd[6]={1,2,3,4,0,0};
uint32_t virtualPwd[20];
uint32_t Readpwd[6];
uint32_t eevalue ;

void (*RunChed_KeyMode)(uint16_t keydat);
static void Read_Administrator_Password(void);

/****************************************************************************
*
*Function Name:void Password_Modify(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
unsigned char CompareValue(uint32_t *pt1,uint32_t *pt2)
{
	unsigned char i ;
   for(i=0;i<6;i++){
		if(*(pt1+i) != *(pt2+i)){
			return 0;
		}
		
	}
	return 1;
   
}
/****************************************************************************
*
*Function Name:static void ReadPassword_EEPROM_SaveData(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void SavePassword_To_EEPROM(void)
{
   static unsigned char value,eeNumbers;
   static uint32_t initvalue =0x01;
   if(run_t.inputNewPasswordTimes ==2){//3 WT.EDIT 2022.10.14 
	for(eeNumbers =0; eeNumbers< 11;eeNumbers++){// password is ten numbers
        run_t.gTimer_8s=0;
	  switch(eeNumbers){	  
		   case 0:
		
			  run_t.userId= ADMINI;
				
		   break;

		   case 1 :
		        run_t.userId = USER_1;
			break;
		  
		   case 2: 
				run_t.userId = USER_2; 
			break;
		   
		   case 3 :
		     run_t.userId = USER_3; 
				
			break;
		   
		   case 4: 
	           run_t.userId = USER_4; 
			break;

		   case 5 :
		       run_t.userId = USER_5;  
			break;
		   
		   case 6: 
		        run_t.userId = USER_6; 
			
		    break;
		   case 7 :
		
		        run_t.userId = USER_7; 
			
		    break;
		   
		   case 8: 
		
			  run_t.userId = USER_8; 
			break;
		   
		   case 9 :
	
			run_t.userId = USER_9; 
				
			break;


		   case 10:
		   	  run_t.gTimer_8s=0;
				run_t.Confirm_newPassword =0; //to save new password of flag 
				
				run_t.password_unlock=0;
				run_t.inputNewPasswordTimes =0;
				
				run_t.lock_fail =1;
				run_t.Numbers_counter =0;
				run_t.passwordsMatch =0 ;
				run_t.buzzer_flag =0;//WT.EDIT 2022.10.06	
				
		        run_t.fail_sound_flag=1; //WT.EDIT 2022.10.06	
		        run_t.saveEEPROM_fail_flag =1; //WT.EDIT 2022.10.06	
		        run_t.clear_inputNumbers_newpassword=0;//WT.EDIT 2022.10.14
		      
		        run_t.Confirm_newPassword =0; //WT.EDIT 2022.09.28
		        run_t.inputNewPassword_Enable =0; //WT.EDIT 2022.09.28
				
			   return ;			
				
		   break;

		  }
        
        EEPROM_Read_Byte(run_t.userId,&run_t.readEepromData,1);
		HAL_Delay(5);
		if(run_t.readEepromData !=1){
	
             value =CompareValue(pwd1, pwd2);
			
			 if(value ==1){
			         EEPROM_Write_Byte(run_t.userId ,&initvalue,1);
					 HAL_Delay(5);
					 EEPROM_Write_Byte(run_t.userId + 0x01,pwd1,6);
					 HAL_Delay(5);

                        run_t.inputDeepSleep_times =0; //WT.EDIT 2022.09.20
			
			    		
			   			run_t.inputNewPasswordTimes =0;
						run_t.password_unlock=0;//accomplish by save task//WT.EIDT 2022.09.12
						run_t.lock_fail =0;
					//	run_t.BackLight =2; //success is new password be save to eeprom
						run_t.Numbers_counter =0;
						 run_t.motor_return_homePosition=0;
				
					
						run_t.Confirm_newPassword =0;//WT.EIDT 2022.09.12
						run_t.buzzer_flag =0; //WT.EDIT 2022.10.05
						run_t.buzzer_longsound_flag =1;//WT.EDIT 2022.10.28
					
						run_t.clear_inputNumbers_newpassword=0;//WT.EDIT 2022.10.14
				        run_t.inputNewPassword_Enable =0; //WT.EDIT 2022.10.14
				        OK_LED_ON(); //WT.EDIT 2022.10.28
						ERR_LED_OFF();
                        run_t.gTimer_8s=4;
						run_t.login_in_success=1; //WT.EDIT 2022.10.31
						run_t.gTimer_1s=0;//WT.EDIT 2022.10.31
		
						
						return ;
					
			

			 }
			 else{
			 	//error
				run_t.inputNewPasswordTimes =0;
				run_t.Confirm_newPassword =0;  //be save eeprom data flag bit

				run_t.password_unlock=0;
				run_t.lock_fail =1;
				run_t.led_blank  =0;
				run_t.motor_return_homePosition=0;
				run_t.Numbers_counter =0;
				run_t.buzzer_flag =0;//WT.EDIT 2022.10.06	
				run_t.fail_sound_flag=1; //WT.EDIT 2022.10.06	
				run_t.buzzer_longsound_flag =0;//WT.EDIT 2022.10.19	
				run_t.saveEEPROM_fail_flag =1; //WT.EDIT 2022.10.06	
				run_t.inputDeepSleep_times =0; //WT.EDIT 2022.09.20
				run_t.buzzer_two_short = 0;//WT.EDIT 2022.10.19
				run_t.clear_inputNumbers_newpassword=0;//WT.EDIT 2022.10.14

				run_t.Confirm_newPassword =0; //WT.EDIT 2022.09.28
				run_t.inputNewPassword_Enable =0; //WT.EDIT 2022.09.28
				run_t.BackLight =1;
				OK_LED_OFF(); //WT.EDIT 2022.10.28
				ERR_LED_ON();
				run_t.gTimer_8s=5;//WT.EDIT 2022.11.01
				return ;
				
				}
              
			  
         	}
		
    	}
		
		
	}


}

/****************************************************************************
*
*Function Name:void RunCheck_Mode(unsigned int dat)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void RunCheck_Mode(uint16_t dat)
{
   unsigned char temp, i,read_numbers;
  
   static unsigned char k0=0xff,k1=0xff,k2=0xff,key,spec;
 
   

    switch(dat){

	  

	case SPECIAL_1 ://0x40: //CIN1->'*'
		
       if(k0 != run_t.getSpecial_1_key){
         k0 = run_t.getSpecial_1_key;
         
		 run_t.getSpecial_2_key++;//n1++;
		 run_t.getNumbers_key++;//n2++;
		 spec=1;


		 
	     run_t.BackLight=1;
	 
		  run_t.buzzer_flag =1;
		
		   run_t.lock_fail=0;//WT.EDIT 2022.09.13
		  run_t.gTimer_8s=0;  //LED turn on holde times
		  
		   POWER_ON();

		  if(run_t.inputNewPassword_Enable ==1){//WT.EDIT 2022.10.13

		      run_t.clear_inputNumbers_newpassword ++;
			  run_t.gTimer_8s=0;
			  if(run_t.clear_inputNumbers_newpassword ==2){ //the second times cancel input new password action.

			      run_t.clear_inputNumbers_newpassword=0;
				  run_t.inputNewPassword_Enable=0;
				  run_t.Confirm_newPassword=0;
			      run_t.inputNewPasswordTimes =0;
				  run_t.BackLight =0;
				   run_t.buzzer_flag =1;
				  run_t.stop_gTimer_8s =1;
				  run_t.input_newPassword_over_number = 0;
				  OK_LED_OFF();
				  ERR_LED_OFF();

			  }
			  run_t.input_newPassword_over_number = 0;//WT.EDIT 2022.10.07
			 
		 
		 if(run_t.clear_inputNumbers_newpassword ==1){//WT.EDIT 2022.10.14//if(run_t.inputNewPasswordTimes ==2){ //the first administrator password
			   run_t.gTimer_8s=0;
		
				for(i=0;i<6;i++){
					  pwd2[i]=0;
					  pwd1[i]=0;
				}
			   run_t.inputNewPasswordTimes =0; //WT.EDIT 2022.10.14
	
			  run_t.Numbers_counter =0 ;
			   run_t.gTimer_8s=0;
			  run_t.password_unlock=3;
		     run_t.Confirm_newPassword=1;
			 run_t.inputNewPwd_OK_led_blank_times=0;
			   
		 }
       	}
		 else{
	        for(i=0;i<6;i++){
		  	   pwd1[i]=0;
			   Readpwd[i]=0;
		
		  	}
		 } //WT.EDIT 2022.10.07
	     ERR_LED_OFF();
		 run_t.gTimer_8s=0;
		 spec=1;
		    run_t.lock_fail =0;
		   run_t.Numbers_counter =0 ;
		   run_t.passwordsMatch = 0;
		   run_t.inputDeepSleep_times =0;
		  
		    
	    }
		
       break;

	

	 case SPECIAL_2://0x200: //CIN10 '#' ->confirm 
         if(k1 != run_t.getSpecial_2_key){
	         k1 = run_t.getSpecial_2_key;

             run_t.getSpecial_1_key++;//n1++
		     run_t.getNumbers_key++;//n2++;
		     spec=1;
			 
			run_t.BackLight=1;
		   
         
			if(run_t.Confirm_newPassword ==0){
				run_t.buzzer_flag =1; 
				
            }
			else if(run_t.inputNewPasswordTimes ==0){
				run_t.buzzer_two_short = 1;
			}
			run_t.gTimer_8s=0;
			POWER_ON();

			if(run_t.Numbers_counter ==0){

				run_t.passwordsMatch = 0;
				run_t.gTimer_8s=0;
			}
		    else if(run_t.Numbers_counter < 4 && run_t.Numbers_counter >0){//error
                OK_LED_OFF();
                ERR_LED_ON();
                run_t.Numbers_counter=0;
                run_t.passwordsMatch = 0;
                run_t.error_times ++ ;
                run_t.lock_fail=1;
                run_t.fail_sound_flag=1;
				run_t.buzzer_flag =0;
                if(run_t.error_times > 4 ){ //OVER 5 error  times auto lock touchkey 60 s
	                run_t.gTimer_10s_start=0;//WT.EDIT 2022.09.20
	                run_t.gTimer_input_error_times_60s =0;
	                run_t.panel_lock=1;
					run_t.gTimer_8s=0;

                }

		   }
		   else{


				if(run_t.inputNewPassword_Enable ==1){ //prepare input newpassword .WT.EDI 2022.10.13//if( run_t.Confirm_newPassword ==1){

			            run_t.inputNewPasswordTimes ++ ;  //recoder times
			             run_t.gTimer_8s=0;
						if(run_t.inputNewPasswordTimes ==1){
						 //Confirm Key "#"
						    run_t.buzzer_flag =0; 
							run_t.buzzer_two_short = 2;

						}
					
						
						run_t.passwordsMatch = 1; //run next step process
						run_t.Numbers_counter=0;
						run_t.inputDeepSleep_times =0;
						run_t.gTimer_8s=0;
						run_t.inputNewPwd_OK_led_blank_times=0;
					
						
			    }
				else if(run_t.motor_return_homePosition==0){ // return home position
						run_t.buzzer_flag =1; 
						run_t.passwordsMatch = 1;
						run_t.inputNewPasswordTimes=0; //08.13
					
						run_t.inputDeepSleep_times =0;
				}
				else if(run_t.motor_return_homePosition==1){ //repeat itself motor doing run

				        run_t.buzzer_flag =1; 
					   run_t.passwordsMatch=1;
				       run_t.oneself_copy_behavior=1;
					   run_t.inputDeepSleep_times =0;
					   run_t.eepromAddress=0;

				 }
				 run_t.gTimer_8s=0;
			}

		}
	 
      break;

	 
	case KEY_0:
		
     
		     key=1;
			 spec=0;
		    run_t.getNumbers_key++;
		     run_t.inputDeepSleep_times =0;
			 run_t.gTimer_8s=0;
             run_t.inputNewPwd_OK_led_blank_times=0;
   
	
		

	 break;

    case KEY_1 :

		key=1;
		spec=0;
		run_t.getNumbers_key++;
		run_t.inputDeepSleep_times =0;
		run_t.gTimer_8s=0;
	    run_t.inputNewPwd_OK_led_blank_times=0;
   	 
	break;
			
    case KEY_2:
		key=1;
		spec=0;
		run_t.getNumbers_key++;
		run_t.inputDeepSleep_times =0;
		run_t.gTimer_8s=0;
		run_t.inputNewPwd_OK_led_blank_times=0;
  
	 
	break;
			
	case  KEY_3:
		key=1;
		spec=0;
		run_t.getNumbers_key++;
		run_t.inputDeepSleep_times =0;
		run_t.gTimer_8s=0;
		run_t.inputNewPwd_OK_led_blank_times=0;

	
    break;
			
	case KEY_4:
			
     
		     key=1;
			 spec=0;
			 run_t.getNumbers_key++;
			  run_t.inputDeepSleep_times =0;
			   run_t.gTimer_8s=0;

               run_t.inputNewPwd_OK_led_blank_times=0;
			
	break;
			
	case KEY_5:
			
     
		     key=1;
			 spec=0;
			 run_t.getNumbers_key++;
			   run_t.inputDeepSleep_times =0;
			    run_t.gTimer_8s=0;
           
              run_t.inputNewPwd_OK_led_blank_times=0;
			
             

		
	break;
			
	case KEY_6:
		
    
		     key=1;
			 spec=0;
		  run_t.getNumbers_key++;
			  run_t.inputDeepSleep_times =0;
			   run_t.gTimer_8s=0;
             run_t.inputNewPwd_OK_led_blank_times=0;
       
		
		
	break;
	case KEY_7:
		
    
		     key=1;
			 spec=0;
			 run_t.getNumbers_key++;
			 run_t.inputDeepSleep_times =0;
			  run_t.gTimer_8s=0;
             run_t.inputNewPwd_OK_led_blank_times=0;
         
		
		
	break;
			
	case KEY_8:
		key=1;
		spec=0;
		run_t.getNumbers_key++;
		run_t.inputDeepSleep_times =0;
		run_t.gTimer_8s=0;
		run_t.inputNewPwd_OK_led_blank_times=0;
	break;

	case KEY_9:
		key=1;
		spec=0;
		run_t.getNumbers_key++;
		run_t.inputDeepSleep_times =0;
		run_t.gTimer_8s=0;
		run_t.inputNewPwd_OK_led_blank_times=0;
	break;
		  

	}  

	if(k2 != run_t.getNumbers_key && key==1 && spec ==0 && run_t.getNumbers_key !=0x40 &&run_t.NumbersKey_pressedNumbers==0){
				
		k2=run_t.getNumbers_key;
		key = 0;
		spec =1;
		run_t.getSpecial_1_key++;//n1++

		run_t.getSpecial_2_key++;//n1++;


		run_t.BackLight=1;
		run_t.NumbersKey_pressedNumbers=1;
		run_t.Numbers_counter ++ ;
		run_t.buzzer_flag =1;

		run_t.gTimer_8s=0;

		run_t.passwordsMatch =0;
		POWER_ON();

		if(run_t.Confirm_newPassword ==1 && run_t.Numbers_counter >6){//WT.EDIT 2022.10.08

			run_t.input_newPassword_over_number = 1;//run_t.lock_fail=1;
			run_t.gTimer_8s=0;
			run_t.fail_sound_flag =1;

		}
		else{
			temp = InputNumber_ToSpecialNumbers((TouchKey_Numbers) dat); //input Numbers
			if(run_t.Numbers_counter > 20) run_t.Numbers_counter =20;
				virtualPwd[run_t.Numbers_counter-1]=temp;
			if(run_t.Numbers_counter < 7){//run_t.inputNewPasswordTimes

			if(run_t.inputNewPasswordTimes ==0 && run_t.inputNewPassword_Enable ==1){//WT.EDIT 2022.10.14
				read_numbers = OverNumbers_Password_Handler();
				if(read_numbers==1){
					run_t.password_unlock=5;

				}
				else
				    pwd2[run_t.Numbers_counter-1]=temp; //the first input new password .
			}
			else  pwd1[run_t.Numbers_counter-1] =temp;

			}

		}

		run_t.gTimer_8s=0;
		run_t.inputNewPwd_OK_led_blank_times=0;
	}
}

/****************************************************************************
*
*Function Name:void RunCheck_Mode(unsigned int dat)
*Function : Read from EEPROM data. 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void RunCommand_Unlock(void)
{

    
	uint8_t i;
    
	 if(run_t.Confirm_newPassword == 1){
	 	run_t.gTimer_8s=0;//WT.EDIT 2022.09.28
	 	Read_Administrator_Password();//WT.EDIT 2022.010.07
	 }
	 else
		ReadPassword_EEPROM_SaveData();
     
	
	  if(Fail == 1){//unlock is fail 

		OK_LED_OFF();
		ERR_LED_ON();
	    run_t.Led_OK_flag=0;
		run_t.Led_ERR_flag =1;
		run_t.oneself_copy_behavior =0;//WT.EDIT 2022.10.28
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
			run_t.buzzer_flag =0; 
			run_t.buzzer_highsound_flag =1; //WT.EDIT 2022.10.28
			run_t.inputDeepSleep_times =0;
			run_t.error_times=0;
			run_t.lock_fail=0;
			run_t.gTimer_8s =0;
			run_t.inputNewPwd_OK_led_blank_times=0;
		 
		
		}
		else{ //runing open lock 
		       if(run_t.oneself_copy_behavior ==1){//WT.EDIT 2022.10.28
                    Buzzer_LongSound(); //WT.EDIT 2022.10.06
			        ERR_LED_OFF();
			        OK_LED_ON();
					run_t.Led_OK_flag =1;
					run_t.Led_ERR_flag=0;
					run_t.buzzer_flag=0;
					run_t.oneself_copy_behavior=0;
					run_t.password_unlock=0;
					Fail=0;
					 run_t.Numbers_counter =0 ;
					   run_t.passwordsMatch = 0;
					   run_t.inputDeepSleep_times =0;
					  for(i=0;i<6;i++){
					  	   pwd1[i]=0;
						   Readpwd[i]=0;
						   pwd2[i]=0;
					
					  	}

			   }
               else{
                   run_t.motor_doing_flag=1;
				   run_t.password_unlock=0;
			    	run_t.Numbers_counter =0 ; //WT.EDIT 2022.10.28
				   run_t.passwordsMatch = 0;
				   run_t.inputDeepSleep_times =0;
					   
			       for(i=0;i<6;i++){
				  	   pwd1[i]=0;
					   Readpwd[i]=0;
					   pwd2[i]=0;
				
				  	}

               }

 
	     }


 		}
}
/****************************************************************************
*
*Function Name:static void ReadPassword_EEPROM_SaveData(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
static void Read_Administrator_Password(void)
{
     
	  static unsigned char value;
	  static uint32_t    ReadAddress; 
      uint8_t i;

	 for(run_t.eepromAddress =0; run_t.eepromAddress <3;run_t.eepromAddress++){ //2022.10.07 be changed ten password 
	  
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

			   default:

			   break;
	
			  
	
		   }

      
	   if(run_t.eepromAddress <3){
	   	 
		    run_t.gTimer_8s =0;//
		    EEPROM_Read_Byte(ReadAddress,readFlag,1);
		    HAL_Delay(5);
		   if(readFlag[0] ==1){// has a been saved pwassword 

                    
					EEPROM_Read_Byte(ReadAddress+0x01,Readpwd,6);
					HAL_Delay(5);
					

                    if(run_t.Numbers_counter > 6){
 
                        value = BF_Search(virtualPwd,Readpwd);
					}
					else
					    value = CompareValue(Readpwd,pwd1);
					
					
					if(value==1)//if(strcmp(pwd1,pwd2)==0)
					{
						readFlag[0]=0;
						run_t.password_unlock=1;
						  run_t.gTimer_8s =0;//
						  for(i=0;i<6;i++){
	                        pwd1[i]=0;
	                        pwd2[i]=0;
	                        Readpwd[i]=0;

                      		}
                        
						return ;

					}
					else{
						  
                     	//run_t.inputNewPassword_Enable =1; //Input Administrator password is OK
						run_t.Numbers_counter =0 ;
						run_t.passwordsMatch = 0;
                  if(run_t.eepromAddress==2){
                         Fail = 1;
						 run_t.gTimer_8s =0;//
						 for(i=0;i<6;i++){
	                        pwd1[i]=0;
	                        pwd2[i]=0;
	                        Readpwd[i]=0;

                         }
						 return ;
                        
                   }
						
					}

			}
            else{
		   
			if(run_t.eepromAddress==2){ //don't has a empty space,default password is  "1,2,3,4" ,don't be write new  password

			        ReadAddress = ADMINI;
                    EEPROM_Read_Byte(ReadAddress,readFlag,1);
                    HAL_Delay(5);
                   if(readFlag[0] ==0){

				    
                     if(run_t.Numbers_counter > 4){//6
 
                            value=0;
							    
                         //value = BF_Search(virtualPwd,origin_pwd);
					 }
                    else
					 value =CompareValue(origin_pwd, pwd1);

				   if(value==1){
									   
						run_t.password_unlock=1;	
						run_t.gTimer_8s =0;//
						  for(i=0;i<6;i++){
                        pwd1[i]=0;
                        pwd2[i]=0;
                        Readpwd[i]=0;

                      }
					
						return ;

					}
					else{

					     Fail = 1;
						 run_t.gTimer_8s =0;//
						   for(i=0;i<6;i++){
                        pwd1[i]=0;
                        pwd2[i]=0;
                        Readpwd[i]=0;

                      }
						 return ;
						
					}
				 }
                 else{
                         Fail = 1;
						 run_t.gTimer_8s =0;//
						   for(i=0;i<6;i++){
                        pwd1[i]=0;
                        pwd2[i]=0;
                        Readpwd[i]=0;

                      }
						 return ;
                 
                 }
             }
			 //n_t.eepromAddress++ ;	
				 
			}
           }

		 
	   	}
}


/****************************************************************************
*
*Function Name:static void ReadPassword_EEPROM_SaveData(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void ReadPassword_EEPROM_SaveData(void)
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
				   Fail = 1;
				   run_t.Led_OK_flag =0;
				   run_t.Led_ERR_flag=1;
				   return ;
				break;
	
		   }

      
	   if(run_t.eepromAddress <10){
	   	   if(run_t.Confirm_newPassword == 1){ //set save new password flag bit by administrator open lock
                ReadAddress = ADMINI;
           }
		   
		    EEPROM_Read_Byte(ReadAddress,readFlag,1);
		  //  HAL_Delay(5);
		   if(readFlag[0] ==1){// has a been saved pwassword 

					EEPROM_Read_Byte(ReadAddress + 0X01,Readpwd,6);
				//	HAL_Delay(5);
					

                    if(run_t.Numbers_counter > 6){
 
                        value = BF_Search(virtualPwd,Readpwd);
					}
					else
					    value = CompareValue(Readpwd,pwd1);
					
					
					if(value==1)//if(strcmp(pwd1,pwd2)==0)
					{
						readFlag[0]=0;
						
						 run_t.password_unlock=1;
						run_t.Led_OK_flag =1;
						run_t.Led_ERR_flag=0;
						return ;

					}
					else{
						if(run_t.Confirm_newPassword ==1){
                     		readFlag[0]=0;
						   Fail = 1;
						   run_t.Led_OK_flag =0;
						   run_t.Led_ERR_flag=1;
							return ;
						}
						//n_t.eepromAddress++ ;	
					}

			}
			else{ //don't has a empty space,default password is  "1,2,3,4" ,don't be write new  password

			     if(ReadAddress == ADMINI){

				    
                     if(run_t.Numbers_counter > 4){
 
                            value=0;
							    
                         //value = BF_Search(virtualPwd,origin_pwd);
					 }
                    else
					 value =CompareValue(origin_pwd, pwd1);

				   if(value==1){
									   
						 run_t.password_unlock=1;
						 run_t.Led_OK_flag =1;
						 run_t.Led_ERR_flag=0;
					
						return ;

					}
					else{

					     Fail = 1;
						  run_t.Led_OK_flag =0;
						  run_t.Led_ERR_flag=1;
						 return ;
						
					}
				 }
				 //n_t.eepromAddress++ ;	
				 
			}

		 
	   	}
	  
	 }
}

/****************************************************************************
*
*Function Name:unsigned char  InputNumber_ToSpecialNumbers(TouchKey_Numbers number)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
unsigned char  InputNumber_ToSpecialNumbers(TouchKey_Numbers number)
{
     unsigned char temp ;
	 switch(number){

      case KEY_1: 
            
	 	    temp = 1;

	  break; 

	  case KEY_2:

	       temp =2;

	  break;

	  case KEY_3:
	  	   temp =3;

	  break;

	  case KEY_4:
	  	   temp =4;
	  break;

	  case KEY_5:
	  	   temp = 5;

	  break;

	  case 	KEY_6:

	       temp =6;

	  break;

	  case KEY_7 :

	       temp =7;
	  break;

	  case KEY_8 :

	       temp =8;
	  break;

	  case KEY_9 :

	       temp =9;
	  break;

	  case KEY_0 :

	       temp =0;
	  break;


      default :
	  	 

	  break;



	 }

	return temp;

}

void RunCheck_KeyMode_Handler(void(*keymode_handler)(uint16_t keydat))
{
      RunChed_KeyMode=keymode_handler; 

}


/****************************************************************************
*
*Function Name:void OverNumbers_Password_Handler(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
uint8_t OverNumbers_Password_Handler(void)
{
     uint32_t    ReadAddress; 
     uint8_t   read_flag;

	ReadAddress = USER_9;
	EEPROM_Read_Byte(ReadAddress,readFlag,0x01);


	if(readFlag[0] ==1){ //over ten numbers password
		
		read_flag = 1;
	}
	else{
	   
	   read_flag = 0;
	}

	return read_flag;


}
