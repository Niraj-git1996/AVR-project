There 3 external hardware interrupt define in atmega 328p
1.INT0=PD2 
2.INT1=PD3
3.INT2=PB2

7	6	5	4	3	2	1	0
INT1	INT0	INT2	-	-	-	IVSEL	IVCE

we can enable and disable INTx bit using GICR(general Interrupt control register).

MCU Control Register (MCUCR)
The MCUCR register allows us to configure the type of interrupt we need as shown by the table below:

7	6	5	4	3	2	1	0
SE	SM2	SM1	SM0	ISC11	ISC10	ISC01	ISC00

ISC01 and ISC00 are used to define level or edge on external INT0 pin activates interrupt.
ISC11 and ISC10 are used to define  level or edge on external INT0 pin activates interrupt.

ISC01/ISC11	ISC00/ISC10	                Description
0	         0	               The low level of INT0/1 generates an interrupt request.
0	         1	               Any logical change on INT0/1 generates an interrupt request.
1	         0	               The falling edge of INT0/1 generates an interrupt request.
1	         1	               The rising edge of INT0/1 generates an interrupt request.

while INT2 is only edge triggered.

General Interrupt Flag Register(GIFR)
The bits of GIFR register are set when an interrupt occurs and cleared automatically when it is processed.

7	6	5	4	3	2	1	0
INTF1	INTF0	INTF2	-	-	-	-	-
Upon triggering an interrupt request , the related INTFx flag is set if interrupt is active,
the AVR will jump to corresponding interrupt vector location.
*************************************************************************************************************************
PIN CHANGE INTERRUPTS:
   There are  22 pin change interrupts pin in atmega 328p they are describe as below 
   
 	         7 bit	 6 bit 	 5 bit 	 4 bit 	 3 bit 	 2 bit 	 1 bit 	 0 bit 
      PCMSK2=   PCINT23	PCINT22	PCINT21	PCINT20	PCINT19	PCINT18	PCINT17	PCINT16
                  PD7     PD6     PD5    PD4      PD3     PD2     PD1    PD0    =ATMEGA 328P PIN                                              

Pin Change Mask Register 2


 	         7 bit  6 bit   5 bit    4 bit          3 bit    2 bit    1 bit  0 bit 
PCMSK1	-	  --    PCINT14 PCINT13  PCINT12	PCINT11	PCINT10	 PCINT9	 PCINT8
                          PC6    PC5      PC4              PC3    PC2      PC1    PC0 =ATMEGA 328P PIN
Pin Change Mask Register 1


 	 7 bit	6 bit 	5 bit 	4 bit 	3 bit 	2 bit 	1 bit 	0 bit 
PCMSK0	PCINT7	PCINT6	PCINT5	PCINT4	PCINT3	PCINT2	PCINT1	PCINT0
         PB7      PB6      PB5   PB4     PB3       PB2    PB1      PB0 = ATMEGA 328P PIN    

Pin Change Mask Register 0
   

 	 7 bit	6 bit 	5 bit 	4 bit 	3 bit 	2 bit 	1 bit 	0 bit 
 PCICR	- 	- 	- 	- 	- 	PCIE2 	PCIE1 	PCIE0 
Pin Change Interrupt Control Register


 	 7 bit	6 bit 	5 bit 	4 bit 	3 bit 	2 bit 	1 bit 	0 bit 
 PCIFR	- 	- 	- 	- 	- 	PCIF2 	PCIF1 	PCIF0 
Pin Change Interrupt Flag Register


    The PCIEx bits in the PCICR registers enable External Interrupts and tells the MCU to check PCMSKx on a pin change state.
 When a pin changes states (HIGH to LOW, or LOW to HIGH) and the corresponding PCINTx bit in the PCMSKx register is HIGH the corresponding PCIFx bit in the PCIFR register is set to HIGH and the MCU jumps to the corresponding Interrupt vector.
