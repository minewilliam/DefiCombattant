/*
 * RobotSense.c
 *
 * Created on: Oct 17, 2019
 * Authors: William, Fred
 * 
 * Description:
 */

#include "RobotSense.h"

enum {Left, Right};
enum {Forward, Reverse};

void RobosenseInit()
{
  pinMode(REFLECTION_SENSOR_RIGHT, INPUT);
  pinMode(REFLECTION_SENSOR_LEFT, INPUT);
  pinMode(REFLECTION_SENSOR_CENTER, INPUT);
  pinMode(REFLECTION_SENSOR_UP, INPUT);
  SERVO_SetAngle(0,30);
}

void FindLine (bool Side)
{
  int SRight, SLeft = 1;

  /*Avance*/
  MOTOR_SetSpeed(Right, -0.2);
  MOTOR_SetSpeed(Left, -0.2);

  /*Boucle jusqu'à temps qu'il trouve une ligne*/
  if (Side == Right)
  {
    while (SRight)
    {
      SRight = digitalRead(REFLECTION_SENSOR_RIGHT);
      if (!SRight)
      {
        delay(100);
        SRight = digitalRead(REFLECTION_SENSOR_RIGHT);
      }
    }
  }

  else
  {
    while (SLeft)
    {
      SLeft = digitalRead(REFLECTION_SENSOR_LEFT);
      if (!SLeft)
      {
        delay(100);
        SLeft = digitalRead(REFLECTION_SENSOR_LEFT);
      }
    }
  }
  
  /*Stop*/
  MOTOR_SetSpeed(Right, 0);
  MOTOR_SetSpeed(Left, 0);
}

void FindBall()
{
  while(!IRSensor())
  {
    #ifdef Dumb
      MOTOR_SetSpeed(Left, -0.2);
      MOTOR_SetSpeed(Right, -0.2);
    #endif
    #ifdef Dumber
      MOTOR_SetSpeed(Left, -0.3);
      MOTOR_SetSpeed(Right, -0.3);
    #endif
  }

  #ifdef Dumb
    delay(500);
  #endif
  MOTOR_SetSpeed(Left, 0);
  MOTOR_SetSpeed(Right, 0);
  
  MOTOR_SetSpeed(Left, 0);
  MOTOR_SetSpeed(Right, 0);
  
  Impale();

  delay(200);
}

void FollowLine(float SpeedCommand, bool Direction)
{
  static float Speed = 0;

  float AdjustRight = 0;
  float AdjustLeft = 0;

  int SLeft = digitalRead(REFLECTION_SENSOR_LEFT);
  int SRight = digitalRead(REFLECTION_SENSOR_RIGHT);
  int SCenter = digitalRead(REFLECTION_SENSOR_CENTER);
  
  Speed = SpeedCommand;
  
  if (Speed < 0.20)
  {
    Speed = 0.20;
  }

  if(!SCenter)
  {
    AdjustLeft = Speed;
    AdjustRight = Speed;
  }
  else if(!SLeft)
  {
    AdjustLeft = Speed + 0.1;
    AdjustRight = Speed - 0.1;
  }
  else if(!SRight)
  {
    AdjustRight = Speed + 0.1;
    AdjustLeft = Speed - 0.1;
  }
  else if(SLeft && SCenter && SRight)
  {
    MOTOR_SetSpeed(Right, -0.15);
    MOTOR_SetSpeed(Left, -0.15);  
  }
  else
  {
    AdjustLeft=0;
    AdjustRight=0;
  }
  
  if (Direction == Reverse)
  {
    MOTOR_SetSpeed(Right, AdjustRight * -1);
    MOTOR_SetSpeed(Left, AdjustLeft * -1);
  }
  else if (Direction == Forward)
  {
    MOTOR_SetSpeed(Right, AdjustRight);
    MOTOR_SetSpeed(Left, AdjustLeft);
  }
}

void LeverUp(void)
{
  #ifdef Dumb
    for (int i = 80; i > 30; i--)
    {
      SERVO_SetAngle(0,i);
      delay(50);
    }
  #endif  

  #ifdef Dumber
    for (int i = 40; i > 10; i--)
    {
      SERVO_SetAngle(0,i);
      delay(50);
    }
  #endif  
}

void MoveBall(void)
{
  #ifdef Dumb
    for (int i = 110; i > 75; i--)
    {
      SERVO_SetAngle(0,i);
      delay(50);
    }
  #endif  

  #ifdef Dumber
    for (int i = 65; i > 40; i--)
    {
      SERVO_SetAngle(0,i);
      delay(50);
    }
  #endif 
}

void Impale(void)
{
  #ifdef Dumb
    SERVO_SetAngle(0,110);
  #endif  

  #ifdef Dumber
    SERVO_SetAngle(0,75);
  #endif 
}

bool IRSensor()
{
  if(digitalRead(REFLECTION_SENSOR_UP)==1){
    return 1;
  }
  else{
    return 0;
  }
}

float IR_Distance (void)
{
  float Distance;
  float Volt;
  uint16_t IRRead;

  IRRead = ROBUS_ReadIR(0);

  Volt = (float)IRRead/1023 * 5;


  Distance = (Volt - 0.1)/20.33;
 
  Distance = 1/Distance;

  return Distance;
}