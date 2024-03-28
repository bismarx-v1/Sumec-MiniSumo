#include "DRV8874PWPR.h"

DRV8874PWPR DRV8874PWPR_Obj(5000, 8);

void setup() {
	// ESP32-S3 has 8 ledc channels starting from 0
	DRV8874PWPR_Obj.LedcChannelLeft = 0;	// Add a ledc channel 
	DRV8874PWPR_Obj.LedcChannelRight = 1;	// Add a ledc channel 

  //DRV8874PWPR_Obj.right(0);
  //DRV8874PWPR_Obj.left(100);
}

void loop() {

    DRV8874PWPR_Obj.left(100);        // Set speed to "100" out of "250" for the left driver
    DRV8874PWPR_Obj.right(-100);    // Set speed to "-100" out of "250" for the right driver
    delay(3000);
    DRV8874PWPR_Obj.left(0);
    DRV8874PWPR_Obj.right(0);
    delay(1000);
    DRV8874PWPR_Obj.left(-100);
    DRV8874PWPR_Obj.right(100);
    delay(3000);
    DRV8874PWPR_Obj.left(0);
    DRV8874PWPR_Obj.right(0);
    delay(1000);
    DRV8874PWPR_Obj.left(100);
    DRV8874PWPR_Obj.right(100);
    delay(3000);
    DRV8874PWPR_Obj.left(0);
    DRV8874PWPR_Obj.right(0);
    delay(1000);
    DRV8874PWPR_Obj.left(-100);
    DRV8874PWPR_Obj.right(-100);
    delay(3000);
    DRV8874PWPR_Obj.left(0);
    DRV8874PWPR_Obj.right(0);
    delay(1000);
    DRV8874PWPR_Obj.left(100);
    DRV8874PWPR_Obj.right(0);
    delay(3000);
    DRV8874PWPR_Obj.left(0);
    DRV8874PWPR_Obj.right(0);
    delay(1000);
    DRV8874PWPR_Obj.left(0);
    DRV8874PWPR_Obj.right(100);
    delay(3000);
    DRV8874PWPR_Obj.left(0);
    DRV8874PWPR_Obj.right(0);
    delay(1000);
    DRV8874PWPR_Obj.left(-100);
    DRV8874PWPR_Obj.right(0);
    delay(3000);
    DRV8874PWPR_Obj.left(0);
    DRV8874PWPR_Obj.right(0);
    delay(1000);
    DRV8874PWPR_Obj.left(0);
    DRV8874PWPR_Obj.right(-100);
    delay(3000);
    DRV8874PWPR_Obj.left(0);
    DRV8874PWPR_Obj.right(0);
    delay(1000);

}