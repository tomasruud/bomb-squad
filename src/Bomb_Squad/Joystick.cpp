#include "Joystick.h"

JoystickDirection get_joystick_vertical_direction(uint16_t y) {

  if(y < JS_THRESHOLD)
    return JS_Up;

  else if(y > 1023 - JS_THRESHOLD)
    return JS_Down;

  else
    return JS_None;
}

uint16_t get_joystick_degree_position(uint16_t x, uint16_t y) {

  
}
