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
#define ss1 (1<<PINB2)
#define ss2 (1<<PINB1)
#define  ss3 (1<<PINB6)



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
   CE1(0x09,0x0F);
   CE2(0x09,0x0F);
   CE3(0x09,0x0F);
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
int main(void)
{
   init_spi();
    unsigned char k,j;
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
      for(k=0;k<5;k++)
      {
          display(alpha[k],1);
          display(alpha[k],2);
          display(alpha[4-k],3);
          _delay_ms(5000);
      }
    }

    return 0;
}

