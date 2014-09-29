#include <SoftI2CMaster.h>

#include <EricksonLab_ISL29033_S.h>
#include <Wire.h>



EricksonLab_ISL29033_S isl = EricksonLab_ISL29033_S(A4,A5);

void setup() {
  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);
  delay(100);
  Serial.begin(9600);
  Wire.begin();
  if(isl.init(3))
    Serial.println("ISL 29033 Measurement Start:"); 
  
}

void loop() {
    Serial.println(1000*isl.read());
    delay(1000);
}

