#include <EricksonLab_ISL29033.h>
#include <Wire.h>



EricksonLab_ISL29033 isl = EricksonLab_ISL29033();

void setup() {
  Serial.begin(9600);
  Wire.begin();
  if(isl.init(1))
    Serial.println("ISL 29033 Measurement Start:"); 
}

void loop() {
    Serial.println(isl.read());
    delay(1000);
}

