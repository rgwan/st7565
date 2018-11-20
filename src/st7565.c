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
//#include "../badapple/imgto5110bmp/badapple.h"


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
#if 1
void DisplayString(char y, char *s)
{
	int i = 0;
	while(*s)
	{
		LCD_Putc((i % 21) * 6, i / 21 + y, *s++);
		i ++;
	}
}

void DisplayHZ()
{
	uint16_t k = 0;
	int x = 0;
	int y = 0;
	int i;
	int j;
	int screen;
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
#endif
int main(void)
{
	

	clock_setup();
	gpio_setup();

	Init_IC(); 
   	Display_fill(0x00);

	/*DisplayString(0, "TRK1: [MO]  [VL]");
	DisplayString(1, " Tenor Saxophone");
	DisplayString(3, "TRK2:       [FM]");
	DisplayString(4, " Glassy E.Piano");
	DisplayString(6, "MIDI: Remote Mode");
	DisplayString(7, "[1] [2]");*/
   	//               "                    "
	/*DisplayString(0, "CH1: 10,000,000.00 Hz");
	DisplayString(1, "090.0\xB0 1.25V [01] Sin");
	DisplayString(3, "CH2: [SYNC TO CH1]");
	DisplayString(4, "000.0\xB0 4.00V [01] Sqr");
	DisplayString(6, "Arbitrary Wave");
	DisplayString(7, "      Generator 2018");*/
	/*DisplayString(0, "Seq. V Terminal 1.0");
	DisplayString(1, "$ step 10");
	DisplayString(2, "  OK");
	DisplayString(3, "$ whoami");
	DisplayString(4, "  root");
	DisplayString(5, "$ play");
	DisplayString(7, "$ _");*/
	/*DisplayString(6, "MIDI: Remote Mode");
	DisplayString(7, "[1] [2]");*/

	//DisplayString(7, "");
	//DisplayString(6, " -- by Ezawa Tami --");
	//DisplayString(7, "2018 LCD Orange Test");
	//while(1);
	
 	while(1)  
 	{
 		DisplayHZ();
 		/*int i;
 		for(i = 0; i < (sizeof(dp) / 128 / 8); i++)
 		{
			Display(&dp[i * 128 * 8]);
			delay_ms(40);
		}*/
	}  
   

	return 0;
}
