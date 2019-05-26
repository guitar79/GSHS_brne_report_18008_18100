
//version 1 : using Adafruit library...
#ifndef setDisplay_h
#define setDisplay_h

    #include <Adafruit_GFX.h>
    #include <Adafruit_SSD1306.h>
    #include <Wire.h>
    
    #define OLED_RESET 4
    Adafruit_SSD1306 display(OLED_RESET);
    
    #define LOGO16_GLCD_HEIGHT 16 
    #define LOGO16_GLCD_WIDTH 16
    #define XPOS 0
    #define YPOS 1
    #define DELTAY 2
    
    void startFMenu()
    {
      display.clearDisplay();
      display.setTextColor(WHITE);
      display.setTextSize(1);
      display.setCursor(0,8);
      display.print(F("    Stepping Motor"));
      display.setTextSize(2);
      display.setCursor(0,16);
      display.print(F(" Controler"));
      display.display();
      delay(5000);
      display.setTextSize(1);
    }

#endif

