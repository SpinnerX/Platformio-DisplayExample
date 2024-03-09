/*
* LCD_Pins.c
*
*  Created on: Oct 24, 2023
*      Author: hussamaldean
*/

#include "stm32f4xx.h"
#include "LCD_Pins.h"

#define AF05						0x05



#define LCD_RES_HIGH(void)			GPIOA->BSRR=GPIO_BSRR_BS7
#define LCD_RES_LOW(void)			GPIOA->BSRR=GPIO_BSRR_BR7

#define LCD_CS_HIGH(void)			GPIOC->BSRR=GPIO_BSRR_BS2
#define LCD_CS_LOW(void)			GPIOC->BSRR=GPIO_BSRR_BR2

#define LCD_DC_HIGH(void)			GPIOD->BSRR=GPIO_BSRR_BS13
#define LCD_DC_LOW(void)			GPIOD->BSRR=GPIO_BSRR_BR13


void LCD_Pin_Init(void)
{
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN|RCC_AHB1ENR_GPIOCEN|RCC_AHB1ENR_GPIODEN;

	/*PA7*/
	GPIOA->MODER|=GPIO_MODER_MODE7_0;
	GPIOA->MODER&=~GPIO_MODER_MODE7_1;
	GPIOA->OSPEEDR|=GPIO_OSPEEDR_OSPEED7;
	GPIOA->ODR|=GPIO_ODR_OD7;

	/*PC2*/
	GPIOC->MODER|=GPIO_MODER_MODE2_0;
	GPIOC->MODER&=~GPIO_MODER_MODE2_1;
	GPIOC->OSPEEDR|=GPIO_OSPEEDR_OSPEED2;
	GPIOC->ODR|=GPIO_ODR_OD2;



	/*PD13*/
	GPIOD->MODER|=GPIO_MODER_MODE13_0;
	GPIOD->MODER&=~GPIO_MODER_MODE13_1;
	GPIOD->OSPEEDR|=GPIO_OSPEEDR_OSPEED13;
	GPIOD->ODR|=GPIO_ODR_OD13;

	/*PF7 and PF9 for SPI1*/

	GPIOF->MODER|=GPIO_MODER_MODE7_1|GPIO_MODER_MODE9_1;
	GPIOF->MODER&=~(GPIO_MODER_MODE7_0|GPIO_MODER_MODE9_0);

	GPIOF->AFR[0]|=(AF05<<GPIO_AFRL_AFSEL7_Pos);
	GPIOF->AFR[1]|=(AF05<<GPIO_AFRH_AFSEL9_Pos);


}


void LCD_SPI_Init(void)
{
	RCC->APB2ENR|=RCC_APB2ENR_SPI1EN;
	SPI1->CR1|=SPI_CR1_MSTR|SPI_CR1_SSM|SPI_CR1_SSI|
	SPI_CR1_BR_1;

	SPI1->CR1|=SPI_CR1_SPE;

}


static void SPI1_transmit(uint8_t *data,uint32_t size)
{
	uint32_t i=0;


	while(i<size)
	{
		/*Wait until TXE is set*/
		while(!(SPI1->SR & (SPI_SR_TXE))){}

		/*Write the data to the data register*/
		SPI1->DR = data[i];
		i++;
	}
	/*Wait until TXE is set*/
	while(!(SPI1->SR & (SPI_SR_TXE))){}

	/*Wait for BUSY flag to reset*/
	while((SPI1->SR & (SPI_SR_BSY))){}

	/*Clear OVR flag*/
	(void) SPI1->DR;
	(void) SPI1->SR;
}


void LCD_RST(void)
{
	LCD_RES_LOW();
	delay(50);
	LCD_RES_HIGH();
	delay(20);

}





void LCD_Write_Cmd(uint8_t cmd)
{
	LCD_CS_LOW();
	LCD_DC_LOW();
	SPI1_transmit(&cmd,1);
	LCD_CS_HIGH();
}


void LCD_Write_Data (uint8_t data)
{
	LCD_CS_LOW();
	LCD_DC_HIGH();
	SPI1_transmit (&data,1);
	LCD_CS_HIGH();
}
