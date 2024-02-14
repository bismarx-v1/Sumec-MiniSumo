#include <WiFi.h>                                     // needed to connect to WiFi
#include <WebServer.h>                                // needed to create a simple webserver (make sure tools -> board is set to ESP32, otherwise you will get a "WebServer.h: No such file or directory" error)
#include <WebSocketsServer.h>                         // needed for instant communication between client and server through Websockets
#include <ArduinoJson.h>                              // needed for JSON encapsulation (send multiple variables with one string)

// SSID and password of Wifi connection:
const char* ssid = "[]";		//ssid
const char* password = "[]";	//pass

// The String below "webpage" contains the complete HTML code that is sent to the client whenever someone connects to the webserver
String webpage = "<!DOCTYPE html><html><head><title>SumecWSRCP</title><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\" /><style>table, th, td {border:1px solid;Width:20%;text-align:left;border-collapse: collapse;padding-left:5px;}</style></head><body style=\"font-family:Consolas; background:#890069; color:#00FFA5;\"><div style=\"margin-left:10%;\"><table style=\"width:80%;  border:2px solid;\"><tr><th style=\"padding-left:0px; width:50%;\"><select name=\"Mode\" id=\"Element_Select_mode\" style=\"width:100%;\"><option value=\"0\">Stop</option><option value=\"1\">Mode1</option><option value=\"2\">Mode2</option><option value=\"3\">Mode3</option></select></th><th><span id=\"Element_Mode\" style=\"white-space: nowrap\">[No Scripts]</span></th><th style=\"padding-left:10px; padding-right:10px;\"><input type=\"button\" id=\"Element_Button_Run\" value=\"Run\" style=\"width:100%;\"></th></tr></table><table style=\"width:80%;  border:2px solid;\"><tr><th colspan=\"3\">Sensors</th></tr><tr><th rowspan=\"3\">Tf-Luna</th><th>Left</th><th><span id=\"Element_TfL_Left\">[No Scripts]</span> cm</th></tr><tr><th>Mid</th><th><span id=\"Element_TfL_Mid\">[No Scripts]</span> cm</th></tr><tr><th>Right</th><th><span id=\"Element_TfL_Right\">[No Scripts]</span> cm</th></tr><tr><th rowspan=\"2\">Sharp<br>GP2Y0D810Z0F</th><th>Left</th><th><span id=\"Element_Sharp_Left\">[No Scripts]</span></th></tr><tr><th>Right</th><th><span id=\"Element_Sharp_Right\">[No Scripts]</span></th></tr><tr><th rowspan=\"3\">QRE1113</th><th>Left</th><th><span id=\"Element_QRE_Left\">[No Scripts]</span></th></tr><tr><th>Rear</th><th><span id=\"Element_QRE_Rear\">[No Scripts]</span></th></tr><tr><th>Right</th><th><span id=\"Element_QRE_Right\">[No Scripts]</span></th></tr><tr><th>IR<br>TSOP382xx</th><th><span id=\"Element_IRHex\">[No Scripts]</span></th><th><span id=\"Element_IRBin\">[No Scripts]</span></th></tr></table><span id=\"Element_Text\" style=\"color:#0F00BC;\">sorry for the colours i see them fine :3 -Nat; also, scripts missing</span></div></body><script>window.onload = document.getElementById('Element_Text').innerHTML = ((Math.round(Math.random())*10%9)?\"sorry for the colours i see them fine :3 -Nat\":\"\");window.onload = document.getElementById('Element_Mode').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"stopped? >~<\":\"stopped? QwQ\"):(Math.round(Math.random())?\"stopped? TwT\":\"stopped? ;w;\"));window.onload = document.getElementById('Element_TfL_Left').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));window.onload = document.getElementById('Element_TfL_Mid').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));window.onload = document.getElementById('Element_TfL_Right').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));window.onload = document.getElementById('Element_Sharp_Left').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));window.onload = document.getElementById('Element_Sharp_Right').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));window.onload = document.getElementById('Element_QRE_Left').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));window.onload = document.getElementById('Element_QRE_Rear').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));window.onload = document.getElementById('Element_QRE_Right').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));window.onload = document.getElementById('Element_IRHex').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));window.onload = document.getElementById('Element_IRBin').innerHTML = (Math.round(Math.random())?(Math.round(Math.random())?\"n/a >~<\":\"n/a QwQ\"):(Math.round(Math.random())?\"n/a TwT\":\"n/a ;w;\"));var Socket;document.getElementById('Element_Button_Run').addEventListener(\"click\", RunButtonFunc);function RunButtonFunc() {var SendObj ={Button_Run:	document.getElementById('Element_Button_Run').value,Select_mode: document.getElementById('Element_Select_mode').value};Socket.send(JSON.stringify(SendObj));}function init() {Socket = new WebSocket('ws:\//' + window.location.hostname + ':81/');Socket.onmessage = function(event) {processCommand(event);};}function zeroPad(num, places) {var zero = places - num.toString().length + 1;return Array(+(zero > 0 && zero)).join(\"0\") + num;}function processCommand(event) {var obj = JSON.parse(event.data);console.log(obj);document.getElementById('Element_Mode').innerHTML = ((obj.Mode == \"0\")?\"Stopped\":((obj.Mode == \"1\")?\"Mode1\":((obj.Mode == \"2\")?\"Mode2\":((obj.Mode == \"3\")?\"Mode3\":\"SomethingWentWrong>~<\"))));document.getElementById('Element_TfL_Left').innerHTML = (obj.TfL_Left);document.getElementById('Element_TfL_Mid').innerHTML = (obj.TfL_Mid);document.getElementById('Element_TfL_Right').innerHTML = (obj.TfL_Right);document.getElementById('Element_Sharp_Left').innerHTML = ((obj.Sharp_Left)?\"Blocked\":\"Clear\");document.getElementById('Element_Sharp_Right').innerHTML = ((obj.Sharp_Right)?\"Blocked\":\"Clear\");document.getElementById('Element_QRE_Left').innerHTML = ((obj.QRE_Left == \"1\")?\"Bright(Edge)\":\"Dim(Floor/Empty)\");document.getElementById('Element_QRE_Rear').innerHTML = ((obj.QRE_Rear == \"1\")?\"Bright(Edge)\":\"Dim(Floor/Empty)\");document.getElementById('Element_QRE_Right').innerHTML = ((obj.QRE_Right == \"1\")?\"Bright(Edge)\":\"Dim(Floor/Empty)\");document.getElementById('Element_IRHex').innerHTML = (zeroPad(parseInt(obj.IR).toString(16), 4));document.getElementById('Element_IRBin').innerHTML = (zeroPad(parseInt(obj.IR).toString(2), 16));}window.onload = function(event) {init();}</script></html>";

// The JSON library uses static memory, so this will need to be allocated:
// -> in the video I used global variables for "doc_tx" and "doc_rx", however, I now changed this in the code to local variables instead "doc" -> Arduino documentation recomends to use local containers instead of global to prevent data corruption

// We want to periodically send values to the clients, so we need to define an "interval" and remember the last time we sent data to the client (with "previousMillis")
int interval = 1000;                                  // send data to the client every 1000ms -> 1s
unsigned long previousMillis = 0;                     // we use the "millis()" command for time reference and this will output an unsigned long

// Initialization of webserver and websocket
WebServer server(80);                                 // the server uses port 80 (standard port for websites
WebSocketsServer webSocket = WebSocketsServer(81);    // the websocket uses port 81 (standard port for websockets

void setup() {
  Serial.begin(115200);                               // init serial port for debugging
 
  WiFi.begin(ssid, password);                         // start WiFi interface
  Serial.println("Establishing connection to WiFi with SSID: " + String(ssid));     // print SSID to the serial interface for debugging
 
  while (WiFi.status() != WL_CONNECTED) {             // wait until WiFi is connected
    delay(1000);
    Serial.print(".");
  }
  Serial.print("Connected to network with IP address: ");
  Serial.println(WiFi.localIP());                     // show IP address that the ESP32 has received from router
  
  server.on("/", []() {                               // define here wat the webserver needs to do
    server.send(200, "text/html", webpage);           //    -> it needs to send out the HTML string "webpage" to the client
  });
  server.begin();                                     // start server
  
  webSocket.begin();                                  // start websocket
  webSocket.onEvent(webSocketEvent);                  // define a callback function -> what does the ESP32 need to do when an event from the websocket is received? -> run function "webSocketEvent()"
}

void loop() {
  server.handleClient();                              // Needed for the webserver to handle all clients
  webSocket.loop();                                   // Update function for the webSockets 
  
  unsigned long now = millis();                       // read out the current "time" ("millis()" gives the time in ms since the Arduino started)
  if ((unsigned long)(now - previousMillis) > interval) { // check if "interval" ms has passed since last time the clients were updated
    
    String jsonString = "";                           // create a JSON string for sending data to the client
    StaticJsonDocument<200> doc;                      // create a JSON container
    JsonObject object = doc.to<JsonObject>();         // create a JSON Object
    object["Mode"] = random(4);                    // write data into the JSON object -> I used "rand1" and "rand2" here, but you can use anything else
    object["TfL_Left"] = random(4096);
    object["TfL_Mid"] = random(4096);
    object["TfL_Right"] = random(4096);
    object["Sharp_Left"] = random(2);
    object["Sharp_Right"] = random(2);
    object["QRE_Left"] = random(2);
    object["QRE_Rear"] = random(2);
    object["QRE_Right"] = random(2);
    object["IR"] = random(65535);
	
    serializeJson(doc, jsonString);                   // convert JSON object to string
    Serial.println(jsonString);                       // print JSON string to console for debug purposes (you can comment this out)
    webSocket.broadcastTXT(jsonString);               // send JSON string to clients
    
    previousMillis = now;                             // reset previousMillis
  }
}

void webSocketEvent(byte num, WStype_t type, uint8_t * payload, size_t length) {      // the parameters of this callback function are always the same -> num: id of the client who send the event, type: type of message, payload: actual data sent and length: length of payload
  switch (type) {                                     // switch on the type of information sent
    case WStype_DISCONNECTED:                         // if a client is disconnected, then type == WStype_DISCONNECTED
      Serial.println("Client " + String(num) + " disconnected");
      break;
    case WStype_CONNECTED:                            // if a client is connected, then type == WStype_CONNECTED
      Serial.println("Client " + String(num) + " connected");
      // optionally you can add code here what to do when connected
      break;
    case WStype_TEXT:                                 // if a client has sent data, then type == WStype_TEXT
      // try to decipher the JSON string received
      StaticJsonDocument<200> doc;                    // create a JSON container
      DeserializationError error = deserializeJson(doc, payload);
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
      }
      else {
        // JSON string was received correctly, so information can be retrieved:
        const char* g_brand = doc["Button_Run"];
        const char* g_type = doc["Select_mode"];
        Serial.println("Received guitar info from user: " + String(num));
        Serial.println("Brand: " + String(g_brand));
        Serial.println("Type: " + String(g_type));
      }
      Serial.println("");
      break;
  }
}
