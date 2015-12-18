#ifndef LEVEL_H_
#define LEVEL_H_

#include "Scene.h"

typedef enum LevelAction {
  STAY,
  WIRE,
  NEXT,
  GAME_OVER
};

class Level : public Scene {
  public:
    Level(TFT *screen) : Scene(screen) {}

    virtual void Bootstrap();
    virtual void HandleFrame(unsigned char frame);
    virtual LevelAction HandleLevelInput();
};

#endif
