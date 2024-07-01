#include "motorsEsp32S3.h"




//normalni void setup() s funkci MOTORS_Setup()
void setup() {
	MOTORS_Setup();
}


//normalni void loop()
void loop() {
  MOTORS_Go(255, 255);
}
