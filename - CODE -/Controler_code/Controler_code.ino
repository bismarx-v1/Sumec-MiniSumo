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

    while(digitalRead(Button_Program) == 1)
    {
      
    }
    

    for(int i=0; i<14; i++)
    {
      digitalWrite(Led, hrany_program[i]);
      delayMicroseconds(889);
      Serial.print(hrany_program[i]);
    }
    Serial.println("");
  }

  if(digitalRead(Button_Start) == 1 && digitalRead(Button_Program) == 0)
  {

    while(digitalRead(Button_Start) == 1)
    {

    }

    for(int i=0; i<14; i++)
    {
      digitalWrite(Led, hrany_start[i]);
      delayMicroseconds(889);
      Serial.print(hrany_start[i]);
    }
    Serial.println("");
  } 
  delay(100);
  digitalWrite(Led, LOW);

}