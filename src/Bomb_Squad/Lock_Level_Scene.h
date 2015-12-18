#ifndef LOCK_LEVEL_H_
#define LOCK_LEVEL_H_

#include "Level.h"

class LockLevel: public Level {
  public:
    LockLevelScene(TFT *screen) : Level(screen) {}

    virtual void Bootstrap();
    virtual void HandleFrame(unsigned char frame);
    virtual LevelAction HandleInput();
};

#endif
