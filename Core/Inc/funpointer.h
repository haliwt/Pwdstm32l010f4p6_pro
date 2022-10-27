#ifndef __FUNPOINTER_H_
#define __FUNPOINTER_H_
#include "main.h"

extern void(*Led_Working_Handler)(void);
extern void(*ReadPassword_Handler)(void);


void Led_Response_Handler(void(*led_doing_handler)(void));
void ReadPwd_Handler(void(*readpwd_mode)(void));

void CheckPassword_Suspend_Handler(void);

void TouchKey_Suspend_Handler(void);






#endif 
