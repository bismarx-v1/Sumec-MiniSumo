#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor1;
VL53L0X sensor2;
VL53L0X sensor3;

int a;
int b;
int c;

void setup()
{
  pinMode(27, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  digitalWrite(27, LOW);
  digitalWrite(25, LOW);
  digitalWrite(26, LOW);

  delay(500);
  Wire.begin();


  Serial.begin (9600);

  digitalWrite(27, HIGH);
  delay(150);
  Serial.println("00");
  sensor1.init(true);

  Serial.println("01");
  delay(100);
  sensor1.setAddress((uint8_t)01);
  Serial.println("02");

  digitalWrite(25, HIGH);
    delay(150);
  sensor2.init(true);
  Serial.println("03");
  delay(100);
  sensor2.setAddress((uint8_t)02);
  Serial.println("04");
  
  digitalWrite(26, HIGH);
    delay(150);
  sensor3.init(true);
  Serial.println("05");
  delay(100);
  sensor3.setAddress((uint8_t)03);
  Serial.println("06");

  Serial.println("addresses set");
  Serial.print("======================== \n");

sensor1.startContinuous();
sensor2.startContinuous();
sensor3.startContinuous();

}

void loop()
{
  
  a=sensor1.readRangeContinuousMillimeters();
  Serial.print("Right: ");
  Serial.print(a);
  Serial.print("\n");
  c=sensor3.readRangeContinuousMillimeters();
  Serial.print("Front: ");
  Serial.print(c);
  Serial.print("\n");
  b=sensor2.readRangeContinuousMillimeters();
  Serial.print("Left: ");
  Serial.print(b);
  Serial.print("\n");
  
  Serial.print("======================== \n");

  //delay(100);
}
