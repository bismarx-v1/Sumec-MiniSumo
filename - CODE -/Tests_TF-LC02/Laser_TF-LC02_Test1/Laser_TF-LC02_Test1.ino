//http://kabinet.fyzika.net/ESP32/ESP32-LCD/ESP32-a-I2C-LCD.php
/* I2C Skener */

#include <Wire.h>														//Tato knihovna obsahuje komunikacni funkce I2C

																		//funkce SETUP se spusti jednou pri stisknuti tlacitka reset nebo pri zapnuti desky.
void setup() {
	Wire.begin(21, 22, 400000);														//inicializace I2C komunikace
	Serial.begin(115200);												//prenosova rychlost serioveho vystupu
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB
	  }
	Serial.println("ESP32 hleda I2C zarizeni");							//vypis uvodni hlasky na Serial Monitor
}

																		//funkce LOOP bezi stale dokola.
void loop() {
	byte error_i2c, address_i2c;										//promenne pro adresu a navrat chyby
	int I2C_Devices;													//promena pro pocet nalezenych zarizeni
	Serial.println("Search started===================================");//vypis hlasky na Serial Monitor
	I2C_Devices = 0;													//pocatecni stav nalezenych zarizeni je 0
	for(address_i2c = 0; address_i2c <= 127; address_i2c++ ) {			//prochazi se adresy od 0 do 127
		delay(10);
		Serial.print(address_i2c);
		Serial.print(" > ");
		Wire.beginTransmission(address_i2c);							//pokus o prenos do zarizeni zadane adresy
		delay(90);
		error_i2c = Wire.endTransmission();								//navrat stavove hodnoty I2C prenosu
		if (error_i2c == 0) {											//pokud je navratova hodnota 0, je to OK, zarizeni existuje
			Serial.print("I2C zarizeni nalezeno na adrese: 0x");			//vypis hlasky na Serial Monitor
			if (address_i2c<16) {												//pokud je adresa mensi nez 16, bude hex adresa jednociferna
				Serial.print("0");
			}
			Serial.println(address_i2c,HEX);								//vypsani adresy nalezeneho zarizeni v hex formatu
			I2C_Devices++;													//naslo se zarizeni, tak zvys počet o 1
		} else if (error_i2c==4) {										//zarizeni tam je, ale nastala nejaka chyba
			Serial.print("Neznama chyba na adrese: 0x");				//vypis hlasky na Serial Monitor
			if (address_i2c<16) {										//opet reseni formatu vypisu adresy mensi nez 16
				Serial.print("0");
			}
			Serial.println(address_i2c,HEX);
		}
		Serial.print(error_i2c);
		switch(error_i2c){
			case 0:
				Serial.println(" success");
				break;
			case 1:
				Serial.println(" data too long to fit in transmit buffer");
				break;
			case 2:
				Serial.println(" received NACK on transmit of address");
				break;
			case 3:
				Serial.println(" received NACK on transmit of data");
				break;
			case 4:
				Serial.println(" other error");
				break;
			case 5:
				Serial.println(" timeout");
				break;
			default:
				Serial.println(" WRONG");
				break;
		}
	}																	//probehlo se všech 128 adres, tak se vypise zaver
	if (I2C_Devices == 0) {												//nic se nenaslo
		Serial.println("No I2C device connected");
	} else {															//nejake zarizeni se nasla a byla vypsana
		Serial.println("One or more I2C devices connected");
	}
	Serial.println("Search ended=====================================");
	delay(2000);
}