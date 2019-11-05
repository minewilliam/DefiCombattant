#include "Functions.h"
#include "RobotSense.h"
#include "Adafruit_TCS34725.h"

#define Dumb
#define One

void setup() 
{
  BoardInit();
  RobosenseInit();
}

void loop()
{
  while (!ROBUS_IsBumper(2));

  int16_t whereThatBallAt = LocateBall();

  if(whereThatBallAt < 0)
  {
    Turn(whereThatBallAt+180, RIGHT);
  }
  else
  {
    Turn(whereThatBallAt+180, LEFT);
  }
  


  /*
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
  #endif*/
  
  //while (1);
}