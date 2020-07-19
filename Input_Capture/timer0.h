#ifndef TIMER0_H_INCLUDED
#define TIMER0_H_INCLUDED

 #include<avr/io.h>

  enum clksource{T_stop=0x00,No_prescale,clk_div8,clk_div64,clk_div256,clk_div1024,
                         T0_falling,T0_rising}; /// related to TCCR0B

 enum comp_modeA{Normal_portA=0x00,toggle_OC0A=0x40,clear_OC0A=0x80,set_OC0A=0xC0};///related to TCCR0A

 enum comp_modeB{Normal_portB=0x00,toggle_OC0B=0x10,clear_OC0B=0x20,set_OC0B=0x30};/// related to TCCR0A

#endif // TIMER0_H_INCLUDED
