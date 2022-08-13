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
	unsigned char getKey;
	uint8_t   getTouchkey;
	uint8_t   getSpecial_1_key;
	uint8_t   getSpecial_2_key;
	uint8_t   getNumbers_key;
	
	
	
	unsigned char adminiId;
	unsigned char Confirm;
	unsigned char inputPwdTimes;

	unsigned char unLock_times;
    unsigned char error_times;
	unsigned char panel_lock;
	unsigned char lock_fail;
	unsigned char led_blank ;
	unsigned char retimes;
	unsigned char clearEeprom;

    unsigned char eepromAddress;
	unsigned char BackLight;
	unsigned char buzzer_flag;
	unsigned char Numbers_counter;
	unsigned char passwordsMatch;
	unsigned char password_unlock;

	unsigned char factory_test;

	

	
	unsigned char gTimer_10s;
	unsigned char gTimer_2s;
	unsigned char gTimer_1s;
	unsigned char gTimer_8s;
	unsigned char gTimer_60s;
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



