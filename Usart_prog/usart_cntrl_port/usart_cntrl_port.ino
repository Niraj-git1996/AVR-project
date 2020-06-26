/* follwing  code shows the USART prootocols implementation  transmit and receive the character using usart buffer UDRE0 the
 pin in atmega 328p is PD0 and PD1 are 
   used as transmit and receive.*/
#include <avr/io.h>
#include <stdint.h>                     // needed for uint8_t
#include<util/delay.h>

#define FOSC 16000000UL                       // Clock Speed
#define BAUD 9600                   //  Baudrate
#define MYUBRR FOSC/16/BAUD -1    /// UBRR0H and UBRR0L register loading with calculation

#define led  (1<<PINB0)  
#define  buzz  (1<<PINB1)
#define led_1  (1<<PINB2)

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
   DDRB|=led|buzz|led_1;
   unsigned char camnd[10][20]={"led on PB0 is ON\n","led on PB0 is OFF\n","buzz on PB1 is ON\n","buzz on PB1 is OFF\n",
                                 "led on PB2 is ON\n","led on PB2 is OFF\n","Invalid Input\n"};
    /* Set Baudrate  */
    UBRR0H = (MYUBRR>>8);
    UBRR0L = (MYUBRR);
 
  /// UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // Enable receiver and transmitter
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1 stp
     UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // Enable receiver and transmitter


    while(1)
    {
        ReceivedChar=uart_recieve();
        if(ReceivedChar!='\0' && ReceivedChar!='\n')
        {
        switch(ReceivedChar)
        {
            case'A':
                     transmit_string(camnd[0]);
                     PORTB|=led;
                     _delay_ms(500);
                     PORTB&=(~led);
                     transmit_string(camnd[1]);
                     break;
            case'B':
                    transmit_string(camnd[2]);
                     PORTB|=buzz;
                     _delay_ms(500);
                     PORTB&=(~buzz);
                     transmit_string(camnd[3]);
                     break;
           case'C':
                     transmit_string(camnd[4]);
                     PORTB|=led_1;
                     _delay_ms(500);
                     PORTB&=(~led_1);
                     transmit_string(camnd[5]);
                      break;
            default:
                      transmit_string(camnd[6]);
                       
      
    }
        }
}//end of main
}
