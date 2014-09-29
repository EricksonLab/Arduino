/*************************************************** 
  This is an example for the Adafruit Thermocouple Sensor w/MAX31855K

  Designed specifically to work with the Adafruit Thermocouple Sensor
  ----> https://www.adafruit.com/products/269

  These displays use SPI to communicate, 3 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_MAX31855.h"

int thermoDO = 5;
int thermoCS = 4;
int thermoCLK = 3;
unsigned long time = 0;
unsigned long lastTime = 0;


Adafruit_MAX31855 thermocouple(thermoCLK, thermoCS, thermoDO);
  
void setup() {
  Serial1.begin(9600);
//  Serial1.println("MAX31855 test");
  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
  // basic readout test, just print the current temp
   time = millis();
   if (time-lastTime >= 1000)
   {
   //  Serial1.println(thermocouple.readInternal());
     int c = thermocouple.readByte();
     if (isnan(c)) {
     //  Serial1.println("Something wrong with thermocouple!");
     } else {
       Serial1.print(time/1000);
       Serial1.print(" ");
       Serial1.print(c);
       Serial1.print(" ");
       Serial1.print(c);
       Serial1.print(" ");
       Serial1.print(c);
       Serial1.print(" #");
     }
   //Serial1.print("F = ");
   //Serial1.println(thermocouple.readFarenheit());
   lastTime = time;
   delay(100);
   }
}
