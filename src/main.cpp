#include "Functions.h"
#include "RobotSense.h"
#include "Adafruit_TCS34725.h"

void setup() 
{
  BoardInit();
}

void loop()
{
  Serial.println(GetColorHex(),HEX);
}

