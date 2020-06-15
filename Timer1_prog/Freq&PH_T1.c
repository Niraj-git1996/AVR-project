/*  In this program we used timer1 in frequency and  phase corrected Mode in atmega 328p .
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

void PWM_A(uint16_t k)
{
    OCR1A=k;
}
void PWM_B(uint16_t k)
{
    OCR1B=0x03ff-k;
}
int main(void)
{
   DDRB |= led|led_1;
    // PB1 and PB2 is now an output
  uint16_t move;
    ICR1 = 0xFFFF;
    // set TOP to 16bit

   OCR1A = 0x3FFF;
    // set PWM for 25% duty cycle @ 16bit
    //uint16_t move;
  OCR1B=0xBFFF;
    // set PWM for 75% duty cycle @ 16bit

    TCCR1A |= (1 << COM1A1)|(1 << COM1B1);
    // set none-inverting mode

   //TCCR1A |= (1 << WGM11)|(;
    TCCR1B |= (1 << WGM13);
    // set Frequency and phase corrected mode PWM mode using ICR1 as TOP

    TCCR1B |= (1 << CS10);
    // START the timer with no prescaler



   while (1);
   {

    // set prescaler to 8 and starts PWM
   }
}

