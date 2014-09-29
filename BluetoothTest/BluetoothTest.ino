unsigned long time, lastTime;
float RPM=0.0;
char comdata[8];
char ch;
int index=0;
boolean havedata=false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lastTime = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
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
    havedata = false;
  }
  time = millis();
  if (time-lastTime>=1000) 
  {
    Serial.println("Received:");
    Serial.println(RPM);
    lastTime = time;
  }
  delay(2);
}
