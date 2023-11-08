/* This program is a parsing routine of TF02 product standard output protocol on Arduino.

The format of data package is 0x59 0x59 Dist_L Dist_H Strength_L Strength_H Sequence_L Sequence_H CheckSum_L
Refer to the product specification for detailed description.
For Arduino board with one serial port, use software to virtualize serial port’s functions: such as UNO board.
*/
#include<SoftwareSerial.h>			// soft serial port header file
SoftwareSerial mySerial(21, 22);		// define the soft serial port as mySerial, pin2 as RX, and pin3 as TX
									//For Arduino board with multiple serial ports such as DUE board, comment out the above two codes, and directly use mySerial port
int dist;							// LiDAR actually measured distance value
int strength;						// LiDAR signal strength
int check;							// check numerical value storage
int i;
int uart[9];						// store data measured by LiDAR
const int HEADER=0x59;				// data package frame header
void setup() {
	Serial.begin(9600);					//set the Baud rate of Arduino and computer serial port
	mySerial.begin(115200);				//set the Baud rate of LiDAR and Arduino serial port
}
void loop() {
	Serial.println("loop start============");
	if (mySerial.available()>0) {			//check whether the serial port has data input
		Serial.println("serial works");
		if(mySerial.read()==HEADER) {			// determine data package frame header 0x59
			Serial.println("if header");
			uart[0]=HEADER;
			if(mySerial.read()==HEADER) {			//determine data package frame header 0x59
				Serial.println("if header 2");
				uart[1]=HEADER;
				for(i=2;i<9;i++) {					// store data to array
					Serial.println("for loop");
					//uart=mySerial.read();
				}
				
				check=uart[0]+uart[1]+uart[2]+uart[3]+uart[4]+uart[5]+uart[6]+uart[7];
				if(uart[8]==(check&0xff)) {			// check the received data as per protocols
					Serial.println("check");
					dist=uart[2]+uart[3]*256;			// calculate distance value_
					strength=uart[4]+uart[5]*256;		// calculate signal strength value_
					Serial.print("dist = ");
					Serial.print(dist);					// output LiDAR tests distance value*
					Serial.print('\t');
					Serial.print("strength = ");
					Serial.print(strength);				// output signal strength value*
					Serial.print('\n');
				}
			}
		}
	}
	Serial.println("loop end================");
	delay(500);
}

/*
Step 3: Data View
Upload the program to the Arduino board and open the serial monitor to check the distance value*
detected by LiDAR in real time and corresponding signal strength as in Figure 3;
Besides, you can also check the data curves on the serial curve plotter, but for that you need to*
modify the code related to serial printing (Serial.print):
Serial.print("dist = ");
Serial.print(dist);					// output LiDAR tests distance value*
Serial.print(' ');
Serial.print("strength = ");
Serial.print(strength);				// output signal strength value*
Serial.print('\n');
Re-compile and upload them to Arduino board. Open the serial curve plotter and you can see two*
curves representing distance and strength as in Figure 4.*/