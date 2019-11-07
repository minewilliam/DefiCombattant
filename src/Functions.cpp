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

    else if (DistanceToDo - DistanceDone <= 30 )
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

int16_t LocateBall(void)
{
  const float rangeMax = 80;
  const float rangeMin = 20;
  const uint16_t turnAngle_Max = 20;
  const int turnIncrement = 1; //Increment in degrees
  const int sensorPoolingRate = 100; //Delay in ms

  int16_t angleOut = 0;
  bool ballFound = false;
  uint16_t turnAngle = 0;
  float range = 10000;

  uint16_t timer = millis();

  Turn(turnAngle_Max, RIGHT);

  while(!ballFound)
  {
    if(timer+sensorPoolingRate <= millis())
    {
    float currentRange = IR_Distance();
      if(rangeMin <= currentRange && currentRange <= rangeMax)
      {
        if(currentRange < range)
        {
          if(range < rangeMax)
          {
            angleOut = turnAngle_Max-turnAngle;
            ballFound = true;
          }
          else
          {
            range = currentRange;
            angleOut = turnAngle_Max-turnAngle;
          }
        }
        else
        {
          angleOut = turnAngle_Max-turnAngle;
          ballFound = true;
        }
        
      }

      if(turnAngle >= turnAngle_Max*2)
      {
        Turn(turnAngle_Max+16,RIGHT);
        ballFound = true;
      }
      
      timer = millis();
    }

    if(!ballFound)
    {
      Turn(turnIncrement, LEFT);
      turnAngle += turnIncrement;
    }
  }
  return angleOut;
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
  
    FollowLine(0.3, Reverse);
  }

  FindBall();
  Move(0.4,1,Forward);
  MoveBall();

  Move(0.4, 15, Forward);

  Turn(135,Left);
  MOTOR_SetSpeed(Left, -0.2);
  MOTOR_SetSpeed(Right, 0.2);
  while (SCenter)
  {
    SCenter = digitalRead(REFLECTION_SENSOR_CENTER);
  }

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
  
    FollowLine(0.3, Reverse);
  }

  Move(0.4,8,Reverse);

  MOTOR_SetSpeed(Left, 0);
  MOTOR_SetSpeed(Right, 0);
  delay(500);
  LeverUp();

  Move(1, 30, Forward);
  Turn(45,Left);
  Move(1, 30, Forward);
  Turn(90,Left);
  Move(1, 50, Forward);
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
  
    FollowLine(0.3, Reverse);
  }

  FindBall();
  Move(0.4,1,Forward);
  MoveBall();

  Move(0.4, 15, Forward);

  Turn(135,Left);
  MOTOR_SetSpeed(Left, -0.2);
  MOTOR_SetSpeed(Right, 0.2);
  while (SCenter)
  {
    SCenter = digitalRead(REFLECTION_SENSOR_CENTER);
  }

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
  
    FollowLine(0.3, Reverse);
  }

  Move(0.4,8,Reverse);
  
  MOTOR_SetSpeed(Left, 0);
  MOTOR_SetSpeed(Right, 0);
  delay(500);
  LeverUp();

  Move(1, 30, Forward);
  Turn(45,Right);
  Move(1, 30, Forward);
  Turn(90,Right);
  Move(1, 50, Forward);
}

void GetBallThree (void)
{
  int SLeft, SCenter, SRight = 0;

  Turn(90,Left);
  FindLine(Right);
  Move(0.4,15,Reverse);
  Turn(100,Left);
  Move(0.4,40,Reverse);
  FindLine(Right);
  Move(0.4,15,Reverse);
  Turn(50,Right);
  
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
  
    FollowLine(0.3, Reverse);
  }

  FindBall();
  Move(0.4,1,Forward);
  MoveBall();

  Move(0.4, 15, Forward);

  Turn(135,Left);
  MOTOR_SetSpeed(Left, -0.2);
  MOTOR_SetSpeed(Right, 0.2);
  while (SCenter)
  {
    SCenter = digitalRead(REFLECTION_SENSOR_CENTER);
  }

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
  
    FollowLine(0.3, Reverse);
  }

  MOTOR_SetSpeed(Left, 0);
  MOTOR_SetSpeed(Right, 0);
  LeverUp();

  Move(1, 30, Forward);
  Turn(45,Right);
  Move(1, 30, Forward);
  Turn(90,Right);
  Move(1, 50, Forward);
}

void GetBallFour (void)
{
  int SLeft, SCenter, SRight = 0;

  Turn(90,Right);
  FindLine(Left);
  Move(0.4,15,Reverse);
  Turn(100,Right);
  Move(0.4,40,Reverse);
  FindLine(Left);
  Move(0.4,15,Reverse);
  Turn(50,Left);
  
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
  
    FollowLine(0.3, Reverse);
  }

  FindBall();
  Move(0.4,1,Forward);
  MoveBall();

  Move(0.4, 15, Forward);

  Turn(135,Left);
  MOTOR_SetSpeed(Left, -0.2);
  MOTOR_SetSpeed(Right, 0.2);
  while (SCenter)
  {
    SCenter = digitalRead(REFLECTION_SENSOR_CENTER);
  }

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
  
    FollowLine(0.3, Reverse);
  }

  MOTOR_SetSpeed(Left, 0);
  MOTOR_SetSpeed(Right, 0);
  LeverUp();

  Move(1, 30, Forward);
  Turn(45,Left);
  Move(1, 30, Forward);
  Turn(90,Left);
  Move(1, 50, Forward);
}

void LeaveBallOne(void)
{
  int SLeft, SCenter, SRight = 0;

  int16_t Place = LocateBall();

  Move(0.4,6,Reverse);
  delay(500);
  Turn(Place+180, RIGHT);

  FindBall();
  MoveBall();
  Move(0.4,15,Forward);
  Turn(180-Place,Right);
  Move(0.4,90,Forward);
  Turn(85,Right);
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
  Move(0.4,50,Reverse);

  MOTOR_SetSpeed(Left, 0);
  MOTOR_SetSpeed(Right, 0);
  
  LeverUp();

  Move(0.4,5,Forward);

  MOTOR_SetSpeed(Left, 0);
  MOTOR_SetSpeed(Right, 0);
}

void LeaveBallTwo(void)
{
  int SLeft, SCenter, SRight = 0;

  int16_t Place = LocateBall();

  Move(0.4,6,Reverse);
  delay(500);
  Turn(Place+180, RIGHT);
  FindBall();
  MoveBall();
  Move(0.4,15,Forward);
  Turn(180-Place,Right);
  Move(0.4,90,Forward);
  Turn(75,Left);
  Move(0.4,10,Reverse);
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
  Move(0.4,50,Reverse);

  MOTOR_SetSpeed(Left, 0);
  MOTOR_SetSpeed(Right, 0);

  LeverUp();

  Move(0.4,5,Forward);

  MOTOR_SetSpeed(Left, 0);
  MOTOR_SetSpeed(Right, 0);
}

void LeaveBallThree(void)
{
  int SLeft, SCenter, SRight = 0;

  int16_t Place = LocateBall();

  Move(0.4,6,Reverse);
  delay(500);
  Turn(Place+180, RIGHT);
  FindBall();
  MoveBall();
  Move(0.4,30,Forward);  
  
  Turn(75+Place,Left);
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
  Move(0.4,50,Reverse);

  MOTOR_SetSpeed(Left, 0);
  MOTOR_SetSpeed(Right, 0);
  
  LeverUp();

  Move(0.4,5,Forward);

  MOTOR_SetSpeed(Left, 0);
  MOTOR_SetSpeed(Right, 0);
}

void LeaveBallFour(void)
{
  int SLeft, SCenter, SRight = 0;

  int16_t Place = LocateBall();

  Move(0.4,6,Reverse);
  delay(500);
  Turn(Place+180, RIGHT);

  FindBall();
  MoveBall();
  Move(0.4,30,Forward);
  Turn(75+Place,Right);
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
  Move(0.4,50,Reverse);

  MOTOR_SetSpeed(Left, 0);
  MOTOR_SetSpeed(Right, 0);
  
  LeverUp();

  Move(0.4,5,Forward);

  MOTOR_SetSpeed(Left, 0);
  MOTOR_SetSpeed(Right, 0);
}