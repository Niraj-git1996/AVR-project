## INPUT CAPTURE AND WAVEFORM GENERATION

**The Atmega 328p as pin PD4(T0) and PD5(T1) are used as taking external clock source from different pheriphals **

***the T0 increment the counter value in TCNT0 till the OCR0A and OCR0B match occured ***

***OCF0A flag is set in TIFR0 when match is occured***

***the T1 increment the counter value in TCNT1 till the OCR1A and OCR1B match occured***

***The clock select should be selected the external T0 pin as rising and falling ***









