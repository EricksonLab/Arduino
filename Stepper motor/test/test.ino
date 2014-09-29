long t,v1,v2,v3;
int c=50;
char comdata[8];
char ch;
int index=0;
boolean havedata=false;

void setup()
{
  t=0;
  v1=30;
  v2=30;
  v3=30;
  Serial.begin(9600);
}

void loop()
{
  havedata=false;
  index=0;
  memset(comdata,0,sizeof(comdata));
  while (Serial.available() > 0)  
    {
      ch=char(Serial.read());
      if((index<7)&&(ch>='0') && (ch<='9'))
      {
        comdata[index++]=ch;
        havedata=true;
      }
      delay(2);
    }
  if (havedata)  
    c=atoi(comdata);
  v1=v1+random(-1,2);
  v2=v2+random(-1,2);
  v3=v3+random(-1,2);
  Serial.print(c);
  Serial.print(" ");
  Serial.print(v1);
  Serial.print(" ");
  Serial.print(c);
  Serial.print(" ");
  Serial.print(v3);
  Serial.print(" #");
//  Serial.print("12345abcde#");
  delay(1000);
}
