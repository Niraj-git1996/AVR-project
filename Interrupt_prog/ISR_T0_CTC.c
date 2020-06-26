/* timer 0 using interrupt in CTC mode
*/

#include <avr/io.h>
#include<stdint.h>
#include<avr/interrupt.h>    /// include interrupt header file
#ifndef F_CPU
#define F_CPU  16000000UL
#endif // F_CPU
#define led_1 (1<<PINB5)
void timer0init()
{
     TCNT0=0;
   OCR0A=250;   /// 16ms delay
     TCCR0A=(1<<WGM01);   /// CTC mode
     TCCR0B=(1<<CS02)|(1<<CS00);   /// prescalar F_CPU/256
}
int main(void)
{
    DDRB|=(1<<DDB5);
   timer0init();
    TIMSK0=(1<<OCIE0A);   /// enable timer0 output compare  flag
    sei();   ///  set global interrupt enable on sreg register
    while(1);

}
/* ISR(interrupt vector name)
  {
  our program
  }
  */

  ISR(TIMER0_COMPA_vect)
  {
    PORTB^=led_1;
  }
