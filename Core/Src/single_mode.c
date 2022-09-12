#include "single_mode.h"
#include "run.h"
#include "led.h"
#include "touchkey.h"
#include "motor.h"
#include "buzzer.h"
#include "key.h"
 uint16_t KeyValue;

static void Save_To_EeepromNewPwd(void);



/*******************************************************
 * 
 * Function Name: void Start_PowerOn_Handler(void)
 * Function: start power on handler
 * INPUT Ref:NO
 * Return Ref:NO
 * 
********************************************************/
void Start_PowerOn_Handler(void)
{
  if(run_t.powerOn ==0){

			run_t.powerOn++;
			run_t.passwordsMatch =0;
			run_t.password_unlock =2;
			run_t.unLock_times=1;
			run_t.gTimer_2s=0;
			run_t.lowPower_flag=0; //low power flag
			POWER_ON();
        } 

}
/*******************************************************
 * 
 * Function Name: void Start_PowerOn_Handler(void)
 * Function: start power on handler
 * INPUT Ref:NO
 * Return Ref:NO
 * 
********************************************************/
void CheckPassword_Lock_Handler(void)
{
	 uint8_t i;
    if(run_t.passwordsMatch==0 && run_t.panel_lock==0){
		if(I2C_Read_From_Device(SC12B_ADDR,0x08,SC_Data,2)==DONE){
        // if(I2C_Simple_Read_From_Device(SC12B_ADDR,SC_Data,2) ==DONE){
			KeyValue =(uint16_t)(SC_Data[0]<<8) + SC_Data[1];
			RunCheck_Mode(KeyValue); 
            if(KeyValue ==0){

				run_t.SpecialKey_pressedNumbers=0;
				run_t.SpecialKey_pressedNumbers_2=0;
			    run_t.NumbersKey_pressedNumbers = 0;
				run_t.getSpecial_1_key++;
				run_t.getSpecial_2_key++;
				run_t.getNumbers_key=0x40;


            }
			  
			}
		}


    if(run_t.passwordsMatch ==1 && run_t.adminiId !=1 ){
		  
		  run_t.passwordsMatch=0;
          run_t.gTimer_8s=0;
          RunCommand_Unlock();

    }

	if(run_t.password_unlock==3){
	  	run_t.passwordsMatch=0  ;
		run_t.panel_lock=0;

	     Save_To_EeepromNewPwd();

      }
      else if(run_t.password_unlock==2){ //lock turn on Open 
		  //return to home position
		 //if(run_t.gTimer_2s ==2 && run_t.unLock_times==1 && run_t.Confirm == 0){
                   run_t.gTimer_8s =0;
				   POWER_ON();
				   if(run_t.gTimer_2s > 2){ //motor open stop times .
				   	   run_t.powerOn=2;
					   Motor_CW_Run();// Close 
					   HAL_Delay(530);//2010//(815);//WT.EDIT 2022.09.09
					   Motor_Stop();
					   run_t.unLock_times =0;
					   for(i=0;i<6;i++){ //WT.EDIT .2022.08.13
						  
					       *(pwd1+i) = 0;//pwd1[i]=0;
						    *(Readpwd+i) =0; //Readpwd[i]=0;

					   }

					  run_t.unLock_times=0;//WT.EDIT 2022.08.18
					  run_t.password_unlock=0;
                   }
                   run_t.gTimer_8s =0;
			
				  
	 }

}
/*******************************************************
 * 
 * Function Name:void Save_To_EeepromNewPwd(void)
 * Function: start power on handler
 * INPUT Ref:NO
 * Return Ref:NO
 * 
********************************************************/
static void Save_To_EeepromNewPwd(void)
{

	static uint8_t i;

     if(run_t.inputPwdTimes == 3 || run_t.inputPwdTimes ==1 ){
		//run_t.Numbers_counter=0;
		run_t.unLock_times =0;
		run_t.inputDeepSleep_times =0;
		run_t.BackLight =1;
		//run_t.inputPwdTimes=1;
		run_t.SaveEeprom_flag=1;

		if(run_t.inputPwdTimes ==1 &&  run_t.record_input_newpwd_times == 0){
			run_t.record_input_newpwd_times++;
			for(i=0;i<6;i++){ //WT.EDIT .2022.08.13
			*(pwd2 + i)=0;//pwd2[i]=0;

			*(pwd1+i)=0;//pwd1[i]=0;

		}
        }
	    else if(run_t.adminiId==1){
		 
		   SavePassword_To_EEPROM();
			
		}
		

     }
	

    
}


