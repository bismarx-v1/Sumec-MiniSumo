//...///////////////////
//..//    Imports    //
//.///////////////////
#include "SWSRCPClientFunctions.h"

//...////////////////////
//..//    Settings    //
//.////////////////////
const char* SWSRCP_SSID = "SWSRCP#01";	//name of the web server's access point
const char* SWSRCP_PASSWORD = "3ac5c0cc-24bd-4d68-90b9-20d97ed3e080";	//pass to the web server's access point
String HOST_NAME = "http://192.168.1.22";	//IP of the web server

//.../////////////////////////
//..//    Other defines    //
//./////////////////////////

String GlobalTestVarMode;	//only for this example

void setup() {
	Serial.begin(115200);	//start serial
	delay(2000);	//wait for serial
	Serial.println("START");	//print "START"
	
	ConnectToAP(SWSRCP_SSID, SWSRCP_PASSWORD);	//function designed to connect to an access point. curently part of the lib.
}

void loop() {
	//...////////////////////////////////////
	//..//    start of the GET process    //
	//.////////////////////////////////////
	Serial.println("\nGET");	//debug print
	
	//.../////////////////////////////////
	//..//    <GET and deserialize>    //
	//./////////////////////////////////
	// SWSRCPRequest([Mode], [Path], [Input], [Server])
	// -used for sending data to the server
	// -I/O
	//  -Input
	//   -String [Mode] - accepts only "post" or "get", POST is explained elsewhere
	//   -String [Path] - the path of the web server that accepts this post request. used in creating the full address - (ex. Path: "get") (ex. full address: "http://192.168.1.22/get")
	//   -String [Input] - should be empty for this Mode
	//   -String [Server] - Internet Protocol address of the webserver (servers IP) - (ex. Server:"http://192.168.1.22")
	//  -Output
	//   -returns server's data as serialized json String
	
	DeserializationError error = deserializeJson(jsonDocument, SWSRCPRequest("get", "get", "", HOST_NAME));
	if(error) {
		Serial.print("GET deserializeJson error: ");
		Serial.println(error.c_str());
	}
	else {	//this will run if the output was deserialized
		const char* VarSiteRunButon = jsonDocument["Button_Run"];
		const char* VarSiteSelectedMode = jsonDocument["Select_Mode"];
		
		if(VarSiteSelectedMode[0] >= 48 && VarSiteSelectedMode[0] <= 57) {	//this is just for debug
			GlobalTestVarMode = VarSiteSelectedMode;
		}
		
		Serial.println("<GET output>");
		Serial.println("Run: " + String(VarSiteRunButon));
		Serial.println("Mode: " + String(VarSiteSelectedMode));
		Serial.println("</GET output>");
	}
	//..||||||||||||||||||||||||||||||||||
	//..||    </GET and deserialize>    ||
	//..||||||||||||||||||||||||||||||||||
	
	//...//////////////////////////////////
	//..//    end of the GET process    //
	//.//////////////////////////////////
	delay(500);
	
	//.../////////////////////////////////////
	//..//    start of the POST process    //
	//./////////////////////////////////////
	Serial.println("\nPOST");	//debug print
	
	String VarMode = GlobalTestVarMode;	//replace with the curent mode of sumec - 0 == stopped; n(1-3) == mode#n (can add more if needed)
	String VarTfL_Left = String(random(4096));	//<data> - replace these lines with data from sensors
	String VarTfL_Mid = String(random(4096));
	String VarTfL_Right = String(random(4096));
	String VarSharp_Left = String(random(2));
	String VarSharp_Right = String(random(2));
	String VarQRE_Left = String(random(2));
	String VarQRE_Rear = String(random(2));
	String VarQRE_Right = String(random(2));	//</data> - up to here
	String VarIR = String(random(65535));	//replace with the decoded IR (RC5 or NAC) value
	
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
		Serial.print("POST - deserializeJson error: ");
		Serial.println(error.c_str());
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
	//..|||||||||||||||||||||||||||||||||||
	//..||    </POST and deserialize>    ||
	//..|||||||||||||||||||||||||||||||||||
	
	//...///////////////////////////////////
	//..//    end of the POST process    //
	//.///////////////////////////////////
	delay(500);
}