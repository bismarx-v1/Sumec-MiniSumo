#include <Arduino.h>
//#include <IRremote.hpp>
#include <IRremote.h>

#define RC5 1

#if defined (RC5)
    #define ADDR_PROGRAM  11
    #define ADDR_START    7
#else
    #define ADDR_PROGRAM  31
    #define ADDR_START    31
#endif

int code;
int adres;
int comand_first;
int comand;
int DohaioID;
int start_control = 0;



const int RECV_PIN = 38;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop(){
  if (irrecv.decode(&results)){
      code = results.value & 0x7FF;  //z přijatého signálu vezme pouze posledních jedenást hodnot a dosadí do proměné code (BIN)
      comand_first = code & 0x3F;    //vytažení posledních 6 hodnot (Dohayo ID)
      comand = comand_first / 0b10;  //vyjmutí poslední hodnoty 
      adres = code / 0b1000000;      //z přijatého signálu vezme prvních 5 hodnot (Adresa) 

      //vypsání všsch hodnot z IR, nejdřívě BIN potom DEC  

      
      Serial.println("");
      Serial.print("recieved signal: ");
      Serial.print(results.value, BIN);
      Serial.print("    DEC: ");
      Serial.println(results.value);
      Serial.print("code: ");
      Serial.print(code, BIN);
      Serial.print("    DEC: ");
      Serial.println(code);
      Serial.print("adresa: ");
      Serial.print(adres, BIN);
      Serial.print("    DEC: ");
      Serial.println(adres);
      Serial.print("comand_first: ");
      Serial.print(comand_first, BIN);
      Serial.print("    DEC: ");
      Serial.println(comand_first);
      Serial.print("comand: ");
      Serial.print(comand, BIN);
      Serial.print("    DEC: ");
      Serial.println(comand);
      Serial.println("");
      Serial.println("==========");
      

      //fáze program
      if (adres == ADDR_PROGRAM) {
        DohaioID = comand;
        Serial.print("DohaioID: ");
        Serial.println(DohaioID);
        Serial.println(" ");
      }

      //fáze startováni
      if (adres == ADDR_START) {
        if (comand == DohaioID) {
          Serial.println("jedeme");
          start_control = 1;

        } 
        else {
          Serial.println("špatný code");
        }
      }

      irrecv.resume();
  }
}

