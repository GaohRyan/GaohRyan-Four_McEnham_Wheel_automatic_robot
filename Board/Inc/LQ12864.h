#ifndef _LQOLED_H
#define _LQOLED_H
//#include "include.h"
#include "common.h"

#define byte uint8
#define word uint16
#define GPIO_PIN_MASK      0x1Fu    //0x1f=31,限制位数为0--31有效
#define GPIO_PIN(x)        (((1)<<(x & GPIO_PIN_MASK)))  //把当前位置1

 extern byte longqiu96x64[768];
 void LCD_Oled_Init(void);
 void LCD_CLS(void);
 void LCD_P6x8Str(byte x,byte y,byte ch[]);
 void LCD_P6x8Num( byte x,byte y,int32 num);
 void LCD_Cler_6x8(byte x, byte y, byte n);		//清除N个6*8字符  
 void LCD_P6x8Num1_C( byte x,byte y,int32 num);
 void LCD_P6x8Num1( byte x,byte y,int32 num);
 void LCD_P8x16Str(byte x,byte y,byte ch[]);
 void LCD_P8x16Num( byte x,byte y,int32 num);
 void LCD_P14x16Str(byte x,byte y,byte ch[]);
 void LCD_Print(byte x, byte y, byte ch[]);
 void LCD_PutPixel(byte x,byte y);
 void LCD__Oled_Rectangle(byte x1,byte y1,byte x2,byte y2,byte gif);
 void Draw_LQLogo(void);
 void Draw_LibLogo(void);
 void Draw_BMP(byte x0,byte y0,byte x1,byte y1,byte bmp[]); 
 void LCD_Fill(byte dat);
 //void LCDole_Num_8x16_C(Site_type site,u32 num, u16 Color, u16 bkColor);
 
 void itoa (int32 num, byte * str );
 //char * itoa (u16 num );
#endif

