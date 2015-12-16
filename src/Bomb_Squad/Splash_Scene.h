#ifndef SPLASH_SCENE_H_
#define SPLASH_SCENE_H_

#include "Scene.h"

#define SPLASH_FILE "splash.bmp"

#define FLAME_X 96
#define FLAME_MAX_X 5

#define FLAME_Y 14
#define FLAME_MAX_Y 4

#define PARTICLE_COUNT 5
#define PARTICLE_INDEX(var, i) ((var >> (i * 3)) & 0x7)
#define PARTICLE_SET(var, i, new) (var & ~(0x7 << (i * 3))) | ((new & 0x7) << (i * 3))

class SplashScene : public Scene {
  public:
    SplashScene(TFT *screen) : Scene(screen) {}

    virtual char *Bootstrap();
    virtual void HandleFrame(unsigned char frame);
    virtual SceneID HandleInput();

  private:
    bool _show = true;
    unsigned short _x = 0;
    unsigned short _y = 0;

    void AnimateParticles(unsigned char frame);
    void AnimateText(unsigned char frame);
};

#endif
