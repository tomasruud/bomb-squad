#ifndef HIGH_LOW_LEVEL_SCENE
#define HIGH_LOW_LEVEL_SCENE

#include "Scene.h"

class HighLowLevelScene : public Scene {
  public:
    HighLowLevelScene(TFT *screen) : Scene(screen) {}

    virtual void Bootstrap();
    virtual void HandleFrame(unsigned char frame);
    virtual SceneID HandleInput();

  private:
    struct {
      uint8_t last_number:4;
    } _data;
};

#endif
