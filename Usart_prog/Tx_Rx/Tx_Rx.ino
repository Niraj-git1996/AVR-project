/* follwing  code shows the USART prootocols implementation  transmit and receive the character using usart buffer UDRE0 the
 pin in atmega 328p is PD0 and PD1 are 
   used as transmit and receive.*/
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
                                     
            

// function to receive data
unsigned char uart_recieve (void)
{
    while(!(UCSR0A) & (1<<RXC0));                   // wait while data is being received
    return UDR0;                                   // return 8-bit data
}

int main()
{

   
    /* Set Baudrate  */
    UBRR0H = (MYUBRR>>8);   /// loading upper 4 bit to UBRR0H
    UBRR0L = (MYUBRR);    // loafing Lower 8 bit to UBRR0L
 
  /// UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // Enable receiver and transmitter
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1 stp
     UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // Enable receiver and transmitter


    while(1)
    {
        ReceivedChar=uart_recieve();  // RECEIVED FROM SERIAL TERMINAL
              transmit_char(ReceivedChar);  /// DISPLAY ON SERIAL TERMINAL
      
            
          
          
    }
}//end of main
