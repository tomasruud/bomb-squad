#ifndef GAME_OVER_SCENE_H_
#define GAME_OVER_SCENE_H_

#include "Scene.h"

class GameOverScene : public Scene {
  public:
    GameOverScene(TFT *screen, bool win = false) : Scene(screen) {
      _win = win;
    }

    virtual void Bootstrap();
    virtual void HandleFrame(unsigned char frame);
    virtual SceneID HandleInput();

  private:
    bool _win = false;
};

#endif
