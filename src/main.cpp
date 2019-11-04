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
  /**int i;

  int SLeft, SCenter, SRight = 0;

  Turn(90,Left);
  FindLine();
  Move(0.4,15,Reverse);
  delay(100);
  Turn(45,Right);
  
  while (!SLeft || !SCenter || !SRight)
  {
    SLeft = digitalRead(REFLECTION_SENSOR_LEFT);
    SCenter = digitalRead(REFLECTION_SENSOR_CENTER);
    SRight = digitalRead(REFLECTION_SENSOR_RIGHT);

    if (SLeft && SCenter && SRight)
    {
      delay (250);
      SLeft = digitalRead(REFLECTION_SENSOR_LEFT);
      SCenter = digitalRead(REFLECTION_SENSOR_CENTER);
      SRight = digitalRead(REFLECTION_SENSOR_RIGHT);
    }
  
    FollowLine(0.4, Reverse);
  }
FindBall();
for (int i = 110; i > 80; i--)
  {
    SERVO_SetAngle(0,i);
    delay(50);
  }

Turn(180, Right);
Move(0.4, 45, Reverse);
  while (1);
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
delay(1000);*/
//Impale();

//delay(2000);
if(IRSensor())
{
 SERVO_SetAngle(0,110);
}
delay(200);
for (int i = 80; i > 30; i--)
  {
    SERVO_SetAngle(0,i);
    delay(50);
  }
delay(1000);
}

