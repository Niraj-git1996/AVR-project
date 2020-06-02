/*
 */

#include <avr/io.h>
#include<util/delay.h>
#include <stdint.h>
#define F_CPU 1000000UL

int main(void)
{
   uint8_t di[]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
   uint8_t cnt,st;
   st=sizeof(di)/sizeof(di[0]);
   DDRB=0XFF;
   DDRD|=(1<<DDD0);
// Insert code

    while(1)
    {
        for(cnt=0;cnt<st;cnt++)
        {
            PORTB =di[cnt];
            _delay_us(100);
            PORTD |=(1<<PIND0);
            _delay_ms(500);
            PORTD &=(~(1<<PIND0));
            _delay_ms(100);
        }
    }

    return 0;
}
