#ifndef LOCK_LEVEL_SCENE
#define LOCK_LEVEL_SCENE

#include "Scene.h"

class InstructionScene : public Scene {
  public:
    InstructionScene(TFT *screen) : Scene(screen) {}

    virtual void Bootstrap();
    virtual void HandleFrame(unsigned char frame);
    virtual SceneID HandleInput();

  private:
    struct {
      unsigned char has_drawn:1;
    } _flags;
};

#endif
