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

int ReflectionSensorLeft,ReflectionSensorRight,ReflectionSensorCenter;

void RobosenseInit()
{
  pinMode(REFLECTION_SENSOR_RIGHT, INPUT);
  pinMode(REFLECTION_SENSOR_LEFT, INPUT);
  pinMode(REFLECTION_SENSOR_CENTER, INPUT);
  pinMode(REFLECTION_SENSOR_UP, INPUT);
  SERVO_SetAngle(0,30);
}

Color COLOR_Read()
{
  uint32_t RGB;
  uint8_t red, blue, green;

  RGB=GetColorHex();
  blue=(RGB&0xFF);
  green=(RGB&0xFF00)>>8;
  red=(RGB&0xFF0000)>>16;

  if (blue>0xE1 && green>0xE1 && red>0xE1)
  {
    return White; 
  }
  
  if (blue<0x50 && green<0x50 && red>0x90)
  {
    return Red;
  }
  
  if (blue<0x60 && green>0x60 && red<0x30)
  {
    return Green;
  }
  
  if (blue>0x90 && green<0x60 && red<0x20)
  {
    return Blue;
  }
  
  if (blue<0x30 && green>0x60 && red>0x60)
  {
    return Yellow;
  }

  return Yellow;
}

void FindLine (bool Side)
{
  int SRight, SLeft = 1;

  /*Avance*/
  MOTOR_SetSpeed(Right, -0.3);
  MOTOR_SetSpeed(Left, -0.3);

  /*Arrete lorsqu'il trouve une ligne*/
  if (Side == Right)
  {
    while (SRight)
    {
      SRight = digitalRead(REFLECTION_SENSOR_RIGHT);
      if (!SRight)
      {
        delay(20);
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
        delay(20);
        SLeft = digitalRead(REFLECTION_SENSOR_LEFT);
      }
    }
  }
  
  

  /*Stop*/
  MOTOR_SetSpeed(Right, 0);
  MOTOR_SetSpeed(Left, 0);
}

bool FollowLine(float SpeedCommand, bool Direction)
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

  return 0;
}

void LeverUp(void)
{
  for (int i = 80; i > 30; i--)
  {
    SERVO_SetAngle(0,i);
    delay(50);
  }
}

void MoveBall(void)
{
  for (int i = 110; i > 80; i--)
  {
    SERVO_SetAngle(0,i);
    delay(50);
  }
}

void Impale(void)
{
  SERVO_SetAngle(0,110);
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

void FindBall()
{
  while(!IRSensor())
  {
    MOTOR_SetSpeed(Left, -0.2);
    MOTOR_SetSpeed(Right, -0.2);
  }

    MOTOR_SetSpeed(Left, 0);
    MOTOR_SetSpeed(Right, 0);

    delay(500);

    Impale();

    delay(200);
}

