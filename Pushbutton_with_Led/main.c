/*
  The code contain push button control the led with AVR
  author:Niraj
 */

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 1000000UL

int main(void)
{
   DDRB |=(1<<DDB2)|(1<<DDB3)|(1<<DDB4);   /// making portB pin 2,3 and 4 as output and led is connected
   DDRB &=~(1<<DDB0)&(~(1<<DDB1));            /// making portB pin 0 and 1 will be input pushbutton is connected

    while(1)
    {
    if (!(PINB&(1<<PINB0)))     ///this pushbutton active low when pressing the push button led will glow
		{
		PORTB |= (1<<PINB2)|(1<<PINB3);
		}
		else
		{
		PORTB &= (~(1<<PINB2)) &(~(1<<PINB3));   ///led will off
		}
     if(!(PINB&(1<<PINB1)))
     {

         PORTB |=(1<<PINB4);             ///pin 4 has buzzer connected with it.
     }
     else
     {

         PORTB&=(~(1<<PINB4));
     }
    }

    return 0;
}
