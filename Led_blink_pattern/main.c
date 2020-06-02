/*   first avr program to display differrnt led pattern on portb or u can display on any other port
 */

#include <avr/io.h>
#include<util/delay.h>
#define F_CPU 1000000UL
int main(void)
{
   unsigned  char z[]={0X01,0X03,0X07,0X0F,0X1F,0X3F,0X7F,0XFF,0xAA,0x55,0xF0,0x0F};
   char st=sizeof(z)/sizeof(z[0]);
   unsigned char b;
   DDRB |=(1<<DDB2)|(1<<DDB3);
//     Insert code
//  for(b=0;b<=st;b++)
//  {
//      PORTB=z[b];
//  }
    while(1)
    {
       PORTB |=(1<<PORTB2);
		PORTB &=~(1<<PORTB3);
		_delay_ms(1000);

		PORTB &=~(1<<PORTB2);
		PORTB |=(1<<PORTB3);
		_delay_ms(1000);

    }

    return 0;
}

