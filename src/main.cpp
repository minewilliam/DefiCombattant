#include <Arduino.h>
#include <LibRobus.h>
#include <PID_v1.h>

//!Placeholder value
//#define STEPSPERMETER 20000 //Encoder steps over one meter
#define STEPSPERTURN 3200
#define MOTOR_MINSPEED 0.15
#define MOTOR_TOPSPEED 0.6
#define MOTOR_ACCELERATION 1.2

//Positions in centimeters
//X:Left-Right
//Y:Forward-Back
int CurrentPosition[] = {0,0};
int Coordinates[][2] = {{50,0},{50,50},{0,50},{0,0}};


double Speed_R, Speed_L;
int64_t Timer1, Timer2;
float PrintT = 100;
double Setpoint = 0;
double RightEncoder, LeftEncoder;

PID PID_Right(&RightEncoder,&Speed_R,&Setpoint,0.01,0.01,0,DIRECT);
PID PID_LEFT(&LeftEncoder,&Speed_L,&Setpoint,0.01,0.01,0,DIRECT);

//bool setAngle(int Motor, float Angle);

void setup() {
  BoardInit();
  delay(2000);
  Timer1 = millis();
  Timer2 = millis();

  PID_LEFT.SetMode(AUTOMATIC);
  PID_Right.SetMode(AUTOMATIC);
  Setpoint = 6400;

  Serial.println("Start");
  ENCODER_Reset(RIGHT);
  ENCODER_Reset(LEFT);
}

void loop() {

  LeftEncoder = (double)ENCODER_Read(LEFT);
  RightEncoder = (double)ENCODER_Read(RIGHT);

  PID_Right.SetTunings(0.008,0.001,0);
  PID_LEFT.SetTunings(0.008,0.001,0);
  PID_LEFT.SetOutputLimits(0,100);
  PID_Right.SetOutputLimits(0,100);
  PID_LEFT.Compute();
  PID_Right.Compute();

  MOTOR_SetSpeed(RIGHT, Speed_R*2/100-1);
  MOTOR_SetSpeed(LEFT, Speed_L*2/100-1);

  if(Timer1 + PrintT <= millis())
  {
    Serial.println(Speed_R*2/100-1);
    Timer1 = millis();
  }

  if(Timer2 + 3000 <= millis())
  {
    if(Setpoint == 6400)
    {
      Setpoint = 0;
    }
    else
    {
      Setpoint = 6400;
    }

    Timer2 = millis();
  }
}

/*
bool setAngle(int Motor, float Angle)
{
  float angleSteps = (Angle*STEPSPERTURN)/360;
  MOTOR_SetSpeed(Motor, Speed);
  if(angleSteps <= ENCODER_Read(Motor))
  {
    MOTOR_SetSpeed(Motor, 0);
    return true;
  }
  else
  {
    return false;
  }
}
*/


