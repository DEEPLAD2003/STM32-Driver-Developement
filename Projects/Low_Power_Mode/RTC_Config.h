#include "stm32f10x.h"
#include "stdint.h"


/*Structure for getting time in HH:MM:SS format*/
typedef struct{
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
}RTC_Time;

/*Structure for getting time in HH:MM:SS format*/
typedef struct{
	uint32_t year;
	uint32_t month;
	uint32_t day;
}RTC_Date;

/* APIS */
void RTC_Init(void);
void RTC_GetTime(RTC_Time *time,uint32_t initial_count);
void RTC_GetDate(RTC_Date *date);
void RTC_SetAlarm(uint8_t hour,uint8_t minutes,uint8_t seconds);
uint8_t Leap_Year(uint8_t year);
