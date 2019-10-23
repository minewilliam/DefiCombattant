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
  while(FollowLine(0.4,500,Reverse))
  {
    delay(100);
  }
  while(true);
}

