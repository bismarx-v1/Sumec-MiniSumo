#include "line.h"

void setup() {
	Serial.begin(115200);
}


void loop() {	/*LINE_Get([Senzor], [Hranice Pro Bool Mod], [Mod]);*/		/*LINE_Get([Sensor], [Threshold For Bool Mode], [Mode]);*/

	/*Bool mod*/	/*Bool mode*/
	/*Porovna vystup senzoru s hranici*/	/*Compares sensor output with threshold*/
	Serial.println(LINE_Get(1, 3000, 0));	/*predni levy,	bool mod*/		/*front left,	bool mode*/
	Serial.println(LINE_Get(2, 3000, 0));	/*predni pravy,	bool mod*/		/*front right,	bool mode*/
	Serial.println(LINE_Get(3, 3000, 0));	/*zadni levy,	bool mod*/		/*back left,	bool mode*/
	Serial.println(LINE_Get(4, 3000, 0));	/*zadni pravy,	bool mod*/		/*back right,	bool mode*/
	
	
	/*Int mod*/		/*Int mode*/
	/*Na hranici nezalezi, return je rovnou hotnota ze senzoru*/	/*Threshold can be anything, just outputs sensor value*/
	Serial.println(LINE_Get(1, 0, 1));		/*predni levy,	int mod*/		/*front left,	int mode*/
	Serial.println(LINE_Get(2, 0, 1));		/*predni pravy,	int mod*/		/*front right,	int mode*/
	Serial.println(LINE_Get(3, 0, 1));		/*zadni levy,	int mod*/		/*back left,	int mode*/
	Serial.println(LINE_Get(4, 0, 1));		/*zadni pravy,	int mod*/		/*back right,	int mode*/
	
	
	Serial.println("===============");
	delay(100);
}