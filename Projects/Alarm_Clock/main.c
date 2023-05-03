#include "stm32f10x.h"
#include "stm32f10x_GPIO.h"
#include "lcd.h"
#include "RTC_Config.h"
int main(void){
	lcd_init();
	RTC_Init();
	lcd_display_clear();
	lcd_display_return_home();
	lcd_print_char(0x31);
	
	
	/*while(1){
		lcd_display_clear();
		lcd_display_return_home();
		uint32_t h=(RTC->CNTL/3600);

		uint32_t *hours=&h;
	//	uint32_t *minutes=(RTC->CNTL%3600)/60;
		//uint32_t *seconds=minutes%6;
		lcd_print_string("TIME - ");
		lcd_print_string(&hours);
		//lcd_print_string(&minutes);
		//lcd_print_string(&seconds);
		delay();
	}*/
}
