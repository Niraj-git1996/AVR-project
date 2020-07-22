/* The ADC is connected controller the adc value in decimal and float is display in 20x4 lcd 
 * the adc0 and adc1 value is display using LCD 4bit mode
 * value display is continuously on LCD 
 */
 #ifndef F_CPU 
 #define F_CPU 16000000UL
 #endif
#include"mylcd_4bit.h"


uint16_t ADCsingleREAD(uint8_t adctouse)
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

float convert(uint32_t val)
{
  float volt;
  volt=val*(5.0/1023.0);
  return volt;
}

int  main()
{
   uint16_t ADCval,ADCval_1;
  // float f2;
   LCDInit();
   LCDClear();
    LCDGotoXY(0,1);
    LCDWriteString("the ADC_0 val:");
    LCDGotoXY(0,2);
    LCDWriteString("The Float val:");
    LCDGotoXY(0,3);
    LCDWriteString("the ADC_1 val:");
    LCDGotoXY(0,4);
    LCDWriteString("The Float val:");
  while(1)
  {
     ADCval=ADCsingleREAD(0);
     ADCval_1=ADCsingleREAD(1);
    LCDGotoXY(14,1);
    LCD_dispDecimal(ADCval,4);
    LCDGotoXY(14,2);
    LCD_dispFloatNum(convert(ADCval));
    LCDGotoXY(14,3);
    LCD_dispDecimal(ADCval_1,4);
    LCDGotoXY(14,4);
    LCD_dispFloatNum(convert(ADCval_1));
  }
  return 0;
}
