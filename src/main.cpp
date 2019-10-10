#include <Arduino.h>
#include <LibRobus.h>
#include "Functions.h"


void setup() 
{
  BoardInit();
  
}

void loop() 
{
  
  Turn(90,Right);
  delay (500);
  Turn(90,Right);
  delay (500);
  Turn(180,Right);
  delay (500);
  Move(0.4,2000,Forward);
  while(1);
}