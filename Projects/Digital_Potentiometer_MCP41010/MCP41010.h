#include "stm32f10x.h"

#define CMD_WRITE_DATA 	(uint8_t)0x11
#define CMD_SHDN				(uint8_t)0x21

void Initialize_GPIO(void);
void DigiPots_SetVal(float* vol_1,float* val2,float* val3);
void Digipot_All_ShutDown(void);
void Digipot_ShutDown_1(void);
void Digipot_ShutDown_2(void);
void Digipot_ShutDown_3(void);

