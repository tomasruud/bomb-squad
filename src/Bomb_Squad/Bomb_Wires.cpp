#include "Bomb_Wires.h"

bool wire_removed(WireColor color) {

  switch(color) {
    case W_BLUE:
      return digitalRead(BLUE_PIN) == LOW;

    case W_ORANGE:
      return digitalRead(ORANGE_PIN) == LOW;

    case W_GREEN:
      return digitalRead(GREEN_PIN) == LOW;

    case W_YELLOW:
      return digitalRead(YELLOW_PIN) == LOW;
  }

  return false;
}
