#ifndef TIMER0_H_INCLUDED
#define TIMER0_H_INCLUDED
/// the timer register loaded with ORing the value
 #include<avr/io.h>

  enum clksource{T_stop=0x00,No_prescale,clk_div8,clk_div64,clk_div256,clk_div1024,
                         T0_falling,T0_rising}; /// related to TCCR0B

 enum comp_modeA{Normal_portA=0x00,toggle_OC0A=0x40,clear_OC0A=0x80,set_OC0A=0xC0};///related to TCCR0A

 enum comp_modeB{Normal_portB=0x00,toggle_OC0B=0x10,clear_OC0B=0x20,set_OC0B=0x30};/// related to TCCR0A

 enum regA_mode{mode0_A=0x00,mode1_A=0x01,mode2_A=0x02,mode3_A=0x03,mode5_A=0x01,mode7_A=0x03};/// related to TCCR0A

 enum regB_mode{mode0_B=0x00,mode1_B=0x00,mode2_B=0x00,mode3_B=0x00,mode5_B=0x08,mode7_B=0x08};/// related to TCCR0B



#endif // TIMER0_H_INCLUDED
