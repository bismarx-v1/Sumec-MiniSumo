//...///////////////////
//..//    Inports    //
//.///////////////////
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>

TaskHandle_t Task1;

//...//////////////////////
//..//    APSettings    //
//.//////////////////////
const char* ssid = "Sumec_#01";			/*sumec's ap ssid*/
const char* password = "SumecPass1";	/*sumec's ap pass*/
IPAddress local_IP(182,168,1,22);		/*sumec's local ip*/
String webpage = "";

//...////////////////////////
//..//    Rest of code    //
//.////////////////////////
IPAddress gateway(182,168,1,5);
IPAddress subnet(255,255,255,0);

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

