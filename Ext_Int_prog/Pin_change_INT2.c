/*The Pin change interrupt is used to perform different operation .There are predefined pin change interrupt Pin
in atmega 328p.there are 22 PCINTx pin .The PCICR are used to enable or disable interrupt PCIE0(PCINT0-PCINT7)
    PCIE1(PCINT8-PCINT14)  and PCIE2(PCINT16-PCINT23)  . the particular Pin can be mask PCMSK0(PCINT0-PCINT7)
    PCMSK1(PCINT8-PCINT14)  and PCMSK2(PCINT16-PCINT23)
*/
///  Tn this code the PCIE0 bit is set in PCICR and PCIMSK1 is enable pin change interrupt from PC0-PC6
#include <avr/io.h>
#include<avr/interrupt.h>    /// include interrupt header file
#include <util/delay.h>

#ifndef F_CPU
#define F_CPU  16000000UL
#endif // F_CPU

#define Int_8  (1<<PINC0)    /// PCINT8
#define  Int_9  (1<<PINC1)    /// PCINT9

#define  led_1 (1<<PIND0)   /// OUTPUT CONTROL BY PCINT8
#define  buzz   (1<<PIND1)    ///OUTPUT CONTROL BY PCINT9

void TimerInit()
{
     TCCR0B=(1<<CS02)|(1<<CS00);   ///F_CPU/1024=64us
  TCCR0A =(1<<WGM01);        ///making CTC mode by setting this bit
  OCR0A=250;               ///loading reg 250x64us=16ms
  TCNT0=0;
}
int main(void)
{
    DDRB &= (~Int_8)&(~Int_9);     // Clear the PC0 AND PC1pin
    // PC0 AND PC1  is now an input
    DDRD|=led_1|buzz;
    PORTC |= Int_8|Int_9;    // turn On the Pull-up
    // PC0 AND PC1 is now an input with pull-up enabled
     //TimerInit();

    PCICR |= (1 << PCIE1);    // set PCIE1 to enable PCMSK1 scan
    PCMSK1 |= (1 << PCINT8)|(1<<PCINT9);  // set PCINT8 AND PCINT9 to trigger an interrupt on state change
    //TIMSK0=(1<<OCIE0A);
    sei();   /// SET THE GLOBAL INTERRUPT ENABLE
    //sei();
    while(1);
    {
   /// SIMULTANEOUSLY CAN DO MANY TASK

    }
    return 0;
}
ISR (PCINT1_vect)
{
    if(!(PINC&Int_8))    /// ACTIVE LOW
    {
       PORTD|=led_1;
    }
    else
        PORTD&=(~led_1);
    if(!(PINC&Int_9))    ///ACTIVE LOW
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
