#include "run.h"
#include "eeprom.h"
#include "led.h"
#include "buzzer.h"
#include "motor.h"
#include "kmp.h"


#define ADMINI     		0x00 //0X00
#define USER_1     		0X08
#define USER_2     		0X10
#define USER_3     		0X18
#define USER_4    	 	0X20  
#define USER_5     		0X28
#define USER_6    	 	0X30
#define USER_7    	 	0X38  
#define USER_8     		0X40
#define USER_9     		0x48
#define USER_10    	 	0x50
#define USER_11         0x58

#define ADMIN_SAVE_ADD         0x80  //administrator of be save 
#define USER_SAVE_ADD_1        0X81
#define USER_SAVE_ADD_2        0x82


RUN_T run_t;

unsigned char Fail;
uint32_t readFlag[1]={0};
uint32_t pwd1[6];
uint32_t pwd2[6];
uint32_t initpwd[6]={1,2,3,4,0,0};
uint32_t virtualPwd[20];
uint32_t Readpwd[6];
 uint32_t eevalue ;
//typedef enum 
//{
//   SPECIAL_1 =0x4000,KEY_1=0x1000, KEY_2=0x400, KEY_3=0x100, KEY_4=0x40, KEY_5=0x10,
//   KEY_6= 0x8000, KEY_7=0x2000, KEY_8=0x800, KEY_9=0x200, KEY_0=0x80, SPECIAL_2=0x20
//
//}TouchKey_Numbers;

//new FPC board
typedef enum 
{
   SPECIAL_1 =0x8000,KEY_1=0x100, KEY_2=0x80, KEY_3=0x40, KEY_4=0x20, KEY_5=0x10,
   KEY_6= 0x4000, KEY_7=0x2000, KEY_8=0x1000, KEY_9=0x800, KEY_0=0x400, SPECIAL_2=0x200

}TouchKey_Numbers;



static unsigned char CompareValue(uint32_t *pt1,uint32_t *pt2);


static void ReadPassword_EEPROM_SaveData(void);


//static void Buzzer_Sound(void);
//static void  BackLight_Fun(void);

static unsigned char  InputNumber_ToSpecialNumbers(TouchKey_Numbers number);

/****************************************************************************
*
*Function Name:void Password_Modify(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
static unsigned char CompareValue(uint32_t *pt1,uint32_t *pt2)
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
   uint32_t initvalue =0x01;
 
   if(run_t.inputPwdTimes ==3){
	for(eeNumbers =0; eeNumbers< 12;eeNumbers++){

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
		
			run_t.userId = USER_10; 
		   break;

		   case 11:
		   	
		       run_t.userId = USER_11; 


		   case 12:
		   	  
				run_t.Confirm_newPassword =0; //to save new password of flag 
				run_t.adminiId =0;
				run_t.password_unlock=0;
				run_t.inputPwdTimes =0;
				
				run_t.lock_fail =1;
				run_t.Numbers_counter =0;
				run_t.passwordsMatch =0 ;
			

				//run_t.gTimer_8s=0;
				
			   return ;			
				
		   break;

		  }
        
        

		EEPROM_Read_Byte(run_t.userId,&run_t.readEepromData,1);
		HAL_Delay(10);
		if(run_t.readEepromData !=1){
	
             value =CompareValue(pwd1, pwd2);
			
			 if(value ==1){
			         EEPROM_Write_Byte(run_t.userId ,&initvalue,1);
					 HAL_Delay(10);
					 EEPROM_Write_Byte(run_t.userId + 0x01,pwd1,6);
					 HAL_Delay(100);

                    
					
					    run_t.gTimer_8s=10;
					    run_t.inputDeepSleep_times =10;
			
			    		run_t.adminiId =0;
			   			run_t.inputPwdTimes =0;
						run_t.password_unlock=0;//accomplish by save task//WT.EIDT 2022.09.12
						run_t.lock_fail =0;
						run_t.BackLight =2;
						run_t.Numbers_counter =0;
						 run_t.unLock_times =0;
				
					
						run_t.Confirm_newPassword =0;//WT.EIDT 2022.09.12
				
						run_t.runTimer_newpassword_16s = 3;
						Buzzer_LongSound();
                        
						return ;
					
			

			 }
			 else{
			 	

                        run_t.inputPwdTimes =0;
				  	    run_t.Confirm_newPassword =0;  //be save eeprom data flag bit
			    		run_t.adminiId =0;
						run_t.password_unlock=0;
						run_t.lock_fail =1;
						run_t.led_blank  =0;
						 run_t.unLock_times =0;
						run_t.Numbers_counter =0;
                      
					
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
   unsigned char temp, i;
  
   static unsigned char k0=0xff,k1=0xff,k2=0xff,key,spec;
 
   

    switch(dat){

	  

	case SPECIAL_1 ://0x40: //CIN1->'*'
		
       if(k0 != run_t.getSpecial_1_key){

	     
		
		  run_t.BackLight=1;
		  TouchKey_Led_Handler();
          HAL_Delay(100);

         if(dat == SPECIAL_1){
          k0 = run_t.getSpecial_1_key;
          spec=1;
		  run_t.SpecialKey_pressedNumbers =1;
		  run_t.buzzer_flag =1;
		
		   run_t.lock_fail=0;//WT.EDIT 2022.09.13
		  run_t.gTimer_8s=0;  //LED turn on holde times
		  run_t.getSpecial_2_key++;//n1++;
		  run_t.getNumbers_key++;//n2++;
		   POWER_ON();

		  if(run_t.inputPwdTimes ==2){
		        for(i=0;i<6;i++){
					  pwd2[i]=0;
				}
		 }
		 else{
	        for(i=0;i<6;i++){
		  	   pwd1[i]=0;
			   Readpwd[i]=0;
		
		  	}
		  
	        ERR_LED_OFF();
			spec=1;
		    run_t.lock_fail =0;
		   run_t.Numbers_counter =0 ;
		   run_t.passwordsMatch = 0;
		   run_t.runInput_newpwd_times =0;
		    
		  }
		}
       }
		
	break;

	

	 case SPECIAL_2://0x200: //CIN10 '#' ->confirm 
         if(k1 != run_t.getSpecial_2_key){
	      
			
		   run_t.BackLight=1;
		   TouchKey_Led_Handler();

		HAL_Delay(100);
		if(dat == SPECIAL_2){
			k1 = run_t.getSpecial_2_key;
			spec=1;
			run_t.SpecialKey_pressedNumbers_2 =1;
			if(run_t.Confirm_newPassword ==0){
				run_t.buzzer_flag =1;
				
            }
			else if(run_t.inputPwdTimes ==0){
				//run_t.buzzer_flag =1;
				run_t.buzzer_two_short = 1;
			}
			run_t.gTimer_8s=0;
			POWER_ON();

			if(run_t.Numbers_counter ==0){

			run_t.passwordsMatch = 0;
			run_t.gTimer_8s=0;
			}
		   else if(run_t.Numbers_counter < 4 && run_t.Numbers_counter >0 ){
			OK_LED_OFF();
			ERR_LED_ON();
			run_t.Numbers_counter=0;
			run_t.passwordsMatch = 0;
			run_t.error_times ++ ;
			run_t.lock_fail=1;
			run_t.fail_sound_flag=1;
			if(run_t.error_times > 4){ //OVER 5 error  times auto lock touchkey 60 s
			run_t.gTimer_60s =0;
			run_t.panel_lock=1;

			}

		   }
		   else{


			if( run_t.Confirm_newPassword ==1){
					run_t.inputPwdTimes ++ ;
					if(run_t.inputPwdTimes ==1){
						run_t.eepromAddress =0;  //administrator passwords 

					}
					else{
						run_t.record_input_newpwd_times=0;
						run_t.buzzer_two_short = 2;
					}

						run_t.passwordsMatch = 1;
						run_t.Numbers_counter=0;
						run_t.inputDeepSleep_times =0;
						run_t.gTimer_8s=0;
						run_t.runTimer_newpassword_16s =0 ;
						run_t.runInput_newpwd_times =0;
			}
			else if(run_t.unLock_times==0){ //lock return home position
				run_t.passwordsMatch = 1;
				run_t.inputPwdTimes=0; //08.13
				run_t.runInput_newpwd_times =0;
				run_t.inputDeepSleep_times =0;
			}

		}
	}  
         
	} 
		   
	 break;

	 
	case KEY_0:
		
     
		     key=1;
			 spec=0;
		    run_t.getNumbers_key++;
		     run_t.inputDeepSleep_times =0;
			 run_t.gTimer_8s=0;
     run_t.runTimer_newpassword_16s =0 ;
     run_t.runInput_newpwd_times =0;
	 
		

	 break;

    case KEY_1 :

	
     	
		     key=1;
			 spec=0;
		 run_t.getNumbers_key++;
			 run_t.inputDeepSleep_times =0;
			  run_t.gTimer_8s=0;
     run_t.runTimer_newpassword_16s =0 ;
     run_t.runInput_newpwd_times =0;
   	 
		
			
    case KEY_2:
         
     	
		     key=1;
		    spec=0;
		   run_t.getNumbers_key++;
		  run_t.inputDeepSleep_times =0;
	      run_t.gTimer_8s=0;
     run_t.runTimer_newpassword_16s =0 ;
     run_t.runInput_newpwd_times =0;
			
	case  KEY_3:
	
  
		     key=1;
			 spec=0;
			 run_t.getNumbers_key++;
			   run_t.inputDeepSleep_times =0;
			    run_t.gTimer_8s=0;
     run_t.runTimer_newpassword_16s =0 ;
     run_t.runInput_newpwd_times =0;
	
		
			
	case KEY_4:
			
     
		     key=1;
			 spec=0;
			 run_t.getNumbers_key++;
			  run_t.inputDeepSleep_times =0;
			   run_t.gTimer_8s=0;
             run_t.runTimer_newpassword_16s =0 ;
     		 run_t.runInput_newpwd_times =0;
			
	break;
			
	case KEY_5:
			
     
		     key=1;
			 spec=0;
			 run_t.getNumbers_key++;
			   run_t.inputDeepSleep_times =0;
			    run_t.gTimer_8s=0;
               run_t.runTimer_newpassword_16s =0 ;
               run_t.runInput_newpwd_times =0;
			
             

		
	break;
			
	case KEY_6:
		
    
		     key=1;
			 spec=0;
		  run_t.getNumbers_key++;
			  run_t.inputDeepSleep_times =0;
			   run_t.gTimer_8s=0;
            run_t.runTimer_newpassword_16s =0 ;
             run_t.runInput_newpwd_times =0;
		
		
	break;
	case KEY_7:
		
    
		     key=1;
			 spec=0;
			 run_t.getNumbers_key++;
			 run_t.inputDeepSleep_times =0;
			  run_t.gTimer_8s=0;
             run_t.runTimer_newpassword_16s =0 ;
              run_t.runInput_newpwd_times =0;
		
		
	break;
			
	case KEY_8:
		
     	
		     key=1;
			 spec=0;
			 run_t.getNumbers_key++;
			 run_t.inputDeepSleep_times =0;
			  run_t.gTimer_8s=0;
               run_t.runTimer_newpassword_16s =0 ;
                run_t.runInput_newpwd_times =0;
          

		
   break;
			
	case KEY_9:
		
		  	 key=1;
		     spec=0;
		      run_t.getNumbers_key++;
		     run_t.inputDeepSleep_times =0;
			  run_t.gTimer_8s=0;
               run_t.runTimer_newpassword_16s =0 ;
                run_t.runInput_newpwd_times =0;
	         

		
	break;
		  

	}  

	
	  if(k2 != run_t.getNumbers_key && key==1 && spec ==0 && run_t.getNumbers_key !=0x40 &&run_t.NumbersKey_pressedNumbers==0){
				
				run_t.BackLight=1;
				
				TouchKey_Led_Handler();

	            HAL_Delay(100);
	           if(dat == KEY_0 ||dat == KEY_1|| dat == KEY_2||dat == KEY_3||dat == KEY_4\
		          ||dat == KEY_5 || dat == KEY_6 || dat == KEY_7||dat == KEY_8||dat == KEY_9){
                k2=run_t.getNumbers_key;
		        key = 0;
			    spec =1;
				run_t.NumbersKey_pressedNumbers=1;
				run_t.Numbers_counter ++ ;
				run_t.buzzer_flag =1;
			
				 run_t.gTimer_8s=0;
		
				 run_t.passwordsMatch =0;
				 POWER_ON();
			     
				temp = InputNumber_ToSpecialNumbers((TouchKey_Numbers) dat); //input Numbers
				if(run_t.Numbers_counter > 20) run_t.Numbers_counter =20;
				virtualPwd[run_t.Numbers_counter-1]=temp;
			
			    
				 
			     if(run_t.Numbers_counter < 7){

				  if(run_t.inputPwdTimes ==2)pwd2[run_t.Numbers_counter-1]=temp;
                  else  pwd1[run_t.Numbers_counter-1] =temp;
			     
                  run_t.runTimer_newpassword_16s =0 ;
                  run_t.runInput_newpwd_times =0;

			    }
				
	  	}

			
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

     if(run_t.powerOn !=1){
		 if(run_t.Confirm_newPassword == 1)run_t.eepromAddress = 0;
		 ReadPassword_EEPROM_SaveData();
     }
	
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
			run_t.gTimer_60s =0;
			//run_t.gTimer_1s =0;
			run_t.panel_lock=1;
			    
		}
        run_t.Confirm_newPassword =0;
	    run_t.adminiId =0;
		 run_t.lock_fail=1;
	    run_t.fail_sound_flag=1;
	    if(run_t.inputPwdTimes ==2){
		        for(i=0;i<6;i++){
					  pwd2[i]=0;
				}
		 }
		 else{
	        for(i=0;i<6;i++){
		  	   pwd1[i]=0;
			   Readpwd[i]=0;
		
		  	}
		  }
		
	  }

	 if(run_t.password_unlock ==1){

         if(run_t.Confirm_newPassword ==1){ //prepare new password 
			run_t.adminiId =1;  //cofirm of administrator input password is correct.
           	 ERR_LED_OFF();
  
		   run_t.unLock_times = 0;
		  run_t.Numbers_counter =0 ;
		  run_t.eepromAddress=0;
		 run_t.passwordsMatch = 0;
		 run_t.password_unlock=3; //motor don't need run to moved .
		 run_t.gTimer_2s =0;
		 run_t.inputDeepSleep_times =0;
		 run_t.error_times=0;
		 run_t.lock_fail=0;
		  run_t.gTimer_8s =0;
		  run_t.lock_fail=0;
		
		}
		else{

		    if(run_t.unLock_times ==0 ){

			     run_t.unLock_times = 1;
			  
				 ERR_LED_OFF();
				 OK_LED_ON();
			     run_t.buzzer_flag=0;
				 run_t.lock_fail=0;
				 Buzzer_LongSound();
				 Motor_CCW_Run();//open passwordlock 
				 HAL_Delay(2100);//__delay_ms(2100);//(800);
				 Motor_Stop();
             
				  run_t.Numbers_counter =0 ;
				  run_t.eepromAddress=0;
				 run_t.passwordsMatch = 0;
				 run_t.password_unlock=2;
				 run_t.error_times=0;
				 run_t.gTimer_8s =4;
				 run_t.lock_fail=0;
				 run_t.gTimer_2s =0;
				 run_t.inputDeepSleep_times =0;
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
static void ReadPassword_EEPROM_SaveData(void)
{
     
	  static unsigned char value ;
     // uint32_t Readpwd[6];
	//  static uint32_t  eevalue ;
	  static uint32_t    ReadAddress;

	 for(run_t.eepromAddress =0; run_t.eepromAddress <12;run_t.eepromAddress++){
	  
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
				 
					  ReadAddress = USER_10;
				   break;
	
				 case 11:
					// ReadAddress = USER_11;
				
				   Fail = 1;
				   return ;
				break;
	
		   }

      
	   if(run_t.eepromAddress <11){
	   	   if(run_t.Confirm_newPassword == 1){ //set save new password flag bit by administrator open lock
                ReadAddress = ADMINI;
           }
		    EEPROM_Read_Byte(ReadAddress,readFlag,1);
		    HAL_Delay(5);
		   if(readFlag[0] ==1){// has a been saved pwassword 

					EEPROM_Read_Byte(ReadAddress + 0X01,Readpwd,6);
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
						return ;

					}
					else{
						if(run_t.Confirm_newPassword ==1){
                            readFlag[0]=0;
						   Fail = 1;
							return ;
						}
						//n_t.eepromAddress++ ;	
					}

			}
			else{ //don't has a null space ,don't has password

			     if(ReadAddress == ADMINI){

				    
                    if(run_t.Numbers_counter > 6){
 
                        value = BF_Search(virtualPwd,initpwd);
					}
					else
					    value =CompareValue(initpwd, pwd1);

				     if(value==1){
									   
						run_t.password_unlock=1;	
					
						return ;

					}
					else{

					     Fail = 1;
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
static unsigned char  InputNumber_ToSpecialNumbers(TouchKey_Numbers number)
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




