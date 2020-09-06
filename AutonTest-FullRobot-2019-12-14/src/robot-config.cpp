#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LeftFrontMotor = motor(PORT11, ratio18_1, false);
motor LeftBackMotor = motor(PORT12, ratio18_1, false);
motor RightFrontMotor = motor(PORT1, ratio18_1, true);
motor FeederLeftMotor = motor(PORT15, ratio18_1, false);
motor FeederRightMotor = motor(PORT5, ratio18_1, false);
motor RackAndPinionMotor = motor(PORT8, ratio18_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}