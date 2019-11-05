/**
 * Functions.h
 *
 * Created on: sept 27, 2019
 * Author: Gabriel
 * 
 * Description:    Prototype de Fonction de base pour que le robot puisse se déplacer.
 */

#include <Arduino.h>
#include <LibRobus.h>
#include "RobotSense.h"

#define Dumber

enum {Left, Right};
enum {Forward, Reverse};

/************************************************
* @brief        This function is used to turn the robot
* @param		uint16_t    : Angle on 360°
* @param		bool 	    : 0 is Left and 1 is Right
* @return 		none
*/
void Turn(uint16_t Angle, bool Side);


/************************************************
* @brief        This function is used to move forward or backward the robot
* @param		float       : Speed 0 to 1
* @param		float 	    : Distance to do in centimeter
* @param		bool 	    : 0 is forward and 1 is backward
* @return 		none
*/
void Move(float SpeedCommand, float DistanceToDo, bool Direction);

void GetBallOne (void);
void GetBallTwo (void);
void GetBallThree (void);
void GetBallFour (void);

void LeaveBallOne(void);
void LeaveBallTwo(void);
void LeaveBallThree(void);
void LeaveBallFour(void);