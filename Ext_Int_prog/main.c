/*The Pin change interrupt is used to perform different operation .There are predefined pin change interrupt Pin
in atmega 328p.there are 22 PCINTx pin .The PCICR are used to enable or disable interrupt PCIE0(PCINT0-PCINT7)
    PCIE1(PCINT8-PCINT14)  and PCIE2(PCINT16-PCINT23)  . the particular Pin can be mask PCMSK0(PCINT0-PCINT7)
    PCMSK1(PCINT8-PCINT14)  and PCMSK2(PCINT16-PCINT23) If at specific pin interrupt is enable that is not use for any
    other purpose
*/
///  Tn this code the PCIE2 bit is set in PCICR and PCIMSK2 is enable pin change interrupt from PD0-PD7
#include <avr/io.h>
#include<avr/interrupt.h>    /// include interrupt header file
#include <util/delay.h>

#ifndef F_CPU
#define F_CPU  16000000UL
#endif // F_CPU

#define Int_16  (1<<PIND0)    /// PCINT16
#define  Int_17 (1<<PIND1)    /// PCINT7

#define  led_1 (1<<PINB0)   /// OUTPUT CONTROL BY PCINT16
#define  buzz   (1<<PINB1)    ///OUTPUT CONTROL BY PCINT7


int main(void)
{
    DDRD &= (~Int_16)&(~Int_17);     // Clear the PD0 AND PD1pin
    // PD0 AND PD1  is now an input
    DDRB|=led_1|buzz;
    PORTD |= Int_16|Int_17;    // turn On the Pull-up
    // PD0 AND PD1 is now an input with pull-up enabled
     //TimerInit();

    PCICR |= (1 << PCIE2);    // set PCIE2 to enable PCMSK2 scan
    PCMSK2 |= (1 << PCINT16)|(1<<PCINT17);  // set PCINT16 AND PCINT17 to trigger an interrupt on state change
    //TIMSK0=(1<<OCIE0A);
    sei();   /// SET THE GLOBAL INTERRUPT ENABLE
    //sei();
    while(1);
    {
   /// SIMULTANEOUSLY CAN DO MANY TASK

    }
    return 0;
}
ISR (PCINT2_vect)
{
    if(!(PIND&Int_16))    /// ACTIVE LOW
    {
       PORTB|=led_1;
    }
    else
        PORTB&=(~led_1);
    if(!(PIND&Int_17))    ///ACTIVE LOW
    {
        PORTB|=buzz;
    }
    else
        PORTB&=(~buzz);
//    if((PINB&Int_1))
//    {
//
//    }
//    else
//        PORTD&=(~buzz);
    /* interrupt code here */
}
