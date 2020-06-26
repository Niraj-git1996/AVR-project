/* This code waits for a character and transmits the character back (with interrupts)  
  with using usart receive interrupt vector the .The pin PD0 and PD1 are dedicated for Transmit and Receive in atmega 328p
  */
 

#include <avr/io.h>
#include <stdint.h>                     // needed for uint8_t

#include <avr/interrupt.h>           /// using interrupt header file to include vector



#define FOSC 16000000                       // Clock Speed
#define BAUD 9600                    // buad rate is 9600 bps
#define MYUBRR FOSC/16/BAUD -1


volatile char ReceivedChar;


int main( void )
{
    /*Set baud rate */
    UBRR0H = (MYUBRR >> 8);
    UBRR0L = MYUBRR;
    
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // Enable receiver and transmitter
    UCSR0B |= (1 << RXCIE0);                    // Enable reciever interrupt flag
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1 stp

    sei();                                      // Lets not forget to enable interrupts =P serting this bit in SREG

    while(1);
    {
                                             // Main loop
    }    
}

ISR (USART_RX_vect)   // ISR calling at particular vector location 
{
    ReceivedChar = UDR0;                       // Read data from the RX buffer
    UDR0 = ReceivedChar;                       // Write the data to the TX buffer
}
