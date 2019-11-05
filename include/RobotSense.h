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

#define Dumber

#define REFLECTION_SENSOR_LEFT 43
#define REFLECTION_SENSOR_RIGHT 41
#define REFLECTION_SENSOR_CENTER 42
#define REFLECTION_SENSOR_UP 40

/**
 * @brief Initializes pins on the arduino.
 * 
 */
void RobosenseInit();

/**
 * @brief This function is used to move until it found a line
 * 
 * @param Side 0 is Left and 1 is Right
 */
void FindLine (bool Side);

/**
 * @brief This function is used to move until it found a line
 */
void FindBall(void);

/**
 * @brief This function is used to move forward or backward the robot
 * 
 * @param SpeedCommand Speed 0 to 1
 * @param Direction 0 is forward and 1 is backward
 */
void FollowLine(float SpeedCommand, bool Direction);

/**
 * @brief Lever le levier
 */
void LeverUp(void);

/**
 * @brief Attack the ball
 */
void Impale(void);


/**
 * @brief Lever la balle pour pouvoir bouger avec la balle
 */
void MoveBall(void);
 
/**
 * @brief Read the IR sensor and return if something is there
 * 
 * @return True if something is under the sensor 
 */
 bool IRSensor(void);