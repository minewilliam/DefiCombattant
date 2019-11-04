#include "Functions.h"
#include "RobotSense.h"
#include "Adafruit_TCS34725.h"

#define N_E Yellow
#define N_W Blue
#define S_E Red
#define S_W Green


//#define colorA 1
//#define colorB 2

void setup() 
{
  BoardInit();
  RobosenseInit();
}

void loop()
{
  //IRSensor();
  /**LeverUp();
  delay(1000);
  Impale();
  delay(1000);**/ 

/*int SLeft = digitalRead(REFLECTION_SENSOR_LEFT);
int SRight = digitalRead(REFLECTION_SENSOR_RIGHT);
int SCenter = digitalRead(REFLECTION_SENSOR_CENTER);*/

  while (1)
  {
    FollowLine(0.4, Reverse);
  }
}

/*
if (colorA == N_E) 
{
    Turn(90, 1);
    delay(2000);
//a changer pour capteur balle
    while (!SLeft && !SRight && !SCenter)
    {
      FollowLine(0.4, Forward);
    }

 
}

if (colorA == N_W)
{
  Turn(90, 0);
  delay(2000);
//a changer pour capteur balle
  while (COLOR_Read != N_W)
  {
    FollowLine(0.4, Forward);
  } 
}

if (colorA == S_W)
{
  Turn(90, 0);
  delay(2000);

  Move(0.4, 52, Reverse);
  delay(2000);

  Turn(90,0);
  delay(2000);
  //a changer pour capteur balle
  while (COLOR_Read != S_W)
  {
    FollowLine(0.4, Forward);
  }
}

if (colorA == S_E)
{
  Turn(90, 1);
  delay(2000);

  Move(0.4, 52, Reverse);
  delay(2000);

  Turn(90,1);
  delay(2000);
  //a changer pour capteur balle
  while (COLOR_Read()!= S_E)
  {
    FollowLine(0.4, Forward);
  }

}
LeverUp();
delay(1000);
Impale();
delay(1000);
}
*/
