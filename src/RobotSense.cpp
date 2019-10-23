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
}

Color COLOR_Read()
{
  return Red;
}

void FollowLine(float SpeedCommand, float DistanceToDo, bool Direction)
{
  float DistanceDone = 0;

  float Speed = 0;

  float AdjustRight = 0;
  float AdjustLeft = 0;

  int EncoderCountRight = 0;
  int EncoderCountLeft = 0;

  bool Deceleration = false;
    
  ENCODER_Reset(Left);
  ENCODER_Reset(Right);
  
  while (DistanceDone < DistanceToDo)
  {
    ReflectionSensorLeft = digitalRead(REFLECTION_SENSOR_LEFT);
    ReflectionSensorRight = digitalRead(REFLECTION_SENSOR_RIGHT);
    ReflectionSensorCenter = digitalRead(REFLECTION_SENSOR_CENTER);

    if (DistanceToDo - DistanceDone > 30 && Speed < SpeedCommand)
    {
      Speed += + 0.03; //Acceleration
    }

    else if (DistanceToDo - DistanceDone < 30 )
    {
      Speed -= 0.03; //Deceleration
      Deceleration = true;
    }
    else
    {
      Speed = SpeedCommand;
    }
    
    if (Speed < 0.20)
    {
      Speed = 0.20;
    }

    if(!ReflectionSensorCenter)
    {
      AdjustLeft = Speed;
      AdjustRight = Speed;
    }
    else if(!ReflectionSensorLeft)
    {
      AdjustLeft = Speed + 0.1;
      AdjustRight = Speed - 0.1;
    }
    else if(!ReflectionSensorRight)
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

    delay(100);

    EncoderCountRight = abs(ENCODER_ReadReset(Right));
    EncoderCountLeft = abs(ENCODER_ReadReset(Left));

    DistanceDone = DistanceDone + (EncoderCountRight + EncoderCountLeft) / 2 / 133.4;
  }

  MOTOR_SetSpeed(Right, 0);
  MOTOR_SetSpeed(Left, 0);

  ENCODER_Reset(Left);
  ENCODER_Reset(Right);
}


