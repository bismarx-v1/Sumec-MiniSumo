

bool LINE_Get(char LINE_Sensor, int LINE_Threshold) {  //input funkce je 'FL' = predni levy, 'FR' = predni pravy, 'BL' = zadni levy, 'BR' = zadni pravy
                              //return: true = bila, false = cerna
  if(LINE_Sensor=='FL') {
    if(analogRead(32)<LINE_Threshold){  //pin leveho predniho senzoru cary (z pohledu sumce)
      return true;
    }
    else {
      return false;
    }
    
  }
  
  if(LINE_Sensor=='FR') {
    if(analogRead(33)<LINE_Threshold){  //pin praveho predniho senzoru cary (z pohledu sumce)
      return true;
    }
    else {
      return false;
    }
    
  }
  
  if(LINE_Sensor=='BL') {
    if(analogRead(34)<LINE_Threshold){  //pin leveho zadniho senzoru cary (z pohledu sumce)
      return true;
    }
    else {
      return false;
    }
    
  }
  
  if(LINE_Sensor=='BR') {
    if(analogRead(35)<LINE_Threshold){  //pin praveho zadniho senzoru cary (z pohledu sumce)
      return true;
    }
    else {
      return false;
    }
    
  }
  
}

 


void setup() {
  Serial.begin(9600);
}



void loop() {
  Serial.println(LINE_Get('FL', 3500));
  Serial.println(LINE_Get('FR', 3500));
  Serial.println(LINE_Get('BL', 3500));
  Serial.println(LINE_Get('BR', 3500));
  Serial.println('====================\n');
}
