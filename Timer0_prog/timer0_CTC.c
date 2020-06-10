/*
   the timer0 is used in CTC mode of setting WGM02 bit in TCCR0A using prescalar F_CPU/1024
   and setting output compare register =250 and TCNT0=0 it will compare the OCOR0A with TCNT0 utill they are
   equal and OCF0 flag will set to 0,and tcnto will again to 0
 */

#include <avr/io.h>
#include<stdint.h>
#define F_CPU  16000000UL
# define led (1<<PINB2)
#define buzz (1<<PINB4)

int main(void)
{
 // DDRB=(1<<DDB2);   ///the led pin is connected pb02
  TCCR0B=(1<<CS02)|(1<<CS00);   ///F_CPU/1024=64us
  TCCR0A =(1<<WGM01);        ///making CTC mode by setting this bit
  OCR0A=250;               ///loading reg 250x64us=16ms
  TCNT0=0;
   DDRB=(1<<DDB2)|(1<<DDB4);   ///the led pin is connected pb02
   uint16_t i=0;
    // Insert code

    while(1)
    {

        while((TIFR0&(1<<OCF0A))==0);   ///OCF0 flag till 0
         PORTB^=led;     ///invert led port
        TCNT0=0;
        TIFR0|=(1<<OCF0A);

    }

    return 0;
}
