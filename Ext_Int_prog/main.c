/*in this program the Pin change interrupt is used to perform different operation .There are predefined pin change interrupt Pin
in atmega 328p.there are 22 PCINTx pin .The PCICR are used to enable or disable interrupt PCIE0(PCINT0-PCINT7)
    PCIE1(PCINT8-PCINT14)  and PCIE2(PCINT16-PCINT23)  . the particular Pin can be mask PCMSK0(PCINT0-PCINT7)
    PCMSK1(PCINT8-PCINT14)  and PCMSK2(PCINT16-PCINT23)
*/

#include <avr/io.h>
#include<avr/interrupt.h>    /// include interrupt header file
#include <util/delay.h>

#ifndef F_CPU
#define F_CPU  16000000UL
#endif // F_CPU

#define Int_0  (1<<PINB0)    /// PCINT0
#define  Int_1  (1<<PINB1)    /// PCINT1

#define  led_1 (1<<PIND0)   /// OUTPUT CONTROL BY PCINT0
#define  buzz   (1<<PIND1)    ///OUTPUT CONTROL BY PCINT1

void TimerInit()
{
     TCCR0B=(1<<CS02)|(1<<CS00);   ///F_CPU/1024=64us
  TCCR0A =(1<<WGM01);        ///making CTC mode by setting this bit
  OCR0A=250;               ///loading reg 250x64us=16ms
  TCNT0=0;
}
int main(void)
{
    DDRB &= (~Int_0)&(~Int_1);     // Clear the PB0 AND PB1pin
    // PB0 (PCINT0 pin) is now an input
    DDRD|=led_1|buzz;
    PORTB |= Int_0|Int_1;    // turn On the Pull-up
    // PB0 AND PB1is now an input with pull-up enabled
     //TimerInit();

    PCICR |= (1 << PCIE0);    // set PCIE0 to enable PCMSK0 scan
    PCMSK0 |= (1 << PCINT0)|(1<<PCINT1);  // set PCINT0 AND PCINT1 to trigger an interrupt on state change
    //TIMSK0=(1<<OCIE0A);
    sei();
    //sei();
    while(1);
    {


    }
    return 0;
}
ISR (PCINT0_vect)
{
    if(!(PINB&Int_0))    /// ACTIVE LOW
    {
       PORTD|=led_1;
    }
    else
        PORTD&=(~led_1);
    if(!(PINB&Int_1))    ///ACTIVE LOW
    {
        PORTD|=buzz;
    }
    else
        PORTD&=(~buzz);
//    if((PINB&Int_1))
//    {
//
//    }
//    else
//        PORTD&=(~buzz);
    /* interrupt code here */
}
