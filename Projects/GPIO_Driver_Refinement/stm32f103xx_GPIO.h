#include "stm32f10x.h"

/*
	Pin Mode and Configuration Macros
*/

#define GPIO_MODE_IN 						      0x00 
#define GPIO_MODE_OUT_10HZ 			      0x01
#define GPIO_MODE_OUT_2HZ				      0x02
#define GPIO_MODE_OUT_50HZ 			      0x03

#define GPIO_CNF_IN_ANALOG			      0x00
#define GPIO_CNF_IN_FLT					      0x01
#define GPIO_CNF_IN_PU       (uint8_t)0x12	/* Set ODR bit 1 for Pull Up   */
#define GPIO_CNF_IN_PD       (uint8_t)0x02	/* Set ODR bit 0 for Pull Down */
#define GPIO_CNF_OUT_PP					      0x00		
#define GPIO_CNF_OUT_OD					      0x01
#define GPIO_CNF_OUT_ALTPP			      0x02
#define GPIO_CNF_OUT_ALTOD			      0x03

typedef struct{
	uint8_t Pin_Number;
	uint8_t  Mode;		/* (INPUT or OUTPUT). Speed(Slew Rate of waveform) can be set by selecting appropriate "Mode Macro". */
	uint8_t  Config;	/* {(INPUT -> Analog, Pull Up/Down, Floating),(OUTPUT -> General Purpose    : Push Pull, Open Drain  */
}GPIO_Pin_Config_t;	/*																									-> Alternate Function : Push Pull, Open Drain )} */
	


typedef struct{
	GPIO_TypeDef* GPIOx;
	GPIO_Pin_Config_t Pin_Config;
}GPIO_Handle_t;

void GPIO_PCLK_CNF(GPIO_TypeDef* GPIOx,uint8_t State);
void GPIO_Init(GPIO_Handle_t gpiox);
void GPIO_Deinit(GPIO_Handle_t gpiox);
void GPIO_Write_Pin(GPIO_TypeDef* GPIOx,uint8_t Pin_Number,uint8_t State);
uint8_t GPIO_Read_Pin(GPIO_TypeDef* GPIOx,uint8_t Pin_Number);
void Delay(void);
