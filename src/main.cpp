#include "Functions.h"
#include "RobotSense.h"

#define Dumber
#define One

void setup() 
{
  BoardInit();
  RobosenseInit();
}

void loop()
{
  while (!ROBUS_IsBumper(3));

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
  //delay(32000);
  delay(5000);
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