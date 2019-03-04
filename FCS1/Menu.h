/*
 * Title       Menu
 * by          Kiehyun Kevin Park
 *
 * Copyright (C) 2012 to 2018 Kiehyun Kevin Park.
 *
*/ 

//Libraries
#include <Arduino.h>
#include <Wire.h>

/*
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(OLED);
*/

#include <U8g2lib.h>
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);


#include <EEPROM.h>
#include <DHT.h>
DHT dht(DHTPIN, DHTTYPE);

//Variables
int chk;

// SETUP KEYs
#define KEY_NONE 0
#define KEY_PREV 1
#define KEY_NEXT 2
#define KEY_SELECT 3
#define KEY_BACK 4

#define uiKeyPrev 8
#define uiKeyNext 9
#define uiKeySelect 10
#define uiKeyBack 7

uint8_t uiKeyCodeFirst = KEY_NONE;
uint8_t uiKeyCodeSecond = KEY_NONE;
uint8_t uiKeyCode = KEY_NONE;


#define MENU0_ITEMS 3
const char *menu0_strings[MENU0_ITEMS] = { "Focus CTL", "Heat CTL", "Setup"};
#define MENU10_ITEMS 2
const char *menu10_strings[MENU10_ITEMS] = { "Focus IN (∧)", "Focus OUT (∨)"};
#define MENU20_ITEMS 3
const char *menu20_strings[MENU20_ITEMS] = { "Heat PWR UP (∧)", "Heat PWR DOWN (∨)", "Heat PWR AUTO (＞)"};
#define MENU30_ITEMS 4
const char *menu30_strings[MENU30_ITEMS] = { "Menu30 - 1", "Menu30 - 2", "Menu30 - 3", "Menu30 - 4"};

uint8_t menu_current = 0;
uint8_t menu_redraw_required = 0;
uint8_t last_key_code = KEY_NONE;



// 버튼 상태 변수
int btn0State = 0;
int btn1State = 0;
int btn2State = 0;
int btn3State = 0;

//DRV8825 마이크로스텝 변수
int ms0State = 0;
int ms1State = 0;
int ms22State = 0;

float rotateDEG1 = 1.8;
float rotateDEG2 = 3.6;

//delay 값
int ssdelay = 50;
int lldelay = 1000;

void uiSetup(void) {
  // configure input keys 
  pinMode(uiKeyPrev, INPUT_PULLUP);           // set pin to input with pullup
  pinMode(uiKeyNext, INPUT_PULLUP);           // set pin to input with pullup
  pinMode(uiKeySelect, INPUT_PULLUP);           // set pin to input with pullup
  pinMode(uiKeyBack, INPUT_PULLUP);           // set pin to input with pullup
}

void uiStep(void) {    //버튼 눌렀을 때 동작하는 함수로.. 개선이 필요함.
  uiKeyCodeSecond = uiKeyCodeFirst;
  if ( digitalRead(uiKeyPrev) == LOW )
    uiKeyCodeFirst = KEY_PREV;
  else if ( digitalRead(uiKeyNext) == LOW )
    uiKeyCodeFirst = KEY_NEXT;
  else if ( digitalRead(uiKeySelect) == LOW )
    uiKeyCodeFirst = KEY_SELECT;
  else if ( digitalRead(uiKeyBack) == LOW )
    uiKeyCodeFirst = KEY_BACK;
  else 
    uiKeyCodeFirst = KEY_NONE;
  
  if ( uiKeyCodeSecond == uiKeyCodeFirst )
    uiKeyCode = uiKeyCodeFirst;
  else
    uiKeyCode = KEY_NONE;
}

void updateOLED_AWS(void) {  //OLED 상단에 AWS 값을 출력.. 개선이 필요함 (변수 출력이 안됨)
  float val_Temp= dht.readTemperature();
  float val_Humi = dht.readHumidity();
  u8g2.setFontMode(1);
  u8g2.setFont(u8g2_font_6x13_tf);
  u8g2.setFontRefHeightText();
  u8g2.setFontPosTop();
  String temp = "aaa";
  u8g2.drawStr(2, 0, "Temp:");
  u8g2.drawStr(66, 0, "Humi:");
  //u8g2.drawStr(2, 0, char(val_Temp, 1));
  //u8g2.drawStr(66, 0, char(val_Humi, 1));
}

void updateOLED_Welcome(void) {  //OLED 환영 메세지
  u8g2.setFont(u8g2_font_6x13_tf);
  u8g2.setFontRefHeightText();
  u8g2.setFontPosTop();
  u8g2.drawStr(2, 0, "Welcome!!");
  //u8g2.drawStr(2, 20, ("GS Focus.. Ver." + String(FirmwareNumber)));
  delay(lldelay);

}

void updateSerialMonitor_AWS() {  //AWS를 시리얼 모니터로 출력
  //Read data and store it to variables hum and temp
  float val_hum = dht.readHumidity();
  float val_temp = dht.readTemperature();
  //Print temp and humidity values to serial monitor
  Serial.print("Humidity: ");
  Serial.print(val_hum);
  Serial.print(" %, Temp: ");
  Serial.print(val_temp);
  Serial.println(" Celsius");
  delay(ssdelay);
}

void drawMenu0(void) {
  uint8_t i, h;
  u8g2_uint_t w, d;
  //u8g2.setFont(u8g2_font_6x13);
  //u8g2.setFontRefHeightText();
  //u8g2.setFontPosTop();

  updateOLED_AWS();   //OLED 상단에 AWS 값을 출력
    
  h = u8g2.getFontAscent()-u8g2.getFontDescent()+1;
  w = u8g2.getWidth();
  for( i = 0; i < MENU0_ITEMS; i++ ) {
    d = (w-u8g2.getStrWidth(menu0_strings[i]))/2;
    u8g2.setDrawColor(1);
    //u8g2.setDefaultForegroundColor();
    if ( i == menu_current ) {
      u8g2.drawBox(0, (i+2)*h+1, w, h);
      u8g2.setDrawColor(2);
      //u8g2.setDefaultBackgroundColor();
    }
    u8g2.drawStr(d, (i+2)*h, menu0_strings[i]);
  }
}

void drawMenu10(void) {
  uint8_t i, h;
  u8g2_uint_t w, d;
  //u8g2.setFont(u8g2_font_6x13);
  //u8g2.setFontRefHeightText();
  //u8g2.setFontPosTop();

  updateOLED_AWS();   //OLED 상단에 AWS 값을 출력
  
  h = u8g2.getFontAscent()-u8g2.getFontDescent();
  w = u8g2.getWidth();
  for( i = 0; i < MENU10_ITEMS; i++ ) {
    d = (w-u8g2.getStrWidth(menu10_strings[i]))/2;
    u8g2.setDrawColor(1);
    //u8g2.setDefaultForegroundColor();
    if ( i == (menu_current - 10) ) {
      u8g2.drawBox(0, (i+2)*h+1, w, h);
      u8g2.setDrawColor(2);
      //u8g2.setDefaultBackgroundColor();
    }
    u8g2.drawStr(d, (i+2)*h, menu10_strings[i]);
  }
  u8g2.drawStr(d, (i+3)*h, "msg");
}

void drawMenu20(void) {
  uint8_t i, h;
  u8g2_uint_t w, d;
  //u8g2.setFont(u8g2_font_6x13);
  //u8g2.setFontRefHeightText();
  //u8g2.setFontPosTop();

  updateOLED_AWS();   //OLED 상단에 AWS 값을 출력
  
  h = u8g2.getFontAscent()-u8g2.getFontDescent();
  w = u8g2.getWidth();
  for( i = 0; i < MENU20_ITEMS; i++ ) {
    d = (w-u8g2.getStrWidth(menu20_strings[i]))/2;
    u8g2.setDrawColor(1);
    //u8g2.setDefaultForegroundColor();
    if ( i == (menu_current - 20) ) {
      u8g2.drawBox(0, (i+2)*h+1, w, h);
      u8g2.setDrawColor(2);
      //u8g2.setDefaultBackgroundColor();
    }
    u8g2.drawStr(d, (i+2)*h, menu20_strings[i]);
  }
}

void drawMenu30(void) {
  uint8_t i, h;
  u8g2_uint_t w, d;
  //u8g2.setFont(u8g2_font_6x13);
  //u8g2.setFontRefHeightText();
  //u8g2.setFontPosTop();

  updateOLED_AWS();   //OLED 상단에 AWS 값을 출력
  
  h = u8g2.getFontAscent()-u8g2.getFontDescent();
  w = u8g2.getWidth();
  for( i = 0; i < MENU30_ITEMS; i++ ) {
    d = (w-u8g2.getStrWidth(menu30_strings[i]))/2;
    u8g2.setDrawColor(1);
    //u8g2.setDefaultForegroundColor();
    if ( i == (menu_current - 30) ) {
      u8g2.drawBox(0, (i+2)*h+1, w, h);
      u8g2.setDrawColor(2);
      //u8g2.setDefaultBackgroundColor();
    }
    u8g2.drawStr(d, (i+2)*h, menu30_strings[i]);
  }
}

void updateMenu(void) {
  if ( uiKeyCode != KEY_NONE && last_key_code == uiKeyCode ) {
    return;
  }
  last_key_code = uiKeyCode;

  if ( menu_current < 10 ) {
    switch ( uiKeyCode ) {
      case KEY_NEXT:
        menu_current++;
        if ( menu_current >= MENU0_ITEMS )
          menu_current = 0;
        Serial.println("Button NEXT is pressed");
        menu_redraw_required = 1;
        break;
      case KEY_PREV:
        if ( menu_current == 0 )
          menu_current = MENU0_ITEMS;
        menu_current--;
        Serial.println("Button PREV is pressed");
        menu_redraw_required = 1;
        break;
      case KEY_SELECT:
        menu_current = (menu_current + 1) * 10 ;
        Serial.println("Button SELECT is pressed");
        menu_redraw_required = 1;
        break;
      case KEY_BACK:
        menu_current = uint8_t((menu_current)/10) ;
        Serial.println("Button BACK is pressed");
        menu_redraw_required = 1;
        break;
    }
  }
  
  if ( menu_current >= 10 & menu_current < 20 ) {
    switch ( uiKeyCode ) {
      case KEY_NEXT:
        menu_current++;
        if ( menu_current >= ( 10 + MENU10_ITEMS - 1 ))
          menu_current = ( 10 + MENU10_ITEMS - 1 );
        //stepper.rotate(rotateDEG1);
        //const char msg = "Motor is rotated toword inside";
        Serial.println("Button NEXT is pressed");
        menu_redraw_required = 1;
        break;
      case KEY_PREV:
        menu_current--;
        if ( menu_current < 10 )
          menu_current = 10 ;
        //stepper.rotate(rotateDEG1);
        //const char msg = "Motor is rotated toword outside";
        Serial.println("Button PREV is pressed");
        menu_redraw_required = 1;
        break;
      case KEY_SELECT:
        Serial.println("Button SELECT is pressed");
        menu_redraw_required = 1;
        break;
      case KEY_BACK:
        menu_current = uint8_t((menu_current)/10 - 1) ;
        Serial.println("Button BACK is pressed");
        menu_redraw_required = 1;
        break;
    }
  }

  if ( menu_current >= 20 & menu_current < 30 ) {
    switch ( uiKeyCode ) {
      case KEY_NEXT:
        menu_current++;
        if ( menu_current >= ( 20 + MENU20_ITEMS - 1 ))
          menu_current = ( 20 + MENU20_ITEMS - 1 );
        Serial.println("Button NEXT is pressed");
        menu_redraw_required = 1;
        break;
      case KEY_PREV:
        menu_current--;
        if ( menu_current < 20 )
          menu_current = 20 ;
        Serial.println("Button PREV is pressed");
        menu_redraw_required = 1;
        break;
      case KEY_SELECT:
        menu_current--;
        if ( menu_current == ( 20 + MENU20_ITEMS - 1 ))
          // Set heat auto ;
        Serial.println("Button SELECT is pressed");
        menu_redraw_required = 1;
        break;
      case KEY_BACK:
        menu_current = uint8_t((menu_current)/10 - 1 ) ;
        Serial.println("Button BACK is pressed");
        menu_redraw_required = 1;
        break;
    }
  }

  if ( menu_current >= 30 & menu_current < 40 ) {
    switch ( uiKeyCode ) {
      case KEY_NEXT:
        menu_current++;
        if ( menu_current >= ( 30 + MENU30_ITEMS) )
          menu_current = 30;
        menu_redraw_required = 1;
        Serial.println("Button NEXT is pressed");
        break;
      case KEY_PREV:
        if ( menu_current == 30 )
          menu_current = ( 30 + MENU30_ITEMS ) ;
        menu_current--;
        Serial.println("Button PREV is pressed");
        menu_redraw_required = 1;
        break;
      case KEY_SELECT:
        //menu_current = (menu_current+1) * 10 ;
        Serial.println("Button SELECT is pressed");
        menu_redraw_required = 1;
        break;
      case KEY_BACK:
        menu_current = uint8_t((menu_current)/10 - 1 ) ;
        Serial.println("Button BACK is pressed");
        menu_redraw_required = 1;
        break;
    }
  }
}

void clearOLED(){
    u8g2.firstPage();  
    do {
    } while( u8g2.nextPage() );
}
