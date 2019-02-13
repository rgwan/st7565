Description
======

ST7565 based COG LCD12864 (Serial mode) example program using libopencm3 library.


Hardware requirement and IO assignment
--------------

It requires a STM32F103C8T6 or equal microcontroller(GD32/MM32/BLM32) with 8MHz external crystal.

Default setting is :
RESET	: PB9
CS	: PB5
RS	: PB6
SCLK	: PB7
SDI	: PB8


Build
--------------

Enter the src directory, and type "make"

Chinese character maker
--------------

Because HZK12/16/24/32/48 is national standard, the font data file is in public domain, so I choose to include it in my repository.

Flash
--------------

Use "make swd" to flash your mcu through ST-Link V2 interface.


Author
--------------

Zhiyuan Wan
