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
const char* ssid = "Sumec_#01";			/*sumec's ap ssid*/
const char* password = "SumecPass1";	/*sumec's ap pass*/
IPAddress local_IP(182,168,1,10);		/*sumec's local ip*/
//the next line is the website
const String webpage = "<!DOCTYPE html>   <html><head>	<title>SumecWSRCP</title>	<meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\" />	<style>		table, th, td {			border:1px solid;			Width:20%;			text-align:left;			border-collapse: collapse;			padding-left:5px;		}	</style></head><body style=\"font-family:Consolas; background:#890069; color:#00FFA5;\">	<div style=\"margin-left:10%;\">		<table style=\"width:80%;  border:2px solid;\">			<tr>				<th style=\"padding-left:0px; width:60%;\">					<select name=\"Mode\" id=\"Element_Select_mode\" style=\"width:100%;\">						<option value=\"0\">Stop</option>						<option value=\"1\">Mode1</option>						<option value=\"2\">Mode2</option>						<option value=\"3\">Mode3</option>					</select>				</th>				<th>					<span id=\"Element_Mode\">[No Scripts]</span>				</th>				<th style=\"padding-left:10px; padding-right:10px;\">					<input type=\"button\" id=\"Element_Button_Run\" value=\"Run\" style=\"width:100%;\">				</th>			</tr>		</table>		<table style=\"width:80%;  border:2px solid;\">			<tr>				<th colspan=\"3\">					Sensors				</th>			</tr>			<tr>				<th rowspan=\"3\">					Tf-Luna				</th>				<th>					Left				</th>				<th>					<span id=\"Element_TfL_Left\">[No Scripts]</span> cm				</th>			</tr>			<tr>				<th>					Mid				</th>				<th>					<span id=\"Element_TfL_Mid\">[No Scripts]</span> cm				</th>			</tr>			<tr>				<th>					Right				</th>				<th>					<span id=\"Element_TfL_Right\">[No Scripts]</span> cm				</th>			</tr>			<tr>				<th rowspan=\"2\">					Sharp<br>GP2Y0D810Z0F				</th>				<th>					Left				</th>				<th>					<span id=\"Element_Sharp_Left\">[No Scripts]</span>				</th>			</tr>			<tr>				<th>					Right				</th>				<th>					<span id=\"Element_Sharp_Right\">[No Scripts]</span>				</th>			</tr>			<tr>				<th rowspan=\"3\">					QRE1113				</th>				<th>					Left				</th>				<th>					<span id=\"Element_QRE_Left\">[No Scripts]</span>				</th>			</tr>			<tr>				<th>					Rear				</th>				<th>					<span id=\"Element_QRE_Rear\">[No Scripts]</span>				</th>			</tr>			<tr>				<th>					Right				</th>				<th>					<span id=\"Element_QRE_Right\">[No Scripts]</span>				</th>			</tr>			<tr>				<th>					IR<br>TSOP382xx				</th>				<th colspan=\"2\">					<span id=\"Element_IR\">[No Scripts]</span>				</th>			</tr>		</table>		<span id=\"Element_Text\" style=\"color:#0F00BC;\">sorry for the colours i see them fine :3 -Nat; also, scripts missing</span>	</div></body><script>	window.onload = document.getElementById('Element_Text').innerHTML = ((Math.round(Math.random())*10%9)?\"sorry for the colours i see them fine :3 -Nat\":\"\");		window.onload = document.getElementById('Element_Mode').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"stopped? >~<\":\"stopped? QwQ\"):(Math.round(Math.random())?\"stopped? TwT\":\"stopped? ;w;\"));		window.onload = document.getElementById('Element_TfL_Left').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));	window.onload = document.getElementById('Element_TfL_Mid').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));	window.onload = document.getElementById('Element_TfL_Right').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));		window.onload = document.getElementById('Element_Sharp_Left').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));	window.onload = document.getElementById('Element_Sharp_Right').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));		window.onload = document.getElementById('Element_QRE_Left').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));	window.onload = document.getElementById('Element_QRE_Rear').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));	window.onload = document.getElementById('Element_QRE_Right').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));		window.onload = document.getElementById('Element_IR').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));		var Socket;		document.getElementById('Element_Button_Run').addEventListener(\"click\", RunButtonFunc);	function RunButtonFunc() {		var SendObj ={			Button_Run:	document.getElementById('Element_Button_Run').value,			Select_mode: document.getElementById('Element_Select_mode').value		};		Socket.send(JSON.stringify(SendObj));	}		function init() {		Socket = new WebSocket('ws:\//' + window.location.hostname + ':81/');		Socket.onmessage = function(event) {			processCommand(event);		};	}		function processCommand(event) {		var RecievedObj = JSON.parse(event.data);		console.log(RecievedObj);		document.getElementById('Element_Mode').innerHTML = ((RecievedObj.Mode)?\"Stopped\":((RecievedObj.Mode)?\"Mode1\":((RecievedObj.Mode)?\"Mode2\":((RecievedObj.Mode)?\"Mode3\":\"SomethingWentWrong>~<\"))));						document.getElementById('Element_TfL_Left').innerHTML = (RecievedObj.TfL_Left);		document.getElementById('Element_TfL_Mid').innerHTML = (RecievedObj.TfL_Mid);		document.getElementById('Element_TfL_Right').innerHTML = (RecievedObj.TfL_Right);						document.getElementById('Element_Sharp_Left').innerHTML = ((RecievedObj.Sharp_Left)?\"\":\"Clear\");		document.getElementById('Element_Sharp_Right').innerHTML = ((RecievedObj.Sharp_Right)?\"\":\"Clear\");				document.getElementById('Element_QRE_Left').innerHTML = ((RecievedObj.QRE_Left)?\"Bright(Edge)\":\"Dim(Floor/Empty)\");		document.getElementById('Element_QRE_Rear').innerHTML = ((RecievedObj.QRE_Rear)?\"Bright(Edge)\":\"Dim(Floor/Empty)\");		document.getElementById('Element_QRE_Right').innerHTML = ((RecievedObj.QRE_Right)?\"Bright(Edge)\":\"Dim(Floor/Empty)\");				document.getElementById('Element_IR').innerHTML = (num.toString(RecievedObj.IR));	}		window.onload = function(event) {		init();	}		</script></html>";

//...////////////////////////
//..//    Rest of code    //
//.////////////////////////
unsigned long WebServer_TimeNow;

IPAddress gateway(182,168,1,5);
IPAddress subnet(255,255,255,0);

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

StaticJsonDocument<400> JsonDoc_tx;
StaticJsonDocument<400> JsonDoc_rx;

String jsonString = "";

JsonObject object;

unsigned long WebServer_TimePrev;

//...//////////////////////////
//..//    OnRecieve Code    //
//.//////////////////////////
void WebSocketEvent(byte num, WStype_t type, uint8_t * payload, size_t length) {
	switch(type) {
		case WStype_DISCONNECTED:
			Serial.print("Core["+String(xPortGetCoreID())+"]: ");
			Serial.println("Client #" + String(num) + " disconnected");
			break;
		
		case WStype_CONNECTED:
			Serial.print("Core["+String(xPortGetCoreID())+"]: ");
			Serial.println("Client #" + String(num) + " connected");
			break;
		
		case WStype_TEXT:
			DeserializationError error =  deserializeJson(JsonDoc_rx, payload);
			if(error) {
				Serial.print("Core["+String(xPortGetCoreID())+"]: ");
				Serial.println("deserializeJson() failed");
				break;
			}
			else {
				const char* RunButton = JsonDoc_rx["Button_Run"];
				const int ModeVar = JsonDoc_rx["Select_mode"];
				
				Serial.print("Core["+String(xPortGetCoreID())+"]: ");
				Serial.print("Mode: " + String(ModeVar));
				Serial.println("\t - " + String(((ModeVar)?"Stopped":((ModeVar)?"Mode1":((ModeVar)?"Mode2":((ModeVar)?"Mode3":"SomethingWentWrong>~<"))))));
			}
			break;
	}
}

//...//////////////////////
//..//    Void Setup    //
//.//////////////////////
void setup() {
	Serial.begin(115200);
	delay(2000);
	
	Serial.print("Core["+String(xPortGetCoreID())+"]: ");
	Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");
	
	Serial.print("Core["+String(xPortGetCoreID())+"]: ");
	Serial.println(WiFi.softAP(ssid, password) ? "Ready" : "Failed!");
	
	Serial.print("Core["+String(xPortGetCoreID())+"]: ");
	Serial.println("AP SSID = " + String(ssid));
	
	Serial.print("Core["+String(xPortGetCoreID())+"]: ");
	Serial.println("AP Pass = " + String(password));
	
	Serial.print("Core["+String(xPortGetCoreID())+"]: ");
	Serial.println(WiFi.softAPIP());
	
	Serial.println("");
	
	server.on("/", [] () {
		server.send(200, "text/html", webpage);
	});
	server.begin();
	webSocket.begin();
	webSocket.onEvent(WebSocketEvent);
}

//...///////////////////////
//..//    Update Code    //
//.///////////////////////
void SumecWebServer_Update(String UpdateVar, int UpdateVarValue) {
	object[UpdateVar] = UpdateVarValue;
}

//.../////////////////////
//..//    Void Loop    //
//./////////////////////
void loop() {
	server.handleClient();
	webSocket.loop();
	
	if(WebServer_TimePrev + 500 <= millis()) {	//500 is the least delay befor update
		jsonString = "";
		JsonObject object = JsonDoc_tx.to<JsonObject>();
		
		SumecWebServer_Update("Mode", random(4));	//Sends an int from <0; 4) to Mode
		
		SumecWebServer_Update("TfL_Left", random(4096));
		SumecWebServer_Update("TfL_Mid", random(4096));
		SumecWebServer_Update("TfL_Right", random(4096));
		
		SumecWebServer_Update("Sharp_Left", random(2));
		SumecWebServer_Update("Sharp_Right", random(2));
		
		SumecWebServer_Update("QRE_Left", random(4096));
		SumecWebServer_Update("QRE_Rear", random(4096));
		SumecWebServer_Update("QRE_Right", random(4096));
		
		SumecWebServer_Update("IR", random(65535));
		
		serializeJson(JsonDoc_tx, jsonString);
		webSocket.broadcastTXT(jsonString);
		
		WebServer_TimePrev = millis();
	}
}

