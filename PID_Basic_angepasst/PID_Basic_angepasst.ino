/********************************************************
 * PID Basic Example
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

#include <PID_v1.h>
#include <AFMotor.h>

AF_DCMotor motor(2);

//Define Variables we'll be connecting to
double Setpoint, Input, Output;
int u, u_stern;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint,0.5,0.4,0.04, DIRECT);

void setup()
{
  motor.setSpeed(255);
 
  motor.run(RELEASE);
  myPID.SetOutputLimits(-255, 255);
  //initialize the variables we're linked to
  Input = (double) analogRead(4);
  Setpoint = (double) analogRead(5);
  
  //Serial.begin(115200);

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  Input = analogRead(4);
  Setpoint = analogRead(5);
  myPID.Compute();
  //Serial.println(Output);
  u=(int) Output;
    if (u>24) {
    motor.run(FORWARD);
    //Serial.println("FORWARD");
    //u_stern = map(u, 0,255, 24, 255);
    motor.setSpeed(u);
  }
  else if (u<-24){
    motor.run(BACKWARD);
    //Serial.println(BACKWARD);
    //u_stern = map(u, 0,-255, -24, -255);
    motor.setSpeed(-u);
    //u=-u;
  }
  else {
    motor.run(RELEASE);
  }
}


