/*
  The code contain push button control the led with AVR
  author:Niraj
 */

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 1000000UL

int main(void)
{
   DDRB |=(1<<DDB2)|(1<<DDB3)|(1<<DDB4);   /// making portB pin 2 and 3 as output and led is connected
   DDRB &=~(1<<DDB0);            /// making portB pin 0 will be input pushbutton is connected

    while(1)
    {
    if (!(PINB&(1<<PINB0)))     ///this pushbutton active low when pressing the push button led will glow
		{
		PORTB |= (1<<PINB2)|(1<<PINB3)|(1<<PINB4);   ///pin 4 has buzzer connected with it.
		}
		else
		{
		PORTB &= (~(1<<PINB2)) &(~(1<<PINB3))&(~(1<<PINB4));   ///led will off and buzzer will off
		}
    }

    return 0;
}
