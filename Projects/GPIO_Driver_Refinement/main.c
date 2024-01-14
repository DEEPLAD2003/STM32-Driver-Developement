#include "stm32f103xx_GPIO.h"
int main(void){
	GPIO_Handle_t gpio_led;
	gpio_led.Pin_Config.Pin_Number=13;
	gpio_led.Pin_Config.Mode=GPIO_MODE_IN;
	gpio_led.Pin_Config.Config=GPIO_CNF_IN_PU;
	gpio_led.GPIOx=GPIOC;
	GPIO_Init(gpio_led);
	GPIO_Deinit(gpio_led);
//	RCC->APB2RSTR|=RCC_APB2RSTR_IOPCRST;
//	RCC->APB2RSTR&=~RCC_APB2RSTR_IOPCRST;
	GPIO_Init(gpio_led);
	
}
