#ifndef WIRE_COLORS_H_
#define WIRE_COLORS_H_

#include "Pins.h"

#define WIRES 4
#define EACH_WIRE int wire = W_BLUE; wire <= W_YELLOW; wire++

typedef enum WireColor {
  W_BLUE,
  W_ORANGE,
  W_GREEN,
  W_YELLOW
};

bool wire_removed(WireColor color);

#endif
