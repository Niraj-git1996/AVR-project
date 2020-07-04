*******Read and Write in External eeprom memory**************

 Mem_write_address  0xA0u    ///SLA+W
Mem_read_address    0xA1u     ///SLA+R

  ##writing condition in EEprom IC 
  Below  is the frame required to write in memory 

|S|A0|HIGH|LOW|DATA0|...|DATAn-1|P|

S.. Start condition
P.. Stop condition
A0.. base address that can be modified by a10,a9,a8 pins
HIGH.. higher byte of 16-bit subaddress
LOW.. lower byte of 16-bit subaddress
DATAx.. some data to write (or no data)
n=max. PAGESIZE (32B)

After each WRITE packet there should be 10ms gap.

##reading condition in EEprom IC
--------------
|S|A0|HIGH|LOW|RS|A1|DATA0|....|DATAn-1|NACK|P|
--------------
dummy write
to write 


S.. Start condition
P...stop condition
A0= base addres for writing in eeprom
HIGH=higher byte of 16-bit subaddress
LOW.. lower byte of 16-bit subaddress
RS== reapeated start condition 
A1= base adddres for reading in eeprom
DATAx.. some data to read to auto incrememt the address (or no data)
NACK=last data without ack
n=max. PAGESIZE (32B)


