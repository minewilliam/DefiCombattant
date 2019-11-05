#include "Functions.h"
#include "RobotSense.h"
#include "Adafruit_TCS34725.h"

#define Dumb
#define A_Four
#define B_One

void setup() 
{
  BoardInit();
  RobosenseInit();
}

void loop()
{
  #ifdef Dumb
    #ifdef A_One
      GetBallOne();
    #endif

    #ifdef A_Two
      GetBallTwo();
    #endif

    #ifdef A_Three
      GetBallThree();
    #endif

    #ifdef A_Four
      GetBallFour();
    #endif
  #endif

  #ifdef Dumber
    #ifdef B_One
     LeaveBallOne();
    #endif

    #ifdef B_Two
      LeaveBallTwo();
    #endif

    #ifdef B_Three
     LeaveBallThree();
    #endif

    #ifdef B_Four
     LeaveBallFour();
    #endif
  #endif
  
  while (1);
}