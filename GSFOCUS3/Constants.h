// -----------------------------------------------------------------------------------

//Constants

// DHT22 pins
#define DHTPIN 2 // what pin we're connected to
#define DHTTYPE DHT22 // DHT 22 (AM2302)

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


// OLED pins
//#define OLED 4
  
// Stepper Dirver (DRV8825) pins
#define DIR 4
#define STEP 3
#define MS0 A1
#define MS1 12
#define MS2 13

// Stepper Driver Models
//#define A4988    1
//#define DRV8825  2

// Stepp motor Models
#define MOTOR_STEPS 200

// Length of each stepper's table
//#define LEN_A4988   5
//#define LEN_DRV8825 6
   
// The various microsteps for different driver models, with the bit modes for each
//unsigned int StepsA4988  [LEN_A4988]  [2] = { {1,0}, {2,1}, {4,2}, {8,3}, {16,7} };
//unsigned int StepsDRV8825[LEN_DRV8825][2] = { {1,0}, {2,1}, {4,2}, {8,3}, {16,4}, {32,5} };