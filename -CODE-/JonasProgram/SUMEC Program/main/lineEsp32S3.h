int LINE_Get(int LINE_Sensor, int LINE_Threshold, int LINE_Mode=0) {
	switch(LINE_Sensor) {
		case 1:	//Front Left
			switch(LINE_Mode) {	//Mode
				case 0:	//Mode 0
					return (analogRead(5)<LINE_Threshold ? 1: 0);
					break;
					
				case 1:	//Mode 1
					return analogRead(5);
					break;
			}
			break;
			
		case 2:	//Front Mid
			switch(LINE_Mode) {	//Mode
				case 0:	//Mode 0
					return (analogRead(7)<LINE_Threshold ? 1: 0);
					break;
					
				case 1:	//Mode 1
					return analogRead(7);
					break;
			}
			break;
			
		case 3:	//Front Right
			switch(LINE_Mode) {	//Mode
				case 0:	//Mode 0
					return (analogRead(6)<LINE_Threshold ? 1: 0);
					break;
					
				case 1:	//Mode 1
					return analogRead(6);
					break;
			}
			break;
			
		case 4:	//Rear
			switch(LINE_Mode) {	//Mode
				case 0:	//Mode 0
					return (analogRead(4)<LINE_Threshold ? 1: 0);
					break;
					
				case 1:	//Mode 1
					return analogRead(4);
					break;
			}
			break;
		
		default:
			return 0;
			break;
		
	}
	return 0;
}