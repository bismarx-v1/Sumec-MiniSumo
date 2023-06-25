#include "Adafruit_VL53L0X.h"
#include <Arduino.h>

#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define LOX3_ADDRESS 0x32

// X-SHUT pins
#define SHT_LOX1 32
#define SHT_LOX2 34
#define SHT_LOX3 35

Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();

VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
VL53L0X_RangingMeasurementData_t measure3;

void setID() {

  Serial.println("-------zacatek setID-----");

  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  delay(10);

  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  digitalWrite(SHT_LOX3, HIGH);
  delay(10);

  // activating LOX1 and reseting LOX2
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);

  // initing LOX1
  Serial.println("pred_1senzor");
  if (!lox1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    //while (1);
  }
  delay(10);

  Serial.println("po_1senzor");

  // activating LOX2
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  Serial.println("pred_2senzor");

  //initing LOX2
  if (!lox2.begin(LOX2_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    //while (1);
  }
  delay(10);

  Serial.println("po_2senzor");

  digitalWrite(SHT_LOX3, HIGH);
  delay(10);

  Serial.println("pred_3senzor");

  if (!lox3.begin(LOX3_ADDRESS)) {
    Serial.println(F("Failed to boot third VL53L0X"));
    //while (1);
  }

  Serial.println("po_3senzor");

  Serial.println("--------konec setID--------");
}

void read_triple_sensors() {

  lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
  lox2.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!
  lox3.rangingTest(&measure3, false); // pass in 'true' to get debug data printout!

  // print sensor one reading
  Serial.print(F("1: "));
  if (measure1.RangeStatus != 4) {    // if not out of range
    Serial.print(measure1.RangeMilliMeter);
  } else {
    Serial.print(F("Out of range"));
  }

  Serial.print(F(" "));

  // print sensor two reading
  Serial.print(F("2: "));
  if (measure2.RangeStatus != 4) {
    Serial.print(measure2.RangeMilliMeter);
  } else {
    Serial.print(F("Out of range"));
  }

  Serial.print(F(" "));

  // print sensor three reading
  Serial.print(F("2: "));
  if (measure3.RangeStatus != 4) {
    Serial.print(measure3.RangeMilliMeter);
  } else {
    Serial.print(F("Out of range"));
  }

  Serial.println();
}

void setup() {
  Serial.begin(9600);

  Serial.println("pred_setup");

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }

  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);
  pinMode(SHT_LOX3, OUTPUT);

  Serial.println(F("Shutdown pins inited..."));

  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);

  Serial.println(F("Both in reset mode...(pins are low)"));

  Serial.println(F("Starting..."));

  setID();

  Serial.println("po_setup");
}

void loop() {
  read_triple_sensors();
  delay(200);

}
