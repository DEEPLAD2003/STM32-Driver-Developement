#include "stm32f10x.h"
#include "stm32f10x_GPIO.h"
int main(){
	RCC->CFGR|=RCC_CFGR_MCO_HSI;
	GPIO_Handle_t mco;
	GPIO_PCLK_CRT(GPIOA,ENABLE);
	mco.pGPIOx=GPIOA;
	mco.GPIO_PinConfig.GPIO_Config=GPIO_CNF_AFPP;
	mco.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_OUT50;
	mco.GPIO_PinConfig.GPIO_PinNumber=8;
	GPIO_ToggleOutputPin(GPIOA,8);
	GPIO_Init(&mco);
	//while(1);
}

