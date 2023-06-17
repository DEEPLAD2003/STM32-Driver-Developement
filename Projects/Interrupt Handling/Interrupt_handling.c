#include "stm32f10x_GPIO.h"
void EXTI9_5_IRQHandler(void);
void EXTI9_5_IRQHandler(void){
	delay();
	GPIO_IRQHandling(6);
	for (int i=0;i<10;i++){
		delay();
		GPIO_ToggleOutputPin(GPIOC,13);
	}
}
int main(void){
	GPIO_Handle_t interrupt_btn;
	interrupt_btn.pGPIOx=GPIOA;
	interrupt_btn.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_IN;
	interrupt_btn.GPIO_PinConfig.GPIO_Config=GPIO_CNF_PUPD;
	interrupt_btn.GPIO_PinConfig.GPIO_PinNumber=6;
	GPIO_PCLK_CRT(GPIOA,ENABLE);
	GPIO_Init(&interrupt_btn);
	EXTI->IMR|=(1<<6);
	//Interrupt handling
	GPIO_InterrupConfig(GPIOA,6,GPIO_TRIG_RISING);
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI9_5,ENABLE);
	//GPIO_IRQPriorityConfig(IRQ_NO_EXTI9_5,15);
	
	GPIO_Handle_t gpio_led;
	gpio_led.pGPIOx=GPIOC;
	gpio_led.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_OUT50;
	gpio_led.GPIO_PinConfig.GPIO_Config=GPIO_CNF_PP;
	gpio_led.GPIO_PinConfig.GPIO_PinNumber=13;
	GPIO_PCLK_CRT(GPIOC,ENABLE);
	GPIO_Init(&gpio_led);
	while (1){
	}
}
