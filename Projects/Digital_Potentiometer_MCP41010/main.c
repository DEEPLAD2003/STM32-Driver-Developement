#include "stm32f10x.h"
#include "MCP41010.h"
#include "stm32f10x_GPIO.h"
#include "stm32f10x_GPIO.h"
int main(void){
	float vol_1=5.0;
	float vol_2=7.4;
	float vol_3=12.0;
	Initialize_GPIO();
	DigiPots_SetVal(&vol_1,&vol_2,&vol_3);
}
