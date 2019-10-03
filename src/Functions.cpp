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