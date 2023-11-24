#define tlacitko 2
#define led 15
//#define RC5 0

#if defined (RC5)
    #define ADDR_PROGRAM  11
    #define ADDR_START    7
#else
    #define ADDR_PROGRAM  0
    #define ADDR_START    3
#endif




// programové funkce
const int LEDPin = 15;
TaskHandle_t Task1;
int LEDBlink = 0;
int Range = 40;  //sensor range setting
int hodnota_cary = 1000;  // určuje zdali je barva spíš bílá nebo černá
int laser_number;  // třídící proměná TF_lun

//IR proměné a nastavení:
int code;
int adres;
int comand_first;
int comand;
int DohaioID;
int start_control = 0;
IRrecv irrecv(38); //IR nastavení

//Klinč taktika => promšna
int KL_hodnota;