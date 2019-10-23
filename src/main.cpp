#include "Functions.h"
#include "RobotSense.h"
#include "Adafruit_TCS34725.h"

void setup() 
{
  BoardInit();
  RobosenseInit();
}

void loop()
{
  // Serial.println(GetColorHex(),HEX);
  FollowLine(0.6,10000,Forward);
}

