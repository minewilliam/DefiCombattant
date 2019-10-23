/*
 * RobotSense.c
 *
 * Created on: Oct 17, 2019
 * Author: William
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

void FollowLine(float SpeedCommand, float DistanceToDo, bool Direction)
{
  float DistanceDone = 0;

  float SpeedRight = 0;
  float SpeedLeft = 0;

  float AdjustRight = 0;
  float AdjustLeft = 0;

  float Kp = 0.000004;
  float Ki = 0.0001;

  int EncoderCountRight = 0;
  int EncoderCountLeft = 0;

  #ifdef Dumb
    int InstantError = 0;
    int CumuledError = 50;
  #endif

  #ifdef Dumber
    int InstantError = 0;
    int CumuledError = -160;
  #endif

  bool Deceleration = 0;
    
  ENCODER_Reset(Left);
  ENCODER_Reset(Right);
  
  while (DistanceDone < DistanceToDo)
  {
    ReflectionSensorLeft = !digitalRead(REFLECTION_SENSOR_LEFT);
    ReflectionSensorRight = !digitalRead(REFLECTION_SENSOR_RIGHT);
    ReflectionSensorCenter = !digitalRead(REFLECTION_SENSOR_CENTER);

    if (DistanceToDo - DistanceDone > 30 && SpeedRight < SpeedCommand)
    {
      SpeedRight = SpeedRight + 0.03; //Acceleration
    }

    else if (DistanceToDo - DistanceDone < 30 )
    {
      SpeedRight = SpeedRight - 0.03; //Deceleration
      if (Deceleration == 0)
      {
        #ifdef Dumb
          CumuledError = 25;
        #endif

        #ifdef Dumber
          CumuledError = -50;
        #endif
      }
      Deceleration = 1;
    }
    else
    {
      SpeedRight = SpeedCommand;
    }
    
    if (SpeedRight < 0.20)
    {
      SpeedRight = 0.20;
    }
    
    SpeedLeft = SpeedRight + (InstantError * Kp) + (CumuledError * Ki);

    if(ReflectionSensorCenter)
    {
      if(ReflectionSensorLeft)
      {
        AdjustLeft = SpeedRight-0.1;
      }
      else if(ReflectionSensorRight)
      {
        AdjustRight = SpeedLeft-0.1;
      }
      else
      {
        AdjustLeft = 0;
        AdjustRight = 0;
      }
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

    InstantError = EncoderCountRight - EncoderCountLeft;
    CumuledError = CumuledError + InstantError;
  }

  MOTOR_SetSpeed(Right, 0);
  MOTOR_SetSpeed(Left, 0);

  ENCODER_Reset(Left);
  ENCODER_Reset(Right);
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
