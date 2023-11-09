#include "motors.h"

//normalni void setup() s funkci MOTORS_Setup()
void setup() {
  MOTORS_Setup();

}


//normalni void loop()
void loop() {
  MOTORS_Go(255*-1, 255*-1);
}
