#include "key.h"
#include "main.h"
#include "gpio.h"
#include "run.h"
#include "led.h"
#include "buzzer.h"


key_types key;
uint8_t buzzertimes;

/*******************************************************************************
    *
    * Function Name: void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
    * Function : Interrupt function call back 
    * Input Ref: GPIO_Pin：interrupt of GPIO of pin number
    * Return Ref: 无
    * 说    明: 无
    *
*******************************************************************************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
   static  uint8_t touchkey=0xff;
    
    if(GPIO_Pin == KEY_Pin){


	    __HAL_GPIO_EXTI_CLEAR_IT(KEY_Pin);
		do{
		 	run_t.lowPower_flag++;
		  	 SystemClock_Config();
			 HAL_ResumeTick();
			 run_t.inputDeepSleep_times =0;
			 	POWER_ON();
			run_t.readI2C_data =1;//WT.EDIT 2022.09.26
			run_t.touchkey_first_turn_on_led =0;//WT.EDIT 2022.09.26
		
	    }while(run_t.lowPower_flag==0);

	}

   if(GPIO_Pin == SC12B_KEY_Pin){
   
      __HAL_GPIO_EXTI_CLEAR_IT(SC12B_KEY_Pin);//WT.EDIT 2022.09.09
      do{//if(run_t.lowPower_flag  < 3){  //WT.EDIT 2022.09.09
	 	 run_t.lowPower_flag++;
	  	 SystemClock_Config();
         HAL_ResumeTick();
	  	 run_t.inputDeepSleep_times =0;
	  	 POWER_ON();
		 if(touchkey != run_t.touchkey_first){
		 	  touchkey = run_t.touchkey_first;
	          run_t.touchkey_first_turn_on_led =1;
		      run_t.readI2C_data =0;//WT.EDIT 2022.09.26
			  run_t.gTimer_200ms=0;
		 }
      	}while(run_t.lowPower_flag ==0);
   }

	 
  }
    
/*******************************************************************************
    *
    * Function Name: unsigned char  Scan_Key(void)
    * Function : state machine of key 
    * Input Ref: NO
    * Return Ref: key of value 
    *
*******************************************************************************/
uint8_t Scan_Key(void)
{
  unsigned char   reval = 0;
  key.read = _KEY_ALL_OFF; //0x1F 
   if(HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin) ==0 )
	{
		key.read &= ~0x01; // 0x1f & 0xfe =  0x1E
		POWER_ON();
		TouchKey_Led_Handler();//BACKLIGHT_2_ON();
	}
	
	
	switch(key.state )
	{
		case start:
		{
			if(key.read != _KEY_ALL_OFF)
			{
				key.buffer   = key.read; //??:key.buffer = 0x1E  POWER KEY 
				key.state    = first;
				key.on_time  = 0;
				key.off_time = 0;
           
                
			}
			break;
		}
		case first: //shot key times 
		{
			if(key.read == key.buffer) // adjust key be down 
			{
				if(++key.on_time> 100 && ++key.on_time < 500) //1000  0.5us -> short time key
				{
					key.value = key.buffer^_KEY_ALL_OFF; // key.value = 0x1E ^ 0x1f = 0x01, com = 0x0E ^ 0x1f = 0x11
					key.on_time = 0;
                    key.state   = second;
                   
                    
				}
			}
			else
			{
				key.state   = start;
			}
			break;
		}
		case second: //long key times 
		{
			if(key.read == key.buffer) //again adjust key if be pressed down 
			{
				if(++key.on_time>2000)// 9000 = 7s long key be down
				{
					
					//key.value = key.value|0x80; //key.value = 0x01 | 0x80  =0x81  
					key.on_time = 0;
					key.state   = finish;
					do{
                        buzzertimes++;
                        BUZZER_KeySound();//Buzzer_ShortSound(); //WT.EDIT 2022.10.05
                        BUZZER_OFF(); 
                        HAL_Delay(300);
                       if(HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin) ==1){
                         buzzertimes=0;
                         return 0;
                       }

                    }while(buzzertimes < 11);
                    if(buzzertimes > 9){
                        buzzertimes=0;
                        BUZZER_KeySound();//Buzzer_ShortSound();
                        BUZZER_OFF(); 
                        HAL_Delay(100);
                        BUZZER_KeySound();//Buzzer_ShortSound();
                        BUZZER_OFF(); 
                       // key.value = key.value|0x80;
                        while(HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin) ==0);
                         key.value = key.value|0x80;
                    }

                   
			  }
			}
			else if(key.read == _KEY_ALL_OFF)  // loose hand 
			{
				if(++key.off_time>5) //30 don't holding key dithering
				{
					key.value = key.buffer^_KEY_ALL_OFF; // key.value = 0x1E ^ 0x1f = 0x01
					
					key.state   = finish; // loose hand,shot time be pressed 
				}
			}
		   
			break;
		}
		case finish:
		{
			
			reval = key.value; // is short time  TIMER_KEY = 0x01  2. long times TIMER_KEY = 0X81
			key.state   = end;
         
			break;
		}
		case end:
		{
			if(key.read == _KEY_ALL_OFF)
			{
				if(++key.off_time>5)//50 //100
				{
					key.state   = start;
                  
				}
			}
			break;
		}
		default:
		{
			key.state   = start;
         
			break;
		}
	}
	return  reval;


}


/*******************************************************
 * 
 * Function Name: void  SideKey_Fun(uint8_t keyvalue)
 * Function: 
 * INPUT Ref:NO
 * Return Ref:NO
 * 
********************************************************/
void  SideKey_Fun(uint8_t keyvalue)
{
	 if(keyvalue == 0x01){
               
		  if(run_t.powerOn ==1 || run_t.powerOn==0){
		  	   run_t.gTimer_8s=5;
			   run_t.powerOn=2;
			  run_t.factory_test = 1;
		      run_t.gTimer_10s_start=0;
			  run_t.gTimer_input_error_times_60s =0;
			  run_t.buzzer_flag =1;
			  POWER_ON();
             
			   
		   }
           else{
           	
                 run_t.runTimer_newpassword_16s =0;
			     run_t.Confirm_newPassword = 1;
           
			
                run_t.inputDeepSleep_times =0;
			  run_t.gTimer_8s=0;
			  run_t.buzzer_flag =1;//WT.EDIT 2022.10.06
		
		     // BUZZER_KeySound();//Buzzer_ShortSound();//WT.EDIT 2022.10.05
             
		  }

		   
      }
      if(keyvalue== 0x81){

        run_t.clearEeprom = 1;
		run_t.inputDeepSleep_times =0;
    

      }




}

