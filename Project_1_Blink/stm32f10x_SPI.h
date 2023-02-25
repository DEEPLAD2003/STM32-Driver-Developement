#ifndef INC_STM32F103XX_SPI_H_
#define INC_STM32F103XX_SPI_H_

#include "stm32f10x.h"
/*
*		Configurable items for SPIx peripheral.
*/
typedef struct{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
}SPI_Config_t;

/*
*		Handle Structrue for SPIx peripheral.
*/
typedef struct{
	SPI_Config_t  SPIConfig;
	SPI_TypeDef  *pSPIx;
}SPI_Handle_t;


/*
*	Macros for SPI Device Mode
*/
#define SPI_DEVICE_MODE_MASTER   		1
#define SPI_DEVICE_MODE_SLAVE   		0

/*
*	Macros for SPI Bus Configuration
*/
#define SPI_BUS_CONFIG_FD						1
#define SPI_BUS_CONFIG_HD						2
#define SPI_BUS_CONFIG_RXONLY				3

/*
*	Macros for SPI Clock Configuration
*/
#define SPI_CLK_SPEED_DIV2						0
#define SPI_CLK_SPEED_DIV4						1
#define SPI_CLK_SPEED_DIV8						2
#define SPI_CLK_SPEED_DIV16						3
#define SPI_CLK_SPEED_DIV32						4
#define SPI_CLK_SPEED_DIV64						5
#define SPI_CLK_SPEED_DIV128					6
#define SPI_CLK_SPEED_DIV256					7

/*
*	Macros for SPI Data Frame Format (DFF)
*/
#define SPI_DFF_8BITS			0
#define SPI_DFF_16BITS		1

/*
*	Macros for SPI Clock Polarity(CPOL)
*/
#define SPI_CPOL_HIGH 		1
#define SPI_CPOL_LOW 			0

/*
*	Macros for Clock Phase(CPHA)
*/
#define SPI_CPHA_HIGH 		1
#define SPI_CPHA_LOW 			0

/*
*	Macros for SPI Software Select Management - (SSM)
*/
#define SPI_SSM_DISABLE				0
#define SPI_SSM_ENABLE 				1

/*
*	Macros for SPI Slave Select Management - (SSM)
*/
#define SPI_SSI_DISABLE				0
#define SPI_SSI_ENABLE 				1

/*********************************************************************************
*												API's supported by the driver
*						For more information check the function definition
***********************************************************************************/

/*
*	Enabling/Disabling SPI Peripheral.
*/
void SPI_ENABLE_OR_DISABLE(SPI_TypeDef *pSPIx,uint8_t EnorDi);

/*
*		Peripheral clock Setup.
*/
void SPI_PCLK_CRT(SPI_TypeDef *pSPIx,uint8_t EnorDi);

/*
*		Initializing SPI peripheral
*/
void SPI_Init(SPI_Handle_t *pSPIHandle);

/*
*		Deinitalizing SPI peripheral
*/
void SPI_Dinit(SPI_TypeDef *pSPIx);

/*
*		Data send and Recieve
*/
void SPI_SendData(SPI_TypeDef *pSPIx,uint8_t *pTxBuffer,uint32_t Len);
void SPI_ReadData(SPI_TypeDef *pSPIx,uint8_t *pRxBuffer,uint32_t Len);

/*
*		IRQ Configuration and ISR Handling.
*/
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_Handling(SPI_TypeDef *pHandle);

/*
*	SSI Configuration
*/
void SPI_SSI_Config(SPI_TypeDef *pSPIx,uint8_t EnorDi);

#endif
