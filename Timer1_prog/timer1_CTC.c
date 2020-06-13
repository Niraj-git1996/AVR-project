/* the CTC mode by setting WGM12 in TCCR1A   register and TCCR1B register  for prescalar F_CPU/64 and waiting for OCF1A to overflow
  and reset timer
 */

#include <avr/io.h>
#include <stdint.h>
#define F_CPU 16000000UL
#define  led (1<<PINB2)



int main(void)
{
   DDRB|=(1<<DDB2);   /// led port b as output
    TCCR1A=(1<<WGM12);                        /// TTCR1A WGM12 set for CTC mode
    TCCR1B=(1<<CS11)|(1<<CS10);     /// prescalar F_CPU/64
    OCR1A=0x4E20;   /// count for 80ms delay
    TCNT1=0;
    while(1)
    {
          while((TIFR1&(1<<OCF1A))==0);   /// wait for OCF1A to 0
          PORTB^=led;                         /// Invert the led
          TCNT1=0;                     /// reset the timer count register
          TIFR1|=(1<<OCF1A);    /// reset the OCF1A

    }

    return 0;
}
