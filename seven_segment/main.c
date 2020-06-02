/* multiplexing 3 SSD with  digit count 000-999 continuously
 */

#include <avr/io.h>
#include<util/delay.h>
#include <stdint.h>
#define F_CPU 1000000UL
#define seg1  (1<<PIND0)      ///pin 0 for segment 1
 #define seg2   (1<<PIND1)    /// pin 1 for segment 2
 #define seg3    (1<<PIND2)    ///pin 3 for segment 3
int main(void)
{
   uint8_t di[]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
   uint8_t cnt,st,i,j;
   st=sizeof(di)/sizeof(di[0]);
   DDRB=0XFF;
   DDRD |=(1<<DDD0);
   DDRD |=(1<<DDD1)|(1<<DDD2);


    while(1)
    {
        for(cnt=0;cnt<st;cnt++)
        {
           _delay_ms(10);
            for(i=0;i<st;i++)
            {
                for(j=0;j<st;j++)
                {
                PORTB=di[cnt];
                PORTD=seg1;
                _delay_ms(50);
                PORTD=~seg1;
                PORTB=di[i];
                PORTD=seg2;
                _delay_ms(50);
                PORTD=~seg2;
                PORTB=di[j];
                PORTD=seg3;
                _delay_ms(70);
                PORTD=~seg3;
                }
            }
        }

//        while(!(PIND&(1<<PIND1)))
//        {
//            if(cnt<st)
//            {
//             PORTD &=(~(1<<PIND0));
//              PORTB =di[cnt++];
//            _delay_us(10);
//            PORTD |=(1<<PIND0);
//            _delay_ms(500);
//            }
//            else
//            {
//                cnt=0;
//                break;
//            }
//        }

//
    }

    return 0;
}
