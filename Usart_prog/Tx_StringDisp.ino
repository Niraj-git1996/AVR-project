/* follwing  code shows the USART prootocols implementation  transmit and receive the character using usart buffer UDRE0 the
 pin in atmega 328p is PD0 and PD1 are 
   used as transmit and receive.*/
   // display the char array with given index 
#include <avr/io.h>
#include <stdint.h>                     // needed for uint8_t
#include<util/delay.h>

#define FOSC 16000000UL                       // Clock Speed
#define BAUD 9600                   //  Baudrate
#define MYUBRR FOSC/16/BAUD -1    /// UBRR0H and UBRR0L register loading with calculation

char ReceivedChar;     /// char variable
// function to send data
void transmit_char (unsigned char data)
{
          while (!( UCSR0A & (1<<UDRE0))); /* Wait for empty transmit buffer*/
          UDR0 = data;            /* Put data into buffer, sends the data */
                                         // wait while register is free
                                       // load data in the register
}
void transmit_string(unsigned char *data)
{
     unsigned int i = 0;
        while(data[i] != 0) /* print the String  "Hello from ATmega328p" */
        {
          while (!( UCSR0A & (1<<UDRE0))); /* Wait for empty transmit buffer*/
          UDR0 = data[i];            /* Put data into buffer, sends the data */
          i++;                             /* increment counter           */
        }                                           // wait while register is free
            
}
// function to receive data
unsigned char uart_recieve (void)
{
    while(!(UCSR0A) & (1<<RXC0));                   // wait while data is being received
    return UDR0;                                   // return 8-bit data
}

int main()
{  
  unsigned char mydata[10][10]={"Apple","Bat","Cat","Dog","Egg","Fish","Grape","Hat"};   // char 2d array is of my data
   // unsigned char data1[]={"B for Bat"};
   unsigned int d=0;
    /* Set Baudrate  */
    UBRR0H = (MYUBRR>>8);
    UBRR0L = (MYUBRR);
 
  /// UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // Enable receiver and transmitter
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1 stp
     UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // Enable receiver and transmitter


    while(1)
    {
        ReceivedChar=uart_recieve();
          if(ReceivedChar >='a' && ReceivedChar <='h')   // check if receive char between given range 
          {
            d=ReceivedChar-'a';                        // char-'a' to get index of mydata array
             transmit_string(mydata[d]);               // callling with string to transmite
          }
          else
              transmit_char(ReceivedChar);    // display same as input 
      
            
          
          
    }
}//end of main
