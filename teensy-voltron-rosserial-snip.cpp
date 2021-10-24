#include <ros.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Vector3.h>
#include <ackermann_msgs/AckermannDriveStamped.h>

std_msgs::Float32 thr_out;
std_msgs::Float32 current_steering;
geometry_msgs::Vector3 pid_coeffcients;
std_msgs::Float32 rpm;

ros::NodeHandle nh;
ros::Subscriber<geometry_msgs::Vector3> pid_sub("/PID_tune", &setPIDCoeffcients);
ros::Subscriber<ackermann_msgs::AckermannDriveStamped> sub("/control_output", &target_set);
ros::Publisher pub("/rpm", &rpm);
ros::Publisher steer_pub("/angle", &current_steering);
ros::Publisher thrpub("/throttle_out", &thr_out);

void idle_state(float controller_steering)
{
  current_steering.data = (3.14 / 2) * (controller_steering / max_steering);
}
void control_state(float controller_steering, float controller_throttle)
{
  current_steering.data = (3.14 / 2) * (controller_steering / max_steering);
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

void publishData()
{

  thr_out.data = throttle_out;
  pub.publish(&rpm);
  thrpub.publish(&thr_out);
  steer_pub.publish(&current_steering);

};

void setup()
{

  nh.getHardware()->setBaud(57600);
  nh.initNode();
  nh.subscribe(sub);
  nh.subscribe(pid_sub);
  nh.advertise(pub);
  nh.advertise(steer_pub);
  nh.advertise(thrpub);

}

void loop(){
  nh.spinOnce();
  
}