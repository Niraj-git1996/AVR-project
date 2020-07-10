******************LIQUID CRYSTAL DISPLAY(LCD) INTERFACING WITH AVR*********************

/***************************************************************************************************
                                   2x16 LCD internal structure
****************************************************************************************************
    
            |<--------------------16 chars on Each Line-------------------->|
           ____________________________________________________________________    
          |\                                                                  /|
          | \ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___/ |
          |  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | |
    Line0 |  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F | |
          |  |___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___| |
          |  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | |
    Line1 |  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F | |
          |  |___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___| |
          | /                                                                \ |
          |/__________________________________________________________________\|
                        | D7 D6 D5 D4 D3 D2 D1 D0 |     EN   RW   RS          
                        |<------Lcd Data Bus----->|    Lcd control Lines
                        |                          |          
***************************************************************************************************/

Pin Number Symbol	Pin Function
 1	   VSS 	      Ground
 2	  VCC	      +5v
 3	  VEE	      Contrast adjustment (VO)
 4	  RS	      Register Select. 0:Command, 1: Data
 5	  R/W	      Read/Write, R/W=0: Write & R/W=1: Read
 6	  EN	      Enable. Falling edge triggered
 7	  D0	      Data Bit 0
 8	  D1	      Data Bit 1
 9	  D2	      Data Bit 2
 10	  D3	      Data Bit 3
 11 	  D4	      Data Bit 4
 12	  D5	      Data Bit 5
 13	  D6	      Data Bit 6
 14	  D7	      Data Bit 7/Busy Flag
 15	 A/LED+	      Back-light Anode(+)
 16	 K/LED-	      Back-Light Cathode(-)

/****************************************************************************************************/

Data Bus:
an alpha numeric lcd has a 8-bit data bus referenced as D0-D7. As it is a 8-bit data bus, we can send the data/cmd to LCD in bytes.

Register Select(RS):
The LCD has two register namely a Data register and Command register. Any data that needs to be displayed on the LCD has to be written to the data register of LCD. Command can be issued to LCD by writing it to Command register of LCD.
RS=0 for writing in command register
RS=1 for writing in data register

Read/Write(RW):
This signal is used to write the data/cmd to LCD and reads the busy flag of LCD. For write operation the RW should be LOW and for read operation the R/W should be HIGH.

Enable(EN):
This pin is used to send the enable trigger to LCD. After sending the data/cmd, Selecting the data/cmd register, Selecting the Write operation. A HIGH-to-LOW pulse has to be send on this enable pin which will latch the info into the LCD register 

/********************************************************************************************************/

LCD Operation

###Steps for Sending Command:
step1: Send the I/P command to LCD.
step2: Select the Control Register by making RS low.
step3: Select Write operation making RW low.
step4: Send a High-to-Low pulse on Enable PIN with some delay_us.


###Steps for Sending Data:
step1: Send the character to LCD.
step2: Select the Data Register by making RS high.
step3: Select Write operation making RW low.
step4: Send a High-to-Low pulse on Enable PIN with some delay_us.

/*****************************************************************************************************/

LCD can be interface in 4-bit or 8 bit mode

##Lcd in 4-bit mode
1.To initialize character lcd in 4 bit mode we send value hex 0x20 to command register of lcd. 
  0x20 tells the lcd controller that we want to communicate in 4-bit mode.
2.It tells the lcd controller that we want 4 bit communication and character size is between 5×7 dot matrix.
3.4-bit mode make use of only just four data pins D4-D5-D6-D7 of lcd
4.In 4-bit mode character is displayed on lcd in two pulse signals. 
5.First the higher four nibbles of a character are sent to the lcd with an enable stroke. 
  Than the lower four nibbles are send with enable stroke.



##Lcd in 8-bit mode
1.To initialize character lcd in 8-bit mode we send vale hex 0x30 to command register of lcd.
  0x30 tells lcd that we want to communicate in 8-bit mode.
2.If our character lcd has 2 lines (rows) we will send 0x38 instead of 0x20. It tells the lcd controller that we want 4 bit communication and   character size is between 5×7 dot matrix
3.In 8-bit mode only one pulse signal is required to display a character on lcd
4.8 bit mode uses the 8 data pins D0-D7 to interface


/******************************************************************************************************/













