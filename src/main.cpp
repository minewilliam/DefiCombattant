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
      delay (20);
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

while (SLeft || SCenter || SRight)
  {
    SLeft = digitalRead(REFLECTION_SENSOR_LEFT);
    SCenter = digitalRead(REFLECTION_SENSOR_CENTER);
    SRight = digitalRead(REFLECTION_SENSOR_RIGHT);

    if (!SLeft && !SCenter && !SRight)
    {
      delay (20);
      SLeft = digitalRead(REFLECTION_SENSOR_LEFT);
      SCenter = digitalRead(REFLECTION_SENSOR_CENTER);
      SRight = digitalRead(REFLECTION_SENSOR_RIGHT);
    }
  
    FollowLine(0.4, Reverse);
  }

  MOTOR_SetSpeed(Left, 0);
  MOTOR_SetSpeed(Right, 0);
  LeverUp();

  Move(1, 30, Forward);

  while (1);
}