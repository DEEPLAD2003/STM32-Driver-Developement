#include "stm32f10x.h"
///////////////////API's for PVD///////////////////
void PVD_Enable(uint8_t status, float threshold);
void PVD_Interrupt_Config(uint8_t status);