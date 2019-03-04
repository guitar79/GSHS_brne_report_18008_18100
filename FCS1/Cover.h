/*
 
 */
// 
#include <Servo.h>
Servo myservo;

int val;    // variable to read the value from the analog pin

int Cover_statusPin1 = 0;
int Cover_statusPin2 = 0;
int Cover_delayTime = 100;

int pos = 0;

char Key5_0 = 't';
char Key5_1 = 'g';
char Key6_0 = "y";
char Key6_1 = "h";

// RELAY pins
#define servoPin1 0
#define servoPin2 1

void cover_open_close() {
  myservo.attach(servoPin1);
  while(!Serial.available()); //시리얼로 데이터 들어올 때까지 대기
  char com_Cover = Serial.read(); //들어온 데이터를 변수 com에 저장
  
  switch(com_Cover) {
    case 't':
      myservo.write(60);
      Cover_statusPin1 = 1;
      delay(Cover_delayTime);
    break;
    
    case 'g':
    Cover_statusPin1 = 0;
    val = map(500, 0, 1023, 0, 60);     // scale it to use it with the servo (value between 0 and 180)
    myservo.write(val); 
    delay(Cover_delayTime); 
    break;
    
    case 'y':
    Cover_statusPin2 = 1;
    val = map(500, 0, 1023, 0, 120);     // scale it to use it with the servo (value between 0 and 180)
    myservo.write(val); 
    delay(Cover_delayTime); 
    break;
    
    case 'h':
    Cover_statusPin2 = 0;
    val = map(500, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
    myservo.write(val); 
    delay(Cover_delayTime); 
    break;
  }
    Serial.print(com_Cover);
    Serial.print("  (");
    Serial.print(Cover_statusPin1);
    Serial.print(",");
    Serial.print(Cover_statusPin2);
    Serial.print(")");
}
