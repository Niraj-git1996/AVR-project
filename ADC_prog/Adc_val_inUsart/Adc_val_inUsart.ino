/* We are using analog digital converter (ADC) there are 6 pin dedicated in atmega 328p PC0-PC5 .The code takes analog value 
  which is intially a 10 bit value(0-1023). It display a decimal value to  serial terminal using UART protocol.
  we are using arduino IDE to display sensor value. the varidics are also used to print constant string in serial terminal.
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdarg.h>
#include <stdint.h>
#include "mystdutil.h"

uint16_t ADCsingleREAD(uint8_t adctouse)
{
    uint16_t ADCval;

    ADMUX = adctouse;         // use #1 ADC
    //util_BitSet(ADMUX,adctouse);
    //ADMUX |= (1 << REFS0);    // use AVcc as the reference
    util_BitSet(ADMUX,REFS0);
    //ADMUX &= ~(1 << ADLAR);   // clear for 10 bit resolution
    util_BitClear(ADMUX,ADLAR);
    //ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);    // 128 prescale for 8Mhz
    util_BitSet(ADCSRA,ADPS2);
    util_BitSet(ADCSRA,ADPS1);
    util_BitSet(ADCSRA,ADPS0);
    //ADCSRA |= (1 << ADEN);    // Enable the ADC
    util_BitSet(ADCSRA,ADEN);
    //ADCSRA |= (1 << ADSC);    // Start the ADC conversion
   util_BitSet(ADCSRA,ADSC);
    while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish
   // while(util_IsBitCleared(ADCSRA,ADSC));
    ADCval = ADC;
    //ADCval = (ADCH << 8) + ADCval;    // ADCH is read so ADC can be updated again

    return ADCval;
}
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
    uint32_t temp;
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
int main()
{

   uint16_t ADCval;
   float f2;
   UART_Init(9600);
//    ADCval=ADCsingleREAD(0);
//    UART_Printf("the value is ");
//    UART_TxDecimal(ADCval);
//    UART_TxChar('\n');
   while(1)
   {
      ADCval=ADCsingleREAD(0);
    UART_Printf("the value in decimal : ");
    UART_TxDecimal(ADCval,4);
    f2=convert(ADCval);
    UART_TxChar('\t');
    UART_Printf("the value is float : ");
    UART_TxFloatNumber(f2);
    UART_TxChar('\n');
    _delay_ms(200);
   }

    return 0;
}
