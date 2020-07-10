/*The character LCD is 20x4 (20 character  with 4 lines) is interface with Atmega 328p in 4bit mode  
 * we can display a char,string ,decimal ,hexadecimal and float  number in LCD
 * we display a string at x and y location
 * we display a scrolling display in LCD
 * In 4 bit mode the 4 data line are connected to D4-D7 of lcd data
 * the data is send in nibble(4bit) since the data size is 8bit(byte)
 * first upper nibble send then lower nibble to 4 bit lines 
 * RS=0 for command and RS=1 for data
*/
#ifndef F_CPU
#define F_CPU 16000000UL
#endif // F_CPU
#include "mylcd_4bit.h"

int main(void)
{
    uint16_t data=0x0Daa;

    LCDInit(LS_BLINK);
    LCDClear();
     LCDGotoXY(0,1);
      LCDWriteString("The scrolling display ");

    while(1)
    {
      LCDHome();
       LCDWriteString("The number demo");
      LCD_scroll(15);
      LCDClear();
      _delay_ms(200);
     LCDGotoXY(0,2);
     LCDWriteString("decimal form=");
      LCD_dispDecimal(data,5);  //void LCD_dispDecimal(uint16_t num,uint8_t k)  k=nuumber of digit
      LCD_scroll(15);
     _delay_ms(500);
       LCDGotoXY(0,3);
      LCDWriteString("hexadeci form=");
      LCD_dispHexadecimal(data,4);                    //LCD_dispHexadecimal(uint16_t num, uint8_t k)
      _delay_ms(500);
      LCDGotoXY(0,4);
      LCDWriteString("float num=");
      LCD_dispFloatNum(12.345);
      _delay_ms(500);
    }

    return 0;
}
