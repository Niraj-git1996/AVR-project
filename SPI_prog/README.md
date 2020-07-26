# Serial Programming Interface(SPI)

**The SPI is a very simply Synchronous (allows devices to send and receive data at the same time) protocol developed by Motorola.**
![spi image](https://electrosome.com/wp-content/uploads/2017/04/SPI-Communication.png)

_SPI uses 4 pins,  A system clock (SCK), a Master Output Slave Input (MOSI), a Master Input Slave Output (MISO) and a Slave Select (SS)_.

**Atmega 328p pin of SPI**
![pin](https://sites.google.com/site/qeewiki/_/rsrc/1301156090101/books/avr-guide/spi/ATmega%20-%20SPI.JPG)

### Shift register


![register](https://circuits4you.com/wp-content/uploads/2019/01/arduino-master-slave-SPI-communication.png)

 **Each clock cycle the register will be shifted to the left by one in both the Master and the Slave.**
The most significant bit (MSB or 7 bit) of the Master will be pushed to the least significant bit (LSB or 0 bit)

#### SPCR(SPI CONTROL REGISTER)

| bit 7| bit 6|	bit 5 |	bit 4| bit 3|bit 2|bit 1|bit 0|
 |-----|------|--------|------|-------|-------|-------|--------|
 |SPCR|	SPIE	|SPE 	|DORD| 	MSTR |	CPOL| 	CPHA |	SPR1 |	SPR0|
 
 


##### SPI Control Register

|Mode|	 CPOL| 	 CPHA|
|----|-------|--------|
| 0|	 0|	 0|
| 1	| 0|	 1|
 |2	| 1	| 0|
 |3	| 1|	 1|
 ![cpol](https://upload.wikimedia.org/wikipedia/commons/thumb/6/6b/SPI_timing_diagram2.svg/400px-SPI_timing_diagram2.svg.png)
 


**Setting the SPE bit within the SPCR register enables SPI.**  

**Setting the SPIE bit HIGH (1) enables the SPI interrupt**.

**The DORD bit within the SPCR register controls the direction of the transmission.**

**The default is LOW(0) will transmits MSB first and LSB last, if the bit is SET(1) will transmit the LSB first and the MSB last.**
![operation](https://cdn.sparkfun.com/assets/c/7/8/7/d/52ddb2dcce395fed638b4567.png)

__The MSTR bit within the SPCR register tells the AVR whether it is a master or a slave.__  
__If the SS pin is set as an input__
__while the AVR is in Master Mode and, the pin is driven LOW (GND), the MSTR bit will be cleared (0) and the user must set the bit HIGH(1) to re-establish Master mode.__

```
    The SPIF bit within the SPSR sets HIGH(1) whenever data transmission is complete even if interrupts are not enabled.  This is useful because we could check the status of the bit in order to figure out if it is safe to write the the SPDR  register
```

###### SPSR(SPI STATUS REGISTER)



|bit 7| bit 6|bit 5|bit 4| bit 3|bit 2 |bit 1|bit 0|
|-----|----------|-------|-------|--------|-------|-------|-------|
|SPSR|	SPIF|	WCOL| 	- |	-| 	- |	- |	SPI2X|


##### System Clock Division Factor


|SPI2X	|SPR1|SPR0 | SCK Frequency|
|-------|----|-----|--------------|
|0	| 0 |	 0|	 Clock / 4|
 |0	| 0|	 1| 	 Clock / 16|
| 0|	 1|	 0| 	 Clock / 64|
 |0	| 1	| 1 |	 Clock / 128|
 |1	| 0| 	 0| 	 Clock / 2|
 |1	| 0| 	 1 	 |Clock / 8|
 |1|	 1| 	 0	| Clock / 32|
 |1	| 1	| 1	| Clock / 64|
 
 

##### SPDR(SPI DATA REGISTER)

|7 bit| 	6 bit |	5 bit |	4 bit |	3 bit |	2 bit |	1 bit |	0 bit|
|-----|-----------|-------|-------|-------|-------|-------|-------|
|MSB|  | | | | | | 	 	 	 	 	 	LSB   


```
Writing to the SPDR register causes data to be loaded into the shift register and automatically triggers the AVR to transmit.
Reading from the SPDR register causes the data to be read from the receive shift register.
```

**The WCOL bit within the SPSR register will be set HIGH(1) if you attempt to write data into the SPDR register during data transmission.
WCOL will be cleared (0) when the SPDR is reed.**

##### END
