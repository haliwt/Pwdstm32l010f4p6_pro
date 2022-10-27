#include "funpointer.h"
#include "single_mode.h"

void(*Led_Working_Handler)(void);
void Led_Response_Handler(void(*led_doing_handler)(void))
{
   Led_Working_Handler = led_doing_handler;

}








