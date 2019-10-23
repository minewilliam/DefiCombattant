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
  LeverUp();
  delay(1000);
  Impale();
  delay(1000);
}
