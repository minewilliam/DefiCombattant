/**
 * @file Cones.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-12-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */


/*----------Includes----------*/
#include "Cones.h"
#include <LibRobus.h>
/*----------Defines-----------*/

/*----------Usings------------*/
using namespace std;

/*---------Variables----------*/


/*---------Prototypes---------*/

void InitCone(void)
{
    SERVO_SetAngle(2,0);
}

void PlaceCone(void)
{
    SERVO_SetAngle(2,45);
    delay(200);
    SERVO_SetAngle(2,0);
}
