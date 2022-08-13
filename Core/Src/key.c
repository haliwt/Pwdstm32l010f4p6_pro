#include "key.h"
//#include "buzzer.h"
#include "gpio.h"
#include "run.h"
#include "led.h"

key_types key;

static uint8_t KEY_LongPress(void);

static uint8_t KEY_ShortPress(void);

static uint8_t SC12B_TouchKey_ShortPress(void);

//unsigned char  Scan_Key(void);

/*******************************************************************************
    *
    * Function Name: static uint8_t KEY_LongPress(void)
    * Function : detected SC12B touch key 
    * Input Ref: GPIO_Pin：interrupt of GPIO of pin number
    * Return Ref: Touchkey of key value   
    *
*******************************************************************************/
static uint8_t KEY_LongPress(void)
{
    
	uint32_t downCnt = 0; //Recorde be pressed of times
    uint8_t  upCnt =0;    //Recorde be release of times

   while(1){

  // HAL_Delay(20);--> don't input interrupt process

   if(HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin)==0){
   	
       downCnt++; //Recored be pressed KEY tinmes
       upCnt =0;
        run_t.gTimes_s++;
	   if(downCnt > 50){

          // BACKLIGHT_2_ON();
          // ClearEEPRO_Data();
          // run_t.passwordsMatch =0;
          // run_t.password_unlock = 0;
           // BACKLIGHT_2_OFF();
           
		   return 0x81;  //long key occur

	   }
	  
	  
   }
   else {

       upCnt ++ ;   //release to key times
       if(upCnt > 5){
         return 0;

	   }



   }
  }


}

static uint8_t KEY_ShortPress(void)
{
    
	uint16_t downCnt = 0; //Recorde be pressed of times
    uint8_t  upCnt =0;    //Recorde be release of times

   while(1){

   //HAL_Delay(20); -> is bug

   if(HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin)==0){
   	
       downCnt++; //Recored be pressed KEY tinmes
       upCnt =0;


	   if(downCnt> 1 && downCnt < 30){

	       if(run_t.powerOn ==2){
		   	   run_t.powerOn ++;
			   run_t.factory_test = 1;
			  run_t.gTimer_60s =0;
			  return 0;
			   
		   }
           else
		       return 0x01;  //long key occur

	   }
	  
	  
   }
   else {

       upCnt ++ ;   //release to key times
       if(upCnt > 4){
         return 0;

	   }



   }
  }


}
/*******************************************************************************
    *
    * Function Name: uint8_t SC12B_TouchKey_ShortPress(void)
    * Function : detected SC12B touch key 
    * Input Ref: GPIO_Pin：interrupt of GPIO of pin number
    * Return Ref: Touchkey of key value 
    * 说    
    *
*******************************************************************************/
static uint8_t SC12B_TouchKey_ShortPress(void)
{
	 
	uint8_t downCnt = 0; //Recorde be pressed of times
    uint8_t  upCnt =0;    //Recorde be release of times

   while(1){

   //HAL_Delay(10);

   if(HAL_GPIO_ReadPin(SC12B_KEY_GPIO_Port,SC12B_KEY_Pin)==1){
   	
       downCnt++; //Recored be pressed KEY tinmes
       upCnt =0;


	   if(downCnt > 1){

	       ERR_LED_OFF();
		   return 0x01;  //has touch key be pressed

	   }
	  
	  
   }
   else {

       upCnt ++ ;   //release to key times
       if(upCnt > 5){
         return 0;

	   }



   }
   }



}
//中断服务函数

  

//void EXTI4_15_IRQHandler(void)
//{
//  //  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);		//调用中断处理公用函数
//    HAL_GPIO_EXTI_IRQHandler(KEY_Pin);
//    HAL_GPIO_EXTI_IRQHandler(SC12B_KEY_Pin);
//}

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
   // uint8_t key;
    
    if(GPIO_Pin == KEY_Pin){
   

//	     if(run_t.password_unlock==2 || run_t.powerOn==2){
//		 	
//		 	  run_t.getKey= KEY_ShortPress();
//		 }
//		  else{
//	      //if(HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin)==0)
//		  	    run_t.clearEeprom = KEY_LongPress();
//		  }


//		  key = Scan_Key();
//		  if(key == 0x01){
//               
//			 if(run_t.powerOn ==2){
//		   	   run_t.powerOn ++;
//			   run_t.factory_test = 1;
//			  run_t.gTimer_60s =0;
//			  return ;
//			   
//		   }
//           else
//		     run_t.getKey == 0x01; // return 0x01;  //long key occur
//		  }

//		  if(key == 0x81){

//            run_t.clearEeprom = 1;


//		  }
	  
	  
  
    
   }
   if(GPIO_Pin == SC12B_KEY_Pin){
      __HAL_GPIO_EXTI_CLEAR_IT(SC12B_KEY_Pin); 
    
      run_t.getTouchkey = SC12B_TouchKey_ShortPress();
    
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
#if 1
uint8_t Scan_Key(void)
{
  unsigned char   reval = 0;
  key.read = _KEY_ALL_OFF; //0x1F 
   if(HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin) ==0 )
	{
		key.read &= ~0x01; // 0x1f & 0xfe =  0x1E
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
				if(++key.on_time> 300) //1000  0.5us -> short time key
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
				if(++key.on_time>9000)// 100000 = 7s long key be down
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


#endif 


