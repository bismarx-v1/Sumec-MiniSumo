
void IRstart() {
  
  while (start_control == 0) {

    decode_results results;

    if (irrecv.decode(&results)) {  //čeká na příchozí signál 

      code = results.value & 0x7FF;  //z přijatého signálu vezme pouze posledních jedenást hodnot a dosadí do proměné code (BIN)
      comand_first = code & 0x3F;    //vytažení posledních 6 hodnot (Dohayo ID)
      comand = comand_first / 0b10;  //vyjmutí poslední hodnoty 
      adres = code / 0b1000000;      //z přijatého signálu vezme prvních 5 hodnot (Adresa) 

      //vypsání všsch hodnot z IR, nejdřívě BIN potom DEC  

      
      Serial.println("");
      Serial.print("recieved signal: ");
      Serial.print(results.value, BIN);
      Serial.print("    DEC: ");
      Serial.println(results.value);
      Serial.print("code: ");
      Serial.print(code, BIN);
      Serial.print("    DEC: ");
      Serial.println(code);
      Serial.print("adresa: ");
      Serial.print(adres, BIN);
      Serial.print("    DEC: ");
      Serial.println(adres);
      Serial.print("comand_first: ");
      Serial.print(comand_first, BIN);
      Serial.print("    DEC: ");
      Serial.println(comand_first);
      Serial.print("comand: ");
      Serial.print(comand, BIN);
      Serial.print("    DEC: ");
      Serial.println(comand);
      Serial.println("");
      Serial.println("==========");
      

      //fáze program
      if (adres == ADDR_PROGRAM) {
        DohaioID = comand;
        Serial.print("DohaioID: ");
        Serial.println(DohaioID);
        Serial.println(" ");
      }

      //fáze startováni
      if (adres == ADDR_START) {
        if (comand == DohaioID) {
          Serial.println("jedeme");
          start_control = 1;
          LEDBlink = 1;

          if(konec == 1)
          {

          }
          else
          {
            konec = 1;
          }

        } else {
          Serial.println("špatný code");
        }
      }

      irrecv.resume();
    }
  }
}
//================================IR čekání -> konec==================================





//================================LED blikání -> začátek================================

void blink()
{
	
		switch(LEDBlink) {
			case 0:
				if(LedBlinkState != 0) {
					//LedBlinkState = 0;
					digitalWrite(LEDPin, 0);
					break;
				}
				
				else 
        {
					break;
				}
			
			case 1:
				if(LedBlinkState != 1) {
					//LedBlinkState = 1;
          while(millis()%400 > 200)    // toto je spatne, vim o tom
          {
					digitalWrite(LEDPin, HIGH);
          }
          while(millis()%400 < 200)
          {
					digitalWrite(LEDPin, LOW);
          }
					break;
				}
				
				else {
					break;
				}
			
			case 2:
				if(LedBlinkState != 2) {
					LedBlinkState = 2;
					digitalWrite(LEDPin, 1);
					delay(500);
					digitalWrite(LEDPin, 0);
					delay(200);
					digitalWrite(LEDPin, 1);
					delay(200);
					digitalWrite(LEDPin, 0);
					delay(200);
					break;
				}
				
				else {
					break;
				}
		}
}
//================================LED blikání -> konec================================

