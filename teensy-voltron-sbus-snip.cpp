#include "SBUS.h"
// a SBUS object, which is on hardware serial port 2
SBUS x8r(Serial2);
void setup()
{
x8r.begin();

}
void loop()
{
  // read the channel values of the RC receiver (16 channels in total)

  // channel 1 = throttle
  // channel 2 = steering
  // channel 5 = deadman switch
  // channel 6 = arm switch
  // channel 7 = mux switch
  if (x8r.readCal(&channels[0], &failSafe, &lostFrame))
  {
    for (int i = 0; i < 16; i++)
    {
      x8r.readCal(&channels[i], &failSafe, &lostFrame);
    }

    deadman = channels[4];
    arm_switch = channels[5];
    mux_switch = channels[6];
    if (mux_switch == -1)
    {
        digitalWrite(CONTROL_LED, HIGH);
        controller_steering = max_steering * channels[1];
        controller_throttle = channels[0];
    } else {
        digitalWrite(CONTROL_LED, LOW);
    }


  }
}