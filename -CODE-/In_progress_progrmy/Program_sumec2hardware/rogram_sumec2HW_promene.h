#define tlacitko 2
#define led 15
//#define RC5 1

#if defined (RC5)
    #define ADDR_PROGRAM  11
    #define ADDR_START    7
#else
    #define ADDR_PROGRAM  31
    #define ADDR_START    31
#endif




// programové funkce
const int LEDPin = 15;
TaskHandle_t Task1;
int LEDBlink = 0;
int LedBlinkState = 0;
int kstav = 0;
int Mode = 1;

int qre_stav = 0;
int qre_number = 0;
int hodnota_cary = 1000;  // určuje zdali je barva spíš bílá nebo černá
int cas_dotek = 0;
int cas_otaceni = 1000;

int stret_vzdalenost = 20;    // vzdalenost pri stretu
int Range = 20;  //hodnota zpozorovani nepritele    -  zmenšen kvůli testování
int laser_number = 0;  // třídící proměná TF_lun

//IR proměné a nastavení:
int code;
int adres;
int comand_first;
int comand;
int DohaioID;
int start_control = 0;
IRrecv irrecv(38); //IR nastavení

