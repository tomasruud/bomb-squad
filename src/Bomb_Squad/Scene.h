#ifndef SCENE_H_
#define SCENE_H_

#include <TFT.h>

#include "Scene_ID.h"

class Scene {
  protected:
    TFT *_screen;

  public:
    Scene(TFT *screen) { _screen = screen; }

    virtual void Bootstrap() {}
    virtual void HandleFrame(unsigned char frame) {}
    virtual SceneID HandleInput() {}
};

#endif
