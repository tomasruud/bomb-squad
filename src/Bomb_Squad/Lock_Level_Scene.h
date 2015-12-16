#ifndef LOCK_LEVEL_SCENE
#define LOCK_LEVEL_SCENE

#include "Scene.h"

class LockLevelScene : public Scene {
  public:
    LockLevelScene(TFT *screen) : Scene(screen) {}

    virtual void Bootstrap();
    virtual void HandleFrame(unsigned char frame);
    virtual SceneID HandleInput();

  private:
};

#endif
