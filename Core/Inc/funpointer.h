#ifndef __FUNPOINTER_H_
#define __FUNPOINTER_H_
#include "main.h"

extern void(*Led_Working_Handler)(void);
void Led_Response_Handler(void(*led_doing_handler)(void));





#endif 
