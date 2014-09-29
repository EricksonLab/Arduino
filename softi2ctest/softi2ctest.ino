#include <SoftI2CMaster.h>

uint8_t dev_address = 0x44;
SoftI2CMaster i2c = SoftI2CMaster( 10,11 );
uint8_t i2cdata[2];
uint8_t light;

void setup() {
  // put your setup code here, to run once:
  
  
  i2cdata[0] = 0;
  i2cdata[1] = 0b10100000;

  i2c.beginTransmission(dev_address);    // start transmission to device 
  i2c.send(i2cdata[0]);                 // send register address
  i2c.send(i2cdata[1]);                 // send data to write  
  i2c.endTransmission();                 // end transmission


  i2cdata[0] = 1;
  i2cdata[1] = 0b00000011;
 
  i2c.beginTransmission(dev_address);    // start transmission to device 
  i2c.send(i2cdata[0]);                 // send register address
  i2c.send(i2cdata[1]);                 // send data to write  
  i2c.endTransmission();                 // end transmission

  delay(2);
  Serial.begin(9600);
  Serial.println("SofwareI2C test with isl29033");
}

void loop() {
  // put your main code here, to run repeatedly:
  i2cdata[0] = 3;


  i2c.beginTransmission(dev_address);      // start transmission to device 
  i2c.send(i2cdata[0]);                   // send register address
  i2c.endTransmission(); 
  

  i2c.beginTransmission(dev_address);      // start transmission to device 
  i2c.requestFrom(dev_address); 

  i2cdata[0] = i2c.receive();
  i2c.endTransmission();                   // end transmission
  
  
  light |= i2cdata[0];
  Serial.println(light);
  delay(1000);
}
