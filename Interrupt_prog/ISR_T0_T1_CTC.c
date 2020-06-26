/* timer 0 and 1 using interrupt in CTC MODE .both display simultaneously
*/

#include <avr/io.h>
#include<stdint.h>
#include<avr/interrupt.h>    /// include interrupt header file
#ifndef F_CPU
#define F_CPU  16000000UL
#endif // F_CPU
#define led_1 (1<<PINB5)
#define  led_2  (1<<PINB6)
void timer0init()
{
     TCNT0=0;
   OCR0A=250;    /// COUNT FOR 16MS
     TCCR0A=(1<<WGM01);  /// SET BIT FOR CTC MODE
     TCCR0B=(1<<CS02)|(1<<CS00); ///prescalar F_CPU/1024
}
void timer1init()
{
    TCNT1=0;
    OCR1A=500;  ///  COUNT LOAD FOR 32MS
    //TCCR1A=0x00;
    TCCR1B=(1<<WGM12)|(1<<CS12)|(1<<CS10);   /// prescalar F_CPU/1024 AND CTC MODE

}
int main(void)
{
    DDRB|=(1<<DDB5)|(1<<DDB6);  ///  LED_1 AND LED_2 BLINK
   timer0init();
   timer1init();
    TIMSK0=(1<<OCIE0A);/// enable timer0 output compare interrupt enable
     TIMSK1=(1<<OCIE1A);/// enable timer1 output compare interrupt enable
    sei();   ///  set global interrupt enable on sreg register
    while(1);

}
/* ISR(interrupt vector name)
  {
  our program
  }
  */
  ISR(TIMER0_OVF_vect)  /// ISR calling using vector name for timer0
  {
     TCNT0=6;
      PORTB^=led_1;
  }
  ISR(TIMER1_OVF_vect)   /// ISR calling using vector name for timer1
  {
      TCNT1=0xFE0C;
      PORTB^=led_2;
  }
  ISR(TIMER0_COMPA_vect)   /// ISR CALLING 8BIT COMPARE REG IN TIMER0
  {
    PORTB^=led_1;
  }
  ISR(TIMER1_COMPA_vect)   /// ISR CALLINH 16BIT COMPARE REG IN TIMER1
  {
      PORTB^=led_2;
  }
