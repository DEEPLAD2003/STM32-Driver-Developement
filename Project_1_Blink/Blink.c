#include "stm32f10x_GPIO.h"
void delay(void);
void delay(void){
		for (int i=0;i<1000000;i++);
}
int main(void)
{	GPIO_Handle_t gpioled;
	gpioled.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_OUT50;
	gpioled.GPIO_PinConfig.GPIO_Config=GPIO_CNF_PP;
	gpioled.GPIO_PinConfig.GPIO_PinNumber=13;
	gpioled.pGPIOx=GPIOC;
	GPIO_PCLK_CRT(GPIOC,ENABLE);
	GPIO_Init(&gpioled);
	
	GPIO_Handle_t button;
	button.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_IN;
	button.GPIO_PinConfig.GPIO_Config=GPIO_CNF_PUPD;
	button.GPIO_PinConfig.GPIO_PinNumber=6;
	button.pGPIOx=GPIOA;
	GPIO_PCLK_CRT(GPIOA,ENABLE);
	GPIO_Init(&button);
	
	while(1){
		GPIO_WriteToOutputPin(GPIOC,13,SET_PIN);
		delay();
		GPIO_WriteToOutputPin(GPIOC,13,RESET_PIN);
		delay();
	}
}

