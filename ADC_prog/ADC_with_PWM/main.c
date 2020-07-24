/*
 */

 #define F_CPU 16000000UL

#include <avr/io.h>
#include<avr/interrupt.h>
#include "timer1.h"
#include "mystdutil.h"

#define led (1<<PINB1)
#define led1 (1<<PINB2)

volatile uint16_t ADC_val;
volatile uint16_t ADC_val_1;

int16_t ADCsingleREAD(uint8_t adctouse)
{
    uint16_t ADCval;

    ADMUX = adctouse;         // use #1 ADC
    //util_BitSet(ADMUX,adctouse);
    //ADMUX |= (1 << REFS0);    // use AVcc as the reference
    util_BitSet(ADMUX,REFS0);
    //ADMUX &= ~(1 << ADLAR);   // clear for 10 bit resolution
    util_BitClear(ADMUX,ADLAR);
    //ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);    // 128 prescale for 8Mhz
    util_BitSet(ADCSRA,ADPS2);
    util_BitSet(ADCSRA,ADPS1);
    util_BitSet(ADCSRA,ADPS0);
    //ADCSRA |= (1 << ADEN);    // Enable the ADC
    util_BitSet(ADCSRA,ADEN);
    //ADCSRA |= (1 << ADSC);    // Start the ADC conversion
   util_BitSet(ADCSRA,ADSC);
    while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish
   // while(util_IsBitCleared(ADCSRA,ADSC));
    ADCval = ADC;
    //ADCval = (ADCH << 8) + ADCval;    // ADCH is read so ADC can be updated again

    return ADCval;
}

int main(void)
{
   DDRB|=led|led1;
   //OCR1A=0x03FF;
   TCNT1=0x00;
   TCCR1A|=mode3_A;  /// timer 1 in phase correct PWM mode
   TCCR1B|=mode3_B;
   TCCR1A|=toggle_OC1A;
   TCCR1A|=toggle_OC1B;
   TCCR1B|=clk_div1024;
   TIMSK1|=(1<<OCIE1A)|(1<<OCIE1B);
   sei();
    // Insert code

    while(1)
    {

      ADC_val=ADCsingleREAD(0);
      ADC_val_1=ADCsingleREAD(1);
    }

    return 0;
}
/// by using the timer in CTC mode the ADC value is given to OCR1A or OCR1B as per reguirement.
/// the OCR1A should be intialised
/// by using the timer in phase correct or fast pwm mode the ADC value is given to TCNT1 register.
ISR(TIMER1_COMPA_vect)
{
  TCNT1=ADC_val;
  //OCR1A=ADC_val;
}

ISR(TIMER1_COMPB_vect)
{
  TCNT1=ADC_val_1;
  //OCR1B=ADC_val_1;
}

