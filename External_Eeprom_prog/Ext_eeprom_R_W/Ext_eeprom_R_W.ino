/*  We are using I2C communication for writing and reading a data from external EEPROM memory and display in using UART communication 
 *  we connect SCL of avr to SCL to eeprom ,SDA of avr to SDA to eeprom 
 *  there is frame structure to write a data and read data from eeprom 
 * |S|A0|HIGH|LOW|DATA0|...|DATAn-1|P|  frame for write
 * |S|A0|HIGH|LOW|RS|A1|DATA0|....|DATAn-1|NACK|P|   Frame for read 
 * In this prog we write and read a byte and string to eeprom
 */

#include <avr/io.h>
#include "i2c.h"      // twi header file
#include  "mystdutil.h"
#include "myuart.h"   // usart header file

#ifndef F_CPU
#define F_CPU 16000000UL
#endif // F_CPU

#define Mem_write_address  0xA0u    ///SLA+W
#define Mem_read_address    0xA1u     ///SLA+R

volatile uint8_t rec;   // global variable volatile for read byte

void EE_write_byte(uint16_t Addr,uint8_t dat)    // taking 16 bit addr and a byte data
{
    I2C_Start();
    I2C_Write(Mem_write_address);
    I2C_Write(util_ExtractByte8to16(Addr));
    I2C_Write(util_ExtractByte0to8(Addr));
    I2C_Write(dat);
    I2C_Stop();
    _delay_ms(20);  // wait for time for internal write operation 
}
void EE_write_string(uint16_t Addr,uint8_t *dat)  // taking 16 bit addr and char array data
{
  uint8_t i=0;
    I2C_Start();
    I2C_Write(Mem_write_address);
    I2C_Write(util_ExtractByte8to16(Addr));
    I2C_Write(util_ExtractByte0to8(Addr));
    while(dat[i]!='\0')
    {
      I2C_Write(dat[i]);    /// writing with auto increment address
      i++;
    }
    I2C_Stop();
    _delay_ms(20);
}
uint8_t EE_read_byte(uint16_t address)
{
    uint8_t data;
    I2C_Start();
    I2C_Write(Mem_write_address);
    I2C_Write(util_ExtractByte8to16(address));
    I2C_Write(util_ExtractByte0to8(address));
    I2C_Start();
    I2C_Write(Mem_read_address);
    data=I2C_Read(0);    // read with nack    
    I2C_Stop();
    return data;
}
void  EE_read_string(uint16_t address,uint8_t len)   // taking 16 bit addr and len of string to read 
{
    uint8_t data;
    I2C_Start();
    I2C_Write(Mem_write_address);
    I2C_Write(util_ExtractByte8to16(address));
    I2C_Write(util_ExtractByte0to8(address));
    I2C_Start();    // repeated start
    I2C_Write(Mem_read_address);
    while(len!=1)
    {
    data=I2C_Read(1);   // read with ack
    UART_TxChar(data);
    len--;
    }
    data=I2C_Read(0);   // rwad with nack
    UART_TxChar(data);
    I2C_Stop();
    _delay_ms(200);
}


int main(void)
{
  uint16_t add1=0x23u,add2=0x89u;  // definning 16 bir addr 
  const char my[]="eeprom first code";  // char array to store 
  uint8_t set='a',set1='b';
  UART_Init(9600);
  I2C_Init();
 // EE_write_byte(add,set);
EE_write_byte(add1,'h');
 //EE_write_byte(add1+1,'i');
 EE_write_string(add2,my);
    // Insert code

    while(1)
    {
      rec=EE_read_byte(add1);
      UART_TxChar(rec);
      //rec=EE_read_byte(add1+1);
      //UART_TxChar(rec);
      UART_TxChar(' ');
      EE_read_string(add2,17); // reading and displaying in uart 
      UART_TxChar('\n');
        
    }

    return 0;
}
