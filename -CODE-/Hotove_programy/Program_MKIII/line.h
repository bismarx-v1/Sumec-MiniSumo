

int LINE_Get(int LINE_Sensor, int LINE_Threshold, int LINE_Mode=0) {
	switch(LINE_Sensor) {
		case 1:	//Front Left
			switch(LINE_Mode) {	//Mode
				case 0:	//Mode 0
					return (analogRead(10)<LINE_Threshold ? 1: 0);
					break;
					
				case 1:	//Mode 1
					return analogRead(10);
					break;
			}
			break;
			
		case 2:	//Front Mid
			switch(LINE_Mode) {	//Mode
				case 0:	//Mode 0
					return (analogRead(10)<LINE_Threshold ? 1: 0);
					break;
					
				case 1:	//Mode 1
					return analogRead(10);
					break;
			}
			break;
			
		case 3:	//Front Right
			switch(LINE_Mode) {	//Mode
				case 0:	//Mode 0
					return (analogRead(9)<LINE_Threshold ? 1: 0);
					break;
					
				case 1:	//Mode 1
					return analogRead(9);
					break;
			}
			break;
			
		case 4:	//Rear
			switch(LINE_Mode) {	//Mode
				case 0:	//Mode 0
					return (analogRead(8)<LINE_Threshold ? 1: 0);
					break;
					
				case 1:	//Mode 1
					return analogRead(8);
					break;
			}
			break;
		
		default:
			return 0;
			break;
		
	}
	return 0;
}