#ifndef WIRE_COLORS_H_
#define WIRE_COLORS_H_

#include "Pins.h"

#define WIRES 4
#define EACH_WIRE uint8_t wire = W_BLUE; wire <= W_YELLOW; wire++

typedef enum WireColor {
  W_BLUE,
  W_ORANGE,
  W_GREEN,
  W_YELLOW
};

typedef struct WireArray {
  WireColor wires[WIRES];
  uint8_t count = 0;
};

class BombWire {
  public:
    static bool IsRemoved(WireColor color);
};

#endif
