#include "Functions.h"
#include "RobotSense.h"
#include "Cones.h"

#define Dumb
#define One

void setup() 
{
  BoardInit();
  RobosenseInit();
  InitCone();
}

void loop()
{
  delay(2000);
  PlaceCone();
}