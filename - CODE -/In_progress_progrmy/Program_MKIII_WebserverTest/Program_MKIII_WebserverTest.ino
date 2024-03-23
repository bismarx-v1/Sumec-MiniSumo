#include <SharpIR.h>
#include <IRremote.h>
#include <Wire.h>
#include "motors.h"
#include "line.h"
#include "TfLunaEsp32S3.h"
//#include "Sharp.h"
#include "rogram_sumec2HW_promene.h"
#include "Program_sumec2_funkce.h"
#include "SWSRCPClientFunctions.h"

//================================IR čekání -> začátek==================================
//...////////////////////
//..//    Settings    //
//.////////////////////
const char* SWSRCP_SSID = "SWSRCP#01";	//name of the web server's access point
const char* SWSRCP_PASSWORD = "3ac5c0cc-24bd-4d68-90b9-20d97ed3e080";	//pass to the web server's access point
String HOST_NAME = "http://192.168.1.22";	//IP of the web server
uint64_t ServerLastUpdate = 0;

String VarMode = "0";
String VarTfL_Left;
String VarTfL_Mid;
String VarTfL_Right;
String VarSharp_Left;
String VarSharp_Right;
String VarQRE_Left;
String VarQRE_Rear;
String VarQRE_Right;

// void setup()
void setup() {

  Serial.begin(9600); //  příprava Serialu a nastavení rychlosti Serialu
  
  ConnectToAP(SWSRCP_SSID, SWSRCP_PASSWORD);	//function designed to connect to an access point. curently part of the lib.

  pinMode(tlacitko, INPUT);  //nastavení test tlačítka na vstup
  pinMode(LEDPin, OUTPUT);  //nastavení kontrolní LED na výstup
  pinMode(scharp1, INPUT);

  MOTORS_Setup(); //stup pro motory  
  TfL_Setup();  //stup pro luny
  irrecv.enableIRIn();  //čekání na IR 
  IRstart(); //čekání na IR
  

  // Rybnik pravidla - otoceni k oponentovy

    
    //MOTORS_Go(255, -255);
    //delay(600);
    
}

//======================================setup -> konec, loop -> začátek================================================

void loop() {

  start_control = 0;
  //blink();

  // po stisknutí TEST tlačítka nastane čekání na IR
  if (digitalRead(tlacitko) >= 1) {
	VarMode = "0";
    LEDBlink = 0;
    MOTORS_Go(0, 0);
    IRstart();
	VarMode = "1";

  }

  // třídící proměná
  laser_number = 0;

  // třídění laserů pomocí proměné
  if (TfL_Get(TfL_Addr2) < Range && TfL_Get(TfL_Addr2) > 0) {  // přední laser
    laser_number = laser_number + 1;
    //primar_luna = 1;
	VarTfL_Mid = String(TfL_Get(TfL_Addr2));
  }

  if (TfL_Get(TfL_Addr1) < Range && TfL_Get(TfL_Addr1) > 0) {  // levý laser
    laser_number = laser_number + 3;
	VarTfL_Left = String(TfL_Get(TfL_Addr1));
  }

  if (TfL_Get(TfL_Addr3) < Range && TfL_Get(TfL_Addr3) > 0) {  // pravý laser
    laser_number = laser_number + 5;
	VarTfL_Right = String(TfL_Get(TfL_Addr3));
  }
  Serial.println("bezim");
  delay(10);

  // rozpohybování Sumce pomocí proměné "laser_number" vzniklé po třídění
  switch (laser_number) {

    case 0:
      MOTORS_Go(255, 255);
      break;

    case 1:

          if(tactic == 0)
          {
            MOTORS_Go(255, 80);
            delay(300);
            while(digitalRead(scharp1) != 1)
            {
              MOTORS_Go(255, 255);
            }
            delay(300);
            MOTORS_Go(0, 255);
            tactic = 1;
          }


      break;

    case 3:
      MOTORS_Go(-255 , 255);
      break;

    case 5:
      MOTORS_Go(255 , -255);
      break;

    case 4:
      MOTORS_Go(0, 255);
      delay(100);
      break;

    case 6:
      MOTORS_Go(255, 0);
      delay(100);
      break;

    case 8:
      MOTORS_Go(255, 255);
      break;

    case 9:
      MOTORS_Go(255, 255);
      break;
      
  }
 
  // dotek bílé čáry levým senzorem
  if (LINE_Get(2, hodnota_cary, 0) == 1) {

    Serial.println("qre 1");
    MOTORS_Go(255, -255);

    if(qre_stav == 1)                            //pokud pred kratkou dobou bylo zpozorováno jiné QRE
    {
      delay((cas_otaceni*2)-100);
      qre_stav = 0;    
    }
    else
    {
      delay(cas_otaceni); 
      qre_stav = 1;
      cas_dotek = millis();   
    }

  }

  // dotek bílé čáry pravým senzorem
  if (LINE_Get(3, hodnota_cary, 0) == 1) {
    
    Serial.println("qre 2");
    MOTORS_Go(-255, 255);

    if(qre_stav == 1)                            //pokud pred kratkou dobou bylo zpozorováno jiné QRE
    {
      delay((cas_otaceni*2)-100);
      qre_stav = 0;  
    }
    else
    {
      delay(cas_otaceni); 
      qre_stav = 1;
      cas_dotek = millis();
    }

  }

  if(millis() - cas_dotek >= cas_otaceni+200)    //po uplinutí času se změní stav při detekování QRE
  {
    qre_stav = 0;  
  }
  
  if(millis()>=ServerLastUpdate+500) {
	ServerLastUpdate = millis();
		//replace with the curent mode of sumec - 0 == stopped; n(1-3) == mode#n (can add more if needed)
	//<data> - replace these lines with data from sensors
	
	
	VarSharp_Left = String(1-digitalRead(35));
	VarSharp_Right = String(1-digitalRead(16));
	VarQRE_Left = String(LINE_Get(1, 3000));
	VarQRE_Rear = String(LINE_Get(4, 3000));
	VarQRE_Right = String(LINE_Get(3, 3000));	//</data> - up to here
	String VarIR = String(0);	//replace with the decoded IR (RC5 or NAC) value
	
	Serial.println("<Sending>");
	Serial.println("VarMode: " + String(VarMode));
	Serial.println("VarTfL_Left: " + String(VarTfL_Left));
	Serial.println("VarTfL_Mid: " + String(VarTfL_Mid));
	Serial.println("VarTfL_Right: " + String(VarTfL_Right));
	Serial.println("VarSharp_Left: " + String(VarSharp_Left));
	Serial.println("VarSharp_Right: " + String(VarSharp_Right));
	Serial.println("VarQRE_Left: " + String(VarQRE_Left));
	Serial.println("VarQRE_Rear: " + String(VarQRE_Rear));
	Serial.println("VarQRE_Right: " + String(VarQRE_Right));
	Serial.println("VarIR: " + String(VarIR));
	Serial.println("</Sending>");
	
	JsonObject obj = jsonDocument2.to<JsonObject>();
	
	obj["Mode"] = String(VarMode);	//assign each value to a set keyword
	obj["TfL_Left"] = String(VarTfL_Left);
	obj["TfL_Mid"] = String(VarTfL_Mid);
	obj["TfL_Right"] = String(VarTfL_Right);
	obj["Sharp_Left"] = String(VarSharp_Left);
	obj["Sharp_Right"] = String(VarSharp_Right);
	obj["QRE_Left"] = String(VarQRE_Left);
	obj["QRE_Rear"] = String(VarQRE_Rear);
	obj["QRE_Right"] = String(VarQRE_Right);
	obj["IR"] = String(VarIR);
	
	String buffer = "";
	serializeJson(jsonDocument2, buffer);	//used to serialize the "jsonDocument2" of type "StaticJsonDocument<>" to a string stored in var. "buffer" of type "String"
	
	//...//////////////////////////////////
	//..//    <POST and deserialize>    //
	//.//////////////////////////////////
	// SWSRCPRequest([Mode], [Path], [Input], [Server])
	// -used for sending data to the server
	// -I/O
	//  -Input
	//   -String [Mode] - accepts only "post" or "get", GET is explained elsewhere
	//   -String [Path] - the path of the web server that accepts this post request. used in creating the full address - (ex. Path: "post") (ex. full address: "http://192.168.1.22/post")
	//   -String [Input] - serialized json ready to be sent
	//   -String [Server] - Internet Protocol address of the webserver (servers IP) - (ex. Server:"http://192.168.1.22")
	//  -Output
	//   -returns exactly what the server recieves, the output can be used for confirming success of the request as serialized json String
	
	DeserializationError error2 = deserializeJson(jsonDocument, SWSRCPRequest("post", "post", buffer, HOST_NAME));
	if(error2) {
		Serial.print("deserializeJson error2: ");
		Serial.println(error2.c_str());
	} else {
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
}

