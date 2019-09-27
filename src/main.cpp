#include <Arduino.h>
#include <LibRobus.h>
#include "Functions.h"

void setup() 
{
  BoardInit();
}

void loop() 
{
  Turn(90, Left);
  delay(1000);
  Turn(90, Right);
  delay(1000);
}