#include "stm32f10x_GPIO.h"
#include "stm32f10x_SPI.h"
#include <string.h>
/*
*		MOSI --> PB5
*		MISO --> PB4
*		SCLK --> PB3
*		NSS  --> PA15
*/

void SPI1_GPIOInits(void){
	GPIO_Handle_t gpio_spi;
	gpio_spi.pGPIOx=GPIOB;
	gpio_spi.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_OUT50;
	gpio_spi.GPIO_PinConfig.GPIO_Config=GPIO_CNF_AFPP;
	//MOSI
	gpio_spi.GPIO_PinConfig.GPIO_PinNumber=5;
	GPIO_Init(&gpio_spi);
	//MISO
	//gpio_spi.GPIO_PinConfig.GPIO_PinNumber=4;
	//GPIO_Init(&gpio_spi);
	//SCLK
	gpio_spi.GPIO_PinConfig.GPIO_PinNumber=3;
	GPIO_Init(&gpio_spi);
	//NSS
	//gpio_spi.pGPIOx=GPIOA;
	//gpio_spi.GPIO_PinConfig.GPIO_PinNumber=15;
	GPIO_Init(&gpio_spi);
}
void SPI1_Inits(void){
	SPI_Handle_t SPI1Handle;
	SPI1Handle.pSPIx=SPI1;
	SPI1Handle.SPIConfig.SPI_SclkSpeed=SPI_CLK_SPEED_DIV8;
	SPI1Handle.SPIConfig.SPI_CPOL=SPI_CPOL_LOW;
	SPI1Handle.SPIConfig.SPI_CPHA=SPI_CPHA_LOW;
	SPI1Handle.SPIConfig.SPI_DFF=SPI_DFF_8BITS;
	SPI1Handle.SPIConfig.SPI_SSM=SPI_SSM_ENABLE;
	SPI1Handle.SPIConfig.SPI_DeviceMode=SPI_DEVICE_MODE_MASTER;
	SPI1Handle.SPIConfig.SPI_BusConfig=SPI_BUS_CONFIG_FD;
	SPI_Init(&SPI1Handle);
}


int main(void){
	//User data or buffer
	char data[]="Hello World";
	// Initializing the GPIO pin for SPI.
	SPI1_GPIOInits();
	// Configuringing the SPI pheripheral
	SPI1_Inits();
	SPI_SSI_Config(SPI1,ENABLE);
	//Enable the SPI Peripheral
	SPI_ENABLE_OR_DISABLE(SPI1,ENABLE);
	//Sending the Data
	SPI_SendData(SPI1,(uint8_t*)data,sizeof(data));
	//Disable the SPI Peripheral
	//SPI_ENABLE_OR_DISABLE(SPI1,DISABLE);
	while(1);
	
}
