#include "dispatch.h"
#include "single_mode.h"
#include "run.h"
#include "led.h"
#include "touchkey.h"
#include "motor.h"
#include "buzzer.h"
#include "key.h"


void PasswordDispatch_Handler(void)
{
   
   switch(run_t.RunSequence){

      case 0:
          Start_PowerOn_Handler(); //power on 
          run_t.RunSequence = 1;

      break;

      case 1:  //check touch key
          CheckTouchKey_Press_Handler();
         if(run_t.password_unlock==2)
            run_t.RunSequence = 2;
         else
         	run_t.RunSequence = 1;

      break;

      case 2: //unlock 
		Unlocking_Hanlder();
	    run_t.RunSequence = 3;
      break;

      case 3: //check if has need set up new password ?
      	Setup_NewPassword_Handler();
      	run_t.RunSequence = 4;
      break;

      case 4: //motor return homeposition 
       void HomePosition_Locking_Pin_Handler();
       run_t.RunSequence = 1;

      break;

      default :

      break;

     }


}