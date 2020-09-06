/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Mon Mar 25 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
// Tank Control 
// This program instructs your robot to use remote control values to move the robot. 
//
// Robot Configuration: 
// [Smart Port]    [Name]        [Type]           [Description]       [Reversed]
// Motor Port 1    FrontLeftMotor     V5 Smart Motor    Left side motor     false
// Motor Port 10   FrontRightMotor    V5 Smart Motor    Right side motor    true
// Motor Port 8    BackLeftMotor      V5 Smart Motor    Arm motor           false
// Motor Port 3    BackRightMotor     V5 Smart Motor    Claw motor          false
//
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here
vex::motor FrontLeftMotor        = vex::motor( vex::PORT1 );
vex::motor FrontRightMotor       = vex::motor( vex::PORT10, true );
vex::motor BackLeftMotor         = vex::motor( vex::PORT8 );
vex::motor BackRightMotor        = vex::motor( vex::PORT3, true );
vex::controller Controller1 = vex::controller();

// true reverses the original direction

int main() {
    // Display that the program has started to the screen.
    Brain.Screen.print("Arcade Control Program Started");
    
    
    
    // Create an infinite loop so that the program can pull remote control values every iteration.
    // This loop causes the program to run forever.
    while(1) {
      //Drive Control
      //Set the left and right motor to spin forward using the controller's Axis positions as the velocity value.
      FrontLeftMotor.spin(vex::directionType::fwd, Controller1.Axis3.position(), vex::velocityUnits::pct);
      FrontRightMotor.spin(vex::directionType::fwd, Controller1.Axis2.position(), vex::velocityUnits::pct);
      BackLeftMotor.spin(vex::directionType::fwd,Controller1.Axis3.position(), vex::velocityUnits::pct);
      BackRightMotor.spin(vex::directionType::fwd,Controller1.Axis2.position(), vex::velocityUnits::pct);
    // Sleep the task for a short amount of time to prevent wasted resources.
    vex::task::sleep(20);
    }
}



    