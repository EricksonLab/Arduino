#include <Wire.h>
#include "EricksonLab_ISL29033.h"

#define ISL29033_ADDR 0x44

#define CMD1 0
#define CMD2 1
#define DATALSB 2
#define DATAMSB 3

unsigned char dev_address;
int rang_index;

EricksonLab_ISL29033::EricksonLab_ISL29033(){
  dev_address = ISL29033_ADDR;
}

EricksonLab_ISL29033::EricksonLab_ISL29033(unsigned char address){
  dev_address = address;
}
int EricksonLab_ISL29033::init()
{
  return init(3);
}  

int EricksonLab_ISL29033::init(int index)
{
  unsigned char i2cdata[2];
  
  rang_index = index;
  
  i2cdata[0] = CMD1;
  i2cdata[1] = 0b10100000;

  Wire.beginTransmission(dev_address);    // start transmission to device 
  Wire.write(i2cdata[0]);                 // send register address
  Wire.write(i2cdata[1]);                 // send data to write  
  Wire.endTransmission();                 // end transmission


  i2cdata[0] = CMD2;
  i2cdata[1] = rang_index;
 
  Wire.beginTransmission(dev_address);    // start transmission to device 
  Wire.write(i2cdata[0]);                 // send register address
  Wire.write(i2cdata[1]);                 // send data to write  
  Wire.endTransmission();                 // end transmission
//  Serial.println("ISL init");
  return 1;
}

/**********************************************************************
 *
 * Reads the lux value back from the sensor.
 *              
 **********************************************************************/
float EricksonLab_ISL29033::read()
{
  unsigned char  i2cdata[6];
  unsigned int light;    
  float lux;
  float max_lux;
//  Serial.println("ISL startread");
  
  i2cdata[0] = DATAMSB;

  Wire.beginTransmission(dev_address);      // start transmission to device 
  Wire.write(i2cdata[0]);                   // send register address
  Wire.endTransmission();                   // end transmission

  Wire.beginTransmission(dev_address);      // start transmission to device 
  Wire.requestFrom((int)dev_address, 1);    // send data n-bytes read/

  while (Wire.available()) {
   i2cdata[0] = Wire.read();                // receive DATA
  }
  Wire.endTransmission();                   // end transmission

  light = ((unsigned int)i2cdata[0])<<8;

  i2cdata[0] = DATALSB;


  Wire.beginTransmission(dev_address);      // start transmission to device 
  Wire.write(i2cdata[0]);                   // send register address
  Wire.endTransmission(); 
  

  Wire.beginTransmission(dev_address);      // start transmission to device 
  Wire.requestFrom((int)dev_address, 1); 

  while (Wire.available()) {
    i2cdata[0] = Wire.read();                // receive DATA
  }
  Wire.endTransmission();                   // end transmission
  
  light |= i2cdata[0];

  // this is a bit lame, ideally use data read back from the device
  // to scale accordingly
  switch (rang_index) {
	case 0 : max_lux = 125.0; break;
	case 1 : max_lux = 500.0; break;
	case 2 : max_lux = 2000.0; break;
	case 3 : max_lux = 8000.0; break;
	default : max_lux = 8000.0;
  }
  lux = (max_lux * (float)light)/65536;
  return lux;
 }