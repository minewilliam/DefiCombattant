/*
 * Functions.c
 *
 *  Created on: Oct 27, 2019
 *      Author: Gabriel
 * 
 *  Description:    Fonctions de base pour que le robot
 *                  puisse se déplacer.
 */

#include "Functions.h"
#include <Arduino.h>
#include <LibRobus.h>

#define Dumb

void Turn(uint16_t Angle, bool Side)
{
  bool ExitLeft = false;
  bool ExitRight = false;
  uint32_t EncoderCountNeeded = 0;
  uint32_t EncoderCountLeft = 0;
  uint32_t EncoderCountRight = 0;

  Angle%=360;

  #ifdef Dumb
    EncoderCountNeeded = 7822*(uint32_t)Angle/360;
  #endif

  #ifdef Dumber
    EncoderCountNeeded = 7820*(uint32_t)Angle/360;
  #endif
  
  ENCODER_Reset(Left);
  ENCODER_Reset(Right);

  if (Side==Left)
  {
    #ifdef Dumb
      MOTOR_SetSpeed(Left,-0.15);
      MOTOR_SetSpeed(Right,0.15);
    #endif

    #ifdef Dumber
      MOTOR_SetSpeed(Left,-0.15);
      MOTOR_SetSpeed(Right,0.1625);
    #endif
  }

  else
  {
    #ifdef Dumb
      MOTOR_SetSpeed(Left,0.16);
      MOTOR_SetSpeed(Right,-0.15);
    #endif

    #ifdef Dumber
      MOTOR_SetSpeed(Left,0.15);
      MOTOR_SetSpeed(Right,-0.15);
    #endif
  }

  while (ExitLeft == false || ExitRight == false)
  {
    EncoderCountLeft = ENCODER_Read(Left);
    EncoderCountRight = ENCODER_Read(Right);

    if (Side == Left)
    {
      if (EncoderCountLeft == ~EncoderCountNeeded)
      {
        MOTOR_SetSpeed(Left,0);
        ExitLeft = true;
      }

      if (EncoderCountRight == EncoderCountNeeded)
      {
        MOTOR_SetSpeed(Right,0); 
        ExitRight = true;
      } 
    }
        
    else
    {
      if (EncoderCountLeft == EncoderCountNeeded)
      {
        MOTOR_SetSpeed(Left,0);
        ExitLeft = true;
      }

      if (EncoderCountRight == ~EncoderCountNeeded)
      {
        MOTOR_SetSpeed(Right,0); 
        ExitRight = true;
      } 
    }
  }
  ENCODER_Reset(Left);
  ENCODER_Reset(Right);
}

void Move(float SpeedCommand, float DistanceToDo, bool Direction)
{
  float DistanceDone = 0;

  float SpeedRight = 0;
  float SpeedLeft = 0;

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

    if (Direction == Reverse)
    {
      MOTOR_SetSpeed(Right, SpeedRight * -1);
      MOTOR_SetSpeed(Left, SpeedLeft * -1);
    }
    else if (Direction == Forward)
    {
      MOTOR_SetSpeed(Right, SpeedRight);
      MOTOR_SetSpeed(Left, SpeedLeft);
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