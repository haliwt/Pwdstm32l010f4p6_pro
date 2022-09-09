#include "key.h"
#include "main.h"
#include "gpio.h"
#include "run.h"
#include "led.h"
#include "buzzer.h"


key_types key;

/*******************************************************************************
    *
    * Function Name: void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
    * Function : Interrupt function call back 
    * Input Ref: GPIO_Pin��interrupt of GPIO of pin number
    * Return Ref: ��
    * ˵    ��: ��
    *
*******************************************************************************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
   // uint8_t key;
    
    if(GPIO_Pin == KEY_Pin){


	    __HAL_GPIO_EXTI_CLEAR_IT(KEY_Pin);
		 if(run_t.lowPower_flag < 2){
		 	run_t.lowPower_flag++;
		  	 SystemClock_Config();
			 HAL_ResumeTick();
		 }
	 

	}




    if(GPIO_Pin == SC12B_KEY_Pin){
   
       
    
     if(run_t.lowPower_flag  < 2){
	 	run_t.lowPower_flag++;
	  	 SystemClock_Config();

	 
	    HAL_ResumeTick();
	  	 
	  
      	}

	  __HAL_GPIO_EXTI_CLEAR_IT(SC12B_KEY_Pin);

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
		BACKLIGHT_2_ON();
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
				if(++key.on_time> 100) //1000  0.5us -> short time key
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
				if(++key.on_time>4500)// 9000 = 7s long key be down
				{
					
					key.value = key.value|0x80; //key.value = 0x01 | 0x80  =0x81  
					key.on_time = 0;
					key.state   = finish;
                  
                   
				}
			}
			else if(key.read == _KEY_ALL_OFF)  // loose hand 
			{
				if(++key.off_time>30) //30 don't holding key dithering
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
				if(++key.off_time>50)//50 //100
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
			    run_t.powerOn=2;
			   run_t.factory_test = 1;
			  run_t.gTimer_60s =0;
			  run_t.buzzer_flag =1;
			  POWER_ON();
             
			   
		   }
           else{
              run_t.getKey =0x01; // return 0x01;  //long key occur
			  run_t.retimes =0;
			  run_t.gTimer_8s=0;
		
		    
              BUZZER_KeySound();
             
		  }
      }
      if(keyvalue== 0x81){

        run_t.clearEeprom = 1;
        //BUZZER_KeySound();
       Buzzer_ShortSound();

      }




}

