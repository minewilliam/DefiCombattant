#include <Arduino.h>
#include <LibRobus.h>

enum {Left, Right};
void Turn(uint16_t Angle, bool Side);

void setup() 
{
  BoardInit();
}

void loop() 
{
  Turn(90, Left);
  delay(1000);
  Turn(90, Right);
  delay(1000);
}

void Turn(uint16_t Angle, bool Side)
{
  bool ExitOne = false;
  bool ExitTwo = false;
  uint32_t EncoderCountNeeded = 0;
  uint32_t EncoderCountLeft = 0;
  uint32_t EncoderCountRight = 0;

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
     if (EncoderCountLeft == (0xFFFFFFFF - EncoderCountNeeded))
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

      if (EncoderCountRight == (0xFFFFFFFF - EncoderCountNeeded))
      {
        MOTOR_SetSpeed(Right,0); 
        ExitTwo = true;
      } 
    }
  }
  ENCODER_Reset(Left);
  ENCODER_Reset(Right);
}

void MoveForward (float Speed)
{

}