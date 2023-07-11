#include "stm32f10x.h"
#include "MCP41010.h"
#include "stm32f103xx_spi.h"
#include "stm32f10x_GPIO.h"
void Initialize_GPIO(void){
	/*
	Data and Clock Pins
	|---- MOSI	A7 ----|---- MISO	A6 ----|---- CLK	A5 ----|
	
	Chip Select Pins
	|---- CS1		A1 ----|---- CS2	A2----|----	CS3		A3 ----|
	*/
	GPIO_Handle_t mosi,clk,cs;
	mosi.pGPIOx=GPIOA;
	clk.pGPIOx=GPIOA;
	cs.pGPIOx=GPIOA;
	GPIO_PCLK_CRT(GPIOA,ENABLE);
	
	mosi.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_OUT50;
	mosi.GPIO_PinConfig.GPIO_Config=GPIO_CNF_AFPP;
	mosi.GPIO_PinConfig.GPIO_PinNumber=7;
	GPIO_Init(&mosi);
	
	clk.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_OUT50;
	clk.GPIO_PinConfig.GPIO_Config=GPIO_CNF_AFPP;
	clk.GPIO_PinConfig.GPIO_PinNumber=5;
	GPIO_Init(&clk);
	
	cs.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_OUT50;
	cs.GPIO_PinConfig.GPIO_Config=GPIO_CNF_PP;
	cs.GPIO_PinConfig.GPIO_PinNumber=0;
	GPIO_Init(&cs);
	cs.GPIO_PinConfig.GPIO_PinNumber=2;
	GPIO_Init(&cs);
	cs.GPIO_PinConfig.GPIO_PinNumber=1;
	GPIO_Init(&cs);
}

void DigiPots_SetVal(float* vol_1,float* vol_2,float* vol_3){
	uint8_t val_1=255-318.79/(*vol_1-1.25);
	uint8_t val_2=255-318.79/(*vol_2-1.25);
	uint8_t val_3=255-318.79/(*vol_3-1.25);
	
	GPIO_WriteToOutputPin(GPIOA,0,RESET);
	GPIO_WriteToOutputPin(GPIOA,2,RESET);
	GPIO_WriteToOutputPin(GPIOA,1,RESET);
	SPI_PeriClockControl(SPI1,ENABLE);
	SPI_Handle_t digi_pot;
	digi_pot.pSPIx=SPI1;
	digi_pot.spiconf.CPHA=SPI_CPHA_Dn;
	digi_pot.spiconf.CPOL=SPI_CPOL_Dn;
	digi_pot.spiconf.BaudRate=SPI_BRR_Fpclk_128;
	digi_pot.spiconf.DFF=SPI_DFF_8;
	digi_pot.spiconf.Mode=SPI_MODE_Master;
	digi_pot.spiconf.SlvManage=SPI_SlvManage_Soft;
	uint8_t command=CMD_WRITE_DATA;
	SPI_Init(&digi_pot);
	
	
	SPI_Enable(SPI1,ENABLE);
	GPIO_WriteToOutputPin(GPIOA,0,SET);
	SPI_SendData(SPI1,&command,1);
	SPI_SendData(SPI1,&val_1,1);
	delay();
	SPI_Enable(SPI1,DISABLE);
	GPIO_WriteToOutputPin(GPIOA,0,RESET);
	
	delay();
	
	SPI_Enable(SPI1,ENABLE);
	GPIO_WriteToOutputPin(GPIOA,1,SET);
	SPI_SendData(SPI1,&command,1);
	SPI_SendData(SPI1,&val_2,1);
	delay();
	SPI_Enable(SPI1,DISABLE);
	GPIO_WriteToOutputPin(GPIOA,1,RESET);
	
	delay();
	
	SPI_Enable(SPI1,ENABLE);
	GPIO_WriteToOutputPin(GPIOA,2,SET);
	SPI_SendData(SPI1,&command,1);
	SPI_SendData(SPI1,&val_3,1);
	delay();
	SPI_Enable(SPI1,DISABLE);
	GPIO_WriteToOutputPin(GPIOA,2,RESET);
}

void Digipot_All_ShutDown(void){
	uint8_t val_1=0x00;
	uint8_t val_2=0x00;
	uint8_t val_3=0x00;
	GPIO_WriteToOutputPin(GPIOA,0,RESET);
	GPIO_WriteToOutputPin(GPIOA,2,RESET);
	GPIO_WriteToOutputPin(GPIOA,1,RESET);
	SPI_PeriClockControl(SPI1,ENABLE);
	SPI_Handle_t digi_pot;
	digi_pot.pSPIx=SPI1;
	digi_pot.spiconf.CPHA=SPI_CPHA_Dn;
	digi_pot.spiconf.CPOL=SPI_CPOL_Dn;
	digi_pot.spiconf.BaudRate=SPI_BRR_Fpclk_128;
	digi_pot.spiconf.DFF=SPI_DFF_8;
	digi_pot.spiconf.Mode=SPI_MODE_Master;
	digi_pot.spiconf.SlvManage=SPI_SlvManage_Soft;
	uint8_t command=CMD_SHDN;
	SPI_Init(&digi_pot);
	
	SPI_Enable(SPI1,ENABLE);
	GPIO_WriteToOutputPin(GPIOA,0,SET);
	SPI_SendData(SPI1,&command,1);
	SPI_SendData(SPI1,&val_1,1);
	delay();
	SPI_Enable(SPI1,DISABLE);
	GPIO_WriteToOutputPin(GPIOA,0,RESET);
	
	delay();
	
	SPI_Enable(SPI1,ENABLE);
	GPIO_WriteToOutputPin(GPIOA,1,SET);
	SPI_SendData(SPI1,&command,1);
	SPI_SendData(SPI1,&val_2,1);
	delay();
	SPI_Enable(SPI1,DISABLE);
	GPIO_WriteToOutputPin(GPIOA,1,RESET);
	
	delay();
	
	SPI_Enable(SPI1,ENABLE);
	GPIO_WriteToOutputPin(GPIOA,2,SET);
	SPI_SendData(SPI1,&command,1);
	SPI_SendData(SPI1,&val_3,1);
	delay();
	SPI_Enable(SPI1,DISABLE);
	GPIO_WriteToOutputPin(GPIOA,2,RESET);
}

void Digipot_ShutDown_1(void){
	uint8_t val_1=0x00;
	GPIO_WriteToOutputPin(GPIOA,0,RESET);
	SPI_PeriClockControl(SPI1,ENABLE);
	SPI_Handle_t digi_pot;
	digi_pot.pSPIx=SPI1;
	digi_pot.spiconf.CPHA=SPI_CPHA_Dn;
	digi_pot.spiconf.CPOL=SPI_CPOL_Dn;
	digi_pot.spiconf.BaudRate=SPI_BRR_Fpclk_128;
	digi_pot.spiconf.DFF=SPI_DFF_8;
	digi_pot.spiconf.Mode=SPI_MODE_Master;
	digi_pot.spiconf.SlvManage=SPI_SlvManage_Soft;
	uint8_t command=CMD_SHDN;
	SPI_Init(&digi_pot);
	
	SPI_Enable(SPI1,ENABLE);
	GPIO_WriteToOutputPin(GPIOA,0,SET);
	SPI_SendData(SPI1,&command,1);
	SPI_SendData(SPI1,&val_1,1);
	delay();
	SPI_Enable(SPI1,DISABLE);
	GPIO_WriteToOutputPin(GPIOA,0,RESET);
}
void Digipot_ShutDown_2(void){
	uint8_t val_1=0x00;
	GPIO_WriteToOutputPin(GPIOA,1,RESET);
	SPI_PeriClockControl(SPI1,ENABLE);
	SPI_Handle_t digi_pot;
	digi_pot.pSPIx=SPI1;
	digi_pot.spiconf.CPHA=SPI_CPHA_Dn;
	digi_pot.spiconf.CPOL=SPI_CPOL_Dn;
	digi_pot.spiconf.BaudRate=SPI_BRR_Fpclk_128;
	digi_pot.spiconf.DFF=SPI_DFF_8;
	digi_pot.spiconf.Mode=SPI_MODE_Master;
	digi_pot.spiconf.SlvManage=SPI_SlvManage_Soft;
	uint8_t command=CMD_SHDN;
	SPI_Init(&digi_pot);
	
	SPI_Enable(SPI1,ENABLE);
	GPIO_WriteToOutputPin(GPIOA,1,SET);
	SPI_SendData(SPI1,&command,1);
	SPI_SendData(SPI1,&val_1,1);
	delay();
	SPI_Enable(SPI1,DISABLE);
	GPIO_WriteToOutputPin(GPIOA,1,RESET);
}
void Digipot_ShutDown_3(void){
uint8_t val_1=0x00;
	GPIO_WriteToOutputPin(GPIOA,2,RESET);
	SPI_PeriClockControl(SPI1,ENABLE);
	SPI_Handle_t digi_pot;
	digi_pot.pSPIx=SPI1;
	digi_pot.spiconf.CPHA=SPI_CPHA_Dn;
	digi_pot.spiconf.CPOL=SPI_CPOL_Dn;
	digi_pot.spiconf.BaudRate=SPI_BRR_Fpclk_128;
	digi_pot.spiconf.DFF=SPI_DFF_8;
	digi_pot.spiconf.Mode=SPI_MODE_Master;
	digi_pot.spiconf.SlvManage=SPI_SlvManage_Soft;
	uint8_t command=CMD_SHDN;
	SPI_Init(&digi_pot);
	
	SPI_Enable(SPI1,ENABLE);
	GPIO_WriteToOutputPin(GPIOA,2,SET);
	SPI_SendData(SPI1,&command,1);
	SPI_SendData(SPI1,&val_1,1);
	delay();
	SPI_Enable(SPI1,DISABLE);
	GPIO_WriteToOutputPin(GPIOA,2,RESET);
}
