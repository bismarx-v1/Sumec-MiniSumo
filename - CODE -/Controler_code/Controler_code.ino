// ledka
#define Led 2
// tlacitka
#define Button_Program 6
#define Button_Start 5

// 1 byt = 1,778ms

int hrany_program[14] {1,1,0,0,1,0,1,1,0,0,0,0,1,1};
int hrany_start[14]   {1,1,0,0,0,1,1,1,0,0,0,0,1,1};

void setup() {

  Serial.begin(9600);

  // ledka => output
  pinMode(Led, OUTPUT);
  // tlacitka => input
  pinMode(Button_Program, INPUT);
  pinMode(Button_Start, INPUT);

}


void high()
{
  // perioda = 27.77us
  // pocet period za 889us = 32x

  for(int i=0; i<32; i++)
  {
    digitalWrite(Led, HIGH);
    delayMicroseconds(27.77*0.25);  // 25% periody
    digitalWrite(Led, LOW); 
    delayMicroseconds(27.77*0.75);  // zbytek periody
  } 
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
        high();      //zapne
        //delayMicroseconds(889);       snad už poslední chyba
      }

      // 1 bit: LOG.0
      if(hrany_program[i] == 0)
      {
        high();      //zapne 
        //delayMicroseconds(889);       snad už poslední chyba
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
        high();      //zapne
        //delayMicroseconds(889);       snad už poslední chyba
      }

      // 1 bit: LOG.0
      if(hrany_start[i] == 0)
      {
        high();      //zapne 
        //delayMicroseconds(889);       snad už poslední chyba
        digitalWrite(Led, LOW);       //vypne
        delayMicroseconds(889);       //čeká druhou polovinu bitu
      }
    }
  }
}