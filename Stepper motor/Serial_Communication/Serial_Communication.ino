void setup()
{
  Serial.begin(9600);
}

int time;
float spd=0;
char comdata[8];
char ch;
int index=0;
boolean havedata=false;

void loop()
{
  havedata=false;
  index=0;
  while (Serial.available() > 0)  
    {
      ch=char(Serial.read());
      if((index<7)&&(ch>='0') && (ch<='9') || (ch=='.'))
      {
        comdata[index++]=ch;
        havedata=true;
      }
      delay(2);
    }
  if(havedata)  
    spd = atof(comdata);
  for(index=0;index<8;index++)
    comdata[index]=0;
  time=(millis()+500)/1000;
  Serial.print(time);
  Serial.print(" ");
  Serial.print(time*0.19+20);
  Serial.print(" ");
  Serial.print(time*0.21+20);
  Serial.print(" ");
  Serial.print(time*0.23+20);
  Serial.print(" ");
  Serial.println(spd);
  delay(1000);
}
