/*  The Serial Programming Interface (SPI) is support full duplex communication these used $ pin MISO,MOSI,SS,SCLK.In atmega
     328p have PB5=sck,PB4=MISO,PB3=MOSI,PB2=SS. We are using MAX7219 as a slave and atmega 328p as  master to write
     data to slave.
     */
/// The multiple MAX7219 led matrix is connected as slave to atmega 328p(master).when master want to send the data to particular slave the 
/// particular ss pin is low and data is written to that.The UART is also used to control the what to written in led matrix.It receive 
/// a char from serial and code it will be displayed  
#include <avr/io.h>
#include <util/delay.h>   /// delay to swuch between character
//#define F_CPU  16000000UL

#define FOSC 16000000                       // Clock Speed
#define BAUD 9600                    // buad rate is 9600 bps
#define MYUBRR FOSC/16/BAUD -1


#define sck (1<<PINB5)
#define mosi (1<<PINB3)
#define ss1 (1<<PINB2)  /// slave 1
#define ss2 (1<<PINB1)  // slave 2
#define  ss3 (1<<PINB6) //slave 3

volatile char RChar;

void init_usart(void)
{
  /*Set baud rate */
    UBRR0H = (MYUBRR >> 8);
    UBRR0L = MYUBRR;
     UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1 stp
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // Enable receiver and transmitter
    //UCSR0B |= (1 << RXCIE0);                    // Enable reciever interrupt flag
    //UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1 stp

}
void transmit_string(unsigned char *data)
{
     unsigned int i = 0;
        while(data[i] != 0) /* print the String  "Hello from ATmega328p" */
        {
          while (!( UCSR0A & (1<<UDRE0))); /* Wait for empty transmit buffer*/
          UDR0 = data[i];            /* Put data into buffer, sends the data */
          i++;                             /* increment counter           */
        }
}// wait while register is fre
void CE1(unsigned char cmd,unsigned char data)  /// IC used the command and data to write led matrix
{
    PORTB&=(~ss1);
    SPDR=cmd;
    while(!(SPSR & (1<<SPIF)));  // wait until transmission is complete

     SPDR=data;
    while(!(SPSR & (1<<SPIF)));  // wait until transmission is complete

    PORTB|=ss1;

}
void CE2(unsigned char cmd,unsigned char data)  /// IC used the command and data to write led matrix
{
    PORTB&=(~ss2);
    SPDR=cmd;
    while(!(SPSR & (1<<SPIF)));  // wait until transmission is complete

     SPDR=data;
    while(!(SPSR & (1<<SPIF)));  // wait until transmission is complete

    PORTB|=ss2;

}
void CE3(unsigned char cmd,unsigned char data)  /// IC used the command and data to write led matrix
{
    PORTB&=(~ss3);
    SPDR=cmd;
    while(!(SPSR & (1<<SPIF)));  // wait until transmission is complete

     SPDR=data;
    while(!(SPSR & (1<<SPIF)));  // wait until transmission is complete

    PORTB|=ss3;

}
void display(uint8_t *data,uint8_t k)  /// take the array input  and call execute using for loop
{
    unsigned char i;
    if(k==1)
    {
    for(i=0;i<8;i++)
    {
        CE1(i+1,data[i]);
    }
    }
    else if(k==2)
    {
      for(i=0;i<8;i++)
    {
        CE2(i+1,data[i]);
    }
    }
    else
    {
      for(i=0;i<8;i++)
    {
        CE3(i+1,data[i]);
    }
    }
}
void init_max7219(void)    /// initialze of  max7219 ic command
{
   CE1(0x09,0x01);
   CE2(0x09,0x01);
   CE3(0x09,0x01);
   CE1(0x0B,0x08);
   CE2(0x0B,0x08);
   CE3(0x0B,0x08);
   CE1(10,16);
   CE2(10,16);
   CE3(10,16);
   CE1(0x0F,0x06);
   CE2(0x0F,0x06);
   CE3(0x0F,0x06);

}
void init_spi(void)   /// spi register initialze for master mode
{
   DDRB|=sck|mosi|ss1|ss2|ss3;    /// making PB as output
   SPCR |= (1<<MSTR);               // Set as Master
    SPCR |= (1<<SPR0)|(1<<SPR1);     // divided clock by 128
    SPCR |= (1<<SPE);                // Enable SPI


}
unsigned char uart_receive (void)
{
    while(!(UCSR0A) & (1<<RXC0));                   // wait while data is being received
    return UDR0;                                   // return 8-bit data
}
int main(void)
{
   init_spi();
   
   //uint8_t A[]={0x3C,0X42,0X42,0X42,0X7E,0X42,0X42,0X42};
  // uint8_t B[]={0X3C,0X44,0X44,0X44,0X3C,0X44,0X44,0X3C};
  // uint8_t C[]={0X38,0X44,0X04,0X04,0X04,0X04,0X44,0X38};
   //uint8_t D[]={0X3C,0X44,0X44,0X44,0X44,0X44,0X44,0X38};
   //uint8_t E[]={0X3C,0X02,0X02,0X02,0X3E,0X02,0X02,0X3C};
   uint8_t  alpha[10][9]={{0x3C,0X42,0X42,0X42,0X7E,0X42,0X42,0X42},{0X3C,0X44,0X44,0X44,0X3C,0X44,0X44,0X3C},
                          {0X38,0X44,0X04,0X04,0X04,0X04,0X44,0X38},{0X3C,0X44,0X44,0X44,0X44,0X44,0X44,0X3C}
                          ,{0X3C,0X02,0X02,0X02,0X3E,0X02,0X02,0X3C}};///char array taking A,B,C,D,E,F
    uint8_t udisp[5][40]={"the led matrix 1 displaying...\n","the led matrix 2 displaying...\n","the led matrix 2 displaying..\n","INVALID INPUT\n"};
    // to display in serial terminal the char matrix is written 
   init_spi();
   init_usart();
   //execute(0x01,0x0F);
   //execute(0x02,0x05);
   

    while(1)
    {
     sp: RChar=uart_receive();
      if(RChar!='\0' && RChar!='\n')
      {
      if(RChar=='1')
      {
       RChar=uart_receive(); 
        if(RChar>='A' && RChar<='E')// VALID INPUT=1A,1B,1C,1D,1E
        {
          display(alpha[RChar-'A'],1);
          transmit_string(udisp[0]);
        }
        else
           {
            transmit_string(udisp[3]);
            goto sp;
           }
      }
      
        else if(RChar=='2')
        {
          RChar=uart_receive();
         if(RChar>='A' && RChar<='E')  // valid input =2A,2B,2C,2D,2E
        {
          display(alpha[RChar-'A'],2);
          transmit_string(udisp[1]); 
        }
        else
        {
          transmit_string(udisp[3]);
           goto sp;
      }
        }
      else if(RChar=='3')
      {
        RChar=uart_receive();
        if(RChar>='A' && RChar<='E')  // VALID INPUT=3A,3B,3C,3D,3E
        {
          display(alpha[RChar-'A'],3);
          transmit_string(udisp[2]); 
        }
        else
        {
          transmit_string(udisp[3]);
            goto sp;
      }
      }
    
      }
     
      }

    return 0;
}

   
