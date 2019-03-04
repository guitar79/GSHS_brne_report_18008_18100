/*
 * Title       Focuser, Optic Cover, Switch controller
 * by          Kiehyun Kevin Park
 *
  *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Description:
 *   Full featured stepper motor telescope microcontroller for Equatorial and
 *   Alt-Azimuth mounts, with the LX200 derived command set.
 *
 * Author: Kiehyun Kevin Park
 *   Kiehyun.Park@gmail.com
 */
// Use Config.xxx.h to configure OnStep to your requirements

#define FirmwareDate   "Feb. 18. 2019"
#define FirmwareNumber "0.1"
#define FirmwareName   "KevinFCS"
#define FirmwareTime   "12:00:00"

//상수들은 따로 저장함
#include "Constants.h"

//기능별로 제작한 함수 라이브러리 파일들
//#include "Menu.h"
//#include "Focus.h"
#include "Cover.h"
#include "Switch.h"

//pcb 보드별 파일들
#include "Config.FCS_teensy3.2.h"
#include "Config.FCS_GSnano.h"

//사용한 라이브러리들
#include <DHT.h>
#include "DHT.h"
DHT dht(DHTPIN, DHTTYPE);

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(OLED_RESET);

#include <SyncDriver.h>
#include <Stepper.h>
#include <BasicStepperDriver.h>
#include <DRV8825.h>
DRV8825 stepper(MOTOR_STEPS, DIR, STEP, MS0, MS1, MS2);

#include <Servo.h>
//Servo myservo;

#include <EEPROM.h>

#include <U8g2lib.h>
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);



void setup() { 
 
  Serial.begin(9600); // 시리얼통신
  dht.begin();  // DHT
  u8g2.begin();
  
  stepper.begin(1, 1);
  
}


void loop() {
  
  //릴레이 스위치 on/off 신호가 오면 동작..
  switch_on_off();

  //경통 커버 open/close 신호가 오면 동작..
  cover_open_close();
   
}
