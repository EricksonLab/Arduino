/*
Adafruit Arduino - Lesson 16. Stepper
*/

#include <Stepper.h>
#include "Adafruit_MAX31855.h"

int in1Pin = A4;
int in2Pin = A3;
int in3Pin = A2;
int in4Pin = A1;

unsigned long time, lastTime;
float RPM=0.0;
int dir=1;

Stepper motor(32, in1Pin, in2Pin, in3Pin, in4Pin); 

int thermoDO1 = 12;
int thermoCS1 = 11;
int thermoCLK1 = 10;

int thermoDO2 = 9;
int thermoCS2 = 8;
int thermoCLK2 = 7;

int thermoDO3 = 6;
int thermoCS3 = 5;
int thermoCLK3 = 4;

char comdata[8];
char ch;
int index=0;
boolean havedata=false;

Adafruit_MAX31855 thermocouple1(thermoCLK1, thermoCS1, thermoDO1);
Adafruit_MAX31855 thermocouple2(thermoCLK2, thermoCS2, thermoDO2);
Adafruit_MAX31855 thermocouple3(thermoCLK3, thermoCS3, thermoDO3);



void setup()
{
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

  // this line is for Leonardo's, it delays the serial interface
  // until the terminal window is opened
//  while (!Serial);
  
  Serial.begin(9600);
  motor.setSpeed(0);
  lastTime = millis();
}

void loop()
{
  havedata=false;
    index=0;
    while (Serial.available() > 0)  
    {
      ch=char(Serial.read());
      if((index<7)&&(ch>='0') && (ch<='9') || (ch=='.') || (ch=='-'))
      {
        comdata[index++]=ch;
        havedata=true;
      }
      delay(2);
    }
    if(havedata)  
    {
      RPM = atof(comdata);
      if (RPM<0.0)
      {
        dir=-1;
      RPM=-RPM;
      }
      else dir = 1;
    }
    for(index=0;index<8;index++)
      comdata[index]=0;
    
  time=millis();
  if (time - lastTime >=1000)
  {
    
    motor.setSpeed((int)(RPM*20));
      //  if (RPM>2.0)
      //    RPM = 2.0;
   // motor.setSpeed(RPM);
    
    motor.step((int)(RPM*(time-lastTime)*512/60000*dir));
    lastTime=time;
      
    Serial.print((millis()/1000));
      
    double c1 = thermocouple1.readCelsius();
    if (isnan(c1)) {
      Serial.print(" NaN");
    } else {
      Serial.print(" ");
      Serial.print(c1);
    }   
    double c2 = thermocouple2.readCelsius();
    if (isnan(c2)) {
      Serial.print(" NaN");
    } else {
      Serial.print(" ");
      Serial.print(c2);
    }   
    double c3 = thermocouple3.readCelsius();
    if (isnan(c3)) {
      Serial.print(" NaN");
    } else {
    Serial.print(" ");
    Serial.print(c3);
    }
    Serial.print(" ");    
    Serial.println(RPM*dir);
  }
}

