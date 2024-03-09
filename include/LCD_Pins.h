/*
 * LCD_Pins.h
 *
 *  Created on: Oct 24, 2023
 *      Author: hussamaldean
 */

#ifndef LCD_PINS_H_
#define LCD_PINS_H_

#include "delay.h"


/*SPI */
void LCD_Pin_Init(void);
void LCD_SPI_Init(void);

/*LCD*/
void LCD_RST(void);
void LCD_Write_Cmd(uint8_t cmd);
void LCD_Write_Data (uint8_t data);



#endif /* LCD_PINS_H_ */
