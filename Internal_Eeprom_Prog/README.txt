  INTERNAL EEPROM(ELECTRICALLY ERASABLE PROGRAMABLE READ ONLY MEMORY) SIZE OF  1KB
  
VR microcontrollers have some amount of EEPROM memory on-chip. 
For instance Atmega328 has 1K of byte addressable EEPROM. EEPROM memory can be used to store and read variables during program execution and is nonvolatile. 
It means that it retains values when power supply is off. 

. Atmega328 has following registers to control EEPROM:

16-bit EEAR (EEARH and EEARL) – EEPROM address register;
EEDR – EEPROM 8-bit data register;
EECR – EEPROM control register.

s Atmega328 has 1K of EEPROM memory highest cell address will be 0x3FF meaning that only 10 bits of 16-bit EEAR register are needed.
In order to avoid failures there is some sequence of writing process:

1.Wait until EEPE bit becomes zero;
2.Write EEPROM address to EEAR register;
3.Write data to EEDR;
4.Set EEMPE bit while keeping EEPE bit zero;
5.In four clock cycles set EEPE bit to initiate writing.

 Atmega328 has one dedicated interrupt EE_READY_vect, that may be set to occur every time
 when EEPROM becomes ready for writing or reading. Usually you would have to poll for EEPE bit become zero in loop – this require active processing power. 
Interrupt driven EEPROM writing may be more efficient especially when memory blocs has to be accessed.

