/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       dmason                                                    */
/*    Created:      Fri Oct 18 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftFrontMotor       motor         11              
// LeftBackMotor        motor         12              
// RightFrontMotor      motor         1               
// RightBackMotor       motor         2               
// FeederLeftMotor      motor         16              
// FeederRightMotor     motor         5               
// RackAndPinionMotor   motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

// ideally this would be in another .h file

void MoveForward(float, int);
void FeederAction(float, bool);
void RotateClockWise(float, int);
void LiftStacker(float, bool);
void Strafe(float, int);

//Defining some constants we measure

float const WheelRadiusInInches = 2.0;
float const Pi = 3.14159267;

// something to measure -- its the diagonal distance between wheels 
// through the CENTER of the robot.  DIAMETER of the robot
float const DiagWheelBaseInInches = 21.75;

bool StopFeeder = true;


using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

// commenting out to test
//    LiftStacker(0.35,true);

    FeederAction(42,true);
   
    // These were a test -- don't use!
    //Strafe(20.0,50);
    //Strafe(-20.0,50);

    MoveForward(15.0, 175);
    MoveForward(34.0, 40);

    
    // slow feeder before turning
    FeederAction(20, true);

    // Got cubes, now turn around 

    RotateClockWise(180.0,100);

    // Move to 45 degrees from goal

    MoveForward(28.0,125);

    // Now rotate 45 degrees

    RotateClockWise(-45.0,100);

    // Move forward fast partway
  
    MoveForward(15,125);

    // Stop feeder and slow down to get in goal

    FeederAction(0, false);    

    MoveForward(5.3,50);

    // Now place cubes, raise stacker

    LiftStacker(2.0,true);

    // Reverse feeder to push cubes down


    FeederAction(40, false);    
  
    // Tilt feeder back a bit, feeder is still spinning

    LiftStacker(1.0, false );

    // Now back robot away

    MoveForward(-18.0, 30);

//   This is the end of the regular match autonomous 

    FeederAction(0, true);


//  Now rotate to point toward blue

    RotateClockWise(-135.0,100);

//  Move stacker back to loading position

    LiftStacker(0.9, false );

// Use wall to line back up again

    Strafe(25.0,90);
    Strafe(-30.0,50);

    // Back up a bit in case we're too close to cubes

    MoveForward(-8.0, 30);

    Strafe(-18.0,50);

    // Go forward to suck up cubes

    FeederAction(40, true);    
    MoveForward(33.0, 35);


//  Slow down feeder and rotate toward red left goal
    FeederAction(20, true);    

    RotateClockWise(-90.0,50);

//  

    FeederAction(0, true);


//  Strafe back to wall

    Strafe(-50.0,50);

//  Spin up feeder again in case we can get a cube   
    FeederAction(30, true);


    // Move toward other goal partway

    MoveForward(30.0, 70);


//  Come back out a bit to avoid bolts on wall  
    Strafe(2.0,50);


//  Head towards goal rest of the way
    MoveForward(40.0, 70);

//  Stop the feeder
    FeederAction(0, true);


//  Near goal, slow down -- want to hit the wall
    MoveForward(6.0, 20);

//  Now back up a bit and get ready to place
//    MoveForward(-8.0, 10);



 // Reverse feeder to push cubes down


    FeederAction(20, false); 

    // Now place cubes, raise stacker
    // somehow this is a bit different on this side

         

    LiftStacker(2.0,true);

// Reverse feeder to push cubes down


    FeederAction(40, false); 

  
    // Tilt feeder back a bit, feeder is still spinning

    LiftStacker(1.0, false );

    // Now back robot away

    MoveForward(-18.0, 30);


    
}


void LiftStacker(float nRotations, bool direction){
  //float liftAngle = nRotations / 360; 
  if (direction == 1) {
    RackAndPinionMotor.spinToPosition(nRotations,turns,true);
  } else{
    RackAndPinionMotor.spinToPosition(-nRotations,turns,true);
  }

  RackAndPinionMotor.setPosition(0,turns);

}

void FeederAction(float FeederSpeed, bool direction){
  if (direction == 1) {
    FeederLeftMotor.setVelocity(FeederSpeed,percent);
    FeederRightMotor.setVelocity(FeederSpeed,percent);
    FeederLeftMotor.spin(forward);
    FeederRightMotor.spin(forward);
  } else{
   FeederLeftMotor.setVelocity(-FeederSpeed,percent);
    FeederRightMotor.setVelocity(-FeederSpeed,percent);
    FeederLeftMotor.spin(forward);
    FeederRightMotor.spin(forward);
  }
}

// Function to move forward, howfar is in INCHES

void MoveForward(float howfar, int howfast) {

// need to convert inches to number of rotations and then to degrees
// number of rotations is how many circumferences the argument howfar is

    float nRotations = howfar / Pi / WheelRadiusInInches / 2.0;

// motion speed
    int motorvelocity = howfast;

    //float RotationDegrees = nRotations * 360.0;

// What this is doing:
// spinToPosition tells it to spin the wheel until it hits the requested position
// the second argument is "degrees" which is a constant that tells it the angle is 
// in -- believe it or not -- degrees
// the last argument tells it to wait or not before moving to the next one.
// The default is true.  This means if we leave the default with the four statements
// below, it will rotate the first wheel, then the next, then the next, and the last
// If we set false, it will get the motor started, then move on to the next statement. 
// So here we set the first 3 to false, but the last one to true.  This should
// move all 4 at essentially the same time, but wait until the last one is done.
// It should move the drivetrain as a whole here. 

    LeftFrontMotor.spinToPosition(nRotations,turns,motorvelocity,rpm, false); // false keeps spinning
    RightFrontMotor.spinToPosition(nRotations,turns,motorvelocity,rpm,false); // also false
    LeftBackMotor.spinToPosition(nRotations,turns,motorvelocity,rpm,false); // also false
    RightBackMotor.spinToPosition(nRotations,turns,motorvelocity,rpm,true); // now true


// attempt to re-set motor encoder.Brain
LeftFrontMotor.setPosition(0, turns); 
RightFrontMotor.setPosition(0, turns);
LeftBackMotor.setPosition(0, turns);
RightBackMotor.setPosition(0, turns);


return;

}



// Function to strafe (comes from MoveForward), howfar is in INCHES
// Positive is to the right, negative is to the left




void Strafe(float howfar, int howfast) {

// need to convert inches to number of rotations and then to degrees
// number of rotations is how many circumferences the argument howfar is

    float nRotations = howfar / Pi / WheelRadiusInInches / 2.0;

// motion speed
    int motorvelocity = howfast;

    //float RotationDegrees = nRotations * 360.0;

// What this is doing:
// spinToPosition tells it to spin the wheel until it hits the requested position
// the second argument is "degrees" which is a constant that tells it the angle is 
// in -- believe it or not -- degrees
// the last argument tells it to wait or not before moving to the next one.
// The default is true.  This means if we leave the default with the four statements
// below, it will rotate the first wheel, then the next, then the next, and the last
// If we set false, it will get the motor started, then move on to the next statement. 
// So here we set the first 3 to false, but the last one to true.  This should
// move all 4 at essentially the same time, but wait until the last one is done.
// It should move the drivetrain as a whole here. 

// Now modified this to strafe -- which is moving left to right.  To do that 
// make the front and back wheels move in opposite directions.Brain

// Move right =
//  RightFrontMotor reverse
//  RightBackMotor  forward
//  LeftFrontMotor  forward
//  LeftBackMotor   reverse

//  Changing sign of nRotations to do this

    LeftFrontMotor.spinToPosition(nRotations,turns,motorvelocity,rpm, false); // false keeps spinning
    RightFrontMotor.spinToPosition(-nRotations,turns,motorvelocity,rpm,false); // also false
    LeftBackMotor.spinToPosition(-nRotations,turns,motorvelocity,rpm,false); // also false
    RightBackMotor.spinToPosition(nRotations,turns,motorvelocity,rpm,true); // now true


// attempt to re-set motor encoder.Brain
LeftFrontMotor.setPosition(0, turns); 
RightFrontMotor.setPosition(0, turns);
LeftBackMotor.setPosition(0, turns);
RightBackMotor.setPosition(0, turns);


return;

}





// Function to rotate the robot clockwise, howfar is in DEGREES

void RotateClockWise(float howfar, int howfast) {

// The idea is to rotate the motors enough to have them travel along
// the circumference of the circle drawn by the wheels around the
// center of the robot. 

    float RobotCircumference = Pi * DiagWheelBaseInInches;

// now we convert howfar into a number of ROBOT rotations

    float RobotRotations = howfar / 360.0; 

// how many wheel rotations is one robot rotation

    float WheelCircumference = Pi * WheelRadiusInInches * 2.0;

// how many times the wheel goes around to travel the circumference (one robot rotation)

    float WheelRotationsInRobotRotation = RobotCircumference / WheelCircumference;

// to turn clockwise, left wheels drive forward, right wheels drive backward.Brain

    float WheelRotations = RobotRotations * WheelRotationsInRobotRotation;

// and back to degrees

//    float LeftWheelDegrees = WheelRotations * 360.0;
//    float RightWheelDegrees = 0.0-LeftWheelDegrees;

//  Now we drive!

    LeftFrontMotor.spinToPosition(WheelRotations,turns,howfast, rpm, false); 
    LeftBackMotor.spinToPosition(WheelRotations,turns,howfast,rpm,false);  

    RightFrontMotor.spinToPosition(-WheelRotations,turns,howfast,rpm,false);  
    RightBackMotor.spinToPosition(-WheelRotations,turns,howfast,rpm,true);  


    // attempt to re-set motor encoder.Brain
LeftFrontMotor.setPosition(0, turns); 
RightFrontMotor.setPosition(0, turns);
LeftBackMotor.setPosition(0, turns);
RightBackMotor.setPosition(0, turns); 

}