/*   total time cycle 80ms of which 48ms ON and 32ms OFF which makes the total duty cycle 60% of time.The F_CPU=8MHZ
   and prescalar clk/256=32us the timer is loaded (256-NN)x32us=total count
 */

#include <avr/io.h>
#include<stdint.h>
#define F_CPU  8000000UL
# define led (1<<PINB2)
void Timer0(uint8_t k)
{
    TCCR0B=(1<<CS02);     /// prescalar set is F_CPU/256
   uint8_t i;
   for(i=0;i<k;i++)
   {
       TCNT0=6;     /// timer count for 8ms
        ///TCCR0B=(1<<CS02);
      while((TIFR0&0x01)==0);
      /// TCCR0B=0;
      TIFR0=0x01;
   }
}
int main(void)
{
  DDRB=(1<<DDB2);   ///the led pin is connected pb02
    // Insert code

    while(1)
    {
        PORTB|=led;  ///total time 80ms  the total duty cycle 60% of total time
        Timer0(6);      ///on time 48ms
        PORTB&=(~led);
        Timer0(4);    ///off time 32ms

    }

    return 0;
}

