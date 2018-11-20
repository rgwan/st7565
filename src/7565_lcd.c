#include <libopencm3/stm32/gpio.h>
#include "7565_lcd.h"
         //1100   
#define VC_ON 0x2C       //1010   
#define VR_ON 0x2A   
#define VF_ON 0x29      //1001   
#ifdef USE_FONT
unsigned char font[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, // Space
	0x3E, 0x5B, 0x4F, 0x5B, 0x3E, // face
	0x3E, 0x6B, 0x4F, 0x6B, 0x3E, // face invert contrast
	0x1C, 0x3E, 0x7C, 0x3E, 0x1C, // heart
	0x18, 0x3C, 0x7E, 0x3C, 0x18, // diamond
	0x1C, 0x57, 0x7D, 0x57, 0x1C, // clubs
	0x1C, 0x5E, 0x7F, 0x5E, 0x1C, // spades
	0x00, 0x18, 0x3C, 0x18, 0x00,
	0xFF, 0xE7, 0xC3, 0xE7, 0xFF, // #9
	0x00, 0x18, 0x24, 0x18, 0x00,
	0xFF, 0xE7, 0xDB, 0xE7, 0xFF, // bullseye circle
	0x30, 0x48, 0x3A, 0x06, 0x0E, // male symbol
	0x26, 0x29, 0x79, 0x29, 0x26, // female symbol
	0x40, 0x7F, 0x05, 0x05, 0x07, // music note 1
	0x40, 0x7F, 0x05, 0x25, 0x3F, // music note 2
	0x5A, 0x3C, 0xE7, 0x3C, 0x5A, // star
	0x7F, 0x3E, 0x1C, 0x1C, 0x08,
	0x08, 0x1C, 0x1C, 0x3E, 0x7F,
	0x14, 0x22, 0x7F, 0x22, 0x14, // up down arrow
	0x5F, 0x5F, 0x00, 0x5F, 0x5F,
	0x06, 0x09, 0x7F, 0x01, 0x7F,
	0x00, 0x66, 0x89, 0x95, 0x6A, // #22
	0x60, 0x60, 0x60, 0x60, 0x60,
	0x94, 0xA2, 0xFF, 0xA2, 0x94, // up down arrow with underscore
	0x08, 0x04, 0x7E, 0x04, 0x08, // up arrow
	0x10, 0x20, 0x7E, 0x20, 0x10, // down arrow
	0x08, 0x08, 0x2A, 0x1C, 0x08, // right arrow
	0x08, 0x1C, 0x2A, 0x08, 0x08, // left arrow
	0x1E, 0x10, 0x10, 0x10, 0x10,
	0x0C, 0x1E, 0x0C, 0x1E, 0x0C,
	0x30, 0x38, 0x3E, 0x38, 0x30,
	0x06, 0x0E, 0x3E, 0x0E, 0x06, // #32
	0x00, 0x00, 0x00, 0x00, 0x00, // space
	0x00, 0x00, 0x5F, 0x00, 0x00, // !
	0x00, 0x07, 0x00, 0x07, 0x00, // "
	0x14, 0x7F, 0x14, 0x7F, 0x14, // #
	0x24, 0x2A, 0x7F, 0x2A, 0x12, // $
	0x23, 0x13, 0x08, 0x64, 0x62, // %
	0x36, 0x49, 0x56, 0x20, 0x50, // &
	0x00, 0x08, 0x07, 0x03, 0x00, // '
	0x00, 0x1C, 0x22, 0x41, 0x00, // (
	0x00, 0x41, 0x22, 0x1C, 0x00, // )
	0x2A, 0x1C, 0x7F, 0x1C, 0x2A, // *
	0x08, 0x08, 0x3E, 0x08, 0x08, // +
	0x00, 0x80, 0x70, 0x30, 0x00, // ,
	0x08, 0x08, 0x08, 0x08, 0x08, // -
	0x00, 0x00, 0x60, 0x60, 0x00, // .
	0x20, 0x10, 0x08, 0x04, 0x02, // /
	0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
	0x00, 0x42, 0x7F, 0x40, 0x00, // 1
	0x72, 0x49, 0x49, 0x49, 0x46, // 2
	0x21, 0x41, 0x49, 0x4D, 0x33, // 3
	0x18, 0x14, 0x12, 0x7F, 0x10, // 4
	0x27, 0x45, 0x45, 0x45, 0x39, // 5
	0x3C, 0x4A, 0x49, 0x49, 0x31, // 6
	0x41, 0x21, 0x11, 0x09, 0x07, // 7
	0x36, 0x49, 0x49, 0x49, 0x36, // 8
	0x46, 0x49, 0x49, 0x29, 0x1E, // 9
	0x00, 0x00, 0x14, 0x00, 0x00, // :
	0x00, 0x40, 0x34, 0x00, 0x00, // ;
	0x00, 0x08, 0x14, 0x22, 0x41, // <
	0x14, 0x14, 0x14, 0x14, 0x14, // =
	0x00, 0x41, 0x22, 0x14, 0x08, // >
	0x02, 0x01, 0x59, 0x09, 0x06, // ?
	0x3E, 0x41, 0x5D, 0x59, 0x4E, // @
	0x7C, 0x12, 0x11, 0x12, 0x7C, // A
	0x7F, 0x49, 0x49, 0x49, 0x36, // B
	0x3E, 0x41, 0x41, 0x41, 0x22, // C
	0x7F, 0x41, 0x41, 0x41, 0x3E, // D
	0x7F, 0x49, 0x49, 0x49, 0x41, // E
	0x7F, 0x09, 0x09, 0x09, 0x01, // F
	0x3E, 0x41, 0x41, 0x51, 0x73, // G
	0x7F, 0x08, 0x08, 0x08, 0x7F, // H
	0x00, 0x41, 0x7F, 0x41, 0x00, // I
	0x20, 0x40, 0x41, 0x3F, 0x01, // J
	0x7F, 0x08, 0x14, 0x22, 0x41, // K
	0x7F, 0x40, 0x40, 0x40, 0x40, // L
	0x7F, 0x02, 0x1C, 0x02, 0x7F, // M
	0x7F, 0x04, 0x08, 0x10, 0x7F, // N
	0x3E, 0x41, 0x41, 0x41, 0x3E, // O
	0x7F, 0x09, 0x09, 0x09, 0x06, // P
	0x3E, 0x41, 0x51, 0x21, 0x5E, // Q
	0x7F, 0x09, 0x19, 0x29, 0x46, // R
	0x26, 0x49, 0x49, 0x49, 0x32, // S
	0x03, 0x01, 0x7F, 0x01, 0x03, // T
	0x3F, 0x40, 0x40, 0x40, 0x3F, // U
	0x1F, 0x20, 0x40, 0x20, 0x1F, // V
	0x3F, 0x40, 0x38, 0x40, 0x3F, // W
	0x63, 0x14, 0x08, 0x14, 0x63, // X
	0x03, 0x04, 0x78, 0x04, 0x03, // Y
	0x61, 0x59, 0x49, 0x4D, 0x43, // Z
	0x00, 0x7F, 0x41, 0x41, 0x41, // [
	0x02, 0x04, 0x08, 0x10, 0x20, // "\"
	0x00, 0x41, 0x41, 0x41, 0x7F, // ]
	0x04, 0x02, 0x01, 0x02, 0x04, // ^
	0x40, 0x40, 0x40, 0x40, 0x40, // _
	0x00, 0x03, 0x07, 0x08, 0x00, // `
	0x20, 0x54, 0x54, 0x78, 0x40, // a
	0x7F, 0x28, 0x44, 0x44, 0x38, // b
	0x38, 0x44, 0x44, 0x44, 0x28, // c    (#100)
	0x38, 0x44, 0x44, 0x28, 0x7F, // d
	0x38, 0x54, 0x54, 0x54, 0x18, // e
	0x00, 0x08, 0x7E, 0x09, 0x02, // f
	0x18, 0xA4, 0xA4, 0x9C, 0x78, // g
	0x7F, 0x08, 0x04, 0x04, 0x78, // h
	0x00, 0x44, 0x7D, 0x40, 0x00, // i
	0x20, 0x40, 0x40, 0x3D, 0x00, // j
	0x7F, 0x10, 0x28, 0x44, 0x00, // k
	0x00, 0x41, 0x7F, 0x40, 0x00, // l
	0x7C, 0x04, 0x78, 0x04, 0x78, // m
	0x7C, 0x08, 0x04, 0x04, 0x78, // n
	0x38, 0x44, 0x44, 0x44, 0x38, // o
	0xFC, 0x18, 0x24, 0x24, 0x18, // p
	0x18, 0x24, 0x24, 0x18, 0xFC, // q
	0x7C, 0x08, 0x04, 0x04, 0x08, // r
	0x48, 0x54, 0x54, 0x54, 0x24, // s
	0x04, 0x04, 0x3F, 0x44, 0x24, // t
	0x3C, 0x40, 0x40, 0x20, 0x7C, // u
	0x1C, 0x20, 0x40, 0x20, 0x1C, // v
	0x3C, 0x40, 0x30, 0x40, 0x3C, // w
	0x44, 0x28, 0x10, 0x28, 0x44, // x
	0x4C, 0x90, 0x90, 0x90, 0x7C, // y
	0x44, 0x64, 0x54, 0x4C, 0x44, // z
	0x00, 0x08, 0x36, 0x41, 0x00, // {
	0x00, 0x00, 0x77, 0x00, 0x00, // |
	0x00, 0x41, 0x36, 0x08, 0x00, // }
	0x02, 0x01, 0x02, 0x04, 0x02, // ~
	0x3C, 0x26, 0x23, 0x26, 0x3C, //
	0x1E, 0xA1, 0xA1, 0x61, 0x12, //
	0x3A, 0x40, 0x40, 0x20, 0x7A, //
	0x38, 0x54, 0x54, 0x55, 0x59, //
	0x21, 0x55, 0x55, 0x79, 0x41, // #132
	0x22, 0x54, 0x54, 0x78, 0x42, // a-umlaut
	0x21, 0x55, 0x54, 0x78, 0x40, //
	0x20, 0x54, 0x55, 0x79, 0x40, //
	0x0C, 0x1E, 0x52, 0x72, 0x12, //
	0x39, 0x55, 0x55, 0x55, 0x59, //
	0x39, 0x54, 0x54, 0x54, 0x59, //
	0x39, 0x55, 0x54, 0x54, 0x58, //
	0x00, 0x00, 0x45, 0x7C, 0x41, //
	0x00, 0x02, 0x45, 0x7D, 0x42, //
	0x00, 0x01, 0x45, 0x7C, 0x40, //
	0x7D, 0x12, 0x11, 0x12, 0x7D, // A-umlaut   Capital A with two dots on top
	0xF0, 0x28, 0x25, 0x28, 0xF0, // #144 Capital A with dot on top
	0x7C, 0x54, 0x55, 0x45, 0x00,
	0x20, 0x54, 0x54, 0x7C, 0x54,
	0x7C, 0x0A, 0x09, 0x7F, 0x49,
	0x32, 0x49, 0x49, 0x49, 0x32,
	0x3A, 0x44, 0x44, 0x44, 0x3A, // o-umlaut
	0x32, 0x4A, 0x48, 0x48, 0x30,
	0x3A, 0x41, 0x41, 0x21, 0x7A,
	0x3A, 0x42, 0x40, 0x20, 0x78,
	0x00, 0x9D, 0xA0, 0xA0, 0x7D,
	0x3D, 0x42, 0x42, 0x42, 0x3D, // O-umlaut
	0x3D, 0x40, 0x40, 0x40, 0x3D,
	0x3C, 0x24, 0xFF, 0x24, 0x24,
	0x48, 0x7E, 0x49, 0x43, 0x66,
	0x2B, 0x2F, 0xFC, 0x2F, 0x2B,
	0xFF, 0x09, 0x29, 0xF6, 0x20,
	0xC0, 0x88, 0x7E, 0x09, 0x03,
	0x20, 0x54, 0x54, 0x79, 0x41,
	0x7F, 0x41, 0x00, 0x41, 0x7F, // hand made brackets (was i symbol 0x00, 0x00, 0x44, 0x7D, 0x41)
	0x30, 0x48, 0x48, 0x4A, 0x32, // #163
	0x38, 0x40, 0x40, 0x22, 0x7A,
	0x00, 0x7A, 0x0A, 0x0A, 0x72,
	0x7D, 0x0D, 0x19, 0x31, 0x7D,
	0x26, 0x29, 0x29, 0x2F, 0x28,
	0x26, 0x29, 0x29, 0x29, 0x26,
	0x30, 0x48, 0x4D, 0x40, 0x20,
	0x1C, 0x22, 0x2A, 0x22, 0x1C, // custom bullseye (was L laying on its side 0x38, 0x08, 0x08, 0x08, 0x08)
	0x08, 0x08, 0x08, 0x08, 0x38,
	0x08, 0x1C, 0x2A, 0x08, 0x08, // left arrow (was 1/2 0x2F, 0x10, 0xC8, 0xAC, 0xBA )
	0x2F, 0x10, 0x28, 0x34, 0xFA,
	0x00, 0x00, 0x7B, 0x00, 0x00,
	0x14, 0x22, 0x7F, 0x22, 0x14, // up_down arrow (was << 0x08, 0x14, 0x2A, 0x14, 0x22)
	0x22, 0x14, 0x2A, 0x14, 0x08, // #176  "0xAF"
	0x06, 0x0F, 0x09, 0x0F, 0x06, // Degree symbol (25% block) missing in old code 0x55, 0x00, 0x55, 0x00, 0x55
	0x06, 0x0F, 0x09, 0x0F, 0x06, // Degree symbol (was 50% block 0xAA, 0x55, 0xAA, 0x55, 0xAA)
	0x44, 0x44, 0x5F, 0x44, 0x44, // plus&minus ( 75% block 0xFF, 0x55, 0xFF, 0x55, 0xFF)
	0x00, 0x00, 0x00, 0xFF, 0x00, // verticle line
	0x10, 0x10, 0x10, 0xFF, 0x00, // #181
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // solid sqaure (guessing 0x14, 0x14, 0x14, 0xFF, 0x00)
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // solid square (was F laying on its side 0x10, 0x10, 0xFF, 0x00, 0xFF) not this one
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // solid sqaure (guessing 0x10, 0x10, 0xF0, 0x10, 0xF0)
	0x14, 0x14, 0x14, 0xFC, 0x00,
	0x14, 0x14, 0xF7, 0x00, 0xFF,
	0x00, 0x00, 0xFF, 0x00, 0xFF,
	0x14, 0x14, 0xF4, 0x04, 0xFC,
	0x08, 0x08, 0x2A, 0x1C, 0x08, // right arrow (was 0x14, 0x14, 0x17, 0x10, 0x1F)
	0x10, 0x10, 0x1F, 0x10, 0x1F,
	0x14, 0x14, 0x14, 0x1F, 0x00,
	0x10, 0x10, 0x10, 0xF0, 0x00,
	0x00, 0x00, 0x00, 0x1F, 0x10,
	0x10, 0x10, 0x10, 0x1F, 0x10,
	0x10, 0x10, 0x10, 0xF0, 0x10,
	0x00, 0x00, 0x00, 0xFF, 0x10,
	0x10, 0x10, 0x10, 0x10, 0x10,
	0x10, 0x10, 0x10, 0xFF, 0x10,
	0x00, 0x00, 0x00, 0xFF, 0x14,
	0x00, 0x00, 0xFF, 0x00, 0xFF, // #200
	0x00, 0x00, 0x1F, 0x10, 0x17,
	0x00, 0x00, 0xFC, 0x04, 0xF4,
	0x14, 0x14, 0x17, 0x10, 0x17,
	0x14, 0x14, 0xF4, 0x04, 0xF4,
	0x00, 0x00, 0xFF, 0x00, 0xF7,
	0x14, 0x14, 0x14, 0x14, 0x14,
	0x14, 0x14, 0xF7, 0x00, 0xF7,
	0x14, 0x14, 0x14, 0x17, 0x14,
	0x10, 0x10, 0x1F, 0x10, 0x1F,
	0x14, 0x14, 0x14, 0xF4, 0x14,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // solid square (was F laying on its side 0x10, 0x10, 0xF0, 0x10, 0xF0) not this one
	0x00, 0x00, 0x1F, 0x10, 0x1F,
	0x00, 0x00, 0x00, 0x1F, 0x14,
	0x00, 0x00, 0x00, 0xFC, 0x14,
	0x00, 0x00, 0xF0, 0x10, 0xF0,
	0x10, 0x10, 0xFF, 0x10, 0xFF,
	0x14, 0x14, 0x14, 0xFF, 0x14,
	0x10, 0x10, 0x10, 0x1F, 0x00,
	0x00, 0x00, 0x00, 0xF0, 0x10,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // solid filled sqaure
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, // half filled square from bottom
	0xFF, 0xFF, 0xFF, 0x00, 0x00, // half filled square from side
	0x00, 0x00, 0x00, 0xFF, 0xFF, // less than half filled sqaure from side
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, // half filled square from top
	0x38, 0x44, 0x44, 0x38, 0x44, // Alpha
	0xFC, 0x4A, 0x4A, 0x4A, 0x34, // Beta
	0x7E, 0x02, 0x02, 0x06, 0x06, // #227
	0x02, 0x7E, 0x02, 0x7E, 0x02, // Pi symbol
	0x63, 0x55, 0x49, 0x41, 0x63, // Summation symbol
	0x38, 0x44, 0x44, 0x3C, 0x04, // #230
	0x40, 0x7E, 0x20, 0x1E, 0x20, // Micro symbol
	0x06, 0x02, 0x7E, 0x02, 0x02, // #232
	0x99, 0xA5, 0xE7, 0xA5, 0x99, // #233
	0x1C, 0x2A, 0x49, 0x2A, 0x1C, // Theta symbol
	0x4C, 0x72, 0x01, 0x72, 0x4C, // Ohms symbol
	0x30, 0x4A, 0x4D, 0x4D, 0x30, // #236
	0x30, 0x48, 0x78, 0x48, 0x30, // Infinity symbol
	0xBC, 0x62, 0x5A, 0x46, 0x3D, // #238
	0x3E, 0x49, 0x49, 0x49, 0x00, // #239
	0x7E, 0x01, 0x01, 0x01, 0x7E, // #240
	0x2A, 0x2A, 0x2A, 0x2A, 0x2A, // Three lines horizontal
	0x44, 0x44, 0x5F, 0x44, 0x44, // Plus and minus symbol
	0x40, 0x51, 0x4A, 0x44, 0x40, // Less Than underscore
	0x40, 0x44, 0x4A, 0x51, 0x40, // Greater Than underscore
	0x00, 0x00, 0xFF, 0x01, 0x03, // #245
	0xE0, 0x80, 0xFF, 0x00, 0x00, // #246
	0x08, 0x08, 0x6B, 0x6B, 0x08, // Division symbol
	0x36, 0x12, 0x36, 0x24, 0x36, // Aproximate symbol
	0x06, 0x0F, 0x09, 0x0F, 0x06, // Degree symbol
	0x00, 0x00, 0x18, 0x18, 0x00, // #250
	0x00, 0x00, 0x10, 0x10, 0x00, // #251
	0x30, 0x40, 0xFF, 0x01, 0x01, // Square Root symbol
	0x00, 0x1F, 0x01, 0x01, 0x1E, // #253
	0x00, 0x19, 0x1D, 0x17, 0x12, // #254
	0x00, 0x3C, 0x3C, 0x3C, 0x3C, // #255
	0x00, 0x00, 0x00, 0x00, 0x00  // #256 NBSP
};

#endif
/******************************delay time***********************************/  
void delay_ms(unsigned int ms)  
{  
 unsigned int n ;  
 while(ms--)  
      {  
       n  =  8600 * 4;  
       while(n--)
       {
       	asm("nop");
       }
      }  
} 
static inline void NOP(void)
{
	int i = 2;
	while(i--)
		asm("nop");
}
  
/****************************reset IC for start****************************/  
void LCD_Reset()  
{  
 gpio_clear(GPIO_RES);
 delay_ms(50);  
 gpio_set(GPIO_RES);
 delay_ms(50);  
}   
  
/*******************************write data to IC**************************/  
void w_dat(unsigned char Dat)  
{  
 unsigned char Num;
 gpio_clear(GPIO_CS);
 NOP();
 gpio_set(GPIO_RS);
 NOP();
 for(Num=0;Num<8;Num++)
 {
  if((Dat&0x80) == 0) gpio_clear(GPIO_SDI);
  else gpio_set(GPIO_SDI);
  NOP();
  Dat = Dat << 1;
  gpio_clear(GPIO_SCLK);
  NOP();
  gpio_set(GPIO_SCLK);
  NOP();
 }
 NOP();
 gpio_set(GPIO_CS);
}  
  
/******************************write Command to IC***********************/  
void w_cmd(unsigned char Command)  
{  
 unsigned char Num;
 gpio_clear(GPIO_CS);
 NOP();
 gpio_clear(GPIO_RS);
 NOP();
 for(Num=0;Num<8;Num++)
 {
  if((Command&0x80) == 0) gpio_clear(GPIO_SDI);
  else gpio_set(GPIO_SDI);
  NOP();
  Command = Command << 1;
  gpio_clear(GPIO_SCLK);
  NOP();
  gpio_set(GPIO_SCLK);
  NOP();
 }
 NOP();
 gpio_set(GPIO_CS);
}  
  
/***************************display picture *****************************/  
void Display(unsigned char *p)  
{  
 unsigned char page,column;  
 for(page=0xB0;page<=0xB7;page++)  
    {  
     w_cmd(page);  //set page address   
     w_cmd(0x10);  //set Column address MSB   
     w_cmd(0x00);  //set column address LSB   
     for(column=0;column<128;column++)  
        {  
         w_dat(*p++);  
        }  
    }  
}  
 
  
void Display_fill(unsigned char fill)  
{  
 unsigned char page,column;  
 for(page=0xB7;page>=0xB0;page--)  
    {  
     w_cmd(page);  //set page address   
     w_cmd(0x10);  //set Column address MSB   
     w_cmd(0x00);  //set column address LSB   
     for(column=0;column<131;column++)  
        {  
         w_dat(fill);  
        }  
    }  
}  
  
  
#if 0 
  
  
void Grid_white()  
{  
 unsigned char page,column;  
 for(page=0xB7;page>=0xB0;page--)  
    {  
     w_cmd(page);  
     w_cmd(0x10);  
     w_cmd(0x00);  
     for(column=0;column<65;column++)  
        {  
         w_dat(0xFF);  
         w_dat(0x00);  
        }  
    }  
}  
  
void Grid_Black()  
{  
 unsigned char page,column;  
 for(page=0xB7;page>=0xB0;page--)  
    {  
     w_cmd(page);  
     w_cmd(0x10);  
     w_cmd(0x00);  
     for(column=0;column<65;column++)  
        {  
         w_dat(0x00);  
         w_dat(0xFF);  
        }  
    }  
}  
  
void Grid_Line1()  
{  
 unsigned char page,column;  
 for(page=0xB7;page>=0xB0;page--)  
    {  
     w_cmd(page);  
     w_cmd(0x10);  
     w_cmd(0x00);  
     for(column=0;column<131;column++)  
        {  
         w_dat(0xAA);  
        }  
    }  
}  
  
void Grid_Line2()  
{  
 unsigned char page,column;  
 for(page=0xB7;page>=0xB0;page--)  
    {  
     w_cmd(page);  
     w_cmd(0x10);  
     w_cmd(0x00);  
     for(column=0;column<131;column++)  
        {  
         w_dat(0x55);  
        }  
    }  
}  
  
void LCD_Putc(char x, char y, char ch)
{
	int page;
	int column;  
	//for(page=0xB0;page<=0xB2;page++)  //Y
	//{  
		LCD_SetY(y);
		LCD_SetX(x);
		for(column=0;column<5;column++)  //X
		{  
			w_dat(font[column + (ch) * 5]);
        	}
        	w_dat(0x00);
	//}  
}

#endif
  
void Init_IC()  
{  
 gpio_clear(GPIO_CS);
 LCD_Reset();  
 w_cmd(0xA3);    //LCD Bias	 selection(1/65 Duty,1/7Bias)   
 w_cmd(0xA0);    //ADC selection(SEG0->SEG128)   
 w_cmd(0xC8);    //SHL selection(COM0->COM64)   
  
 w_cmd(0x26);    //Regulator Resistor Selection   
 delay_ms(5);  
 w_cmd(0x81);    //Electronic Volume   
 w_cmd(0x20);    //Reference Register selection  Vo=(1+Rb/Ra)(1+a)*2.1=10   
 w_cmd(VC_ON);    //Power Control(Vc=1;Vr=0;Vf=0)   
 delay_ms(10);  
 w_cmd(VC_ON|VR_ON);  
 delay_ms(10);  
 w_cmd(VC_ON|VR_ON|VF_ON);  
 delay_ms(10);  
 w_cmd(0xF8);  
 w_cmd(0x01);  
  
 delay_ms(5);  
 w_cmd(0xAF);    //Display on   
 w_cmd(0xA6);
   
}  
  


