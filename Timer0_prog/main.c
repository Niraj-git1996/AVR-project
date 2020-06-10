/* timer 0 using interrupt in normal mode
*/

#include <avr/io.h>
#include<stdint.h>
#include<avr/interrupt.h>    /// include interrupt header file
#ifndef F_CPU
#define F_CPU  16000000UL
#endif // F_CPU
#define led (1<<PINB5)

int main(void)
{
    DDRB|=(1<<DDB5);   /// led as a output
    OCR0A=250;               ///loading reg 250x64us=16ms
    ///TCNT0=0;
    ///TCCR0B=(1<<CS02)|(1<<CS00);   ///F_CPU/1024=64us
    TCCR0A =(1<<WGM01);        ///making CTC mode by setting this bit
     TCCR0B=(1<<CS02)|(1<<CS00);   ///F_CPU/1024=64us
    TIMSK0=(1<<OCIE0A);   /// enable timer0 overflow flag in timer interrupt mask register
    sei();   ///  set interrupt enable
    while(1);

}
/* ISR(interrupt vector name)
  {
  our program
  }
//  */
//  ISR(TIMER0_OVF_vect)  /// ISR calling using vector name
//  {
//      TCNT0=6;
//      PORTB^=led;
//  }
ISR(TIMER0_COMP_vect)
{
    TCNT0=0;
    PORTB^=led;
}
