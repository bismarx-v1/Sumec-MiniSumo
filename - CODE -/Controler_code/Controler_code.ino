// ledka
#define Led 2
// tlacitka
#define Button_Program 6
#define Button_Start 5

// 1 byt = 1,778ms

int hrany_program[14] {1,1,0,0,1,0,1,1,0,0,0,0,0,0};
int hrany_start[14] {1,1,0,0,0,1,1,1,0,0,0,0,0,0};

void setup() {

  Serial.begin(9600);

  // ledka => output
  pinMode(Led, OUTPUT);
  // tlacitka => input
  pinMode(Button_Program, INPUT);
  pinMode(Button_Start, INPUT);

}

void loop() {


  if(digitalRead(Button_Program) == 1 && digitalRead(Button_Start) == 0)
  {

    // while pro čekání na odstisknutí tlačítka:
    while(digitalRead(Button_Program) == 1) 
    {
      
    }

    Serial.println("1");
    
    // projetí celého signálu
    for(int i=0; i<14; i++)
    {
      // 1 bit: LOG.1
      if(hrany_program[i] == 1)
      {
        digitalWrite(Led, LOW);       //vypne
        delayMicroseconds(889);       //čeká polovinu bitu
        digitalWrite(Led, HIGH);      //zapne
        delayMicroseconds(889);       //čeká druhou polovinu bitu
      }

      // 1 bit: LOG.0
      if(hrany_program[i] == 0)
      {
        digitalWrite(Led, HIGH);      //zapne 
        delayMicroseconds(889);       //čeká polovinu bitu
        digitalWrite(Led, LOW);       //vypne
        delayMicroseconds(889);       //čeká druhou polovinu bitu
      }
    }

  }




  if(digitalRead(Button_Program) == 0 && digitalRead(Button_Start) == 1)
  {

    // while pro čekání na odstisknutí tlačítka:
    while(digitalRead(Button_Start) == 1) 
    {
      
    }

    Serial.println("1");
    
    // projetí celého signálu
    for(int i=0; i<14; i++)
    {
      // 1 bit: LOG.1
      if(hrany_start[i] == 1)
      {
        digitalWrite(Led, LOW);       //vypne
        delayMicroseconds(889);       //čeká polovinu bitu
        digitalWrite(Led, HIGH);      //zapne
        delayMicroseconds(889);       //čeká druhou polovinu bitu
      }

      // 1 bit: LOG.0
      if(hrany_start[i] == 0)
      {
        digitalWrite(Led, HIGH);      //zapne 
        delayMicroseconds(889);       //čeká polovinu bitu
        digitalWrite(Led, LOW);       //vypne
        delayMicroseconds(889);       //čeká druhou polovinu bitu
      }
    }
  }
}