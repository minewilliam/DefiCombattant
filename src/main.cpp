#include <Arduino.h>
#include "Adafruit_TCS34725.h"
#include "LibRobus.h"

void setup() 
{
  BoardInit();
}


void loop()
{
  Serial.println(GetColorHex(),HEX);
}

