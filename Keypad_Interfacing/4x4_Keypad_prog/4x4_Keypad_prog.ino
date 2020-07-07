/*  In this code we interface 4x4 keypad with atmega 328 .we used port B of whuch 4 pins are ouput and 4 pins are input and port pin are high internally 
*/  
//note--> following code fails to detect the last columns key instead its take the 3rd  columns valuw if we press last columns key . 
#ifndef F_CPU 
#define F_CPU 16000000UL
#endif
#include "mystdutil.h"
#include "myuart.h"
#include <util/delay.h>

#define KEY_PRT  PORTB
#define KEY_DDR  DDRB
#define KEY_PIN  PINB

uint8_t keypad [4][4]={ {'1','2','3','A'},
                        {'4','5','6','B'},
                        {'7','8','9','C'},
                        {'*','0','#','D'}   };


/***************************************************************************************************
                             PORT configurations/Connections as per picsimlab
 ****************************************************************************************************
           4X4 KEYPAD INTERFACE WITH ATMEGA 328P
            ___________________
           |    |    |    |    |
           | 1  | 2  | 3  | A  |--------- L1-->PB4
           |____|____|____|____|
           |    |    |    |    |
           | 4  | 5  | 6  | B  |--------- L2-->PB5
           |____|____|____|____|
           |    |    |    |    |
           | 7  | 8  | 9  | C  |--------- L3-->PB6
           |____|____|____|____|
           |    |    |    |    |
           | *  | 0  | #  | D  |--------- L4-->PB7
           |____|____|____|____|
             |    |    |    |
             |    |    |    |____________ C4-->PB3
             |    |    |
             |    |    |_________________ C3-->PB2
             |    |
             |    |______________________ C2-->PB1
             |
             |___________________________ C1-->PB0

 ****************************************************************************************************/

volatile uint8_t key;
void Release_key()
{
  uint8_t collac;
   do
    {
      KEY_PRT&=0x0F;
      collac=(KEY_PIN&0x0F);
    }while(collac!=0x0F);
}
void Is_keypress()
{
  uint8_t collac;
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
}
int main()
{
  UART_Init(9600);
  uint8_t collac,rollac;
  KEY_DDR=0xF0;   /*  PB0 PB1 PB2 PB3 are input | PB4 PB5 PB6 PB7 are output */
    KEY_PRT=0xFF;  // making rows and columns are high


  while(1)
  {
     // Release_key();
      do
    {
      KEY_PRT&=0x0F;
      collac=(KEY_PIN&0x0F);
    }while(collac!=0x0F);
     // Is_keypress();
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
        rollac=3;    // save the row location
        break;    // exit while loop
       }
       KEY_PRT=0xBF;             //ground row 1
       collac=(KEY_PIN&0x0F);    // read the columns
       if(collac!=0x0F)       // colums detected
       {
        rollac=2;    // save the roe location
        break;    // exit while loop
       }
       KEY_PRT=0xDF;             //ground row 2
       collac=(KEY_PIN&0x0F);    // read the columns
       if(collac!=0x0F)       // colums detected
       {
        rollac=1;    // save the row location
        break;    // exit while loop
       }
       KEY_PRT=0xEF;             //ground row 3
       collac=(KEY_PIN&0x0F);// read the columns
       if(collac!=0x0F)       // colums detected
       {
        rollac=0;    // save the row location
        break;    // exit while loop
       }
    }
    if(collac==0x0E)
    {
      key=keypad[rollac][0];
      UART_TxChar(key);
    }
    else if(collac==0x0D)
    {
      key=keypad[rollac][1];
      UART_TxChar(key);
    }
    else if(collac=0x0B)
    {
      key=keypad[rollac][2];
      UART_TxChar(key);
    }
    else if(collac=0x07)
    {
      key=keypad[rollac][3];
      UART_TxChar(key);
    }
     // UART_TxChar(26);
  }
  return 0;
}
