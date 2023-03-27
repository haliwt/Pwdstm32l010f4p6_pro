#include "interrupt_manager.h"
#include "run.h"


/****************************************************************************
*
*Function Name:void HAL_TIM_PeriodElapsedHalfCpltCallback(TIM_HandleTypeDef *htim)
*Function : half -> 16bit, TIM2 timing time is 10ms 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

    static unsigned char t0;

	if(htim->Instance==TIM2){
  
    t0++;
    
	run_t.gTimer_200ms ++;
    if(t0>99){ //10*100 =1000ms "1s"
       t0=0;
	   
	  run_t.gTimer_10s_start++;
	   run_t.gTimer_1s ++;
	   
	   run_t.gTimer_8s++;
	   run_t.gTimer_10s ++;
	   run_t.gTimer_ADC ++;
	  
	   if(run_t.gTimer_10s_start>9){ //10s
		 run_t.gTimer_10s_start=0;
		 run_t.gTimer_input_error_times_60s++;
	     run_t.inputDeepSleep_times++;
		
	    

	   }
	
    }  

	}
}


