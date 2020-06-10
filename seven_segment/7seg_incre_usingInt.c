/*
 */

#include <avr/io.h>
#include<avr/interrupt.h>    /// include interrupt header file
#include <util/delay.h>

#ifndef F_CPU
#define F_CPU  16000000UL
#endif // F_CPU


#define seg1  (1<<PIND4);
#define seg2  (1<<PIND5);

volatile uint8_t x=0;


int main(void)
{
    DDRD&=(~(1<<DDD2))&(~(1<<DDD3));/// INT0=PD2 and INT1=PD3
    PORTD=0x0C;
    DDRD|=(1<<DDD4)|(1<<DDD5);
    DDRB=0xFF; /// output data pin of seven segment
    //EICRA=(1<<ISC01)|(1<<ISC11);  /// external interrupt control register
    unsigned int y,z;
	unsigned char arr1[]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
    EIMSK=(1<<INT0)|(1<<INT1);   /// external interrupt mask register
    EICRA=(1<<ISC01)|(1<<ISC11);  /// external interrupt control register
    sei();
    while(1)
    {
           y=x/10;
			z=x%10;
		    PORTD=seg1;
			PORTB=arr1[y];
			_delay_ms(500);
			 PORTD=seg2;
		     PORTB=arr1[z];
			_delay_ms(200);

    }
    return 0;
}

ISR(INT0_vect)    /// pin D2
{
    x++;
    _delay_ms(200);

}

ISR(INT1_vect)    /// pin D3
{

            if(x>0)
            {
			x--;
			_delay_ms(200);
            }
            else
                x=0;
}
