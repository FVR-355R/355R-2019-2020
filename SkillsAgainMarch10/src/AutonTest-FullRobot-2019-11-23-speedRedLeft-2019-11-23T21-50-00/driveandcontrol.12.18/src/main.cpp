/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Wed Sep 25 2019                                           */
/*    Description:  Tank Drive                                                */
/*    This sample allows you to control the V5 Clawbot using the both         */
/*    joystick. Adjust the deadband value for more accurate movements.        */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftFrontMotor       motor         11              
// RightFrontMotor      motor         1               
// LeftBackMotor        motor         12              
// RightBackMotor       motor         2               
// FeederLeftMotor      motor         16              
// FeederRightMotor     motor         5               
// RackAndPinionMotor   motor         8               
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // Deadband stops the motors when Axis values are close to zero.
  int deadband = 5;

  // How fast the feeder motors will spin
  int FeederSpeed = 50;
  int LifterSpeed = 30;

  while (true) {
    // Get the velocity percentage of the left motor. (Axis3)
    int leftMotorSpeed = Controller1.Axis3.position();
    // Get the velocity percentage of the right motor. (Axis2)
    int rightMotorSpeed = Controller1.Axis2.position();
    // What is the state of button L1
    bool L1Down = Controller1.ButtonL1.pressing();
    // What is the state of button R1
    bool R1Down = Controller1.ButtonR1.pressing();

    bool UpArrowPushed = Controller1.ButtonUp.pressing();
    bool DownArrowPushed = Controller1.ButtonDown.pressing();

    // Set the speed of the left motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(leftMotorSpeed) < deadband) {
      // Set the speed to zero.
      LeftFrontMotor.setVelocity(0, percent);
      LeftBackMotor.setVelocity(0, percent);

    } else {
      // Set the speed to leftMotorSpeed
      LeftFrontMotor.setVelocity(leftMotorSpeed, percent);
      LeftBackMotor.setVelocity(leftMotorSpeed, percent);

    }

    // Set the speed of the right motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(rightMotorSpeed) < deadband) {
      // Set the speed to zero
      RightFrontMotor.setVelocity(0, percent);
      RightBackMotor.setVelocity(0, percent);

    } else {
      // Set the speed to rightMotorSpeed
      RightFrontMotor.setVelocity(rightMotorSpeed, percent);
      RightBackMotor.setVelocity(rightMotorSpeed, percent);

    }

    // Spin both motors in the forward direction.
    LeftFrontMotor.spin(forward);
    LeftBackMotor.spin(forward);

    RightFrontMotor.spin(forward);
    RightBackMotor.spin(forward);


//  stop motors if nobody is pressed or if BOTH are pressed
    if ( (!L1Down && !R1Down) || (L1Down && R1Down) ) {
       FeederLeftMotor.setVelocity(0,percent);
       FeederRightMotor.setVelocity(0,percent);
// L1 pressed feeds in
    } else if (L1Down && !R1Down)   {
       FeederLeftMotor.setVelocity(FeederSpeed,percent);
       FeederRightMotor.setVelocity(FeederSpeed,percent);
// R1 pressed pushes out       
    } else if (R1Down && !L1Down)   {
       FeederLeftMotor.setVelocity(-FeederSpeed,percent);
       FeederRightMotor.setVelocity(-FeederSpeed,percent);
    } else {  // should never get here
      FeederLeftMotor.setVelocity(0,percent);
      FeederRightMotor.setVelocity(0,percent);
    }
    
  // actually spin the Feeder motors

    FeederLeftMotor.spin(forward);
    FeederRightMotor.spin(forward);


//  up and down arrows
 
   if ( (!UpArrowPushed && !DownArrowPushed) || (UpArrowPushed && DownArrowPushed) ) {
       RackAndPinionMotor.setVelocity(0,percent);
      
// Up Arrow tilts it up
    } else if (UpArrowPushed && !DownArrowPushed)   {
         RackAndPinionMotor.setVelocity(LifterSpeed,percent);
       
// Down arrow tilts it down       
    } else if (DownArrowPushed && !UpArrowPushed)   {
      RackAndPinionMotor.setVelocity(-LifterSpeed,percent);
       
    } else {  // should never get here
      RackAndPinionMotor.setVelocity(0,percent);
      
    }
RackAndPinionMotor.spin(forward);




    wait(25, msec);
  }
}
