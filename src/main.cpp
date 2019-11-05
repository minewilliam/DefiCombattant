#include "Functions.h"
#include "RobotSense.h"
#include "Adafruit_TCS34725.h"

#define Dumber
#define Four

void setup() 
{
  BoardInit();
  RobosenseInit();
}

void loop()
{
  while (!ROBUS_IsBumper(2));

  #ifdef Dumb
    #ifdef One
      GetBallOne();
    #endif

    #ifdef Two
      GetBallTwo();
    #endif

    #ifdef Three
      GetBallThree();
    #endif

    #ifdef Four
      GetBallFour();
    #endif
  #endif

  #ifdef Dumber
    #ifdef One
     LeaveBallOne();
    #endif

    #ifdef Two
      LeaveBallTwo();
    #endif

    #ifdef Three
     LeaveBallThree();
    #endif

    #ifdef Four
     LeaveBallFour();
    #endif
  #endif
  
  while (1);
}