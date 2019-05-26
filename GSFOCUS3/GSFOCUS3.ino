

// EQ Simple Focuser
// Arduino code in controlling an absolute focuser
// using a stepper motor
//https://blog.naver.com/chandong83/220875868466
//https://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html#a9d917f014317fb9d3b5dc14e66f6c689
#include <AccelStepper.h>
#include <DRV8825.h>
#include <BasicStepperDriver.h>

#include "Switch.h"
//#include "U8Display.h"
#include "setDisplay.h"

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Declaration needed for the DRV8825 Library
DRV8825 stepper(MOTOR_STEPS, DIR,STEP,MS0,MS1,MS2);
//AccelStepper stepper1(AccelStepper::FULL4WIRE, motorPin5, motorPin7, motorPin6, motorPin8);
bool isMoving = false;

// for command purposes
String inputString = "";
int step = 0;
int stepmode = 1;
int speedmode = 1;
float mult=1;
int backlashStep = 0;
String lastDirection = "NONE"; //"OUTWARD"
String currentDirection = "NONE";

// for pin values : cw(clockwise but 시계반대방향), ccw(counterclockwise but 시계방향) : 정방향, 역방향
//https://m.blog.naver.com/PostView.nhn?blogId=glooory&logNo=220926317204&proxyReferer=https%3A%2F%2Fwww.google.com%2F


// for manual control
bool positionReported = false;
float Speed;
float nowRPM;
unsigned long currentPosition = 250000;
double distance = 0;

int state=1;
bool ismove = false;
// temperature and humidity sensor
//http://blog.naver.com/PostView.nhn?blogId=nkkh159&logNo=220604500053
DHT_Unified dht(DHT22_PIN,DHT22);
int delayMS;

void setup() 
    {
        Serial.begin(baudrate);
        Serial.println(F("EQFOCUSER_STEPPER#"));

        Speed = 100; //step per sec
        stepper.setRPM(60*Speed/MOTOR_STEPS);
        nowRPM = 60*Speed/MOTOR_STEPS;
        
        inputString.reserve(200);

        dht.begin();
        display.begin(SSD1306_SWITCHCAPVCC,0x3C);
        pinset();
        startFMenu();
        
        sensor_t sensor;
        dht.humidity().getSensor(&sensor);
        
        delayMS = sensor.min_delay/1000;
        setstep();
    }


void loop() 
    {
                    if (distance != 0) 
                        {
                          // let the stepper finish the movement
                          positionReported = false;
                        }
                    if (distance == 0 && !positionReported) 
                        {
                          reportPosition();
                          delay(500);
                          positionReported = true;
                        }
            display.clearDisplay();
         buttonRead();
         menu();
            display.display();
    }

void buttonRead()
{
  controljudge();
    if(state==4) motorControl();
    else {
      if(S[0]&&state<=3&&state>1) state--;
      else if(S[0] && state==6 && stepmode<8) stepmode = stepmode * 2;
      
      if(S[1]&&state<3) state++;
      else if(S[1] && state==6 && stepmode>1) stepmode = stepmode / 2;
      
      if(S[2]&&state<=3) state+=3;
      
      if(S[3]&&state==5) {state=1;currentPosition = 250000;}
      else if(S[3]&&state>3) 
        {if(state==6) setstep(); state-=3; if(!ismove) isMoving = false;}
    }
}

void moveTo(long toPosition)
{
//  DRV8825 stepper(MOTOR_STEPS, DIR,STEP,MS0,MS1,MS2);
  ismove = true;
  isMoving = true;
  distance = toPosition - currentPosition;

  stepper.rotate(distance*1.8);
  stepper.setRPM(nowRPM);
  
  distance = 0;
  isMoving = false;
  ismove = false;
}

void reportPosition() 
    {
        Serial.print(F("POSITION:"));
        Serial.print(currentPosition);
        Serial.println("#");
    }
    
// test if direction is the same, otherwise apply backlash step
// this method is only applicable for manual focusing changes
void applyBacklashStep(int toPosition, String lastDirection, String currentDirection) 
    {
        if (lastDirection == currentDirection) 
            {
                // no backlash
                moveTo(toPosition);
            }
        else 
            {
                // apply backlash
                moveTo(toPosition + backlashStep);
                currentPosition = toPosition - backlashStep;
            }
    }

void setstep()
{
  switch(stepmode)
  {
    case 1:
    digitalWrite(MS0,LOW);
    digitalWrite(MS1,LOW);
    digitalWrite(MS2,LOW);
      break;  
      
    case 2:
    digitalWrite(MS0,HIGH);
    digitalWrite(MS1,LOW);
    digitalWrite(MS2,LOW);
      break;
      
    case 4:
    digitalWrite(MS0,LOW);
    digitalWrite(MS1,HIGH);
    digitalWrite(MS2,LOW);
      break;
      
    case 8:
    digitalWrite(MS0,HIGH);
    digitalWrite(MS1,HIGH);
    digitalWrite(MS2,LOW);
      break;
      
//    case 16:
//    digitalWrite(MS0,LOW);
//    digitalWrite(MS1,LOW);
//    digitalWrite(MS2,HIGH);
//      break;
//      
//    case 32:
//    digitalWrite(MS0,HIGH);
//    digitalWrite(MS1,HIGH);
//    digitalWrite(MS2,HIGH);
//      break;
    
  }
}
