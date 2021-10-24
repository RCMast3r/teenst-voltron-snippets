// request and verifies the status of the odrive in startup (setting the odrive to allow for control)
void arm_odrive()
{
  digitalWrite(relay_in, HIGH);
  int requested_state;

  digitalWrite(LED_BUILTIN, LOW);

  delay(100);
  delay(100);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  while ((odrive.GetCurrentState(axis_braking) != ODriveTeensyCAN::AXIS_STATE_CLOSED_LOOP_CONTROL) && 
    (odrive.GetCurrentState(axis_steering) != ODriveTeensyCAN::AXIS_STATE_CLOSED_LOOP_CONTROL))
  {
    digitalWrite(LED_BUILTIN, LOW);
    requested_state = ODriveTeensyCAN::AXIS_STATE_CLOSED_LOOP_CONTROL;
    odrive.RunState(axis_braking, requested_state);
    delay(100);
    odrive.RunState(axis_steering, requested_state);
    delay(100);
  }
  digitalWrite(LED_BUILTIN, HIGH);
  
  odrive_st = no_error;
  // analogWrite(ODRIVE_status_led, 4096);
}

// run the full calibration sequence of the odrive
void calibrate_odrive()
{
  int requested_state;
  digitalWrite(LED_BUILTIN, LOW);

  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);

  requested_state = ODriveTeensyCAN::AXIS_STATE_FULL_CALIBRATION_SEQUENCE;
  odrive.RunState(axis_steering, requested_state);
  delay(100);
  odrive.RunState(axis_braking, requested_state);
  delay(100);

  while ((odrive.GetCurrentState(axis_steering) != ODriveTeensyCAN::AXIS_STATE_IDLE) 
    && (odrive.GetCurrentState(axis_steering) != ODriveTeensyCAN::AXIS_STATE_IDLE))
  {
    delay(100);
    
  }
  delay(100);
  
  requested_state = ODriveTeensyCAN::AXIS_STATE_HOMING;
  odrive.RunState(axis_steering, requested_state);
  delay(200);
  
  while (odrive.GetCurrentState(axis_steering) != ODriveTeensyCAN::AXIS_STATE_IDLE)
  {
    delay(100);
    
  }

  digitalWrite(LED_BUILTIN, LOW);
}

void odrive_reset()
{

  odrive.ClearErrors(axis_steering);
  delay(100);
  odrive.ClearErrors(axis_braking);
  delay(100);
}

// run the calibration and arming sequence for the odrive
void armOdrivefull()
{
  odrive_reset();
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);

  // Calibrating steering and braking axises.
  calibrate_odrive();

  // Arming Odrive
  arm_odrive();
}