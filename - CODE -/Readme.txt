last change: 12.4.2024


- note: not yet modified classes


- location of main code is: MAIN_CODE\src
- location of header files is: MAIN_CODE\include 
- test's program located in test folder 


- Actual pins:


Motors pins:
	Nsleep = 11
	Left_EN = 14
 	Left_PH = 12
 	Right_EN = 21
 	Right_PH = 13

QRE pins: 
	QRE_left = 10
	QRE_right = 9
	QRE_rear = 8

Sharp pins: 
	sharp_left = 35
	sharp_right = 16

Led pins:
	IRled = 38
	Led_red = 47
	Led_orange = 48


- IR problem:
Protocol=RC5 Address=0xB Command=0x10 Toggle=1 Raw-Data=0x1AD0 13 bits MSB first
Send with: IrSender.sendRC5(0xB, 0x10, <numberOfRepeats>);

Overflow
Received noise or an unknown (or not yet enabled) protocol
rawData[100]: 
 -2911600
 + 950,- 850
 +1850,- 850 + 900,- 850 + 850,-1800 + 950,- 800
 + 900,- 900 +1850,-1700 +1850,- 800 + 950,- 850
 + 950,-1700 + 900,-3350 + 950,- 850 + 950,- 800
 +1850,- 850 + 950,-1700 + 950,- 850 + 950,- 800
 +1850,-1700 +1850,- 850 + 900,- 850 + 950,-1700
 + 950,-3350 + 950,- 850 +1800,- 850 + 900,- 850
 + 950,-1750 + 900,- 850 + 950,- 850 +1800,-1750
 +1800,- 850 + 950,- 850 + 900,-1700 +1000,-3300
 + 950,- 850 + 900,- 850 +1850,- 850 + 900,-1750
 + 900,- 850 + 950,- 850 +1800,-1750 +1800,- 850
 + 950,- 850 + 900,-1750 + 950,-3300 + 950,- 850
 +1800,- 850 + 950,- 850 + 950,-1700 + 900,- 850
 + 950
Sum: 121050

