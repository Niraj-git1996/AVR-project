/*The Lcd connected in  4bit mode with uC  the uart is used to write a data to lcd from uart buffer 
 * The small application is created  is  password Based unlock system
 * In this system user enter password is wrong it display number of attempt remaining and wrong password
 * if user number of attempt  are used the system locked is display on lcd and buzzer is activated 
 * If user entered the correct password  the correct is display
 * the password is stored as constant char
 */
 #ifndef F_CPU 
 define F_CPU 16000000UL
 #endif

 #include"myuart.h"
 #include "mylcd_4bit.h"
#include "mystdutil.h"

 #define buzz  (1<<PINB5)
 volatile uint8_t rec;
  uint8_t cnt=0;
  const uint8_t *pass="niraj";
  
uint8_t flag_val(uint8_t flag)
{
  rec=UART_RxChar();
      if(rec!='\n' && rec!=' ')
      {
         LCDData(rec);
         if(rec!=pass[cnt])
             flag=1;
         cnt++;
      }
      return flag;
}
uint8_t IsAttempt(uint8_t Attempt)
{
        Attempt--;
        LCDData((util_Dec2Ascii(Attempt)));
        LCDWriteString(" attempt rem");
         _delay_ms(1000);
         return Attempt;
}
 int main()
 {
    UART_Init(9600);
    LCDInit();
    LCDClear();
    DDRB|=buzz;
    PORTB&=~buzz;
    uint8_t flag=0,Attempt=4;
    //const uint8_t pass[]="niraj";
    LCDGotoXY(0,1);
    LCDWriteString("Enter pass below:");
    LCDGotoXY(5,2);
    while(1)
    {
      PORTB&=~buzz;
      if(cnt<5)
      {
         flag=flag_val(flag);
     }
    else
      {
        rec=UART_RxChar();
        rec=UART_RxChar();
        if(rec=='\n')
        {
         _delay_ms(200);
      cnt=0;
      LCDGotoXY(5,2);
      if(flag==1)
      {
        if(Attempt=IsAttempt(Attempt))
        {
        LCDGotoXY(5,2);
      LCDWriteString("wrong pass   ");
      _delay_ms(800);
      flag=0;
      }
      else
       {
         LCDGotoXY(5,2);
      LCDWriteString("system locked");
      PORTB|=buzz;
      while(1);
       }
      }
      else
      {
        LCDWriteString("correct pass ");
        _delay_ms(1000);
        Attempt=3;
      }
      LCDGotoXY(5,2);
      LCDWriteString("             ");
      LCDGotoXY(5,2);
      }
      }
    }
    return 0;
 }
