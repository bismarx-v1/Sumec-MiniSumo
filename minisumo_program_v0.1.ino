#define m1 3
#define m2 4

#define intenzita1 5
#define intenzita2 6
#define intenzita3 7
#define intenzita4 8

void setup() {
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);

  pinMode(intenzita1, INPUT);
  pinMode(intenzita2, INPUT);
  pinMode(intenzita3, INPUT);
  pinMode(intenzita4, INPUT);

  Serial.begin(9600);
}
int detekce_cary(){
  int vysledek = 0;
  vysledek = digitalRead(intenzita1)+digitalRead(intenzita2)+digitalRead(intenzita3)+digitalRead(intenzita4);
  return(vysledek);
}

void loop() {
  while(detekce_cary()==0){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, HIGH);
  }
  
  int i = 0;
  while(detekce_cary()>0||i==1000){
    digitalWrite(m1, HIGH); 
    digitalWrite(m2, LOW);
    if(detekce_cary()>0){
      delay(1);
      i=1;
    }
  }
}

