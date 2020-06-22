/*  The Serial Programming Interface (SPI) is support full duplex communication these used $ pin MISO,MOSI,SS,SCLK.In atmega
     328p have PB5=sck,PB4=MISO,PB3=MOSI,PB2=SS. We are using MAX7219 as a slave and atmega 328p as  master to write
     data to slave.
     */
/// The MAX7219 are used to write a single alphabet in a led matrix one by one
#include <avr/io.h>
#include <util/delay.h>   /// delay to swuch between character
#define F_CPU  16000000UL

#define sck (1<<PINB5)
#define mosi (1<<PINB3)
#define ss (1<<PINB2)



void execute(unsigned char cmd,unsigned char data)  /// IC used the command and data to write led matrix
{
    PORTB&=(~ss);
    SPDR=cmd;
    while(!(SPSR & (1<<SPIF)));  // wait until transmission is complete

     SPDR=data;
    while(!(SPSR & (1<<SPIF)));  // wait until transmission is complete

    PORTB|=ss;

}
void display(uint8_t *data)  /// take the array input  and call execute using for loop
{
    unsigned char i;
    for(i=0;i<8;i++)
    {
        execute(i+1,data[i]);
    }
}
void init_max7219(void)    /// initialze of  max7219 ic command
{
   execute(0x09,0b0000011);

   execute(0x0B,0x01);
   execute(0x0C,0x02);
   execute(0x0F,0x06);

}
void init_spi(void)   /// spi register initialze for master mode
{
   DDRB|=sck|mosi|ss;    /// making PB as output
   SPCR |= (1<<MSTR);               // Set as Master
    SPCR |= (1<<SPR0)|(1<<SPR1);     // divided clock by 128
    SPCR |= (1<<SPE);                // Enable SPI


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
    // Insert code
   init_spi();
   //execute(0x01,0x0F);
   //execute(0x02,0x05);

    while(1)
    {
      display(alpha[0]);
      _delay_ms(1000);
      display(alpha[1]);
      _delay_ms(1000);
      display(alpha[2]);
      _delay_ms(1000);
      display(alpha[3]);
      _delay_ms(1000);
      display(alpha[4]);
      _delay_ms(1000);
    }

    return 0;
}
