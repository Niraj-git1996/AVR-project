/*  In this we used two output compare register of  timer0 which is of 8 bit OCR0A and OCR0B.
  It program create variable duty cycle wave to get led dim and glow regularly at 200ms delay
  As timer0 PWM pin in Atmega 328p is PD5 and PD6 are respectively for ocoa and ocob
  we use Fast PWM mode  */

#include <avr/io.h>
#include<util/delay.h>
#ifndef F_CPU
#define F_CPU  16000000UL
#endif // F_CPU

#define servo (1<<PIND6)   /// OCOA  PWM pin
#define servo1  (1<<PIND5)   /// OCOB PWM pin

void PWM_A(uint8_t k)
{
    OCR0A=k;
}
void PWM_B(uint8_t k)
{
    OCR0B=255-k;
}
int main(void)
{
    uint8_t  brightness;
    DDRD |= servo|servo1;
    // PD6 is now an output
    ///PD5 is now as output
    // set PWM for  duty cycle varies


    TCCR0A |= (1 << COM0A1)|(1<<COM0B1);
    // using OCR0A and OCR0B has none-inverting mode

    TCCR0A |= (1 << WGM00)|(1<<WGM01);
    // set fast PWM Mode

    TCCR0B |= (1 << CS01);
    // set prescaler to 8 and starts PWM


    while (1)
    {
        // we have a working Fast PWM
           for (brightness = 0; brightness < 255; ++brightness)
        {
            // set the brightness as duty cycle
            PWM_A(brightness);   /// compare A high
            PWM_B(brightness);    /// compare B low
            // delay so as to make the user "see" the change in brightness
            _delay_ms(200);

        }
        for (brightness = 255; brightness > 0; --brightness)
        {
            // set the brightness as duty cycle
            PWM_A(brightness);
            PWM_B(brightness);
            // delay so as to make the user "see" the change in brightness
            _delay_ms(200);
        }
    }
}
