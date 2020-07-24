/*the adc value is taken from adc data register for A0-A5 we take any two analog pin and store value
  compare two values and and depend upon the operation the buzzer or led on.
 */

#include <avr/io.h>
#include "mystdutil.h"
#define buzz (1<<PINB4)

volatile uint16_t ADC_val_0;
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
     DDRB|=buzz;
     PORTB&=~buzz;

    // Insert code

    while(1)
    {
        ADC_val_0=ADCsingleREAD(0);
        ADC_val_1=ADCsingleREAD(1);
        if(ADC_val_0>ADC_val_1)
            PORTB|=buzz;
        else
            PORTB&=~buzz;
    }

    return 0;
}
