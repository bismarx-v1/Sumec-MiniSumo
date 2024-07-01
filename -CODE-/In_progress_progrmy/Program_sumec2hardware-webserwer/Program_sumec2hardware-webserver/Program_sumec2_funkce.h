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
        start_control = 1;                    // pozor
      }

      //fáze startováni
      if (adres == ADDR_START) {
        if (comand == DohaioID) {
          Serial.println("jedeme");
          start_control = 1;
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

void CodeForTask1(void * parameter) {	/*Code for core 0*/
	
	for(;;) {	//void loop()
		switch(LEDBlink) {
			case 0:
				if(LedBlinkState != 0) {
					LedBlinkState = 0;
					digitalWrite(LEDPin, 0);
					break;
				}
				
				break;
			
			case 1:
				LedBlinkState = 1;
				digitalWrite(LEDPin, 1);
				delay(100);
				digitalWrite(LEDPin, 0);
				delay(100);
				break;
			
			case 2:
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
		
		// ===============================Nat Simak's webserver -> zacatek==================
		if(SWSRCP_DISABLE) {
			
		} else {
				
			//.../////////////////////////////////
			//..//    <GET and deserialize>    //
			//./////////////////////////////////
			DeserializationError error = deserializeJson(jsonDocument, SWSRCPRequest("get", "get", "", HOST_NAME));
			if(error) {
				Serial.print("GET - deserializeJson error: ");
				Serial.println(error.c_str());
			}
			else {	//this will run if the output was deserialized
				char* VarSiteRunButon = jsonDocument["Button_Run"];	// unused
				char* VarSiteSelectedMode = jsonDocument["Select_Mode"];	// unused
				
				if(VarSiteSelectedMode[0] >= 48 && VarSiteSelectedMode[0] <= 57) {	//this is just for debug
				 TypMode = VarSiteSelectedMode;
				}
				
				if(SWSRCP_DEBUG) {	// just for debug
					Serial.println("<GET output>");
					Serial.println("Run: " + String(VarSiteRunButon));
					Serial.println("Mode: " + String(VarSiteSelectedMode));
					Serial.println("</GET output>");
				}
			}
			//..||||||||||||||||||||||||||||||||||
			//..||    </GET and deserialize>    ||
			//..||||||||||||||||||||||||||||||||||
			
			//...//////////////////////////////////
			//..//    <POST and deserialize>    //
			//.//////////////////////////////////
			JsonObject obj = jsonDocument2.to<JsonObject>();
		
			obj["Mode"] = String(VarMode);	//assign each value to a set keyword
			obj["TfL_Left"] = String(TfL_Get(0x11));
			obj["TfL_Mid"] = String(TfL_Get(0x12));
			obj["TfL_Right"] = String(TfL_Get(0x13));
			obj["Sharp_Left"] = String(0);
			obj["Sharp_Right"] = String(0);
			obj["QRE_Left"] = String(LINE_Get(1, hodnota_cary, 0));
			obj["QRE_Rear"] = String(LINE_Get(4, hodnota_cary, 0));
			obj["QRE_Right"] = String(LINE_Get(3, hodnota_cary, 0));
			obj["IR"] = String(code);
			
			String buffer = "";
			serializeJson(jsonDocument2, buffer);	//used to serialize the "jsonDocument2" of type "StaticJsonDocument<>" to a string stored in var. "buffer" of type "String"
			
			DeserializationError error2 = deserializeJson(jsonDocument, SWSRCPRequest("post", "post", buffer, HOST_NAME));
			if(error2) {
				Serial.print("POST - deserializeJson error: ");
				Serial.println(error.c_str());
			} else {
				if(SWSRCP_DEBUG) {
					String OutMode = jsonDocument["Mode"];
					String OutTfL_Left = jsonDocument["TfL_Left"];
					String OutTfL_Mid = jsonDocument["TfL_Mid"];
					String OutTfL_Right = jsonDocument["TfL_Right"];
					String OutSharp_Left = jsonDocument["Sharp_Left"];
					String OutSharp_Right = jsonDocument["Sharp_Right"];
					String OutQRE_Left = jsonDocument["QRE_Left"];
					String OutQRE_Rear = jsonDocument["QRE_Rear"];
					String OutQRE_Right = jsonDocument["QRE_Right"];
					String OutIR = jsonDocument["IR"];
					
					Serial.println("<POST confirm>");
					Serial.print("Mode: " + String(OutMode));
					Serial.print("TfL_Left: " + String(OutTfL_Left));
					Serial.print("TfL_Mid: " + String(OutTfL_Mid));
					Serial.print("TfL_Right: " + String(OutTfL_Right));
					Serial.print("Sharp_Left: " + String(OutSharp_Left));
					Serial.print("Sharp_Right: " + String(OutSharp_Right));
					Serial.print("QRE_Left: " + String(OutQRE_Left));
					Serial.print("QRE_Rear: " + String(OutQRE_Rear));
					Serial.print("QRE_Right: " + String(OutQRE_Right));
					Serial.print("IR: " + String(OutIR));
					Serial.println("</POST confirm>");
				}
			}
			//..|||||||||||||||||||||||||||||||||||
			//..||    </POST and deserialize>    ||
			//..|||||||||||||||||||||||||||||||||||
		}
		
		// ===============================Nat Simak's webserver -> konec====================
		
	}
}
//================================LED blikání -> konec================================

