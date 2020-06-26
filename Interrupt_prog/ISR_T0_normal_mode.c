/* timer 0 using interrupt in normal mode
*/

#include <avr/io.h>
#include<stdint.h>
#include<avr/interrupt.h>    /// include interrupt header file
#ifndef F_CPU
#define F_CPU  8000000UL
#endif // F_CPU
#define led (1<<PINB5)

int main(void)
{
    DDRB|=(1<<DDB5);   /// led as a output
    TCNT0=6;    /// count for 8ms
    TCCR0B=(1<<CS02);   /// prescalar for F_CPU/256

    TIMSK0=(1<<TOIE0);   /// enable timer0 overflow flag in timer interrupt mask register
    sei();   ///  set interrupt enable
    while(1);

}
/* ISR(interrupt vector name)
  {
  our program
  }
  */
  ISR(TIMER0_OVF_vect)  /// ISR calling using vector name
  {
      TCNT0=6;
      PORTB^=led;
  }
