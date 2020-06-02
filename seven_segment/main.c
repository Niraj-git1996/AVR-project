/* It will continuously display digit 0-9 in SSD with push_button control(this code is for active low pushbutton output
 */

#include <avr/io.h>
#include<util/delay.h>
///#include <stdint.h>
#define F_CPU 1000000UL

int main(void)
{
   uint8_t di[]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F,0X77,0X7C,0X39,0X79,0X73,0X6F,0X74,0X38,0X3F,0X73,0X6D,0X3E};
   uint8_t cnt=0,st;
   st=sizeof(di)/sizeof(di[0]);
   DDRB=0XFF;
   DDRD|=(1<<DDD0);
   DDRD&=(~(1<<DDD1));
// Insert code

    while(1)
    {
        while(!(PIND&(1<<PIND1)))
        {
            if(cnt<st)
            {
             PORTD &=(~(1<<PIND0));
              PORTB =di[cnt++];
            _delay_us(10);
            PORTD |=(1<<PIND0);
            _delay_ms(500);
            }
            else
            {
                cnt=0;
                break;
            }
        }

//        for(cnt=0;cnt<st;cnt++)
//        {
//            PORTB =di[cnt];
//            _delay_us(100);
//            PORTD |=(1<<PIND0);
//            _delay_ms(500);
//            PORTD &=(~(1<<PIND0));
//            _delay_ms(100);
//        }
    }

    return 0;
}
