/*
   total time cycle 200ms of which 100ms ON and 100ms OFF which makes the total duty cycle 50% of time.The clk=16MHZ
   and prescalar clk/1024=64us the timer is loaded (256-NN)x64us=total count,the pushbutton control will generate a wave until we
   pushbutton
 */

#include <avr/io.h>
#include<stdint.h>
#define F_CPU  16000000UL
# define led (1<<PINB2)
#define sw (1<<PINB4)
void Timer0(uint8_t k)
{
    ///TCCR0B=(1<<CS02)| (1<<CS00);   ///prescalar clk/1024
   uint8_t i;
   for(i=0;i<6;i++)
   {
       TCNT0=0;         /// count loaded for 100ms
        ///TCCR0B=(1<<CS02);
        TCCR0B=(1<<CS02)| (1<<CS00);/// prescalar F_CPU/1024
      while((TIFR0&0x01)==0);
      TCCR0B=0;
      TIFR0=0x01;
   }
}
int main(void)
{
  DDRB=(1<<DDB2);   ///the led pin is connected pb02
  DDRB &=(~(1<<DDB4));  /// pushbutton connected
    // Insert code

    while(1)
    {
        if(!(PINB&sw))    ///pushbutton control
        {
        PORTB^=led;  ///total time 200ms  the total duty cycle 50% of total time
        Timer0(1);      ///on time 100ms
        PORTB^=led;
        Timer0(1);    ///off time 100ms
        }
        else
            PORTB&=(~led);
    }

    return 0;
}


