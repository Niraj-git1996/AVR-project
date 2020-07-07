*** KEYPAD Interfacing****************

/***************************************************************************************************
                             PORT configurations/Connections
 ****************************************************************************************************
       4x4 KEYPAD INTERFACING
            ___________________
           |    |    |    |    |
           | 0  | 1  | 2  | 3  |--------- R0
           |____|____|____|____|
           |    |    |    |    |
	   | 4  | 5  | 6  | 7  |--------- R1
           |____|____|____|____|
           |    |    |    |    |
           | 8  | 9  | A  | B  |--------- R2
           |____|____|____|____|
	   |    |    |    |    |
           | C  | D  | E  | F  |--------- R3
           |____|____|____|____|
             |    |    |    |
             |    |    |    |____________ C3
             |    |    |
             |    |    |_________________ C2
             |    |
             |    |______________________ C1
             |
             |___________________________ C0

 ****************************************************************************************************/
/***************************************************************************************************
                             PORT configurations/Connections
 ****************************************************************************************************
           4X3 KEYPAD INTERFACING 
            _______________
           |    |    |    |    
           | 1  | 2  | 3  |--------- L1-->PB7
           |____|____|____|
           |    |    |    | 
           | 4  | 5  | 6  |--------- L2-->PB6
           |____|____|____|
           |    |    |    |   
           | 7  | 8  | 9  | --------- L3-->PB5
           |____|____|____|
           |    |    |    | 
           | *  | 0  | #  |--------- L4-->PB4
           |____|____|____|
             |    |    |    
             |    |    |                    PB0
             |    |    |
             |    |    |_________________ C3-->PB1
             |    |
             |    |______________________ C2-->PB2
             |
             |___________________________ C1-->PB3

 ****************************************************************************************************/

ports setup in avr for keypad
1.rows(R0-R3) of keypad are output
2.columns(C0-C3) of keypad are input
3.make 4 port pin as output and connect to row of keypad.
4. make 4 port pin as input and connect to columns of keypad.
5.make all port pin as high intially


Step to get key value from keypad
1.check the condition of key press release
2. check the key press detected 
3.delay for time and again check key press detected
4.Is press detected  check at whick key is pressed
5. key checking is done by grounding a single row at a time.
5. if row founded check at which columns is at key press
6. then particular number is search in intially define command word.
7.begin again with step 1


