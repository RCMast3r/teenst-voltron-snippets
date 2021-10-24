#include <AutoPID.h>

double KP = 0.004;
double KI = 0.0001;
double KD = 1.0;
volatile double current_rpm, set_rpm, throttle_out;
AutoPID speedPID(&current_rpm, &set_rpm, &throttle_out, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);

void setPIDCoeffcients(geometry_msgs::Vector3 msg)
{
  if( (prevmsgx !=msg.x) ||(prevmsgy !=msg.y) || (prevmsgz !=msg.z)){
    speedPID.setGains((double)msg.x, (double)msg.y, (double)msg.z);
    prevmsgx = msg.x;
    prevmsgy = msg.y;
    prevmsgz = msg.z;
  }

}
void setup()
{

}
void target_set(const ackermann_msgs::AckermannDriveStamped &msg)
{
  if (mux_switch == 0)
  {
    digitalWrite(CONTROL_LED, LOW);
    set_rpm = msg.drive.speed;
    // set_rpm = (msg.drive.speed * 60) / (.0254 * 11); 
    if(set_rpm == 0)
    {
      speedPID.setIntegral(0);
    }
    controller_steering = max_steering * msg.drive.steering_angle * (2 / 3.14);
  }
}
void loop()
{
    // only if we are in the autonomous mode do we want to run the PID
    if(mux_switch == 0) {
      //throttle_control((float)throttle_out);
      speedPID.run();
      controller_throttle = throttle_out;
    }


}