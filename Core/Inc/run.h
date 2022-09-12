#ifndef __RUN_H_
#define __RUN_H_
#include "main.h"


enum Signal {                   /* enumeration for CParser signals */
     TOUCH_KEY_SIG,IN_NUMBER_SIG,  ZERO_SIG
};


enum State {                     /* enumeration for CParser states */
   INPUTKEY, MODIFYPSWD, EXIT
};


typedef struct __RUN_T{
	//enum State state_;
    //unsigned char cmdCtr_;   //event order cunter

    unsigned char powerOn;
	unsigned char getKey_saveNewPwd_flag;
	uint8_t   getTouchkey;
	uint8_t   getSpecial_1_key;
	uint8_t   getSpecial_2_key;
	uint8_t   getNumbers_key;
	uint8_t   RunSequence;
	uint8_t    runTimer_newpassword_16s;
	uint8_t  record_input_newpwd_times;
	uint8_t  runInput_newpwd_times;
	
	
	
	unsigned char adminiId;
	unsigned char Confirm_newPassword;
	unsigned char inputPwdTimes;

	unsigned char unLock_times;
    unsigned char error_times;
	unsigned char panel_lock;
	unsigned char lock_fail;
	unsigned char led_blank ;
	unsigned char inputDeepSleep_times;
	unsigned char clearEeprom;
    
    unsigned char eepromAddress;
    
    
    
    
	unsigned char BackLight;
	unsigned char buzzer_flag;
	uint8_t buzzer_two_short;
	unsigned char Numbers_counter;
	unsigned char passwordsMatch;
	unsigned char password_unlock;

	unsigned char factory_test;
	uint8_t lowPower_flag;
    uint8_t SpecialKey_pressedNumbers;
	uint8_t SpecialKey_pressedNumbers_2;
	uint8_t NumbersKey_pressedNumbers;

	

	
	unsigned char gTimer_10s;
	unsigned char gTimer_2s;
	unsigned char gTimer_1s;
	unsigned char gTimer_8s;
	unsigned char gTimer_60s;
	unsigned char gTimer_ADC;
	uint8_t gTimes_s;

	uint32_t userId;
    uint32_t readEepromData;
	
}RUN_T;


extern RUN_T run_t;
extern uint32_t pwd1[6];
extern uint32_t pwd2[6];
extern uint32_t Readpwd[6];





void RunCheck_Mode(uint16_t dat);
void RunCommand_Unlock(void);


void SavePassword_To_EEPROM(void);

void CParserDispatch(void);












#endif 



