#ifndef LOCK_LEVEL_H_
#define LOCK_LEVEL_H_

#include "Level.h"

#include "Arduino.h"

class LockLevel: public Level {
  public:
    LockLevel(TFT *screen) : Level(screen) {}

    virtual void Bootstrap();
    virtual void HandleFrame(unsigned char frame);
    virtual LevelAction HandleLevelInput();

    struct {
      uint16_t first:4;
      uint16_t second:4;
      uint16_t third:4;
      uint16_t fourth:4;
    } _numbers;
};

#endif
