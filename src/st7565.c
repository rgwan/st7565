/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.If not, see <http://www.gnu.org/licenses/>.
 */

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/scb.h>
#include <stdint.h>

#include "7565_lcd.h"


#include "../hzk/out.h"

/* Set STM32 to 72 MHz. */
static void clock_setup(void)
{
	rcc_clock_setup_in_hse_8mhz_out_72mhz();
	rcc_css_enable();

	/* Enable GPIOC clock. */
	rcc_periph_clock_enable(RCC_GPIOC);
	rcc_periph_clock_enable(RCC_GPIOB);
	rcc_periph_clock_enable(RCC_GPIOA);
	
	rcc_periph_clock_enable(RCC_TIM2);
}

static void gpio_setup(void)
{
	gpio_set(GPIOA, GPIO1 | GPIO2 | GPIO3);
	gpio_set(GPIOC, GPIO13 | GPIO14 | GPIO15);
	
	gpio_set(GPIOB, GPIO0 | GPIO1);
	gpio_set(GPIOB, GPIO12 | GPIO13 | GPIO14| GPIO15);
	/* Set GPIO12 (in GPIO port B) to 'output push-pull'. */
	gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ,
		GPIO_CNF_OUTPUT_PUSHPULL, GPIO0 | GPIO1 |GPIO11 | GPIO12 | GPIO13 | GPIO14| GPIO15);
	
	gpio_set_mode(GPIOC, GPIO_MODE_INPUT,
		GPIO_CNF_INPUT_PULL_UPDOWN, GPIO13 | GPIO14 | GPIO15);
		
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ,
		GPIO_CNF_OUTPUT_PUSHPULL, GPIO8 | GPIO2 | GPIO3);
		
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ,
		GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,
		GPIO_TIM2_CH2);	
		
	gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ,
		GPIO_CNF_OUTPUT_PUSHPULL, GPIO3 | GPIO4 |GPIO5 | GPIO6 | GPIO7 | GPIO8| GPIO9);	 
}
void DisplayString(char y, char *s);

void DisplayString(char y, char *s)
{
	int i = 0;
	while(*s)
	{
		LCD_Putc((i % 21) * 6, i / 21 + y, *s++);
		i ++;
	}
}

int main(void)
{
	

	clock_setup();
	gpio_setup();

	Init_IC(); 
   	Display_fill(0x00); 
	/*DisplayString(0, "Hello world!");
	DisplayString(1, "Aloha Oe, Aloha oe~");
	DisplayString(2, "E ke onaona noho i kalipo One fond embrace");
	DisplayString(4, "ahoi ae au ");
	DisplayString(5, "Until we meet again~");
	DisplayString(6, " -- by Ezawa Tami --");
	DisplayString(7, "2018 LCD Orange Test");*/
	//LCD_SetY(1);
	//LCD_SetX(1);
	//for(i = 0; i < 168; i++)
	//	LCD_Putc((i % 21) * 6, i / 21, i);

	/*for(j = 0; j < 2; j++)
	{
		LCD_SetY(j);
		for(i = 0; i < 16 ; i++);
		{
			LCD_SetX(i);
			w_dat(0x02);
		}
	}*/
	uint16_t k = 0;
	int x = 0;
	int y = 0;
	int i;
	int j;
	int screen;
	   	
 	while(1)  
 	{
 		x = 0;
 		y = 0;
 		for(k = 0; k < sizeof(cr_table); k++)
 		{
 			if(cr_table[k] == 0x01)
 			{
 				y += 1;
 				x = 0;
 			}
 			if(y == 4)
 			{
 				y = 0;
 				x = 0;
  				delay_ms(1000);
  				gpio_toggle(GPIOB, GPIO11);
  				Display_fill(0x00); 
 			}
			for(j = 0; j < 2; j ++)
			{
				LCD_SetY(j + y * 2);
				LCD_SetX(x * 16);
				for(i=0;i<16;i++)  //X
				{  
					w_dat(font_cn[k][i + j * 16]);
		       		}
		       	}
		       	x++;
 		}
  		delay_ms(1000);
  		gpio_toggle(GPIOB, GPIO11);
  		Display_fill(0x00); 
	}  
   

	return 0;
}
