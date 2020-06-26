***ANALOG TO DIGITAL CONVERTER***


 ATmega168/328 has 6 different device pins but only 1 ADC (Analog to Digital Converter) converter.  
 The 6 input pins are connected to a multiplexer which basically allows a single input to be connected to the ADC in order to get a reading.  So we have to be smart about how to use our ADC and how to prioritize our readings.

 **THEORY OF OPERATION**


 	7 bit 	6 bit 	5 bit 	4 bit 	3 bit 	2 bit 	1 bit 	0 bit 
ADMUX	REFS1	REFS0 	ADLAR 	- 	MUX3 	MUX2 	MUX1 	MUX0 

**ADC Multiplexer Selection Register**


 REFS1	REFS0 	Voltage Reference Selection 
 0	     0 	       AREF, Internal Vref turned off 
 0	     1 	       AVcc with external capacitor on AREF pin 
 1	     0 	       Reserved 
 1	     1 	       Internal 1.1V (ATmega168/328) or  2.56V on (ATmega8)

*REF Bits*


 *ADLAR in the ADMUX Register is LOW (0)
 	    7 bit 	6 bit 	5 bit 	4 bit 	3 bit 	2 bit 	1 bit 	0 bit 
 ADCH	- 	- 	- 	- 	- 	- 	ADC9 	ADC8 
 ADCL	 ADC7	ADC6 	ADC5 	ADC4 	ADC3 	ADC2 	ADC1 	ADC0 

**ADC Data Register**


*ADLAR in the ADMUX Register is HIGH (1)*
 	    7 bit 	6 bit 	5 bit 	4 bit 	3 bit 	2 bit 	1 bit 	0 bit 
 ADCH	ADC9 	ADC8 	ADC7 	ADC6 	ADC5 	ADC4 	ADC3 	ADC2 
 ADCL	 ADC1	ADC0 	- 	- 	- 	- 	- 	-                        

**ADC Data Register**


 	     7 bit	6 bit 	5 bit 	4 bit 	3 bit 	2 bit 	1 bit 	0 bit 
 ADCSRA	ADEN 	ADSC 	ADFR* 	ADIF 	ADIE 	ADPS2 	ADPS1 	ADPS0 
NOTE * ADATE in ATmega168/328, ADFR in ATmega8

**ADC Control and Status Register A**

 ADPS2	ADPS1 	ADPS0 	Division Factor 
   0	0	       0	2 *
   0	0	       1	2 
   0	1	       0	4 
   0	1 	       1	8 
   1	0	       0	16 
   1	0	       1	32 
   1	1	       0	64 
   1	1	       1	128 

**ADPS Bits**

*ATmega168/328:*

Processor Clock Speed / 200k = x  (round up to next division factor)

eg.  Using a 1Mhz Clock
1MHrz / 200k = 
1,000,000 / 200,000 = 5
next highest = 8































