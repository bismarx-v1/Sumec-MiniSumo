bool LINE_Get(int LINE_Sensor, int LINE_Threshold) {  //input funkce je 1 = predni levy, 2 = predni pravy, 3 = zadni levy, 4 = zadni pravy
                              //return: true = bila, false = cerna
  if(LINE_Sensor==1) {
    if(analogRead(32)<LINE_Threshold){  //pin leveho predniho senzoru cary (z pohledu sumce)
      return true;
    }
    else {
      return false;
    }
    
  }

  else {
    if(LINE_Sensor==2) {
      if(analogRead(33)<LINE_Threshold){  //pin praveho predniho senzoru cary (z pohledu sumce)
        return true;
      }
      else {
        return false;
      }
      
    }
    
    else {
      if(LINE_Sensor==3) {
        if(analogRead(34)<LINE_Threshold){  //pin leveho zadniho senzoru cary (z pohledu sumce)
          return true;
        }
        else {
          return false;
        }
        
      }
      
      else {
        if(LINE_Sensor==4) {
          if(analogRead(35)<LINE_Threshold){  //pin praveho zadniho senzoru cary (z pohledu sumce)
            return true;
          }
          else {
            return false;
          }
          
        }
        else {
          Serial.println("Error Line 47 wrong input. ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ")
          return false;
        }
      }
    }
  }
}

 


void setup() {
  Serial.begin(9600);
}



void loop() {
  Serial.println(LINE_Get(1, 3500));
  Serial.println(LINE_Get(2, 3500));
  Serial.println(LINE_Get(3, 3500));
  Serial.println(LINE_Get(4, 3500));
  Serial.println("====================");
  delay(1000);
}
