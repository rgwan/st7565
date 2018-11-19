void delay_ms(unsigned int ms);
void LCD_Reset(void);
void w_dat(unsigned char Dat);
void w_cmd(unsigned char Command);
void Display(unsigned char *p);
void Display_fill(unsigned char fill);
void Grid_white(void);
void Grid_Black(void);
void Grid_Line1(void);
void Grid_Line2(void);
void Init_IC(void);
void LCD_Putc(char x, char y, char ch);


#define GPIO_RES	GPIOB, GPIO9
#define GPIO_CS		GPIOB, GPIO5
#define GPIO_RS		GPIOB, GPIO6
#define GPIO_SCLK	GPIOB, GPIO7
#define GPIO_SDI	GPIOB, GPIO8

#define LCD_SetX(x) w_cmd(((x) & 0xf0) >> 4 | 0x10); w_cmd((x) & 0x0f)

#define LCD_SetY(y) w_cmd(((y) & 0x7) | 0xB0)

extern unsigned char font[];
