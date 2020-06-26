/* timer 0 and 1 using interrupt in CTC MODE .both display simultaneously
*/

#include <avr/io.h>
#include<stdint.h>
#include<avr/interrupt.h>    /// include interrupt header file
#include <util/delay.h>

#ifndef F_CPU
#define F_CPU  16000000UL
#endif // F_CPU
#define seg1  (1<<PIND0)      ///pin 0 for segment 1
 #define seg2   (1<<PIND1)    /// pin 1 for segment 2
 #define seg3    (1<<PIND2)    ///pin 3 for segment 3
#define led_1 (1<<PINC5)
#define  led_2  (1<<PINC4)
void timer0init()
{
     TCNT0=0;
   OCR0A=250;    /// COUNT FOR 16MS
     TCCR0A=(1<<WGM01);  /// SET BIT FOR CTC MODE
     TCCR0B=(1<<CS02)|(1<<CS00); ///prescalar F_CPU/1024
}
void timer1init()
{
    TCNT1=0;
    OCR1A=500;  ///  COUNT LOAD FOR 32MS
    //TCCR1A=0x00;
    TCCR1B=(1<<WGM12)|(1<<CS12)|(1<<CS10);   /// prescalar F_CPU/1024 AND CTC MODE

}

int main(void)
{
    DDRC|=(1<<DDC5)|(1<<DDC4);  ///  LED_1 AND LED_2 BLINK
     uint8_t di[]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
   uint8_t cnt,st,i,j;
   st=sizeof(di)/sizeof(di[0]);
    DDRB=0XFF;
   DDRD |=(1<<DDD0);
   DDRD |=(1<<DDD1)|(1<<DDD2);
   timer0init();
   timer1init();
    TIMSK0=(1<<OCIE0A);/// enable timer0 output compare interrupt enable
     TIMSK1=(1<<OCIE1A);/// enable timer1 output compare interrupt enable
    sei();   ///  set global interrupt enable on sreg registe

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

    }
  return 0;
}
/* ISR(interrupt vector name)
  {
  our program
  }
  */
  ISR(TIMER0_OVF_vect)  /// ISR calling using vector name for timer0
  {
     TCNT0=6;
      PORTB^=led_1;
  }
  ISR(TIMER1_OVF_vect)   /// ISR calling using vector name for timer1
  {
      TCNT1=0xFE0C;
      PORTB^=led_2;
  }
  ISR(TIMER0_COMPA_vect)   /// ISR CALLING 8BIT COMPARE REG IN TIMER0
  {
    PORTC^=led_1;
  }
  ISR(TIMER1_COMPA_vect)   /// ISR CALLINH 16BIT COMPARE REG IN TIMER1
  {
      PORTC^=led_2;
  }



