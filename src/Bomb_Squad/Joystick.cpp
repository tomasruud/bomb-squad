#include "Joystick.h"
#include "Pins.h"
#include "Arduino.h"

JoystickDirection get_joystick_vertical_direction() {

  uint16_t y = analogRead(JOY_Y_PIN);

  if(y < JS_THRESHOLD)
    return JS_Up;

  else if(y > 1023 - JS_THRESHOLD)
    return JS_Down;

  else
    return JS_None;
}
