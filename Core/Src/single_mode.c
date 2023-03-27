#include "single_mode.h"
#include "run.h"
#include "led.h"
#include "touchkey.h"
#include "motor.h"
#include "buzzer.h"
#include "key.h"
#include "delay.h"
#include "funpointer.h"
 uint16_t KeyValue;

static void Save_To_EeepromNewPwd(void);
static void UnLock_Aand_SaveData_Handler(void);

void (*TouchKey_Handler)(void);


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
    
	if(HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin) ==0   && run_t.powerOn ==0){
	              run_t.powerOn++;
				  run_t.factory_test = 1;
			      run_t.gTimer_10s_start=0;
				  run_t.gTimer_input_error_times_60s =0;
				  run_t.buzzer_flag =1;
				  POWER_ON();
				  run_t.backlight_label  = BACKLIGHT_FACTORY_LED;
	  
	  }
	 else{
	 	if(run_t.powerOn ==0){

					run_t.powerOn++;
					run_t.passwordsMatch =0;
					run_t.password_unlock =4; // 4: power on is motor 1/4 angle
					run_t.motor_return_homePosition=0; //
					run_t.gTimer_8s=0;
				
					run_t.lowPower_flag=0; //low power flag
				
					POWER_ON();
					BACKLIGHT_ON();
					BUZZER_KeySound();//WT.EDIT 2022.09.12
		           
		  } 
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
	static  uint16_t temValue;
    if(run_t.touchkey_first_turn_on_led==0 && run_t.panel_lock ==0){//wake up touch key
                 
				
		if(run_t.gTimer_200ms > 10){//10*10=100 WT.EDIT 2022.12.12 //50*10ms = 500ms
		    run_t.gTimer_200ms=0;
				 	
			if(I2C_Read_From_Device(SC12B_ADDR,0x08,SC_Data,2)==DONE){
       
			     temValue =(uint16_t)(SC_Data[0]<<8) + SC_Data[1];
				 if(temValue !=0){
					BACKLIGHT_ON();
					run_t.touchkey_first_turn_on_led=1;
					run_t.readI2C_data =1;
					run_t.normal_works_state = 1;
					 

				 }
				
			}
		 }
    }
	
    if(run_t.passwordsMatch==0 && run_t.panel_lock==0 && run_t.readI2C_data ==1 && run_t.factory_test ==0){
	  TouchKey_Handler();
     }


   if(run_t.passwordsMatch ==1 && run_t.inputNewPassword_Enable==0 ){
		  
		  run_t.passwordsMatch=0;
		  if(run_t.login_in_success ==0) //WT.EDIT 2022.10.31
             run_t.gTimer_8s=0;
          RunCommand_Unlock();
    }
	UnLock_Aand_SaveData_Handler();

}

/**************************************************************************
	*
	*Funtcion Name:static void UnLock_Aand_SaveData_Handler(void)
	*Function : to special action process 
	*Input Ref: NO
	*Return Ref:NO
	*
**************************************************************************/
static void UnLock_Aand_SaveData_Handler(void)
{
   
	switch(run_t.password_unlock){


	case 3: //SaveData to EEPROM //new password for the first input 
        run_t.passwordsMatch=0  ;

	   Save_To_EeepromNewPwd();
    break;

	
	case 4: //Power On motor run 1/4 angle
	  
         Motor_CW_Run();// Close 
		 HAL_Delay(530);//WT.EDIT 2022.09.19
		 Motor_Stop();
		 run_t.motor_return_homePosition=0;//WT.EDIT 2022.08.18
		 run_t.password_unlock=0;
	     run_t.gTimer_8s=0;
		 Panel_LED_Off();
	

	break;

    case 5: // over times ten numbers posswords 
		run_t.gTimer_8s=0;
		run_t.Confirm_newPassword =0; //to save new password of flag 

		run_t.password_unlock=0;
		run_t.inputNewPasswordTimes =0;

		
		run_t.Numbers_counter =0;
		run_t.passwordsMatch =0 ;
		run_t.buzzer_flag =0;//WT.EDIT 2022.10.06	

		run_t.fail_sound_flag=1; //WT.EDIT 2022.10.06	
		run_t.saveEEPROM_fail_flag =1; //WT.EDIT 2022.10.06	
		run_t.clear_inputNumbers_newpassword=0;//WT.EDIT 2022.10.14

		run_t.Confirm_newPassword =0; //WT.EDIT 2022.09.28
		run_t.inputNewPassword_Enable =0; //W

		//led control led
		run_t.lock_fail =1;   //input new password is error
		run_t.backlight_label = BACKLIGHT_ERROR_BLINK;

    break;

	default :

	break;

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

	
	
	 if(run_t.inputNewPassword_Enable ==1 && run_t.inputNewPasswordTimes !=1 ){//WT.EDIT .2022.09.28.if(run_t.adminiId==1){
		
		   SavePassword_To_EEPROM();
			
	 }
	run_t.motor_return_homePosition=0;
	run_t.inputDeepSleep_times =0;
	
	
}
/*******************************************************
 * 
 * Function Name:void TouchKey(void)
 * Function: start power on handler
 * INPUT Ref:NO
 * Return Ref:NO
 * 
********************************************************/
void TouchKey(void)
{
	 if(I2C_Read_From_Device(SC12B_ADDR,0x08,SC_Data,2)==DONE){
         //if(I2C_Simple_Read_From_Device(SC12B_ADDR,SC_Data,2) ==DONE){
			
             KeyValue =(uint16_t)(SC_Data[0]<<8) + SC_Data[1];
				RunCheck_Mode(KeyValue); 
	            if(KeyValue ==0){

	            run_t.NumbersKey_pressedNumbers = 0;
	            run_t.getSpecial_1_key++;
	            run_t.getSpecial_2_key++;
	            run_t.getNumbers_key=0x40;

            }
	     
			  
	 }
}

void TouchKey_Run_Handler(void (*touchkey_huandler)(void))
{

	TouchKey_Handler=touchkey_huandler;

}



