#ifndef WIRE_LEVEL_H_
#define WIRE_LEVEL_H_

#include "Level.h"
#include "Bomb_Wires.h"

class WireLevel : public Level {

  public:
    WireLevel(TFT *screen, WireColor color) : Level(screen) {
      _color = color;
    }

    virtual void Bootstrap();
    virtual void HandleFrame(unsigned char frame);
    virtual LevelAction HandleLevelInput();

  private:
    void Draw();

    WireColor _color;
};

#endif
