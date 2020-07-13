#ifndef MYLCD_4BIT_H_INCLUDED
#define MYLCD_4BIT_H_INCLUDED

#include<avr/io.h>
#include<util/delay.h>
#include "mystdutil.h"
/***************************************************************************************************
                        List of commonly used LCD Commands 
****************************************************************************************************/
#define CMD_LCD_CLEAR                0x01u
#define CMD_LCD_RETURN_HOME          0x02u
#define CMD_DISPLAY_ON_CURSOR_OFF    0x0Cu
#define CMD_DISPLAY_ON_CURSOR_ON     0x0Eu
#define CMD_DISPLAY_ON_CURSOR_BLINK  0x0Fu
#define CMD_LCD_FOUR_BIT_MODE        0x28u
#define CMD_LCD_EIGHT_BIT_MODE       0x38u
/**************************************************************************************************/
/***************************************************************************/
#define LCD_DATA_PORT 	PORTB
#define LCD_E_PORT 		  PORTB
#define LCD_RS_PORT 	   PORTB
#define LCD_RW_PORT 	  PORTB

#define LCD_DATA_DDR 	DDRB
#define LCD_E_DDR 		DDRB
#define LCD_RS_DDR 		DDRB
#define LCD_RW_DDR 		DDRB

#define LCD_E_POS  	PB4
#define LCD_RS_POS  PB7
#define LCD_RW_POS  PB6
#define LCD_DATA_PIN	PINB

/******************************************************************************/


#define SET_E()   util_BitSet(LCD_E_PORT,LCD_E_POS)             //util_BitSet(x,bit) 
#define SET_RS()  util_BitSet(LCD_RS_PORT,LCD_RS_POS)
#define SET_RW()  util_BitSet(LCD_RW_PORT,LCD_RW_POS)

#define CLEAR_E()   util_BitClear(LCD_E_PORT,LCD_E_POS)          //util_BitClear(x,bit)
#define CLEAR_RS()  util_BitClear(LCD_RS_PORT,LCD_RS_POS)
#define CLEAR_RW()  util_BitClear(LCD_RW_PORT,LCD_RW_POS)
/****************************************************************************/
#define LS_BLINK 0B00000001
#define LS_ULINE 0B00000010

#define LCDCmd(c) (LCDByte(c,0))
#define LCDData(d) (LCDByte(d,1))

#define LCDClear() LCDCmd(CMD_LCD_CLEAR)
#define LCDHome() LCDCmd(CMD_LCD_RETURN_HOME);
/*********************************************************************************/
uint8_t LcdlineNum[] = {0x80, 0xc0, 0x94, 0xD4};

void LCDWriteString(const char *msg);
void LCDBusyLoop();
void LCDInit();
void LCDByte(uint8_t c, uint8_t isdata);
void LCDGotoXY(uint8_t x, uint8_t y);
void LCD_dispDecimal(uint16_t num, uint8_t k);
void LCD_dispHexadecimal(uint16_t num, uint8_t k);
void LCD_dispFloatNum(float v_number);
void LCD_scroll(uint8_t shift);
/*********************************************************************************/
void LCDBusyLoop()
{
  //This function waits till lcd is BUSY

  uint8_t busy, status = 0x00, temp;

  //Change Port to input type because we are reading data
  LCD_DATA_DDR &= 0xF0;

  //change LCD mode
  SET_RW();		//Read mode
  CLEAR_RS();		//Read status

  //Let the RW/RS lines stabilize

  _delay_us(0.5);		//tAS


  do
  {

    SET_E();

    //Wait tDA for data to become available
    _delay_us(0.5);

    status = LCD_DATA_PIN;
    status = status << 4;

    _delay_us(0.5);

    //Pull E low
    CLEAR_E();
    _delay_us(1);	//tEL

    SET_E();
    _delay_us(0.5);

    temp = LCD_DATA_PIN;
    temp &= 0x0F;

    status = status | temp;

    busy = status & 0b10000000;

    _delay_us(0.5);
    CLEAR_E();
    _delay_us(1);	//tEL
  } while (busy);

  CLEAR_RW();		//write mode
  //Change Port to output
  LCD_DATA_DDR |= 0x0F;

}


void LCDInit()
{
  //After power on Wait for LCD to Initialize
  _delay_ms(30);

  //Set IO Ports
  LCD_DATA_DDR |= (0x0F);
  LCD_E_DDR |= (1 << LCD_E_POS);
  LCD_RS_DDR |= (1 << LCD_RS_POS);
  LCD_RW_DDR |= (1 << LCD_RW_POS);

  LCD_DATA_PORT &= 0XF0;
  CLEAR_E();
  CLEAR_RW();
  CLEAR_RS();

  //Set 4-bit mode
  _delay_us(0.3);	//tAS

   SET_E();
  LCD_DATA_PORT |= (0b00000001); //[B] To transfer 0b00100000 i was using LCD_DATA_PORT|=0b00100000
  _delay_us(1);
  CLEAR_E();
  _delay_us(1);

  //Wait for LCD to execute the Functionset Command
  //	LCDBusyLoop();                                    //[B] Forgot this delay
  _delay_ms(20);
  //Now the LCD is in 4-bit mode

  	//LCDCmd(CMD_DISPLAY_ON_CURSOR_OFF);	//Display On and cursor off
  //LCDCmd(CMD_DISPLAY_ON_CURSOR_ON); //Display On and cursor  on
    LCDCmd(CMD_DISPLAY_ON_CURSOR_BLINK);  //Display On and cursor off
  LCDCmd(CMD_LCD_FOUR_BIT_MODE);			//function set 4-bit,2 line 5x7 dot format
}

void LCDByte(uint8_t c, uint8_t isdata)
{
  //Sends a byte to the LCD in 4bit mode
  //cmd=0 for data
  //cmd=1 for command

  uint8_t hn, ln;			//Nibbles
  uint8_t temp;

  hn = c >> 4;
  ln = (c & 0x0F);

  if (isdata == 0)
    CLEAR_RS();
  else
    SET_RS();

  _delay_us(0.500);		//tAS

  SET_E();

  //Send high nibble

  temp = (LCD_DATA_PORT & 0XF0) | (hn);
  LCD_DATA_PORT = temp;

  _delay_us(1);			//tEH

  //Now data lines are stable pull E low for transmission

  CLEAR_E();

  _delay_us(1);

  //Send the lower nibble
  SET_E();

  temp = (LCD_DATA_PORT & 0XF0) | (ln);

  LCD_DATA_PORT = temp;

  _delay_us(1);			//tEH

  //SEND

  CLEAR_E();

  _delay_us(1);			//tEL

  //LCDBusyLoop();
  _delay_ms(20);
}

void LCDGotoXY(uint8_t x, uint8_t y) // y=1-4
{
  if (y > 0)
  {
    LCDCmd(LcdlineNum[y - 1] + x); // x should be in hex
  }
  else
    LCDCmd(LcdlineNum[0] + x); // x should be in hex
}


void LCDWriteString(const char *msg)
{
  while (*msg != '\0')
  {
    LCDData(*msg);
    msg++;
  }
}

void LCD_dispDecimal(uint16_t num, uint8_t k)
{
  uint16_t temp;
  uint16_t sd[6] = {0};
  uint8_t j = 0;
  while (num != 0)
  {
    temp = util_GetMod16(num, C_DECIMAL_U8 );
    sd[j] = temp;
    num = num / C_DECIMAL_U8;
    j++;
  }
  while (k--)
  {
    LCDData(0x30 + sd[k]);
  }
}

void LCD_dispHexadecimal(uint16_t num, uint8_t k)
{
  uint16_t temp;
  uint16_t sd[6] = {0};
  uint8_t j = 0;
  while (num != 0)
  {
    temp = util_GetMod16(num, C_HEX_U8 );
    sd[j] = temp;
    num = num / C_HEX_U8;
    j++;
  }
  LCDWriteString("0x");
  while (k--)
  {
    LCDData(util_Hex2Ascii(sd[k])); //util_Hex2Ascii(Hex)
  }
}

void LCD_dispFloatNum(float v_number)
{
  uint32_t temp;
  temp=(uint32_t)v_number;
  LCD_dispDecimal(temp,3);
  LCDData('.');
  v_number=v_number-temp;
  temp=v_number*10000;
  LCD_dispDecimal(temp,4);
}

void LCD_scroll(uint8_t shift)
{
  uint8_t i;
  for(i=0;i<shift;i++)
      {
        LCDCmd(0x1c);/* shift entire display right */
        _delay_ms(200);
      }
      for(i=0;i<shift;i++)
      {
        LCDCmd(0x18);/* shift entire display left */
        _delay_ms(200);
      }
}


#endif // MYLCD_4BIT_H_INCLUDED
