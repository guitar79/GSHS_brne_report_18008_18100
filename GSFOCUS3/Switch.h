
#ifndef Switch_h
#define Switch_h

//스위치 핀 번호
#define UPpin 8
#define DOWNpin 9
#define RIGHTpin 7
#define LEFTpin 10

//모터드라이버 핀 번호
#define DIR 4
#define STEP 3
#define MS0 15
#define MS1 12
#define MS2 13
#define MOTOR_STEPS 200

//BaudRate
#define baudrate 115200

// for the temperature and hubmidity sensor
#define DHT22_PIN 2



//about button switch
short S[4]={0}; short now[4]={1}; short was[4]={0};

//어떻게 입력이 되었나?
void controljudge()
{
  now[0]=digitalRead(UPpin);
  now[1]=digitalRead(DOWNpin);
  now[2]=digitalRead(RIGHTpin);
  now[3]=digitalRead(LEFTpin);
  for(int i=0;i<4;i++)
  {
  if(now[i]!=was[i]&&now[i]==0) S[i]=1;
  else S[i]=0;
      was[i]=now[i];
  }
}

//설정된 핀번호 풀업저항으로 선언
void pinset()
{
  pinMode(UPpin,INPUT_PULLUP);
  pinMode(DOWNpin,INPUT_PULLUP);
  pinMode(RIGHTpin,INPUT_PULLUP);
  pinMode(LEFTpin,INPUT_PULLUP);
}


#endif
