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
	uint8_t   getTouchkey;
	uint8_t   getSpecial_1_key;
	uint8_t   getSpecial_2_key;
	uint8_t   getNumbers_key;
	uint8_t   RunSequence;
	uint8_t   repeat_key_flag; 


  
	uint8_t  saveEEPROM_fail_flag ; //WT.EDIT 2022.10.06	
	uint8_t  eeprom_Reset_flag;
	uint8_t  clearEeeprom_count;
	
	
	
	unsigned char Confirm_newPassword;
	unsigned char inputNewPasswordTimes;

	unsigned char motor_return_homePosition;
    unsigned char error_times;
	unsigned char panel_lock;
	unsigned char lock_fail;
	unsigned char led_blank ;
	unsigned char inputDeepSleep_times;
	unsigned char clearEeprom;
    
    unsigned char eepromAddress;
    uint8_t ADC_times;
	
	uint8_t fail_sound_flag;
	uint8_t touchkey_first_turn_on_led;
	uint8_t touchkey_first;
	uint8_t readI2C_data;
    uint8_t inputNewPassword_Enable;
	uint8_t buzzer_longsound_flag;
    uint8_t clear_inputNumbers_newpassword;
	uint8_t inputNewPwd_times;
    
    
	unsigned char BackLight;
	unsigned char buzzer_flag;
	uint8_t buzzer_two_short;
	unsigned char Numbers_counter;
	unsigned char passwordsMatch;
	unsigned char password_unlock;
    

	unsigned char factory_test;
	uint8_t lowPower_flag;
    uint8_t SpecialKey_pressedNumbers;
	
	uint8_t NumbersKey_pressedNumbers;

	uint8_t clearEeeprom_done;
	uint8_t normal_works_state ;
	uint8_t input_newPassword_over_number;
	uint8_t stop_gTimer_8s;

	

	uint8_t gTimer_200ms;
	unsigned char gTimer_10s;
	unsigned char gTimer_1s;
	unsigned char gTimer_8s;
	unsigned char gTimer_60s;
	unsigned char gTimer_ADC;
	
	uint8_t  gTimer_input_error_times_60s;
	uint8_t gTimes_s;
	uint8_t gTimer_10s_start;
	uint8_t gTimer_motor_transience_100ms;

	uint16_t motorRunCount;
	uint16_t   returnHomePosition_Count;

	uint32_t userId;
    uint32_t readEepromData;
	
}RUN_T;


extern RUN_T run_t;
extern uint32_t pwd1[6];
extern uint32_t pwd2[6];
extern uint32_t Readpwd[6];




extern void (*RunChed_KeyMode)(uint16_t keydat);
void RunCheck_Mode(uint16_t dat);
void RunCommand_Unlock(void);


void SavePassword_To_EEPROM(void);

void CParserDispatch(void);


void RunCheck_KeyMode_Handler(void(*keymode_handler)(uint16_t keydat));

void ReadPassword_EEPROM_SaveData(void);







#endif 



