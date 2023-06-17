#include "stm32f10x.h"
#include "stm32f10x_GPIO.h"
#include "lcd.h"
#include "stdio.h"
#include "string.h"
#include "RTC_Config.h"
void RTCAlarm_IRQHandler(void);
void RTCAlarm_IRQHandler(void){	
	GPIO_ToggleOutputPin(GPIOB,12);
}


int main(void){

	/* initializing the Buzzer pin for output of buzzer.*/
	/*GPIO_Handle_t buzzer;
	buzzer.pGPIOx=GPIOB;
	GPIO_PCLK_CRT(GPIOB,ENABLE);
	buzzer.GPIO_PinConfig.GPIO_PinNumber=12;
	buzzer.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_OUT50;
	buzzer.GPIO_PinConfig.GPIO_PinMode=GPIO_CNF_PP;
	GPIO_Init(&buzzer);
	
	
	RTC_Time time;
	lcd_init();
	RTC_Init();
	char time_buffer[14];
	lcd_display_clear();*/
	while(1){
		lcd_display_return_home();
		/*RTC_GetTime(&time,412110);
		sprintf(time_buffer,"TIME-%d:%d:%d",time.hours,time.minutes,time.seconds);
		lcd_print_string(time_buffer);*/
	}
}
