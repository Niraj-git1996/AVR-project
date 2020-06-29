#ifndef MYUART_H_INCLUDED
#define MYUART_H_INCLUDED

#include <avr/io.h>
#include <stdarg.h>

#include "mystdutil.h"

#define F_CPU 16000000UL
void UART_Init(uint16_t v_baudRate_u16)
{

   uint16_t MYUBRR=F_CPU/16/v_baudRate_u16 -1;

   UBRR0L=util_ExtractByte0to8(MYUBRR);
   UBRR0H=util_ExtractByte8to16(MYUBRR);
   util_BitSet(UCSR0C,UCSZ01);
   util_BitSet(UCSR0C,UCSZ00);
   UCSR0A=0X00;
   util_BitSet(UCSR0B,RXEN0);
   util_BitSet(UCSR0B,TXEN0);
}
void UART_TxChar(char uartData_u8)
{
  while(util_IsBitCleared(UCSR0A,UDRE0));
          UDR0=uartData_u8;
}
void UART_TxString(unsigned char *data)
{
   unsigned int i = 0;
        while(data[i] != 0) /* print the String  "Hello from ATmega328p" */
        {
          while (!( UCSR0A & (1<<UDRE0))); /* Wait for empty transmit buffer*/
          UDR0 = data[i];            /* Put data into buffer, sends the data */
          i++;                             /* increment counter           */
        }                                           // wait while register is free


}
 void UART_Printf(const char *arglist,...)
 {
  const char *ptr;
  char ch;
  va_list argp;
  va_start(argp, arglist);
  for(ptr=arglist;*ptr!='\0';ptr++)
  {
    ch=*ptr;
    UART_TxChar(ch);
  }
  va_end(argp);
 }

void UART_TxDecimal(uint32_t  num,uint8_t k)
{
    uint8_t temp;
    uint8_t sd[k]={0};
    uint8_t i=0;
    while(num!=0)
    {
        temp=num%10;
        sd[i]=util_Dec2Ascii(temp);
        //UART_TxChar(sd);
        num=num/10;
        i++;
    }
    while(k--)
    {
      UART_TxChar(sd[k]);
    }
}
void UART_TxFloatNumber(float v_floatNumber_f32)
{
  uint32_t v_tempNumber_u32;
  v_tempNumber_u32 = (uint32_t) v_floatNumber_f32;
  UART_TxDecimal(v_tempNumber_u32,4);
  UART_TxChar('.');
  v_floatNumber_f32 = v_floatNumber_f32 - v_tempNumber_u32;
  v_tempNumber_u32 = v_floatNumber_f32 * 10000;
  UART_TxDecimal(v_tempNumber_u32,5);
}

float convert(uint32_t val)
{
  float volt;
  volt=val*(5.0/1023.0);
  return volt;
}


#endif // MYUART_H_INCLUDED
