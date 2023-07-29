#include "main.h"
#include "stm32f10x_GPIO.h"
#include "stm32f10x_SPI.h"
#include <string.h>
/*
*		MOSI --> PA7
*		MISO --> PA6
*		SCLK --> PA5
*		NSS  --> PA4
*/
void SPI1_GPIOInits(void){
	GPIO_Handle_t gpio_spi;
	gpio_spi.pGPIOx=GPIOA;
	gpio_spi.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_OUT50;
	gpio_spi.GPIO_PinConfig.GPIO_Config=GPIO_CNF_AFPP;
	//MOSI
	gpio_spi.GPIO_PinConfig.GPIO_PinNumber=7;
	GPIO_Init(&gpio_spi);
	//SCLK
	gpio_spi.GPIO_PinConfig.GPIO_PinNumber=5;
	GPIO_Init(&gpio_spi);
	//NSS
	gpio_spi.GPIO_PinConfig.GPIO_Config=GPIO_CNF_PP;
	gpio_spi.GPIO_PinConfig.GPIO_PinNumber=4;
	GPIO_Init(&gpio_spi);
	
}
SPI_Handle_t SPI1Handle;

void SPI1_Inits(void){
	SPI1Handle.pSPIx=SPI1;
	SPI1Handle.SPIConfig.SPI_DeviceMode=SPI_DEVICE_MODE_MASTER;
	SPI1Handle.SPIConfig.SPI_BusConfig=SPI_BUS_CONFIG_TXONLY;
	SPI1Handle.SPIConfig.SPI_SclkSpeed=SPI_CLK_SPEED_DIV64;
	SPI1Handle.SPIConfig.SPI_DFF=SPI_DFF_16BITS;
	SPI1Handle.SPIConfig.SPI_CPOL=SPI_CPOL_LOW;
	SPI1Handle.SPIConfig.SPI_CPHA=SPI_CPHA_LOW;
	SPI1Handle.SPIConfig.SPI_SSM=SPI_SSM_ENABLE;
	SPI1Handle.SPIConfig.SPI_MultiMaster=SPI_MULTI_MSTR_DIS;
	SPI1Handle.SPIConfig.SPI_Transmission_Format=SPI_DATA_TRANS_MSB;
	SPI_Init(&SPI1Handle);
}


int main(void){
	char data[]="Heet Depani";
	SPI1_GPIOInits();
	GPIO_WriteToOutputPin(GPIOA,4,RESET);
	SPI1_Inits();
	SPI_EN_DIS(SPI1,ENABLE);
	GPIO_WriteToOutputPin(GPIOA,4,SET);
	SPI_Send_Data_HD(&SPI1Handle,(uint8_t*)data,strlen(data));
	GPIO_WriteToOutputPin(GPIOA,4,RESET);
	SPI_EN_DIS(SPI1,DISABLE);
	delay();
}
