#ifndef GAME_SCENE
#define GAME_SCENE

#include "Scene.h"

class GameScene : public Scene {
  public:
    GameScene(TFT *screen) : Scene(screen) {}

    virtual void Bootstrap();
    virtual void HandleFrame(unsigned char frame);
    virtual SceneID HandleInput();
};

#endif
