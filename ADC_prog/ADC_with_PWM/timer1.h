#ifndef TIMER1_H_INCLUDED
#define TIMER1_H_INCLUDED

#include<avr/io.h>
/// used ORing operation with TCCR1A or TCCR1B

enum clksource{T_stop=0x00,No_prescale,clk_div8,clk_div64,clk_div256,clk_div1024,
                         T0_falling,T0_rising}; /// related to TCCR1B

enum comp_modeA{Normal_portA=0x00,toggle_OC1A=0x40,clear_OC1A=0x80,set_OC1A=0xC0};///related to TCCR1A

enum comp_modeB{Normal_portB=0x00,toggle_OC1B=0x10,clear_OC1B=0x20,set_OC1B=0x30};/// related to TCCR1A

enum regA_mode{mode0_A=0x00,mode1_A=0x01,mode2_A=0x02,mode3_A=0x03,mode4_A=0x00,mode5_A=0x01,mode6_A=0x02,mode7_A=0x03,
                mode8_A=0x00,mode9_A=0x01,mode10_A=0x02,mode11_A=0x03,mode12_A=0x00,mode14_A=0x02,mode15_A=0x03};
                /// related to TCCR1A

enum regB_mode{mode0_B=0x00,mode1_B=0x00,mode2_B=0x00,mode3_B=0x00,mode4_B=0x08,mode5_B=0x08,mode6_B=0x08,
                mode7_B=0x08,mode8_B=0x10,mode9_B=0x10,mode10_B=0x10,mode11_B=0x10,mode12_B=18,mode14_B=0x18,mode15_B=0x18};
              /// realted to TCCR1B





#endif // TIMER1_H_INCLUDED
