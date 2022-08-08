#include "led.h"

void BackLight_Fun(void);

void DispLed_Fun(void)
{
          BackLight_Fun();
		  Buzzer_Sound();
		  if(run_t.clearEeprom==1){
			   run_t.gTimer_8s =0;
			   run_t.retimes =10;
			   run_t.led_blank = 1;
			  run_t.clearEeprom = 0;
			  ClearEEPRO_Data();
			  Buzzer_LongSound();
			 
		  }
 
			 
   
 
	   if(run_t.panel_lock ==1){
		  run_t.gTimer_1s =10;
			 ERR_LED_OFF();
			 BACKLIGHT_2_OFF();
			 BACKLIGHT_OFF();
			 
		   if(run_t.gTimer_60s > 59){
			   run_t.panel_lock =0;
			   run_t.error_times = 0;
 
		   }
 
 
	   }


}

/****************************************************************************
*
*Function Name:void BackLight_Fun(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void BackLight_Fun(void)
{
     static unsigned char cnt,endcnt;

	 if(run_t.BackLight ==1 ){

			
		      BACKLIGHT_ON() ;
	          BACKLIGHT_2_ON();
		    
	}

	 if(run_t.BackLight ==2 ){

          OK_LED_OFF();
		  BACKLIGHT_OFF() ;
	      BACKLIGHT_2_OFF();

	 }

	if(run_t.gTimer_8s >8){
		run_t.BackLight =0;
		run_t.lock_fail=0;
		run_t.gTimer_8s=0;
		BACKLIGHT_OFF() ;
        BACKLIGHT_2_OFF();
		OK_LED_OFF();
		ERR_LED_OFF();
		run_t.led_blank =0;
	
        if(run_t.retimes > 5){
			 run_t.retimes =0;
	         run_t.adminiId =0;  //after a period of time auto turn off flag
			 run_t.Confirm = 0; //after a period of time auto turn off flag
			 run_t.passsword_unlock=0;
			 run_t.unLock_times =0;
			 run_t.Confirm =0 ;
        }


	}

	if(run_t.lock_fail==1){
		 cnt ++ ;
		 
        OK_LED_OFF();

	
        if(cnt < 120 ){

		    ERR_LED_ON();
			
		}
		else if(cnt > 120 && cnt < 240)
	        ERR_LED_OFF();

		if(cnt>239) cnt = 0;

	}
   


	if( run_t.adminiId==1 || run_t.led_blank  ==1){

	   cnt ++ ;
	   run_t.lock_fail=0;

	       
		if(run_t.retimes < 5 ){ //120s
			 run_t.gTimer_8s=0;
			
				
		}
      
        if(cnt < 99 ){

		    OK_LED_ON();
			
		}
		else if(cnt>99 && cnt < 201)
	        OK_LED_OFF();

		if(cnt>200)cnt = 0;
		
	}

	if(run_t.factory_test ==1){
		run_t.getKey = 0;

	    BACKLIGHT_ON() ;
        BACKLIGHT_2_ON();
		OK_LED_ON();
		ERR_LED_ON();
		BAT_LED_ON();

	  if(run_t.gTimer_60s > 60){
          run_t.getKey = 0;
	      run_t.factory_test =0;
	      BAT_LED_OFF();


	  }



	}

}



