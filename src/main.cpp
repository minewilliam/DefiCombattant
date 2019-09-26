#include <Arduino.h>
#include <LibRobus.h>

//!Placeholder value
#define STEPSPERMETER 20000 //Encoder steps over one meter
#define MOTOR_MINSPEED 0.15
#define MOTOR_TOPSPEED 0.6
#define MOTOR_ACCELERATION 1.2

//Positions in centimeters
//X:Left-Right
//Y:Forward-Back
int CurrentPosition[] = {0,0};
int Coordinates[][2] = {{50,0},{50,50},{0,50},{0,0}};

float Speed = 0;

void setup() {
  BoardInit();
  delay(2000);
}

void loop() {
  for(int i = 0; i < 4; i++)
  {
    while(!moveToPosition(Coordinates[i],MOTOR_TOPSPEED));
  }
}

bool moveToPosition(int position[2], float topSpeed)
{
  return false;
}

