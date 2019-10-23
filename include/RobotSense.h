/**
 * RobotSense.h
 *
 * Created on: Oct 17, 2019
 * Author: William
 * 
 * Description:  Librairie des capteurs du robot
 */

#include <Arduino.h>
#include <LibRobus.h>

#define Dumb

#define REFLECTION_SENSOR_LEFT 41
#define REFLECTION_SENSOR_RIGHT 42
#define REFLECTION_SENSOR_CENTER 43

int ReflectionSensorLeft,ReflectionSensorRight,ReflectionSensorCenter;

enum {Left, Right};
enum {Forward, Reverse};

enum Color
{
    Red,
    Green,
    Blue,
    Yellow,
    Black,
    White
};

/**
 * @brief Initializes pins on the arduino.
 * 
 */
void RobosenseInit();

/**
 * @brief Returns value from the color sensor
 * 
 * @return Colors enum 
 */
Color COLOR_Read();

/**
 * @brief This function is used to move forward or backward the robot
 * 
 * @param SpeedCommand Speed 0 to 1
 * @param DistanceToDo Distance to do in centimeter
 * @param Direction 0 is forward and 1 is backward
 */
void FollowLine(float SpeedCommand, float DistanceToDo, bool Direction);

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool LineFound();

/**
 * @brief Returns the distance sensed by the infrared sensor
 * 
 * @return int 
 */
int IR_Distance();

