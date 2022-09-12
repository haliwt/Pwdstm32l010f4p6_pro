#ifndef __BUZZER_H_
#define __BUZZER_H_
//#include "main.h"


#define BEEP_GPIO_Pin            GPIO_PIN_6
#define BEEP_GPIO_Port           GPIOA


#define BUZZER_OFF()     HAL_GPIO_WritePin(BEEP_GPIO_Port , BEEP_GPIO_Pin , GPIO_PIN_RESET)


void BUZZER_KeySound(void);


void Buzzer_LongSound(void);

void Buzzer_High_Sound(void);
void Buzzer_ReSound(void);

void Buzzer_ShortSound(void);
void Buzzer_Off(void);

#endif 
