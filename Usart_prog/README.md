  ****the USART program are done in Arduino IDE and written in embedded C language and tested 
     using picsimlab and using virtual COM port to upload code and communicate with picsimlab arduino***
 Hardware wise serial is simple.  Most the time you will be using 2 pins and a ground, 
the RXD (Receive Data) and TXD (Transmit Data).  The device that you are trying to talk to will also have a TX and a RX pin,
 in order to get the two devices talking you have to hook up the TX of each device to the RX pin of the other. 


So we have 3 Control and Status Registers (A, B & C).  Register A mainly contains status data.
  Register B contains all interrupt settings and some none optional settings.
  Register C contains all the configuration settings.

UCSR0A	RXCn 	TXCn 	UDREn 	FEn 	DORn 	PEn 	U2Xn 	MPCMn 	    ATmega168/328
 
USART Control and Status Register A

UCSR0B	RXCIE0	TXCIE0	UDRIE0 	RXEN0	TXEN0	UCSZ02 	RXB80	TXB80	ATmega168/328 

USART Control and Status Register B

UCSR0C	UMSELn1	UMSELn0	UPMn1	UPMn0	USBSn	UCSZn1	UCSZn0	UCPOLn	ATmega168/328 

USART Control and Status Register C 

 UMSELn	 UMSELn0	 MODE
0	0	 Asynchronous Operation 
0	1	 Synchronous Operation 
1	0	 (Reserved)
1	1	 Master SPI Mode
UMSEL Bits Settings (ATmega168/328 Only)

UPM1 UPM0  	
                 PARITY MODE
0	0	 Disabled 
0	1	 Reserved 
1	0	 Enabled, Even Parity 
1	1	 Enabled, Odd Parity 
UPM (UPMn) Bit Settings

USBS (USBS0)	 Stop Bit(s) 
0	 1 bit 
1	 2 bit 
USBS (USBS0) Bit Settings


UCSZ2 UCSZ1 UCSZ0 	 CHAR SIZE
0	0 	0 	 5-bit
0	0 	1 	 6-bit
0	1 	0 	 7-bit
0	1 	1 	 8-bit
1	0 	0 	 Reserved
1	0 	1 	 Reserved
1	1 	0 	 Reserved
1	1 	1 	 9-bit
UCSZ (UCSZn) Bit Settings

formula for UBRR value

ubrr_value = (Clock_Speed[a.k.a. FOSC] / 16 / Baud_Rate) - 1


   Now that we have our communication up and running we need to be able to monitor its status and any faults.  This is done by Register A (UCSRA or UCSRnA)  

    The RXC(RXCn) bit (Receive Complete) will be set to HIGH(1) when data has been received and is available in the UDR (UDR0) buffer.  

    The TXC(TXCn) bit (Transmission Complete) is set to HIGH(1) when a transmission is completed and there is no other data to send.  

    The UDRE(UDREn) is set to HIGH(1) when the buffer (UDR/UDRn) is empty, and therefore ready to be written.  

    The FE(FE0) bit (Frame Error) is set HIGH(1) if the next bit in the receive buffer has a Frame Error.  If the recieve buffer is read the FE(FE0) bit is cleared.
