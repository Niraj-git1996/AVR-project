/*
  The code contain push button control the led with AVR
  author:Niraj
 */

#include <avr/io.h>
#include <util/delay.h>
#include "mystdutil.h"
#define F_CPU 1000000UL

int main(void)
{
    util_BitSet(DDRB,2);
    util_BitSet(DDRB,3);
    util_BitSet(DDRB,4);
   //DDRB |=(1<<DDB2)|(1<<DDB3)|(1<<DDB4);   /// making portB pin 2,3 and 4 as output and led is connected
   ///DDRB &=~(1<<DDB0)&(~(1<<DDB1));            /// making portB pin 0 and 1 will be input pushbutton is connected
   util_BitClear(DDRB,0);
   util_BitClear(DDRB,1);
  // util_BitSet(PORTB,0);   /// INERNAL PULL-UP
   //util_BitSet(PORTB,1);   /// INERNAL PULL-UP ACTIVE

    while(1)
    {
    //if (!(PINB&(1<<PINB0)))     ///this pushbutton active low when pressing the push button led will glow
   if(util_IsBitCleared(PINB,0))
		{
		PORTB |= (1<<PINB4)|(1<<PINB3);
		}
		else
		{
		PORTB &= (~(1<<PINB4)) &(~(1<<PINB3));   ///led will off
		}
     //if(!(PINB&(1<<PINB1)))
     if(util_IsBitCleared(PINB,1))
     {

         PORTB |=(1<<PINB2);             ///pin 4 has buzzer connected with it.
     }
     else
     {

         PORTB&=(~(1<<PINB2));
     }
    }

    return 0;
}
