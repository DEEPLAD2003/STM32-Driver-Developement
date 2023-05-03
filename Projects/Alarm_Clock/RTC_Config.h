#include "stm32f10x.h"
#include "stdint.h"


/*Structure for getting time in HH:MM:SS format*/
typedef struct{
	uint32_t hours;
	uint32_t minutes;
	uint32_t seconds;
}RTC_Time;

/*Structure for getting time in HH:MM:SS format*/
typedef struct{
	uint32_t hours;
	uint32_t minutes;
	uint32_t seconds;
}RTC_Date;

/* APIS */
void RTC_Init(void);
void RTC_GetTime(RTC_Time *time);
