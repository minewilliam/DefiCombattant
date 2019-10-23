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

int ReflectionSensorLeft, ReflectionSensorRight, ReflectionSensorCenter;

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

bool FollowLine(float SpeedCommand, bool Direction)
{
  static int ReflectionSensorLeft_debounce, ReflectionSensorRight_debounce, ReflectionSensorCenter_debounce;
  static bool Following = false;
  static bool NewFollower = true;
  static float DistanceDone = 0;
  static float Speed = 0;
  static int EncoderCountRight = 0;
  static int EncoderCountLeft = 0;

  float AdjustRight = 0;
  float AdjustLeft = 0;
  
  if(NewFollower)
  {
    ReflectionSensorLeft_debounce = true;
    ReflectionSensorRight_debounce = true;
    ReflectionSensorCenter_debounce = true;
    NewFollower = false;
    Following = true;
    DistanceDone = 0;
    Speed = 0;
    EncoderCountRight = 0;
    EncoderCountLeft = 0;
    ENCODER_Reset(Left);
    ENCODER_Reset(Right);
  }

  if (Following)
  {
    //Start Read & Debounce
    int SLeft = digitalRead(REFLECTION_SENSOR_LEFT);
    int SRight = digitalRead(REFLECTION_SENSOR_RIGHT);
    int SCenter = digitalRead(REFLECTION_SENSOR_CENTER);

    ReflectionSensorLeft = SLeft;
    ReflectionSensorRight = SRight;
    ReflectionSensorCenter = SCenter;

    // if(ReflectionSensorLeft != SLeft)
    // {
    //   if(ReflectionSensorLeft_debounce == SLeft)
    //   {
    //     ReflectionSensorLeft = SLeft;
    //   }
    //   ReflectionSensorLeft_debounce = SLeft;
    // }

    // if(ReflectionSensorRight != SRight)
    // {
    //   if(ReflectionSensorRight_debounce == SRight)
    //   {
    //     ReflectionSensorRight = SRight;
    //   }
    //   ReflectionSensorRight_debounce = SRight;
    // }

    // if(ReflectionSensorCenter != SCenter)
    // {
    //   if(ReflectionSensorCenter_debounce == SCenter)
    //   {
    //     ReflectionSensorCenter = SCenter;
    //   }
    //   ReflectionSensorCenter_debounce = SCenter;
    // }

    

    //End Read & Debounce

    if (DistanceDone < 30 && Speed < SpeedCommand)
    {
      Speed += 0.03; //Acceleration
    }

    Speed = SpeedCommand;
    
    if (Speed < 0.20)
    {
      Speed = 0.20;
    }

    if(!ReflectionSensorCenter&&!ReflectionSensorRight&&!ReflectionSensorLeft)
    {
      Following = false;
    }
    else if(!ReflectionSensorCenter)
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
      Following = false;
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

    EncoderCountRight = abs(ENCODER_ReadReset(Right));
    EncoderCountLeft = abs(ENCODER_ReadReset(Left));

    DistanceDone = DistanceDone + (EncoderCountRight + EncoderCountLeft) / 2 / 133.4;
  }

  if(!Following)
  {
    NewFollower = true;
  }

  return Following;
}


