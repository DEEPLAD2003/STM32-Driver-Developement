#include "stm32f10x.h"
#include "stm32f10x_GPIO.h"
#include "RTC_Config.h"
int main(void){
	GPIO_Handle_t gpioled;
	gpioled.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_OUT2;
	gpioled.GPIO_PinConfig.GPIO_Config=GPIO_CNF_PP;
	gpioled.GPIO_PinConfig.GPIO_PinNumber=13;
	gpioled.pGPIOx=GPIOC;
	GPIO_PCLK_CRT(GPIOC,ENABLE);
	GPIO_Init(&gpioled);
	//GPIO_WriteToOutputPin(GPIOC,13,RESET_PIN);
	
	RTC_Time time;
	RTC_Date date;
	
	/////// setting initial time /////////////
	time.seconds=00;
	time.minutes=45;
	time.hours=3;
	/////// setting initial date //////////
	date.day=31;
	date.month=12;
	date.year=2023;
	
	RTC_Init();
	while(1){
		
		
		if(RTC->CNTL>0x20){
			GPIO_ToggleOutputPin(GPIOC,13);
			delay();
		}
		RTC_GetTime(&time);
		RTC_GetDate(&date);
	}
}
