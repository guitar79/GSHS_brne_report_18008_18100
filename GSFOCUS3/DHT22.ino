
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

/**
  for DHT routine
*/
void humidityTemperatureReport() 
    {
      delay(delayMS);

      sensors_event_t event;

      dht.temperature().getEvent(&event);
      if(isnan(event.temperature)) {
                    Serial.print("TEMPERATURE:");
                    Serial.print("UNKNOWNERROR");
                    Serial.println("#");
      }
      else {
                    Serial.print("TEMPERATURE:");
                    Serial.print(event.temperature, 2);
                    Serial.println("#");
                    delay(delayMS);
      }

      dht.humidity().getEvent(&event);
      if(isnan(event.relative_humidity)) {
                    Serial.print("HUMIDITY:");
                    Serial.print("UNKNOWNERROR");
                    Serial.println("#");
      }
      else {
                    Serial.print("HUMIDITY:");
                    Serial.print(event.relative_humidity, 2);
                    Serial.println("#");
                    delay(delayMS);
      }
    }

void playDHT()
{
  if(!isMoving) {
      sensors_event_t event;

            display.setCursor(6,0); display.print("T: ");
      dht.temperature().getEvent(&event);
      if(isnan(event.temperature)) {
                    display.print("ERR");
      }
      else {
                    display.print(event.temperature, 2);
      }
            display.setCursor(70,0); display.print("H: ");
      dht.humidity().getEvent(&event);
      if(isnan(event.relative_humidity)) {
                    display.println("ERR");
      }
      else {
                    display.println(event.relative_humidity, 2);
      }
  }
  else {
    display.setCursor(0,0);
    display.println(F("   Motor Rotating"));
  }
  
}



