/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       SDV Template                                              */
/*    Author:       VEX Robotics                                              */
/*    Description:  Blank Pre-Configured V5 SDV Project                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "vision-config.h"

using namespace vex;

brain        Brain;
motor        LeftMotor(PORT1, gearSetting::ratio18_1, false);
motor        RightMotor(PORT2, gearSetting::ratio18_1, true);
drivetrain   Drivetrain = drivetrain(LeftMotor, RightMotor, 145, 200, distanceUnits::mm);
// Vision Sensor is already configured as 'Vision5' on PORT5

int main() {
}
