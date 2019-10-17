#include <Arduino.h>
#include <LibRobus.h>
#include "Functions.h"


void setup() 
{
  BoardInit();
}

void loop() 
{
  //Aller
  Move(0.4,120,Forward);
  delay(250);

  Turn(90,Left);
  delay(250);
  
  Move(0.4,105,Forward);
  delay(250);
  
  Turn(90,Right);
  delay(250);
  
  Move(0.4,50,Forward);
  delay(250);

  Turn(90,Right);
  delay(250);

  Move(0.4,50,Forward);
  delay(250);

  Turn(93,Left);
  delay(250);

  Move(0.4,200,Forward);
  delay(250);

  Turn(90,Right);
  delay(250);

  Move(0.4,42,Forward);
  delay(250);

  Turn(90,Left);
  delay(250);

  Move(0.4,150,Forward);
  delay(250);

  //Retour
  Turn(180,Left);
  delay(250);

  Move(0.4,150,Forward);
  delay(250);
  //ballon
  Move(0.6,110,Forward);
  delay(250);

  /*Turn(180,Right);
  delay(250);

  Move(0.4,97,Forward);

  Turn(90,Left); //left pcq il revient pour aller retour
  delay(250);

  Move(0.4,40,Forward);
  delay(250);  

  Turn(90,Left);
  delay(250);

  Move(0.4,200,Forward);
  delay(250);

  Turn(90,Right);
  delay(250);

  Move(0.4,50,Forward);
  delay(250);

  Turn(90, Left);
  delay(250);

  Move(0.4,50,Forward);
  delay(250);

  Turn(92, Left);
  delay(250);

  Move(0.4,105,Forward);
  delay(250);

  Turn(90, Right);
  delay(250);

  Move(0.4,120,Forward);
  delay(250);*/

  while(1);
}