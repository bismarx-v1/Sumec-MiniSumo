#define tlacitko 2
#define led 47

#define scharp_L 35
#define scharp_P 16

//#define RC5 1

#if defined (RC5)
    #define ADDR_PROGRAM  11
    #define ADDR_START    7
#else
    #define ADDR_PROGRAM  31
    #define ADDR_START    31
#endif




// programové funkce
const int LEDPin = 48;
//TaskHandle_t Task1;
int LEDBlink = 1;
int LedBlinkState = 0;
int kstav = 0;
bool tactic_stop = 0;   

int BATERRY_MODE = 1;           //PRO UPRAVENI TIPU BATERIE 3 clanek = 2,   2 clanek = 1

int qre_stav = 0;
int qre_number = 0;
int hodnota_cary = 1000;  // určuje zdali je barva spíš bílá nebo černá
int cas_dotek = 0;
int cas_otaceni = 300;
int posledni_qre = 1;

//int stret_vzdalenost = 20;    // vzdalenost pri stretu - Neplati
int Range = 20;  //hodnota zpozorovani nepritele    -  zmenšen kvůli testování
int laser_number = 0;  // třídící proměná TF_lun
int primar_luna = 0;

//IR proměné a nastavení:
int code;
int adres;
int comand_first;
int comand;
int DohaioID;
int start_control = 0;



IRrecv irrecv(38); //IR nastavení

