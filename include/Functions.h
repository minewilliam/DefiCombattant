#include <Arduino.h>
#include <LibRobus.h>

enum {Left, Right};

/************************************************
* @brief        This function is used to turn the robot
* @param		uint16_t    : Angle on 360°
* @param		bool 	    : 0 is Left - 1 is Right
* @return 		none
*/
void Turn(uint16_t Angle, bool Side);