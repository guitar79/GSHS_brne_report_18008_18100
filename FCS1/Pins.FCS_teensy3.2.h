// -------------------------------------------------------------------------------------------------
// Pin map for FCS_Teensy3.2

// DHT22 pins
#define DHTPIN 2 // what pin we're connected to
#define DHTTYPE DHT22 // DHT 22 (AM2302)

// SVO pins (Cover Open/Close)
#define COVER1 0 // 
#define COVER1 1 // 

// BUTTON pins (User interface)
#define uiKeyPrev 5
#define uiKeyNext 6
#define uiKeySelect 8
#define uiKeyBack 7

// OLED pins (User interface)
#define SDA 25
#define SCL 26

// MOTOR DRV pins (DRV8825)
#define Axis1DirPin  4    // Pin 21 (Dir)
#define Axis1StepPin  4    // Pin 20 (Step)
#define Axis1_FAULT   14  // Pin 18 (Fault)
//#define Axis1_Aux    
#define Axis1_M2      17    // Pin 17 (Microstep Mode 2 or SPI CS)
#define Axis1_M1      16    // Pin 16 (Microstep Mode 1 or SPI SCK)
#define Axis1_M0      15    // Pin 15 (Microstep Mode 0 or SPI MOSI)
#define Axis1_EN      14    // Pin 14 (Enable)

// OLED pins
//#define OLED 4


#define boardtype 1   //select boardtype....

#if boardtype==1  //standrad  4ch
#define relayPin1  10
#define relayPin2  8
#define relayPin3  6
#define relayPin4  4
#define relayPin5  9      //only 8ch
#define relayPin6  10     //only 8ch
#define relayPin7  11     //only 8ch
#define relayPin8  12     //only 8ch

#elif boardtype==2  //njp  4ch
#define relayPin1  9
#define relayPin2  10
#define relayPin3  11
#define relayPin4  12
#define relayPin5  5      //only 8ch
#define relayPin6  6      //only 8ch
#define relayPin7  7      //only 8ch
#define relayPin8  8      //only 8ch

#elif boardtype==3  //standrad  8ch
#define relayPin1  5
#define relayPin2  6
#define relayPin3  7
#define relayPin4  8
#define relayPin5  9
#define relayPin6  10
#define relayPin7  11
#define relayPin8  12
#endif
