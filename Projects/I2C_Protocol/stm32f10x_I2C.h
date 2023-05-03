#ifndef INC_STM32F103XX_SPI_H_
#define INC_STM32F103XX_SPI_H_
#include <stm32f10x.h>
#include "stm32f10x_GPIO.h"
//******************Macros for I2C Pheripheral***********************//
//I2C PERIPHERAL CLOCK ENABLE MACROS 
#define I2C1_PERI_CLK 		       21
#define I2C2_PERI_CLK 		       22
#define I2C_PERI_ENABLE					 0
#define I2C1_PERI_RST 		       21
#define I2C2_PERI_RST 		       22

/*
****************************Configurable items for User Application*****************************
			1. I2C_SCL Speed
			2. I2C_Device Address
			3. I2C_AckControl
			4. I2C_FMDutyCycle
*/
typedef struct{
	uint32_t I2C_SCL_Speed;
	uint8_t I2C_Device_ADDR;
	uint32_t I2C_AckControl;
	uint32_t I2C_FM_DutyCycle;
}I2C_Config_t;

typedef struct{
	 I2C_Config_t I2C_Config;
	 I2C_TypeDef  *pI2C;
}I2C_Handle_t;



/*********************************************************************************
*												API's supported by the driver
*						For more information check the function definition
***********************************************************************************/
/*
* API to get the peripheral Clock value.*/
uint32_t RCC_GET_PERI_VAL(uint8_t peri);
/*
*	Enabling/Disabling I2C Peripheral.
*/
void I2C_ENABLE_OR_DISABLE(I2C_TypeDef *pI2Cx,uint8_t EnorDi);

/*
*		Peripheral clock Setup.
*/
void I2C_PCLK_CRT(I2C_TypeDef *pI2Cx,uint8_t EnorDi);

/*
*		Initializing I2C peripheral
*/
void I2C_Init(I2C_Handle_t *pI2CHandle);

/*
*		Deinitalizing I2C peripheral
*/
void I2C_Dinit(I2C_TypeDef *pI2Cx);

/*
*		Data send and Recieve
*/



/*
*		IRQ Configuration and ISR Handling.
*/
void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void I2C_Handling(SPI_TypeDef *pHandle);






#endif





