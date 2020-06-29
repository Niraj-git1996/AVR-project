/*  In atmega 328p there is internal 1kb non-volatile memory where data is rstain even after the power is off. We have used the eeprom register to cofigure the eeprom 
   in different modes and  write abd read data to onternal eeprom memory 
*/
// In this code we auding uart to display  value read and write in eeeprom memory . 
#include<stdio.h>
//#include <avr/io.h>
#include <util/delay.h>
#include "mystdutil.h"
#include "myuart.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif // F_CPU
   volatile uint8_t *rch=NULL;
void eeprom_write_byte1(uint16_t addr, uint8_t data)
{
  while (EECR & (1 << EEPE)); /*wait until previous write any*/
  EEAR = addr;
  EEDR = data;
  EECR |= (1 << EEMPE);
  EECR |= (1 << EEPE);
}

uint8_t eeprom_read_byte1(uint16_t addr)
{
  while (EECR & (1 << EEPE)); /*wait until previous write any*/
  EEAR = addr;
  EECR |= (1 << EERE);
  return EEDR;
}
void  eeprom_read_byte_disp(uint16_t addr)
{
  uint8_t dat;
  while (EECR & (1 << EEPE)); /*wait until previous write any*/

  EEAR = addr;
  EECR |= (1 << EERE);
  dat=EEDR;
  UART_TxChar(dat);
}
/*assumes s is a proper null terminated string*/
void eeprom_write_string(uint16_t addr, char *s)
{
  while (*s)
  {
    eeprom_write_byte1(addr, *s );
    ++s;
    ++addr;
  }
}

/* read a string of len characters maximum starting at addr.
   modify according to your need!
*/
void eeprom_read_string(uint16_t addr,int len)
{
  while (len)
  {
    eeprom_read_byte_disp(addr);
    addr++;
    --len;
  }
  return;
}

int main(void)
{
  uint8_t rb8, wb8 = 'a',i;
  unsigned int addr=0x00,addr_copy=0x00,addr1 = 0x56;
  uint8_t *snd="string is stored in eeprom";
  unsigned int leng =sizeof(snd)/sizeof(snd[0]);
  UART_Init(9600);

  // Insert code

  while (1)
  {
     eeprom_write_string(addr1,snd);
     _delay_ms(50);
  //   eeprom_read_string(addr1,16);
    // UART_TxChar('\n');
      for(i=0;i<26;i++)
      {
      eeprom_write_byte1(addr,wb8++);
        addr=addr+1;
      } 
     _delay_ms(200);
     for(i=0;i<26;i++)
     {
     rb8=eeprom_read_byte1(addr--);
     UART_TxChar(rb8);
     UART_TxChar('\n');
     _delay_ms(200);
//    }
       //for(i=0;i<26;i++)      // reading an alphabet a-z into eeprom memory
//      //{
//        rb8=eeprom_read_byte1(addr_copy);
//        UART_TxChar(rb8);
//        UART_TxChar('\n');
//        ++addr_copy;
//        _delay_ms(200);
//      }
  }
  }

  return 0;
}
