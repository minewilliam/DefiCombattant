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

void Turn(uint16_t Angle, bool Side)
{
    bool ExitOne = false;
    bool ExitTwo = false;
    uint32_t EncoderCountNeeded = 0;
    uint32_t EncoderCountLeft = 0;
    uint32_t EncoderCountRight = 0;

    Angle%=360;
    EncoderCountNeeded = 7822*(uint32_t)Angle/360;

    ENCODER_Reset(Left);
    ENCODER_Reset(Right);

    if (Side==Left)
    {
        MOTOR_SetSpeed(Left,-0.15);
        MOTOR_SetSpeed(Right,0.15);
    }

    else
    {
        MOTOR_SetSpeed(Left,0.15);
        MOTOR_SetSpeed(Right,-0.15);
    }

    while (ExitOne == false || ExitTwo == false)
    {
        EncoderCountLeft = ENCODER_Read(Left);
        EncoderCountRight = ENCODER_Read(Right);

        if (Side == Left)
        {
            if (EncoderCountLeft == ~EncoderCountNeeded)
            {
                MOTOR_SetSpeed(Left,0);
                ExitOne = true;
            }

            if (EncoderCountRight == EncoderCountNeeded)
            {
                MOTOR_SetSpeed(Right,0); 
                ExitTwo = true;
            } 
        }
        
        else
        {
            if (EncoderCountLeft == EncoderCountNeeded)
            {
                MOTOR_SetSpeed(Left,0);
                ExitOne = true;
            }

            if (EncoderCountRight == ~EncoderCountNeeded)
            {
                MOTOR_SetSpeed(Right,0); 
                ExitTwo = true;
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

  float Kp = 0;
  float Ki = 0.0001;

  int EncodeurCountRight = 0;
  int EncodeurCountLeft = 0;

  int InstantError = 0;
  int CumuledError = 25;
    
  
  while (DistanceDone < DistanceToDo)
  {
  
    if (DistanceToDo - DistanceDone > 30 and SpeedRight < SpeedCommand)
    {
      SpeedRight = SpeedRight + 0.02; //Acceleration
    }
    else if (DistanceToDo - DistanceDone < 30 and SpeedRight > 0.15)
    {
      SpeedRight = SpeedRight - 0.02; //Deceleration
    }
    else
    {
      SpeedRight = SpeedCommand;
    }
    
    SpeedLeft = SpeedRight + (InstantError * Kp) + (CumuledError * Ki);

    if (Direction == Reverse)
    {
      MOTOR_SetSpeed(RIGHT, SpeedRight * -1);
      MOTOR_SetSpeed(LEFT, SpeedLeft * -1);
    }
    else if (Direction == Forward)
    {
      MOTOR_SetSpeed(RIGHT, SpeedRight);
      MOTOR_SetSpeed(LEFT, SpeedLeft);
    }

    delay(100);

    EncodeurCountRight = abs(ENCODER_ReadReset(RIGHT));
    EncodeurCountLeft = abs(ENCODER_ReadReset(LEFT));

    DistanceDone = DistanceDone + (EncodeurCountRight + EncodeurCountLeft) / 2 / 133.4;

    InstantError = EncodeurCountRight - EncodeurCountLeft;
    CumuledError = CumuledError + InstantError;

    //Serial.println(DistanceDone);
  }

  MOTOR_SetSpeed(RIGHT, 0);
  MOTOR_SetSpeed(LEFT, 0);
}