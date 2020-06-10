This folder contain timer0 related code where timer0 used as 
normal mode,CTC  mode , and generating 60% and 80% duty cycle.
The switch control wave program contain output is display until 
pushbutton is hold.
It uses different registers
Timer 0 is a 8 bit timer. It basically means it can count from 0 to 2^8 255.
 The operation of timer 0 is straight forward. The TCNT0 register hold the timer Count and it is incremented on every timer "tick".
 If the timer is turned on it ticks from 0 to 255 and overflows. If it does so, a Timer OverFlow Flag(TOV) is set.

You can as well load a count value in TCNT0 and start the timer from a specific count. 
Another interesting feature is that a value can be set in the Output Compare Register (OCR0), 
and whenever TCNT0 reaches that value, the Output Compare Flag (OCF0) flag is Set.
 TCCR0 register
The Frequency of the Clock Source with CS02, CS01, CS00 bits.
