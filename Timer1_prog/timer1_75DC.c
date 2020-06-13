/* total time of wave form is 100ms of which 75ms is ON and 25ms is OFF the 75% duty cycle. the timer1 is 16bit counter which can count 0000-FFFF
the timer count(TCNT1) is loaded for 25ms which is called multiple time for delay of 25xn ms to get count to load in
TCNT1=(65536-NN)x8us we used prescalar set is F_CPU/64.
 */

#include <avr/io.h>
#include <stdint.h>
#define F_CPU 16000000UL
#define  led (1<<PINB2)

void Timer1(uint8_t k)
{
    uint8_t i;
      TCCR1A=0X0;                        /// nothing set at TTCR1A
    TCCR1B=(1<<CS11)|(1<<CS10);         /// setting prescalar to F_CPU/64 in TCCR1B
 for(i=0;i<k;i++)                   /// calling 25xk times delay
 {
     TCNT1=0XE796;                    /// loading count for 25ms in TCNT1
     ///TCCR1B|=(1<<CS11)|(1<<CS10);
     while((TIFR1&0x01)==0);           /// timer overflow occur
     ///TCCR1B=0;
     TIFR1=0x01;
 }
}

int main(void)
{
   DDRB|=(1<<DDB2);   /// led port b as output

    while(1)
    {
        PORTB|=led;
        Timer1(3);    ///75ms  ON time
        PORTB&=(~led);  /// toggle led
        Timer1(1);     ///25ms OFF time
    }

    return 0;
}
