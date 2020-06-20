/* follwing  code shows the USART prootocols implementation  transmit and receive the character using usart buffer UDRE0 the
  pin in atmega 328p is PD0 and PD1 are
   used as transmit and receive.*/
#include <avr/io.h>
#include <stdint.h>                     // needed for uint8_t
#include<util/delay.h>

#define FOSC 16000000UL                       // Clock Speed
#define BAUD 9600                   //  Baudrate
#define MYUBRR FOSC/16/BAUD -1    /// UBRR0H and UBRR0L register loading with calculation

#define wd0  (1<<PINB0)
#define  wd1  (1<<PINB1)
#define   wd2  (1<<PINB2)
#define wd3     (1<<PINB3)
volatile char ReceivedChar;     /// char variable
// function to send data
void transmit_char (unsigned char data)
{
  while (!( UCSR0A & (1 << UDRE0))); /* Wait for empty transmit buffer*/
  UDR0 = data;            /* Put data into buffer, sends the data */
  // wait while register is free
  // load data in the register
}
void transmit_string(unsigned char *data)
{
  unsigned int i = 0;
  while (data[i] != 0) /* print the String  "Hello from ATmega328p" */
  {
    while (!( UCSR0A & (1 << UDRE0))); /* Wait for empty transmit buffer*/
    UDR0 = data[i];            /* Put data into buffer, sends the data */
    i++;                             /* increment counter           */
  }                                           // wait while register is free

}
// function to receive data
unsigned char uart_recieve (void)
{

  while (!(UCSR0A) & (1 << RXC0));                // wait while data is being received
  return UDR0;
  // return 8-bit data
}

int main()
{
  DDRB = 0x0F;
  unsigned char camnd[5][20] = {"stepper motor CW\n", "stepper motor ACW\n", "Invalid Input\n"};
  /* Set Baudrate  */
  UBRR0H = (MYUBRR >> 8);
  UBRR0L = (MYUBRR);
  unsigned char period = 15;
  /// UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // Enable receiver and transmitter
  UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1 stp
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // Enable receiver and transmitter
  UCSR0B |= (1 << RXCIE0);                    // Enable reciever interrupt
  sei();


  while (1)
  {
   
    if (ReceivedChar != '\0' && ReceivedChar != '\n')
    {
      if (ReceivedChar == 'C')
      {
        transmit_string(camnd[0]);
        for (int i = 0; i < 48; i++)
        {
          PORTB = 0x09;
          _delay_ms(period);
          PORTB = 0x08;
          _delay_ms(period);
          PORTB = 0x0C;
          _delay_ms(period);
          PORTB = 0x04;
          _delay_ms(period);
          PORTB = 0x06;
          _delay_ms(period);
          PORTB = 0x02;
          _delay_ms(period);
          PORTB = 0x03;
          _delay_ms(period);
          PORTB = 0x01;
          _delay_ms(period);
        }
        PORTB = 0x09;   /* Last step to initial position */
        _delay_ms(500);
      }
      else if (ReceivedChar == 'A')
      {
        transmit_string(camnd[1]);
        for (int i = 0; i < 48; i++)
        {
          PORTB = 0x01;
          _delay_ms(period);
          PORTB = 0x03;
          _delay_ms(period);
          PORTB = 0x02;
          _delay_ms(period);
          PORTB = 0x06;
          _delay_ms(period);
          PORTB = 0x04;
          _delay_ms(period);
          PORTB = 0x0C;
          _delay_ms(period);
          _delay_ms(period);
          PORTB = 0x08;
          _delay_ms(period);
          PORTB = 0x09;
          _delay_ms(period);

        }
        PORTB = 0x09;
        _delay_ms(500);
      }
      else
        transmit_string(camnd[2]);
    }
  }//end of main
}
ISR (USART_RX_vect)
{
    ReceivedChar = UDR0;                       // Read data from the RX buffer
                           // Write the data to the TX buffer
}
