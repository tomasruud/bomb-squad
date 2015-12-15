#ifndef SPLASH_SCENE_H_
#define SPLASH_SCENE_H_

#include "Scene.h"

#define SPLASH_FILE "splash.bmp"

#define FLAME_MIN_X 99
#define FLAME_MAX_X 104

#define FLAME_MIN_Y 14
#define FLAME_MAX_Y 18

#define PARTICLE_COUNT 5

class SplashScene : public Scene {
  public:
    SplashScene(TFT *screen) : Scene(screen) {}

    virtual char *Bootstrap();
    virtual void HandleFrame(unsigned char frame);

  private:
    void AnimateParticles(unsigned char frame);
    void AnimateText(unsigned char frame);
};

#endif
