#include "stm32f10x.h"
#include "stm32f10x_GPIO.h"
#include "RTC_Config.h"
void RTCAlarm_IRQHandler(void); 
void RTCAlarm_IRQHandler(void){
	EXTI->PR|=EXTI_PR_PR17;
	for(int i=0; i<10;i++){
		delay();
		GPIO_ToggleOutputPin(GPIOC,13);
	}
	RTC->CRL&=~RTC_CRL_ALRF;
	
}

int main(void){
	GPIO_Handle_t gpioled;
	gpioled.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_OUT50;
	gpioled.GPIO_PinConfig.GPIO_Config=GPIO_CNF_PP;
	gpioled.GPIO_PinConfig.GPIO_PinNumber=13;
	gpioled.pGPIOx=GPIOC;
	GPIO_PCLK_CRT(GPIOC,ENABLE);
	GPIO_Init(&gpioled);
	
	RTC_Time time;
	RTC_Date date;
	
	/////// setting initial time /////////////
	time.seconds=41;
	time.minutes=10;
	time.hours=2;
	/////// setting initial date //////////
	date.day=1;
	date.month=4;
	date.year=1999;
	
	RTC_Init();

	//////// Setting Alarm with Interrupt /////////////////
	Enable_Alarm();
	RTC_AlarmInterrupt(ENABLE);
	RTC_SetAlarm(0,0,5);	
	while(1){
		RTC_GetTime(&time);
		RTC_GetDate(&date);
	}
}
