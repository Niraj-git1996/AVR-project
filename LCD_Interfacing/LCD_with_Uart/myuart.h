#ifndef MYUART_H_INCLUDED
#define MYUART_H_INCLUDED

#include <avr/io.h>
#include <stdarg.h>
#include <stdint.h>
#include "mystdutil.h"

#define F_CPU 16000000UL

/***************************************************************************************************/
#define C_DefaultDigitsToTransmit_U8          0xffu    // Will transmit the exact digits in the number
#define C_MaxDigitsToTransmit_U8              10u      // Max decimal/hexadecimal digits to be transmitted
#define C_NumOfBinDigitsToTransmit_U8         16u      // Max bits of a binary number to be transmitted
#define C_MaxDigitsToTransmitUsingPrintf_U8   C_DefaultDigitsToTransmit_U8 /* Max dec/hexadecimal digits to be displayed using printf */
/**************************************************************************************************/

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

uint8_t UART_RxChar(void)
{
  while(util_IsBitCleared(UCSR0A,RXC0));
        return UDR0;
}
 void UART_printf(const char *arglist,...)
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
 void UART_TxNumber(uint8_t v_numericSystem_u8, uint32_t v_number_u32, uint8_t v_numOfDigitsToTransmit_u8)
{
    uint8_t i=0,a[10];

    if(C_BINARY_U8 == v_numericSystem_u8)
    {
        while(v_numOfDigitsToTransmit_u8!=0)
        {
            /* Start Extracting the bits from the specified bit positions.
             Get the Acsii values of the bits and transmit */
            i = util_GetBitStatus(v_number_u32,(v_numOfDigitsToTransmit_u8-1));
            UART_TxChar(util_Dec2Ascii(i));
            v_numOfDigitsToTransmit_u8--;
        }    
    }     
    else if(v_number_u32==0)
    {
        /* If the number is zero then update the array with the same for transmitting */
        for(i=0;((i<v_numOfDigitsToTransmit_u8) && (i<C_MaxDigitsToTransmit_U8)) ;i++)
            UART_TxChar('0');
    }
    else
    {
        for(i=0;i<v_numOfDigitsToTransmit_u8;i++)
        {
            /* Continue extracting the digits from right side
               till the Specified v_numOfDigitsToTransmit_u8 */
            if(v_number_u32!=0)
            {
                /* Extract the digits from the number till it becomes zero.
                First get the remainder and divide the number by 10 each time.

                example for Decimal number:
                If v_number_u32 = 123 then extracted remainder will be 3 and number will be 12.
                The process continues till it becomes zero or max digits reached*/
                a[i]=util_GetMod32(v_number_u32,v_numericSystem_u8);
                v_number_u32=v_number_u32/v_numericSystem_u8;
            }
            else if( (v_numOfDigitsToTransmit_u8 == C_DefaultDigitsToTransmit_U8) ||
                    (v_numOfDigitsToTransmit_u8 > C_MaxDigitsToTransmit_U8))
            {
                /* Stop the iteration if the Max number of digits are reached or
                 the user expects exact(Default) digits in the number to be transmitted */ 
                break;
            }
            else
            {
                /*In case user expects more digits to be transmitted than the actual digits in number,
                  then update the remaining digits with zero.
                Ex: v_number_u32 is 123 and user wants five digits then 00123 has to be transmitted */
                a[i]=0;
            }
        }

        while(i)
        { 
            /* Finally get the ascii values of the digits and transmit*/
            UART_TxChar(util_Hex2Ascii(a[i-1]));
            i--;
        }
    }


}
void UART_Printf(const char *argList, ...)
{
  const char *ptr;
  va_list argp;
  int v_num_s16;
  long int v_num_s32;
  uint16_t v_num_u16;
  uint32_t v_num_u32;
  char *str;
  char  ch;
  uint8_t v_numOfDigitsToTransmit_u8;
#if (Enable_UART_TxFloatNumber==1)
  double v_floatNum_f32;
#endif  


  va_start(argp, argList);

  /* Loop through the list to extract all the input arguments */
  for(ptr = argList; *ptr != '\0'; ptr++)
  {

    ch= *ptr;
    if(ch == '%')         /*Check for '%' as there will be format specifier after it */
    {
        ptr++;
        ch = *ptr;
       if((ch>=0x30) && (ch<=0x39))
      {
         v_numOfDigitsToTransmit_u8 = 0;
         while((ch>=0x30) && (ch<=0x39))
          {
           v_numOfDigitsToTransmit_u8 = (v_numOfDigitsToTransmit_u8 * 10) + (ch-0x30);
           ptr++;
           ch = *ptr;
        }
      }
      else
      {
        v_numOfDigitsToTransmit_u8 = C_MaxDigitsToTransmitUsingPrintf_U8;
      }       


      switch(ch)       /* Decode the type of the argument */
      {
      case 'C':
      case 'c':     /* Argument type is of char, hence read char data from the argp */
        ch = va_arg(argp, int);
        UART_TxChar(ch);
        break;

      case 'd':    /* Argument type is of signed integer, hence read 16bit data from the argp */
        v_num_s16 = va_arg(argp, int);
        if(v_num_s16<0)
         { /* If the number is -ve then display the 2's complement along with '-' sign */ 
           v_num_s16 = -v_num_s16;
           UART_TxChar('-');
         }
        UART_TxNumber(C_DECIMAL_U8,v_num_s16,v_numOfDigitsToTransmit_u8);
        break;
        
      case 'D':    /* Argument type is of integer, hence read 16bit data from the argp */
        v_num_s32 = va_arg(argp, long int);       
        if(v_num_s32<0)
         { /* If the number is -ve then display the 2's complement along with '-' sign */
           v_num_s32 = -v_num_s32;
           UART_TxChar('-');
         }
        UART_TxNumber(C_DECIMAL_U8,v_num_s32,v_numOfDigitsToTransmit_u8);     
        break;  

      case 'u':    /* Argument type is of unsigned integer, hence read 16bit unsigned data */
        v_num_u16 = va_arg(argp, uint16_t);     
        UART_TxNumber(C_DECIMAL_U8,v_num_u16,v_numOfDigitsToTransmit_u8);       
        break;
      
      case 'U':    /* Argument type is of integer, hence read 32bit unsigend data */
        break;      

      case 'x':  /* Argument type is of hex, hence hexadecimal data from the argp */
        v_num_u16 = va_arg(argp, uint16_t);       
        UART_TxNumber(C_HEX_U8,v_num_u16,v_numOfDigitsToTransmit_u8);     
        break;

      case 'X':  /* Argument type is of hex, hence hexadecimal data from the argp */
        v_num_u32 = va_arg(argp, uint32_t);           
        UART_TxNumber(C_HEX_U8,v_num_u32,v_numOfDigitsToTransmit_u8);       
        break;

      
      case 'b':  /* Argument type is of binary,Read int and convert to binary */
        v_num_u16 = va_arg(argp, uint16_t);   
        
        if(v_numOfDigitsToTransmit_u8 == C_MaxDigitsToTransmitUsingPrintf_U8)
           v_numOfDigitsToTransmit_u8 = 16;
               
        UART_TxNumber(C_BINARY_U8,v_num_u16,v_numOfDigitsToTransmit_u8);      
        break;

      case 'B':  /* Argument type is of binary,Read int and convert to binary */
        v_num_u32 = va_arg(argp, uint32_t);     
                
        if(v_numOfDigitsToTransmit_u8 == C_MaxDigitsToTransmitUsingPrintf_U8)
           v_numOfDigitsToTransmit_u8 = 32;   
               
        UART_TxNumber(C_BINARY_U8,v_num_u32,v_numOfDigitsToTransmit_u8);        
        break;


      case 'F':
      case 'f': /* Argument type is of float, hence read double data from the argp */
#if (Enable_UART_TxFloatNumber==1)        
        v_floatNum_f32 = va_arg(argp, double);        
        UART_TxFloatNumber(v_floatNum_f32);
#endif            
        break;                


      case 'S':
      case 's': /* Argument type is of string, hence get the pointer to sting passed */
        str = va_arg(argp, char *);
        UART_TxString(str);     
        break;

      case '%':
        UART_TxChar('%');
        break;
      }
    } 
    else
    {
      /* As '%' is not detected transmit the char passed */
      UART_TxChar(ch);
    }
  }

  va_end(argp);
}

void UART_TxDecimal(uint32_t  num,uint8_t k)
{
    uint32_t temp;
    uint32_t sd[6]={0};
    uint8_t i=0;
    while(num!=0)
    {
        temp=util_GetMod32(num,C_DECIMAL_U8 );
        sd[i]=util_Dec2Ascii(temp);
        //UART_TxChar(sd);
        num=num/C_DECIMAL_U8;
        i++;
    }
    while(k--)
    {
      UART_TxChar(sd[k]);
    }
}

void UART_TxHex(uint32_t  num,uint8_t k)
{
    uint32_t temp;
    uint32_t sd[6]={0};
    uint8_t i=0;
    while(num!=0)
    {
        temp=util_GetMod32(num,C_HEX_U8);
        sd[i]=util_Hex2Ascii(temp);
        //UART_TxChar(sd);
        num=num/C_HEX_U8;
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
