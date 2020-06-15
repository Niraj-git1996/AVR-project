/*
 */

#include <avr/io.h>
#include<avr/interrupt.h>    /// include interrupt header file
#include <util/delay.h>

#ifndef F_CPU
#define F_CPU  16000000UL
#endif // F_CPU



#define led_1  (1<<PIND0)
#define led_2   (1<<PIND1)

int main(void)
{
    DDRD&=(~(1<<DDD2))&(~(1<<DDD3));
    PORTD=0x0C;
    DDRD|=(1<<DDD0)|(1<<DDD1);
    //EICRA=(1<<ISC01)|(1<<ISC11);  /// external interrupt control register
    EIMSK=(1<<INT0)|(1<<INT1);   /// external interrupt mask register
    EICRA=(1<<ISC01)|(1<<ISC11);  /// external interrupt control register
    sei();
    while(1);
    return 0;
}

ISR(INT0_vect)
{
    PORTD^=led_1;

}

ISR(INT1_vect)
{
    PORTD^=led_2;

}
