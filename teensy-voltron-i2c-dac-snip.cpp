#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 digital_throttle;


void throttle_control(float t_val)
{
  int controller_throttle = maxthrottle * t_val;
  if(controller_throttle >= 0){
    bool test = digital_throttle.setVoltage(controller_throttle, false);
    current_throttle = controller_throttle;
    //Serial.println(current_throttle);
    //analogWrite(throttle, (int)controller_throttle);
  } else {
    bool test = digital_throttle.setVoltage(0, false);
  }

}
void control_state(float controller_steering, float controller_throttle)
{
  if ((controller_throttle - controller_deadband) > 0)
  {
    brake(0);
    throttle_control(controller_throttle);
  }
}


void setup()
{
  digital_throttle.begin(MCP4725_I2CADDR_DEFAULT, &Wire);
  digital_throttle.setVoltage(0, false, 100000UL);
}

void loop()
{
    control_state(contr_str, contrl_thr);
}