#include "ODriveTeensyCAN.h"
ODriveTeensyCAN odrive;
//ODRIVE STUFF
//on the odrive I am using node ids 3 and 5 (this is for the CAN connection to the odrive)
int axis_steering = 3;
int axis_braking = 5;
float controller_steering;
float controller_throttle;
SimpleTimer check_odrive;
// DOES NOT WORK
void checkOdrive()
{
  if (odrive.GetAxisError(axis_braking) != 0 || odrive.GetAxisError(axis_steering) != 0)
  {
    odrive_st = error;
  }
}

void brake(float b_val)
{
  float val = max_brake * b_val;
  odrive.SetTorque(axis_braking, -val);
}
void control_state(float controller_steering, float controller_throttle)
{
  odrive.SetPosition(axis_steering, controller_steering);
  
  if ((controller_throttle - controller_deadband) > 0)
  {
    brake(0);
    throttle_control(controller_throttle);
  }
  else if (controller_throttle < 0)
  {
    throttle_control(0.0003);
    brake(controller_throttle);
  }
  else
  {
    brake(0);
    throttle_control(0.0003);
  }
}
void setup()
{

  check_odrive.setInterval(250, checkOdrive);

}
void loop()
{
  control_state(controller_steering, controller_throttle);
  check_odrive.run();
}