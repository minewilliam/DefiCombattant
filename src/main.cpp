#include "Functions.h"
#include "RobotSense.h"
#include "Adafruit_TCS34725.h"

#define Three

void GetBallOne (void);
void GetBallTwo (void);
void GetBallThree (void);
void GetBallFour (void);

void setup() 
{
  BoardInit();
  RobosenseInit();
}

void loop()
{
  #ifdef One
    GetBallOne();
  #endif

  #ifdef Two
    GetBallTwo();
  #endif

  #ifdef Three
    GetBallThree();
  #endif

  #ifdef Four
    GetBallFour();
  #endif

  while (1);
}

void GetBallOne (void)
{
  int SLeft, SCenter, SRight = 0;

  Turn(90,Left);
  FindLine(Right);
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
MoveBall();

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
  Turn(45,Left);
  Move(1, 30, Forward);
  Turn(90,Left);
  Move(1, 30, Forward);
}

void GetBallTwo (void)
{
  int SLeft, SCenter, SRight = 0;

  Turn(90,Right);
  FindLine(Left);
  Move(0.4,15,Reverse);
  delay(100);
  Turn(45,Left);
  
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
MoveBall();

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
  Turn(45,Left);
  Move(1, 30, Forward);
  Turn(90,Left);
  Move(1, 30, Forward);
}

void GetBallThree (void)
{
  int SLeft, SCenter, SRight = 0;

  Turn(90,Left);
  FindLine(Right);
  Move(0.4,15,Reverse);
  Turn(90,Left);
  Move(0.4,50,Reverse);
  FindLine(Right);
  Move(0.4,15,Reverse);
  Turn(45,Right);
  
  while (!SLeft || !SCenter || !SRight)
  {
    SLeft = digitalRead(REFLECTION_SENSOR_LEFT);
    SCenter = digitalRead(REFLECTION_SENSOR_CENTER);
    SRight = digitalRead(REFLECTION_SENSOR_RIGHT);

    if (SLeft && SCenter && SRight)
    {
      delay (100);
      SLeft = digitalRead(REFLECTION_SENSOR_LEFT);
      SCenter = digitalRead(REFLECTION_SENSOR_CENTER);
      SRight = digitalRead(REFLECTION_SENSOR_RIGHT);
    }
  
    FollowLine(0.4, Reverse);
  }

FindBall();
MoveBall();

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
  Turn(45,Left);
  Move(1, 30, Forward);
  Turn(90,Left);
  Move(1, 30, Forward);
}