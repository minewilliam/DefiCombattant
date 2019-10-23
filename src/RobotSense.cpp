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
}

bool FollowLine(float SpeedCommand, bool Direction)
{
  static int ReflectionSensorLeft_debounce, ReflectionSensorRight_debounce, ReflectionSensorCenter_debounce;
  static bool Following = true;
  static bool Following_debounce = true;
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
    Following_debounce = true;
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

    if(ReflectionSensorLeft != SLeft)
    {
      if(ReflectionSensorLeft_debounce == SLeft)
      {
        ReflectionSensorLeft = SLeft;
      }
      ReflectionSensorLeft_debounce = SLeft;
    }

    if(ReflectionSensorRight != SRight)
    {
      if(ReflectionSensorRight_debounce == SRight)
      {
        ReflectionSensorRight = SRight;
      }
      ReflectionSensorRight_debounce = SRight;
    }

    if(ReflectionSensorCenter != SCenter)
    {
      if(ReflectionSensorCenter_debounce == SCenter)
      {
        ReflectionSensorCenter = SCenter;
      }
      ReflectionSensorCenter_debounce = SCenter;
    }

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

    if(ReflectionSensorCenter&&ReflectionSensorRight&&ReflectionSensorLeft)
    {
      Following = false;
    }
    else if(!ReflectionSensorCenter&&!ReflectionSensorRight&&!ReflectionSensorLeft)
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

    EncoderCountRight = abs(ENCODER_ReadReset(Right));
    EncoderCountLeft = abs(ENCODER_ReadReset(Left));

    DistanceDone = DistanceDone + (EncoderCountRight + EncoderCountLeft) / 2 / 133.4;
  }
  else
  {
    NewFollower = true;
    ENCODER_Reset(Left);
    ENCODER_Reset(Right);
  }

  return Following;
}

void LeverUp(void)
{
    SERVO_Enable(0);
    SERVO_SetAngle(0,0);
}

void Impale(void)
{
    SERVO_Enable(0);
    SERVO_SetAngle(0,90);
}
