/*  In this program we used timer1 in 10 bit phase corrected Mode in atmega 328p using interrupt method.
  Pin PB1 and PB2 are dedicated  for PWM pin in TImer1 in atmega 328p In 10 bit timer overflow at 0x03FF.
  ocnxPCPWM =Fclk/[2*top*prescalar]
 */

#include <avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

#ifndef F_CPU
#define F_CPU  16000000UL
#endif // F_CPU

#define servo (1<<PIND6)   /// OCOA  PWM pin
#define servo1  (1<<PIND5)   /// OCOB PWM pin#

#define  led (1<<PINB1)    /// OC1A PWM pin
#define led_1  (1<<PINB2)   ///OC1B PWM PIN

#define  sw (1<<PIND1)

//void PWM_A(uint8_t k)
//{
//    OCR0A=k;
//}
//void PWM_B(uint8_t k)
//{
//    OCR0B=255-k;
//}
int main(void)
{
    ///uint8_t  brightness;
    DDRB |= led|led_1;   /// Pin PB1 has output for OC1A
    DDRD|=servo|servo1;
    DDRD&=(~sw);
   // PB1 as output
  // OCR1A = 0x01FF;
   OCR0A=0x80;
   // set PWM for 50% duty cycle at 10bit
   TCCR1A |= (1 << COM1A1)|(1<<COM1B1);
   //TCCR0A|=(1<<COM0A1);
   // set non-inverting mode
   TCCR1A |= (1 << WGM11)| (1 << WGM10);
//TCCR0A|=(1<<WGM00);

   // set 10bit phase corrected PWM Mode
   TCCR1B |= (1 << CS11);
  // TCCR0B|=(1<<CS01);
   TIMSK1|=(1<<OCIE1A)|(1<<OCIE1B);
   sei();
   // set prescaler to 8 and starts PWM
   while (1)
   {
       if(!(PIND&sw))
          {
              PORTD|=servo1;
          }
          else
            PORTD&=(~servo1);
    // set prescaler to 8 and starts PWM
   }
}
ISR(TIMER1_COMPA_vect)
{

    OCR1A=0x01FF;
}
ISR(TIMER1_COMPB_vect)
{

    OCR1B=0x02FF;
}
