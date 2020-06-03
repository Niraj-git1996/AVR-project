/* multiplexing 3 SSD with  digit count 000-999 continuously
 */

//#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#define buzz (1<<PINC3)    /// buzzer connected when equal digit display on both segment
#define switch_1  (1<<PINB0)   ///increment push button to increase counter
#define  switch_2  (1<<PINB1)    ///decrement push_button to decrease counter
#define seg1    (1<<PINC0)    /// to on the segment 1
#define  seg2  (1<<PINC1)    ///to o the segment 2
int main(void)
{
	DDRB = 0x00;    ///push button connected
	DDRC = 0xff;     ///on and off pin seven segment
	DDRD = 0xff;     ///data pin of seven segment
	unsigned int i,x=0,y,z;
	unsigned char arr1[]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
    while(1)
    {
        if((PINB&switch_1)==0x01)
		{
			x++;
			_delay_ms(100);
		}
		else if ((PINB&switch_2)==0x02)
		{
            if(x>0)
            {
			x--;
			_delay_ms(100);
            }
            else
                x=0;
		}

		 {

		    y=x/10;
			z=x%10;
		    PORTC=seg1;
			PORTD=arr1[y];
			_delay_ms(140);
			 PORTC=seg2;
		     PORTD=arr1[z];
			_delay_ms(120);
          if(arr1[y]==arr1[z])
          {
              PORTC=buzz;
              _delay_ms(80);
          }

		 }

    }
}

