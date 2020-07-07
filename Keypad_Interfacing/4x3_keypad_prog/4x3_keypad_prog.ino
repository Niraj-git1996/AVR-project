/*
   the 4x3 keypad interfacing with avr 4 rows and 3 col are there. keypad are connected to port B
*/
#ifndef F_CPU 
#define F_CPU 16000000UL
#endif
#include "mystdutil.h"
#include "myuart.h"
#include <util/delay.h>

#define KEY_PRT  PORTB
#define KEY_DDR  DDRB
#define KEY_PIN  PINB

uint8_t keypad_lookup [4][3]={ {'1','2','3'},
                              {'4','5','6'},
                              {'7','8','9'},
                              {'*','0','#'}  };

/***************************************************************************************************
                             PORT configurations/Connections
 ****************************************************************************************************
           4X3 KEYPAD INTERFACING 
            _______________
           |    |    |    |    
           | 1  | 2  | 3  |--------- L1-->PB7
           |____|____|____|
           |    |    |    | 
           | 4  | 5  | 6  |--------- L2-->PB6
           |____|____|____|
           |    |    |    |   
           | 7  | 8  | 9  | --------- L3-->PB5
           |____|____|____|
           |    |    |    | 
           | *  | 0  | #  |--------- L4-->PB4
           |____|____|____|
             |    |    |    
             |    |    |                    PB0
             |    |    |
             |    |    |_________________ C3-->PB1
             |    |
             |    |______________________ C2-->PB2
             |
             |___________________________ C1-->PB3

 ****************************************************************************************************/




volatile uint8_t key;

int main()
{
  uint8_t collac,rowlac;
  KEY_DDR=0xF0;   /*  PB0 PB1 PB2 PB3 are input | PB4 PB5 PB6 PB7 are output */
    KEY_PRT=0xFF;  // making rows and columns are high

     while(1)
  {
    do
    {
      KEY_PRT&=0x0F;
      collac=(KEY_PIN&0x0F);
    }while(collac!=0x0F);
    do
    {
      do
      {
        _delay_ms(20);
        collac=(KEY_PIN&0x0F);
      }while(collac==0x0F);
      _delay_ms(20);
      collac=(KEY_PIN&0x0F);
    }while(collac!=0x0F);

    while(1)
    {
      KEY_PRT=0x7F;             //ground row 0
       collac=(KEY_PIN&0x0F);    // read the columns
       if(collac!=0x0F)       // colums detected
       {
        rowlac=0;    // save the roe location
        break;    // exit while loop
       }
       KEY_PRT=0xBF;             //ground row 1
       collac=(KEY_PIN&0x0F);    // read the columns
       if(collac!=0x0F)       // colums detected
       {
        rowlac=1;    // save the roe location
        break;    // exit while loop
       }
       KEY_PRT=0xDF;             //ground row 2
       collac=(KEY_PIN&0x0F);    // read the columns
       if(collac!=0x0F)       // colums detected
       {
        rowlac=2;    // save the row location
        break;    // exit while loop
       }
       KEY_PRT=0xEF;             //ground row 3
       collac=(KEY_PIN&0x0F);// read the columns
       if(collac!=0x0F)       // colums detected
       {
        rowlac=3;    // save the row location
        break;    // exit while loop
       }
       
    }
    if(collac==0x07)
      key=keypad_lookup[rowlac][0];
    else if(collac==0x0B)
      key=keypad_lookup[rowlac][1];
    else 
      key=keypad_lookup[rowlac][2];
     

     UART_TxChar(key);
  }
  return 0;
}
