#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"
#include <BasicStepperDriver.h>
#include <DRV8825.h>
#include <SyncDriver.h>
#include <Stepper.h>
#include <EEPROM.h>

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define MOTOR_STEPS 200

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH 16
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define UPpin 8
#define DOWNpin 9
#define RIGHTpin 10
#define LEFTpin 7

#define DIR 4
#define STEP 3
#define MS0 15
#define MS1 12
#define MS2 13
DRV8825 stepper(MOTOR_STEPS, DIR, STEP, MS0, MS1, MS2);

short S[4]={0}; short now[4]={1}; short was[4]={0};
unsigned long MOTOR_ANGLE,ANGLE;
float hum; float temp;
unsigned long P_MT=0,P_MT2=0; unsigned long C_MT=millis();
int copystate=0;

int state=1;
int change;
int cstate=0;

void step32()
{
  digitalWrite(MS0,LOW);
  digitalWrite(MS1,LOW);
  digitalWrite(MS2,HIGH);
}
void setup()
{
  Serial.begin(9600);
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
  pinMode(UPpin,INPUT_PULLUP);
  pinMode(DOWNpin,INPUT_PULLUP);
  pinMode(RIGHTpin,INPUT_PULLUP);
  pinMode(LEFTpin,INPUT_PULLUP);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,8);
  display.print("    Stepping Motor");
  display.setTextSize(2);
  display.setCursor(0,16);
  display.print(" Controler");
  display.display();
  delay(5000);
  Serial.print("start!");
  stepper.setRPM(60);
  display.setTextSize(1);
}
void playDHT(void)
{
hum = dht.readHumidity();
temp= dht.readTemperature();
}
void menu()
{
  display.setCursor(6,0); display.println("T: " + String(temp, 2));
  display.setCursor(70,0); display.println("H: " + String(hum, 2));
  if(state==1||state==2) 
  {display.setCursor(46,8); display.println("<MENU>");}
  else if(state==11) display.print("   rotating analog");
  else if(state==12)
  {display.setCursor(32,8); display.print("MOTOR RESET");}
  else if(state==21) 
  {display.setCursor(16,8); display.print("rotating digital");}
    display.setCursor(0,16);
      if(state==1||state==2) display.print("   motor control");
      else if(state==12) display.print("   press R to RESET");
      if(state==1) {display.setCursor(0,16);display.print(" >");}
      if(state==11) 
      {display.setCursor(10,16); display.print("up,down to control");}
      else if(state==21)
      {display.setCursor(0,16); display.print("changing step: "); display.print(change);}
    display.setCursor(0,24);
      if(state==1||state==2) display.print("   MOTOR RESET");
      else if(state==11||state==12||state==21) {display.print("<                   >"); 
      display.setCursor(46,24); if(state!=12) display.print(MOTOR_ANGLE);
      else display.print(ANGLE);}
    if(state==2) {display.setCursor(0,24);display.print(" >");}
   if(state==22)
    {  display.setCursor(8,12); display.print("RESET DONE to ");
       display.setCursor(90,12); display.print(ANGLE);
       display.setCursor(10,20); display.print("press L to go back");
       MOTOR_ANGLE=ANGLE;}
  }

void state11()
{
  if(now[0]==0&&MOTOR_ANGLE<500000&&MOTOR_ANGLE>9999)
    {
     if(copystate==0) {P_MT=C_MT;copystate=1;MOTOR_ANGLE++;stepper.rotate(1.8);}
     else if(C_MT-P_MT<600) MOTOR_ANGLE;
     else if(C_MT-P_MT<2000) {MOTOR_ANGLE+=3;stepper.setRPM(240);stepper.rotate(5.4);}
     else if(C_MT-P_MT<4000) {MOTOR_ANGLE+=33;stepper.setRPM(300);stepper.rotate(59.4);}
     else if(C_MT-P_MT<6000) {MOTOR_ANGLE+=83;stepper.setRPM(600);stepper.rotate(149.4);}
     else {MOTOR_ANGLE+=333;stepper.setRPM(800);stepper.rotate(599.4);}
    }
    else if(now[1]==0&&MOTOR_ANGLE<500000&&MOTOR_ANGLE>9999)
    {
     if(copystate==0) {P_MT=C_MT;copystate=1;MOTOR_ANGLE--;stepper.rotate(-1.8);}
     else if(C_MT-P_MT<600) MOTOR_ANGLE;
     else if(C_MT-P_MT<2000) {MOTOR_ANGLE-=3;stepper.setRPM(240);stepper.rotate(-5.4);}
     else if(C_MT-P_MT<4000) {MOTOR_ANGLE-=33;stepper.setRPM(300);stepper.rotate(-59.4);}
     else if(C_MT-P_MT<6000) {MOTOR_ANGLE-=83;stepper.setRPM(600);stepper.rotate(-149.4);}
     else {MOTOR_ANGLE-=333;stepper.setRPM(800);stepper.rotate(-599.4);}
    }
    else copystate=0;
    if(MOTOR_ANGLE>=500000) MOTOR_ANGLE=499999;
    if(MOTOR_ANGLE<=10000) MOTOR_ANGLE=10000;
}
void changeit()
{
  if(cstate==1) change=30;
  else if(cstate==2) change=100;
  else if(cstate==3) change=400;
  else if(cstate==4) change=1600;
  else if(cstate==5) change=3200;
  else if(cstate==6) change=9600;
  else if(cstate==7) change=32000;
  else if(cstate==0) change=-30;
  else if(cstate==-1) change=-100;
  else if(cstate==-2) change=-400;
  else if(cstate==-3) change=-1600;
  else if(cstate==-4) change=-3200;
  else if(cstate==-5) change=-9600;
  else if(cstate==-6) change=-32000;
}
void playmotor()
{
  step32();
  stepper.setRPM(1800);
  if(cstate==-6||cstate==7) stepper.setRPM(3200);
  stepper.rotate(1.8*change);
  MOTOR_ANGLE+=change;
  delay(300);
}
void state21()
{
  changeit();
  if(S[0]==1) cstate++;
  else if(S[1]==1) cstate--;
  if(cstate==-7) cstate=7;
  else if(cstate==8) cstate=-6;
  if(S[2]==1&&MOTOR_ANGLE<500000&&MOTOR_ANGLE>9999) playmotor();
    if(MOTOR_ANGLE>=500000) MOTOR_ANGLE=499999;
    if(MOTOR_ANGLE<=10000) MOTOR_ANGLE=10000;
}
void state12()
{
  if(now[0]==0&&ANGLE<500000&&ANGLE>9999)
    {
     if(copystate==0) {P_MT=C_MT;copystate=1;ANGLE++;}
     else if(C_MT-P_MT<600) ANGLE;
     else if(C_MT-P_MT<2000) ANGLE+=3;
     else if(C_MT-P_MT<4000) ANGLE+=33;
     else if(C_MT-P_MT<6000) ANGLE+=83;
     else ANGLE+=333;
    }
    else if(now[1]==0&&ANGLE<500000&&ANGLE>9999)
    {
     if(copystate==0) {P_MT=C_MT;copystate=1;ANGLE--;}
     else if(C_MT-P_MT<600) ANGLE;
     else if(C_MT-P_MT<2000) ANGLE-=3;
     else if(C_MT-P_MT<4000) ANGLE-=33;
     else if(C_MT-P_MT<6000) ANGLE-=83;
     else ANGLE-=333;
    }
    else copystate=0;
    if(ANGLE>=500000) ANGLE=499999;
    if(ANGLE<=10000) ANGLE=10000;
}
void buttonRead()
{
  controljudge();
  if(state==11) state11(); 
  else if (state==21) state21();
  else if (state==12) state12();
  if(S[0]&&state<10&&state>1) state--;
  if(S[1]&&state<2) state++;
  if(S[2]&&state<20) state+=10;
  if(S[3]&&state==22) {state=1;ANGLE=100000;}
  if(S[3]&&state>10) state-=10;
  
}
void controljudge()
{
  for(int i=0;i<4;i++)
  {
       if(i==0) now[i]=digitalRead(UPpin);
  else if(i==1) now[i]=digitalRead(DOWNpin);
  else if(i==2) now[i]=digitalRead(RIGHTpin);
  else if(i==3) now[i]=digitalRead(LEFTpin);
  if(now[i]!=was[i]&&now[i]==0) S[i]=1;
  else S[i]=0;
      was[i]=now[i];
  }
}
void loop()
{
  Serial.println(MOTOR_ANGLE);
  C_MT=millis();
  if(state<10)playDHT();
  buttonRead();
  display.clearDisplay();
  menu();
  display.display();
}
