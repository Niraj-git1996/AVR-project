//#include <avr/io.h>
#include "myuart.h"
#include "mystdutil.h"
#include <string.h>
#include<stdint.h>
#include<util/delay.h>
//#define F_CPU 16000000UL



int main(void)
{
 // uint8_t len;
  
  int val;
  float f2;
  UART_Init(9600);

  // Insert code

  while (1)
  {
   
   // str1=UART_RxString();
   // str1 = (uint8_t*)calloc(leng, sizeof(uint8_t));
   //f2=convert(val);
   //UART_TxString(send);
   UART_Printf("the value code is\n");
  // UART_TxFloatNumber(f2);
  // UART_TxNumber(10,val,C_DefaultDigitsToTransmit_U8);
  // UART_TxChar('\n');
   _delay_ms(200);
    
    
    
  }

  return 0;
}
