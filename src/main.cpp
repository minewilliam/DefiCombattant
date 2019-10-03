#include <Arduino.h>
#include <LibRobus.h>
#include "Functions.h"

void setup() 
{
  BoardInit();
  Move(0.5, 100, Forward); 
  delay(5000);
}

void loop() 
{
  Move(0.5, 30.48, Forward); 
  Turn(90,Left);
}