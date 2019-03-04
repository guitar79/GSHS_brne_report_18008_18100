/*
 
 */
// 

int Relay_statusPin1 = 0;
int Relay_statusPin2 = 0;
int Relay_statusPin3 = 0;
int Relay_statusPin4 = 0;
int Relay_delayTime = 100;

char Key1_0 = 'q';
char Key1_1 = 'a';
char Key2_0 = "w";
char Key2_1 = "s";
char Key3_0 = "q";
char Key3_1 = "d";
char Key4_0 = "r";
char Key4_1 = "f";


// Relay pins
#define RelayPin1 1
#define RelayPin2 2
#define RelayPin3 3
#define RelayPin4 4

void switch_on_off() {
  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);
  
  while(!Serial.available()); //시리얼로 데이터 들어올 때까지 대기
  char com_Relay = Serial.read(); //들어온 데이터를 변수 com에 저장
  
  switch(com_Relay) {
    case 'q':
    digitalWrite(RelayPin1, 1) ;  Relay_statusPin1 = 1;
    delay(Relay_delayTime);
    break;
    case 'a':
    digitalWrite(RelayPin1, 0) ; Relay_statusPin1 = 0;
    delay(Relay_delayTime);
    break;
    case 'w':
    digitalWrite(RelayPin2, 1) ; Relay_statusPin2 = 1;
    delay(Relay_delayTime);
    break;
    case 's':
    digitalWrite(RelayPin2, 0) ; Relay_statusPin2 = 0;
    delay(Relay_delayTime);
    break;
    case 'e':
    digitalWrite(RelayPin3, 1) ; Relay_statusPin3 = 1;
    delay(Relay_delayTime);
    break;
    case 'd':
    digitalWrite(RelayPin3, 0) ; Relay_statusPin3 = 0;
    delay(Relay_delayTime);
    break;
    case 'r':
    digitalWrite(RelayPin4, 1) ; Relay_statusPin4 = 1;
    delay(Relay_delayTime);
    break;
    case 'f':
    digitalWrite(RelayPin4, 0) ; Relay_statusPin4 = 0;
    delay(Relay_delayTime);
    break;
  }
    Serial.print(com_Relay);
    Serial.print("  (");
    Serial.print(Relay_statusPin1);
    Serial.print(",");
    Serial.print(Relay_statusPin2);
    Serial.print(",");
    Serial.print(Relay_statusPin3);
    Serial.print(",");
    Serial.print(Relay_statusPin4);
    Serial.println(")"); 
}
