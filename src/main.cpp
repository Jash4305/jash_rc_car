#include <Arduino.h>


void setup()
{
  Serial.begin(115200);

  delay(2000);

  Serial.println("================================");
  Serial.println("       JASH RC CAR TEST");
  Serial.println("================================");
  Serial.println("ESP32 BOOTED!");
}

void loop()
{
  Serial.println("HELLO FROM ESP32");
  delay(1000);
}