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
#include <Adafruit_TCS34725.h>

#define Dumb

#define colorA 
#define colorB

#define N_E Yellow
#define N_W Blue
#define S_E Red
#define S_W Green

#define REFLECTION_SENSOR_LEFT 43
#define REFLECTION_SENSOR_RIGHT 41
#define REFLECTION_SENSOR_CENTER 42
#define REFLECTION_SENSOR_UP 40



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
 * @param Direction 0 is forward and 1 is backward
 */
bool FollowLine(float SpeedCommand, bool Direction);

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

/**
 * @brief Lever le levier
 */
void LeverUp(void);

/**
 * @brief Baisser le levier
 */
void Impale(void);
 
 /**LEcteur infrarouge **/
 bool IRSensor(void);