/* Input capture waveform waveform generation the input capture is done by T0 pin(PD4) in atmega 328p
*  It increments the TCNT0 value till OCR0A
 */

#include <avr/io.h>
#define F_CPU 16000000UL;
#include "timer0.h"
#define button  (1<<PIND4)    /// T0 pin
#define  led  (1<<PIND6)   ///ocoA

int main(void)
{
  DDRD&=~button; ///input button
   DDRD|=led;
   OCR0A=0x01;///set the external counter value in OCR0A number of times-2
   TCNT0=0x00;
   ///TCCR0A|=set_OC0A;  ///after the counter value of external clock turn on LED connected to OC0//
    TCCR0A|=toggle_OC0A;/// It toggles the led on OC0 pin after the certain external clock
    TCCR0B|=T0_rising; ///clock count after rising edge
    //  TCCR0B|=T0_falling;/// clock count after falling edge
// Insert code

    while(1)
    {
       while((TIFR0&(1<<OCF0A))==0);
         //OCR0A=3;
         TCNT0=0;
        TIFR0|=(1<<OCF0A);

    }


    return 0;
}
