// ledka
#define Led 2
// tlacitka
#define Button_Program 4
#define Button_Start 5

// 1 byt = 1,778ms

int hrany_program[14] {1,1,1,0,1,0,1,1,0,0,0,0,1,0};
int hrany_start[14] {1,1,1,0,0,1,1,1,0,0,0,0,1,0};

void setup() {

  // ledka => output
  pinMode(Led, OUTPUT);
  // tlacitka => input
  pinMode(Button_Program, INPUT);
  pinMode(Button_Start, INPUT);

}

void loop() {
  
  if(digitalRead(Button_Program) == 1 && digitalRead(Button_Start) == 0)
  {
    for(int i=0; i<14; i++)
    {
      digitalWrite(Led, hrany_program[i]);
      delayMicroseconds(1700);
    }
    delay(10);
    digitalWrite(Led, 0);
  }

  if(digitalRead(Button_Start) == 1 && digitalRead(Button_Program) == 0)
  {
    for(int i=0; i<14; i++)
    {
      digitalWrite(Led, hrany_Start[i]);
      delayMicroseconds(1700);
    }
    delay(10);
    digitalWrite(Led, 0);
  } 

}
