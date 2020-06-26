#ifndef MYUART_H_INCLUDED
#define MYUART_H_INCLUDED


#include <avr\io.h>
#include <stdarg.h>
#include "mystdutil.h"

/***************************************************************************************************
                      PreCompile configurations to enable/disable the functions
****************************************************************************************************
PreCompile configuration to enable or disable the API's.
 1.Required interfaces can be enabled/disabled by configuring
   its respective macros to 1/0.
 2. By default all the API's are enabled except for FLOAT transmission.
 3. Transmitting of floating number takes huge controller
    resources and need to be enabled only if required.
	This implies for other interfaces as well.
***************************************************************************************************/
#define    Enable_UART_TxString          1
#define    Enable_UART_RxString          1
#define    Enable_UART_TxNumber          1
#define    Enable_UART_TxFloatNumber     0
#define    Enable_UART_Printf            1
/**************************************************************************************************/

/***************************************************************************************************
                             Commonly used UART macros/Constants
***************************************************************************************************/
#define C_DefaultDigitsToTransmit_U8          0xffu    // Will transmit the exact digits in the number
#define C_MaxDigitsToTransmit_U8              10u      // Max decimal/hexadecimal digits to be transmitted
#define C_NumOfBinDigitsToTransmit_U8         16u      // Max bits of a binary number to be transmitted
#define C_MaxDigitsToTransmitUsingPrintf_U8   C_DefaultDigitsToTransmit_U8 /* Max dec/hexadecimal digits to be displayed using printf */
/**************************************************************************************************/







/***************************************************************************************************
                             Function Prototypes
 ***************************************************************************************************/

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

uint8_t UART_RxChar(void)
{
  while(util_IsBitCleared(UCSR0A,RXC0));
        return UDR0;
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
uint8_t *UART_RxString()
{
  char ch;
    uint8_t len = 0;
    uint8_t *ptr_string=NULL;
  while(1)
  {
    ch=UART_RxChar();    //Receive a char

    if((ch=='\r') || (ch=='\n')) //read till enter key is pressed
    {                //once enter key is pressed null terminate the string
      ptr_string[len]=0;           //and break the loop
      break;          
    }
        else if((ch=='\b') && (len!=0))
        {
        len--;    //If backspace is pressed then decrement the index to remove the old char
        }
        else
        {
            ptr_string[len]=ch; //copy the char into string and increment the index
            len++;
        }
  }
       ptr_string=malloc(len*sizeof(uint8_t));
       return ptr_string;   
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
void UART_TxFloatNumber(float v_floatNumber_f32)
{
  uint32_t v_tempNumber_u32;
  /* Dirty hack to support the floating point by extracting the integer and fractional part.
      1.Type cast the number to int to get the integer part.
    2.transmit the extracted integer part followed by a decimal point(.).
    3.Later the integer part is made zero by subtracting with the extracted integer value.
    4.Finally the fractional part is multiplied by 100000 to support 6-digit precision */

  v_tempNumber_u32 = (uint32_t) v_floatNumber_f32;
  UART_TxNumber(C_DECIMAL_U8,v_tempNumber_u32,C_DefaultDigitsToTransmit_U8);

  UART_TxChar('.');

  v_floatNumber_f32 = v_floatNumber_f32 - v_tempNumber_u32;
  v_tempNumber_u32 = v_floatNumber_f32 * 1000000;
  UART_TxNumber(C_DECIMAL_U8,v_tempNumber_u32,C_DefaultDigitsToTransmit_U8);
}
#if(Enable_UART_Printf==1)
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
 #endif
 
#endif // MYUART_H_INCLUDED
