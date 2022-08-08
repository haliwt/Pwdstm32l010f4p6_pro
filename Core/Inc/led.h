#ifndef    __LED_H_
#define    __LED_H_
#include "main.h"


#define  BACKLIGHT_PGIO_PIN    		GPIO_PIN_1     
#define  BACKLIGHT_GPIO       		GPIOB


#define  BACKLIGHT_ON()         HAL_GPIO_WritePin(BACKLIGHT_GPIO,BACKLIGHT_PGIO_PIN,GPIO_PIN_SET)        // (PORTCbits.RC0= 1)
#define  BACKLIGHT_OFF()        HAL_GPIO_WritePin(BACKLIGHT_GPIO,BACKLIGHT_PGIO_PIN,GPIO_PIN_RESET)  ///  (PORTCbits.RC0 =0)


#define  BACKLIGHT_2_GPIO_PIN       GPIO_PIN_7
#define  BACKLIGHT_2_GPIO            GPIOA

#define  BACKLIGHT_2_ON()       HAL_GPIO_WritePin(BACKLIGHT_2_GPIO,BACKLIGHT_2_GPIO_PIN,GPIO_PIN_SET)//  (PORTCbits.RC3 = 1)
#define  BACKLIGHT_2_OFF()      HAL_GPIO_WritePin(BACKLIGHT_2_GPIO,BACKLIGHT_2_GPIO_PIN,GPIO_PIN_RESET)//  (PORTCbits.RC3 = 0)


#define BAT_LED_GPIO_PIN         GPIO_PIN_1 
#define BAT_LED_GPIO             GPIOA

#define  BAT_LED_ON()          HAL_GPIO_WritePin(BAT_LED_GPIO,BAT_LED_GPIO_PIN,GPIO_PIN_RESET)//  (PORTCbits.RC4 = 0)
#define  BAT_LED_OFF()         HAL_GPIO_WritePin(BAT_LED_GPIO,BAT_LED_GPIO_PIN,GPIO_PIN_SET) //  (PORTCbits.RC4 =1 )

#define OK_LED_GPIO_PIN      	 GPIO_PIN_2
#define OK_LED_GPIO          	 GPIOA

#define  OK_LED_ON()           HAL_GPIO_WritePin(OK_LED_GPIO,OK_LED_GPIO_PIN,GPIO_PIN_RESET) //(PORTAbits.RA1 = 0)
#define  OK_LED_OFF()          HAL_GPIO_WritePin(OK_LED_GPIO,OK_LED_GPIO_PIN,GPIO_PIN_SET)///   (PORTAbits.RA1 = 1)

#define  ERR_LED_GPIO_PIN     	GPIO_PIN_3
#define  ERR_LED_GPIO       	GPIOA


#define  ERR_LED_ON()          HAL_GPIO_WritePin(ERR_LED_GPIO,ERR_LED_GPIO_PIN,GPIO_PIN_RESET)//  (PORTAbits.RA0 =0)
#define  ERR_LED_OFF()         HAL_GPIO_WritePin(ERR_LED_GPIO,ERR_LED_GPIO_PIN,GPIO_PIN_SET)   //  (PORTAbits.RA0 =1)





//#define KEY1_RA2_GetValue()        //   PORTAbits.RA2
void DispLed_Fun(void);

#endif 

   