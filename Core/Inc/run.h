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
	unsigned char passswordsMatch;
	unsigned char passsword_unlock;

	unsigned char factory_test;

	
	unsigned char gTimer_10s;
	unsigned char gTimer_2s;
	unsigned char gTimer_1s;
	unsigned char gTimer_8s;
	unsigned char gTimer_60s;

	uint32_t userId;
	
}RUN_T;


extern RUN_T run_t;


void RunCheck_Mode(unsigned int dat);
void RunCommand_Unlock(void);

//void Modidy_NewPassword_Function(void);
//unsigned char CompareValue(unsigned char *pt1,unsigned char *pt2);

void Buzzer_Sound(void);
void BackLight_Fun(void);

void SavePassword_To_EEPROM(void);
void ClearEEPRO_Data(void);
void CParserDispatch(void);










#endif 



