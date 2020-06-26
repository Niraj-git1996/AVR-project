/* timer 0 and 1 using interrupt in normal mode .both display simultaneously
*/

#include <avr/io.h>
#include<stdint.h>
#include<avr/interrupt.h>    /// include interrupt header file
#ifndef F_CPU
#define F_CPU  16000000UL
#endif // F_CPU
#define led_1 (1<<PINB5)
#define led_2 (1<<PINB6)
int main(void)
{
    DDRB|=(1<<DDB5)|(1<<DDB6);   /// led_1 and led_2 as a output
    TCNT0=6;    /// count for 4ms
   /// TCCR0A=0x00;
    TCCR0B=(1<<CS02);   /// prescalar is F_CPU/256
    TCNT1=0xFE0C;       /// count for 8ms
   /// TCCR1A=0x00;
    TCCR1B=(1<<CS12);    /// prescalar for F_CPU/256

    TIMSK0=(1<<TOIE0);   /// enable timer0 overflow flag
    TIMSK1=(1<<TOIE1);   /// enable timer1 overflow flag
    sei();   ///  set global interrupt enabke on sreg register
    while(1);

}
/* ISR(interrupt vector name)
  {
  our program
  }
  */
  ISR(TIMER0_OVF_vect)  /// ISR calling using vector name for timer0
  {
     TCNT0=6; /// loading again
      PORTB^=led_1;
  }
  ISR(TIMER1_OVF_vect)   /// ISR calling using vector name for timer1
  {
      TCNT1=0xFE0C;
      PORTB^=led_2;
  }
