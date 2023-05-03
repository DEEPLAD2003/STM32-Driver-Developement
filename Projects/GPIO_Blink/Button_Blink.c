#include "stm32f10x_GPIO.h"
#include <string.h>
int main(void)
{	GPIO_Handle_t gpioled;
	gpioled.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_OUT2;
	gpioled.GPIO_PinConfig.GPIO_Config=GPIO_CNF_PP;
	gpioled.GPIO_PinConfig.GPIO_PinNumber=13;
	gpioled.pGPIOx=GPIOC;
	GPIO_PCLK_CRT(GPIOC,ENABLE);
	GPIO_Init(&gpioled);
	
	
	
	while(1){
		GPIO_WriteToOutputPin(GPIOC,13,SET_PIN);
		delay();
		GPIO_WriteToOutputPin(GPIOC,13,RESET_PIN);
		delay();
	}
}