#include <IRremote.h>


int recvPin = 39;
int i = 0;
IRrecv irrecv(recvPin);

int IRstart()
{

  int code;
  int adres;
  int comand_first;
  int comand;
  int DohaioID;
  int start_control;

  decode_results results;        

  if (irrecv.decode(&results)) {  

    code = results.value & 0x7FF;
    comand_first = code & 0x3F;
    comand = comand_first / 0b10;
    adres = code / 0b1000000; 

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
    irrecv.resume();

    if(adres == 11)
    {
    Serial.println("program!");

      DohaioID = comand;
      Serial.print(DohaioID);
      Serial.println(" ");
        

    }
    if(adres == 7)
    {
      if(comand == DohaioID)
      {
        Serial.println("jedeme"); 
        start_control = 1;   
      }

      else
      {
        Serial.println("špatný code");    
      }                 
    }
    return(start_control);
  }
}

void IR_setup()
{
  irrecv.enableIRIn();
}

