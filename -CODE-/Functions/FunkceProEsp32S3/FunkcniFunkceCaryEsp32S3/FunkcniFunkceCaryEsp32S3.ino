#include "lineEsp32S3.h"

void setup() {
	Serial.begin(115200);
}


void loop() {	/*LINE_Get([Senzor], [Hranice Pro Bool Mod], [Mod]);*/		/*LINE_Get([Sensor], [Threshold For Bool Mode], [Mode]);*/

	/*Bool mod*/	/*Bool mode*/
	/*Porovna vystup senzoru s hranici*/	/*Compares sensor output with threshold*/
	Serial.print("left:\t");
	Serial.println(LINE_Get(1, 3000, 1));	/*predni levy,			bool mod*/		/*front left,	bool mode*/
	/*Serial.print("mid:\t");
	Serial.println(LINE_Get(2, 1000, 1));	/*predni prostredni,	bool mod*/		/*front mid,	bool mode*/
	Serial.print("right:\t");
	Serial.println(LINE_Get(3, 3000, 1));	/*predni pravy,			bool mod*/		/*front right,	bool mode*/
	Serial.print("rear:\t");
	Serial.println(LINE_Get(4, 3000, 1));	/*zadni,				bool mod*/		/*rear,			bool mode*/
	
	/*
	/*Int mod*/		/*Int mode*/
	/*Na hranici nezalezi, return je rovnou hotnota ze senzoru*/	/*Threshold can be anything, just outputs sensor value*/
	//Serial.print("left:\t");
	//Serial.println(LINE_Get(1, 0, 1));		/*predni levy,			int mod*/		/*front left,	int mode*/
	//Serial.print("mid:\t");
	//Serial.println(LINE_Get(2, 0, 1));		/*predni prostredni,	int mod*/		/*front mid,	int mode*/
	//Serial.print("right:\t");
	//Serial.println(LINE_Get(3, 0, 1));		/*predni pravy,			int mod*/		/*front right,	int mode*/
	/*Serial.print("rear:\t");
	Serial.println(LINE_Get(4, 0, 1));		/*zadni,				int mod*/		/*rear,			int mode*/
	
	
	Serial.println("===============");
	delay(100);
}