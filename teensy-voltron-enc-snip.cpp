#include "FreqMeasure.h"

void setup()
{
    FreqMeasure.begin();
}

void loop(){
    
    // timeout for rpm
    unsigned long test = millis();
    if((test - current_rpm_change_time) > RPM_TIMEOUT) {
      rpm.data = 0;
    }
    
    if (FreqMeasure.available()) {
      // average several reading together
      sum = sum + FreqMeasure.read();
      count = count + 1;
      current_rpm_change_time = millis();
      if (count > 1) {
          float testRpm = FreqMeasure.countToFrequency(sum / count)*12;
          if ( testRpm - prev_rpm < 100)
          {
            rpm.data = testRpm;
            current_rpm = (double)testRpm;
            prev_rpm = testRpm;
          }
          // Serial.printf("Current RPM: %f \n", testRpm);
        sum = 0;
        count = 0;
        prev_rpm = testRpm;
      }
    }

}