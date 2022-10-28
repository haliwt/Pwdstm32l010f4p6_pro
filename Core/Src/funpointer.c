#include "funpointer.h"
#include "single_mode.h"
#include "run.h"
#include "led.h"
#include "eeprom.h"
#include "kmp.h"
#include "buzzer.h"
#include "touchkey.h"
#include "motor.h"

uint32_t fvirtualPwd[6];
uint32_t forigin_pwd[4]={1,2,3,4};
uint32_t freadFlag[1];

//static void Suspend_TouchKey_Fun(uint16_t dat);


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
/****************************************************************************
*
*Function Name:void TouchKey_Suspend_Handler(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void TouchKey_Suspend_Handler(void)
{
    static uint16_t KeyValue;
    if(run_t.passwordsMatch ==0){
    if(I2C_Read_From_Device(SC12B_ADDR,0x08,SC_Data,2)==DONE){
         //if(I2C_Simple_Read_From_Device(SC12B_ADDR,SC_Data,2) ==DONE){
			
             KeyValue =(uint16_t)(SC_Data[0]<<8) + SC_Data[1];
				 Suspend_TouchKey_Fun(KeyValue);
	            if(KeyValue ==0){

	       
	          
	            run_t.NumbersKey_pressedNumbers = 0;
	            run_t.getSpecial_1_key++;
	            run_t.getSpecial_2_key++;
	            run_t.getNumbers_key=0x40;

            }
	     
			  
	 }

 }

}
/****************************************************************************
*
*Function Name:static Suspend_TouchKey_Fun(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void Suspend_TouchKey_Fun(uint16_t dat)
{
    unsigned char temp, i;
  
   static unsigned char k0=0xff,k1=0xff,k2=0xff,key,spec;
 
   

    switch(dat){

	  

	case SPECIAL_1 ://0x40: //CIN1->'*'
		
       if(k0 != run_t.getSpecial_1_key){
         k0 = run_t.getSpecial_1_key;
         spec=1;
	    
	     run_t.getSpecial_2_key++;//n1++;
		  run_t.getNumbers_key++;//n2++;


		run_t.BackLight=1;
		 run_t.gTimer_8s=0;  //LED turn on holde times 
		   run_t.buzzer_flag =1;
		
		   run_t.lock_fail=0;//WT.EDIT 2022.09.13
	
		  // POWER_ON();

		  for(i=0;i<6;i++){
		  	   pwd1[i]=0;
			   Readpwd[i]=0;
		
		  	}
		
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

		     run_t.getSpecial_1_key++;
		     run_t.getNumbers_key++;//n2++;
			
		   run_t.BackLight=1;
           spec=1;

			run_t.gTimer_8s=0;
			run_t.buzzer_flag =1;
			//POWER_ON();

			if(run_t.Numbers_counter ==0){

				run_t.passwordsMatch = 1;
				run_t.gTimer_8s=0;
			}
		    else if(run_t.Numbers_counter < 4 && run_t.Numbers_counter >0){
                OK_LED_OFF();
                ERR_LED_ON();
                run_t.Numbers_counter=0;
                run_t.passwordsMatch = 1;
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


		
                        
					   run_t.passwordsMatch=1;

				   
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
             run_t.inputNewPwd_times=0;
   
	
		

	 break;

    case KEY_1 :

		key=1;
		spec=0;
		run_t.getNumbers_key++;
		run_t.inputDeepSleep_times =0;
		run_t.gTimer_8s=0;
	    run_t.inputNewPwd_times=0;
   	 
	break;
			
    case KEY_2:
         
     	
		     key=1;
		    spec=0;
		   run_t.getNumbers_key++;
		  run_t.inputDeepSleep_times =0;
	      run_t.gTimer_8s=0;
          run_t.inputNewPwd_times=0;
  
	 
	break;
			
	case  KEY_3:
	
  
		     key=1;
			 spec=0;
			 run_t.getNumbers_key++;
			   run_t.inputDeepSleep_times =0;
			    run_t.gTimer_8s=0;
              run_t.inputNewPwd_times=0;
 
	
    break;
			
	case KEY_4:
			
     
		     key=1;
			 spec=0;
			 run_t.getNumbers_key++;
			  run_t.inputDeepSleep_times =0;
			   run_t.gTimer_8s=0;

               run_t.inputNewPwd_times=0;
			
	break;
			
	case KEY_5:
			
     
		     key=1;
			 spec=0;
			 run_t.getNumbers_key++;
			   run_t.inputDeepSleep_times =0;
			    run_t.gTimer_8s=0;
           
              run_t.inputNewPwd_times=0;
			
             

		
	break;
			
	case KEY_6:
		
    
		     key=1;
			 spec=0;
		  run_t.getNumbers_key++;
			  run_t.inputDeepSleep_times =0;
			   run_t.gTimer_8s=0;
             run_t.inputNewPwd_times=0;
       
		
		
	break;
	case KEY_7:
		
    
		     key=1;
			 spec=0;
			 run_t.getNumbers_key++;
			 run_t.inputDeepSleep_times =0;
			  run_t.gTimer_8s=0;
             run_t.inputNewPwd_times=0;
         
		
		
	break;
			
	case KEY_8:
		
     	
		     key=1;
			 spec=0;
			 run_t.getNumbers_key++;
			 run_t.inputDeepSleep_times =0;
			  run_t.gTimer_8s=0;
          
             run_t.inputNewPwd_times=0;
          

		
   break;
			
	case KEY_9:
		
		  	 key=1;
		    spec=0;
		    run_t.getNumbers_key++;
		    run_t.inputDeepSleep_times =0;
			 run_t.gTimer_8s=0;
     
            run_t.inputNewPwd_times=0;
	         

		
	break;
		  

	}  

	
	  if(k2 != run_t.getNumbers_key && key==1 && spec ==0 && run_t.getNumbers_key !=0x40 &&run_t.NumbersKey_pressedNumbers==0){
				
				k2=run_t.getNumbers_key;
		      key = 0;
			   spec =1;

			   run_t.getSpecial_2_key++;
			   run_t.getSpecial_1_key++;

				run_t.BackLight=1;
				run_t.NumbersKey_pressedNumbers=1;
				run_t.Numbers_counter ++ ;
				run_t.buzzer_flag =1;
			
				 run_t.gTimer_8s=0;
		
				 run_t.passwordsMatch =0;
				 POWER_ON();

					temp = InputNumber_ToSpecialNumbers((TouchKey_Numbers) dat); //input Numbers
					if(run_t.Numbers_counter > 20) run_t.Numbers_counter =20;
					fvirtualPwd[run_t.Numbers_counter-1]=temp;
				
				    
					 
				     if(run_t.Numbers_counter < 7){//run_t.inputNewPasswordTimes

					  if(run_t.inputNewPasswordTimes ==0 && run_t.inputNewPassword_Enable ==1){//WT.EDIT 2022.10.14
					  	pwd2[run_t.Numbers_counter-1]=temp; //the first input new password .
					  }
	                  else  pwd1[run_t.Numbers_counter-1] =temp;
				     
				     }
	                  

				    
				
			  
			 run_t.gTimer_8s=0;
		     run_t.inputNewPwd_times=0;
     }


}

/****************************************************************************
*
*Function Name:void OpenLock(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
static void OpenLock(void)
{
   
	  static unsigned char value;
	  static uint32_t    ReadAddress; 
   
	// for(run_t.eepromAddress =0; run_t.eepromAddress <11;run_t.eepromAddress++){ //2022.10.07 be changed ten password 
	 
	
      while(run_t.eepromAddress <10){

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
                    run_t.eepromAddress =0;
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

		 
	   	}//run_t.eepromAddress
	   run_t.eepromAddress ++;
	 }//while(run_t.eepromAddress < 9);
   

}


void RunMotor_Definite_Handler(void) //definite motor
{

        static uint8_t led=0;
		uint8_t i;
		if(run_t.motor_doing_flag==1){//open lock doing

		
			    
				run_t.gTimer_8s =0;//WT.EDIT.2022.10.06
                
			    run_t.motorRunCount++;
				
				
				 if(run_t.motor_return_homePosition==0 ){
				 	run_t.motor_return_homePosition= 1; 
				    Buzzer_LongSound(); //WT.EDIT 2022.10.06
				    Motor_CCW_Run();//open passwordlock 
					  run_t.Led_OK_flag=1;
					 run_t.Led_ERR_flag =0;
				     run_t.buzzer_flag=0;
					 run_t.lock_fail=0;
					 ERR_LED_OFF();
				     OK_LED_ON();
					
					   run_t.Numbers_counter =0 ;
						 run_t.eepromAddress=0;
						 run_t.passwordsMatch = 0;
						
						 run_t.error_times=0;
						
						 run_t.gTimer_8s =0;//WT.EDIT.2022.10.06

						 run_t.returnHomePosition_Count=0;
						 run_t.password_unlock=0;
				 }
			     
				 if(run_t.motorRunCount>1500 && run_t.motorRunCount <2501){
					 Motor_Stop();
					 if(led==0){
					 	led++;
					    run_t.Led_OK_flag=0;
					 }
				 
					}
                  if(run_t.motorRunCount >2499){
				      run_t.motor_doing_flag=0;
				      run_t.motor_returnRun_flag =1;
				      led=0;
                  }
                  if(run_t.Led_OK_flag ==0) OK_LED_OFF();
				  else  OK_LED_ON();

          }
		
         /*--------motor return run back home position--------*/
		  if(run_t.motor_returnRun_flag ==1){
		
			run_t.returnHomePosition_Count++;
			if(run_t.motorRunCount >1499){
			    Motor_CW_Run();// Close
			    run_t.motorRunCount =0;
			}
			
			if(run_t.returnHomePosition_Count > 2498){
			     Motor_Stop();
				for(i=0;i<6;i++){ //WT.EDIT .2022.08.13

				*(pwd1+i) = 0;//pwd1[i]=0;
				*(Readpwd+i) =0; //Readpwd[i]=0;
                
	           }
				
				run_t.motor_return_homePosition=0;//WT.EDIT 2022.08.18
				run_t.motor_returnRun_flag =0;
                run_t.gTimer_8s =4;//WT.EDIT 2022.10.06
			}
		  }
}
