#ifndef __SINGLE_MODE_
#define   __SINGLE_MODE_
#include "main.h"


extern void (*TouchKey_Handler)(void);
void Start_PowerOn_Handler(void);
void CheckPassword_Lock_Handler(void);

void CheckTouchKey_Press_Handler(void);

void TouchKey_Run_Handler(void (*touchkey_huandler)(void));

void TouchKey(void);

void TouchKey_Only_Buzzer(void);


#endif 

