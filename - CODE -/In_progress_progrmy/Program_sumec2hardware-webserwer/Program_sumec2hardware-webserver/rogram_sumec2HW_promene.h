#define tlacitko 2
#define led 15
//#define RC5 0

#if defined (RC5)
    #define ADDR_PROGRAM  11
    #define ADDR_START    7
#else
    #define ADDR_PROGRAM  31
    #define ADDR_START    7
#endif




// programové funkce
const int LEDPin = 15;
TaskHandle_t Task1;
int LEDBlink = 0;
int Range = 40;  //sensor range setting
int hodnota_cary = 1000;  // určuje zdali je barva spíš bílá nebo černá
int laser_number;  // třídící proměná TF_lun
int LedBlinkState = 0;

//IR proměné a nastavení:
int code;
int adres;
int comand_first;
int comand;
int DohaioID;
int start_control = 0;
IRrecv irrecv(38); //IR nastavení

//střet taktika
int scas = 0; 

//...//////////////////////////
//..//    SWSRCPSettings    //
//.//////////////////////////
char SWSRCP_DISABLE = 0;
char SWSRCP_DEBUG = 0;
const char* SWSRCP_SSID = "SWSRCP#01";	//name of the web server's access point
const char* SWSRCP_PASSWORD = "3ac5c0cc-24bd-4d68-90b9-20d97ed3e080";	//pass to the web server's access point
String HOST_NAME = "http://192.168.1.22";	//IP of the web server

char* VarMode;	// sumec's mode
char* TypMode;