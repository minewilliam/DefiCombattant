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
  while(true) 
  {
  //while(!ROBUS_IsBumper(2));
  delay(1000);
  // Serial.println(GetColorHex(),HEX);
  while(FollowLine(0.4, Reverse))
  {
    delay(100);
  }

  MOTOR_SetSpeed(Right, 0);
  MOTOR_SetSpeed(Left, 0);
  }
}

