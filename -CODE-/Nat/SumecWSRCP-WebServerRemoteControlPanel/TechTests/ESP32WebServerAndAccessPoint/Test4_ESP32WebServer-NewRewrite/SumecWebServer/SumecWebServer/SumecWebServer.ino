//...///////////////////
//..//    Imports    //
//.///////////////////
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>

//...//////////////////////
//..//    APSettings    //
//.//////////////////////
const char* ssid = "[]";			/*router's ap ssid*/
const char* password = "[]";	/*router's ap pass*/

const String webpage = "<!DOCTYPE html><html><head><title>SumecWSRCP</title><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\" /><style>table, th, td {border:1px solid;Width:20%;text-align:left;border-collapse: collapse;padding-left:5px;}</style></head><body style=\"font-family:Consolas; background:#890069; color:#00FFA5;\"><div style=\"margin-left:10%;\"><table style=\"width:80%;  border:2px solid;\"><tr><th style=\"padding-left:0px; width:50%;\"><select name=\"Mode\" id=\"Element_Select_Mode\" style=\"width:100%;\"><option value=\"0\">Stop</option><option value=\"1\">Mode1</option><option value=\"2\">Mode2</option><option value=\"3\">Mode3</option></select></th><th><span id=\"Element_Mode\" style=\"white-space: nowrap\">[No Scripts]</span></th><th style=\"padding-left:10px; padding-right:10px;\"><input type=\"button\" id=\"Element_Button_Run\" value=\"Run\" style=\"width:100%;\"></th></tr></table><table style=\"width:80%;  border:2px solid;\"><tr><th colspan=\"3\">Sensors</th></tr><tr><th rowspan=\"3\">Tf-Luna</th><th>Left</th><th><span id=\"Element_TfL_Left\">[No Scripts]</span> cm</th></tr><tr><th>Mid</th><th><span id=\"Element_TfL_Mid\">[No Scripts]</span> cm</th></tr><tr><th>Right</th><th><span id=\"Element_TfL_Right\">[No Scripts]</span> cm</th></tr><tr><th rowspan=\"2\">Sharp<br>GP2Y0D810Z0F</th><th>Left</th><th><span id=\"Element_Sharp_Left\">[No Scripts]</span></th></tr><tr><th>Right</th><th><span id=\"Element_Sharp_Right\">[No Scripts]</span></th></tr><tr><th rowspan=\"3\">QRE1113</th><th>Left</th><th><span id=\"Element_QRE_Left\">[No Scripts]</span></th></tr><tr><th>Rear</th><th><span id=\"Element_QRE_Rear\">[No Scripts]</span></th></tr><tr><th>Right</th><th><span id=\"Element_QRE_Right\">[No Scripts]</span></th></tr><tr><th>IR<br>TSOP382xx</th><th>0x<span id=\"Element_IRHex\">[No Scripts]</span></th><th>0b<span id=\"Element_IRBin\">[No Scripts]</span></th></tr></table><span id=\"Element_Text\" style=\"color:#0F00BC;\">sorry for the colours i see them fine :3 -Nat; also, scripts missing</span></div></body><script>window.onload = document.getElementById('Element_Text').innerHTML = ((Math.round(Math.random())*10%9)?\"sorry for the colours i see them fine :3 -Nat\":\"\");window.onload = document.getElementById('Element_Mode').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"stopped? >~<\":\"stopped? QwQ\"):(Math.round(Math.random())?\"stopped? TwT\":\"stopped? ;w;\"));window.onload = document.getElementById('Element_TfL_Left').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));window.onload = document.getElementById('Element_TfL_Mid').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));window.onload = document.getElementById('Element_TfL_Right').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));window.onload = document.getElementById('Element_Sharp_Left').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));window.onload = document.getElementById('Element_Sharp_Right').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));window.onload = document.getElementById('Element_QRE_Left').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));window.onload = document.getElementById('Element_QRE_Rear').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));window.onload = document.getElementById('Element_QRE_Right').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));window.onload = document.getElementById('Element_IRHex').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));window.onload = document.getElementById('Element_IRBin').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));var Socket;document.getElementById('Element_Button_Run').addEventListener(\"click\", RunButtonFunc);function RunButtonFunc() {var SendObj ={Button_Run:	document.getElementById('Element_Button_Run').value,Select_Mode: document.getElementById('Element_Select_Mode').value};Socket.send(JSON.stringify(SendObj));}function init() {Socket = new WebSocket('ws:\//' + window.location.hostname + ':81/');Socket.onmessage = function(event) {processCommand(event);};}function zeroPad(num, places) {var zero = places - num.toString().length + 1;return Array(+(zero > 0 && zero)).join(\"0\") + num;}function processCommand(event) {var obj = JSON.parse(event.data);document.getElementById('Element_Mode').innerHTML = ((obj.Mode == \"0\")?\"Stopped\":((obj.Mode == \"1\")?\"Mode1\":((obj.Mode == \"2\")?\"Mode2\":((obj.Mode == \"3\")?\"Mode3\":\"SomethingWentWrong>~<\"))));document.getElementById('Element_TfL_Left').innerHTML = (obj.TfL_Left);document.getElementById('Element_TfL_Mid').innerHTML = (obj.TfL_Mid);document.getElementById('Element_TfL_Right').innerHTML = (obj.TfL_Right);document.getElementById('Element_Sharp_Left').innerHTML = ((obj.Sharp_Left)?\"Blocked\":\"Clear\");document.getElementById('Element_Sharp_Right').innerHTML = ((obj.Sharp_Right)?\"Blocked\":\"Clear\");document.getElementById('Element_QRE_Left').innerHTML = ((obj.QRE_Left == \"1\")?\"Bright(Edge)\":\"Dim(Floor/Empty)\");document.getElementById('Element_QRE_Rear').innerHTML = ((obj.QRE_Rear == \"1\")?\"Bright(Edge)\":\"Dim(Floor/Empty)\");document.getElementById('Element_QRE_Right').innerHTML = ((obj.QRE_Right == \"1\")?\"Bright(Edge)\":\"Dim(Floor/Empty)\");document.getElementById('Element_IRHex').innerHTML = (zeroPad(parseInt(obj.IR).toString(16), 4));document.getElementById('Element_IRBin').innerHTML = (zeroPad(parseInt(obj.IR).toString(2), 16));}window.onload = function(event) {init();}</script></html>";

//.../////////////////////////
//..//    Other defines    //
//./////////////////////////
WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

unsigned long TimeLast;

StaticJsonDocument<200> doc_tx;
StaticJsonDocument<200> doc_rx;

void SWSRCPWiFiConnect() {	//Connect to WiFi
	Serial.print("Connecting to " + String(ssid));
	WiFi.begin(ssid, password);	//Start connecting to ssid with password
	while(WiFi.status() != WL_CONNECTED) {	//print a dot every second before connecting
		delay(1000);
		Serial.print(".");
	}
	
	Serial.print("\nConnected to " + String(ssid) + " with ip ");
	Serial.println(WiFi.localIP());
}

void SWSRCPSetup() {	//Start the webserver
	server.on("/", []() {
		server.send(200, "text\html", webpage);
	});
	
	server.begin();
	webSocket.begin();
	webSocket.onEvent(webSocketEvent);
}

void webSocketEvent(byte ClientNum, WStype_t type, uint8_t * payload, size_t length) {
	switch(type) {
		case WStype_DISCONNECTED:
			Serial.println("Client #" + String(ClientNum) + " disconnected");
			break;
			
		case WStype_CONNECTED:
			Serial.println("Client #" + String(ClientNum) + " connected");
			break;
			
		case WStype_TEXT:
			
			//deserializeJson(doc_rx, payload);
			DeserializationError error = deserializeJson(doc_rx, payload);
			//int error = 1;
			if(error) {
				Serial.println("Desr error");
				return;
			}
			else {
				const char* SiteRunButon = doc_rx["Button_Run"];
				const char* SiteSelectedMode = doc_rx["Select_Mode"];
				
				Serial.println("Run: " + String(SiteRunButon));
				Serial.println("Mode: " + String(SiteSelectedMode));
			}
			break;
	}
}



void setup() {
	Serial.begin(115200);
	
	SWSRCPWiFiConnect();
	
	SWSRCPSetup();
}





void loop() {
	server.handleClient();
	webSocket.loop();
	
	if(TimeLast+500<=millis()) {
		String jsonString = "";
		JsonObject object = doc_tx.to<JsonObject>();
		
		object["Mode"] = random(4);
		object["TfL_Left"] = random(4096);
		object["TfL_Mid"] = random(4096);
		object["TfL_Right"] = random(4096);
		object["Sharp_Left"] = random(2);
		object["Sharp_Right"] = random(2);
		object["QRE_Left"] = random(2);
		object["QRE_Rear"] = random(2);
		object["QRE_Right"] = random(2);
		object["IR"] = random(65535);
		
		serializeJson(doc_tx, jsonString);
		
		webSocket.broadcastTXT(jsonString);
		TimeLast = millis();
	}
}