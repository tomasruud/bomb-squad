#ifndef DIFFICULTY_SCENE_H_
#define DIFFICULTY_SCENE_H_

#include "Scene.h"
#include "Joystick.h"

#define FLAME_X 32
#define FLAME_Y 59

#define FLAME_MAX_X 5
#define FLAME_MAX_Y 4

#define PARTICLE_COUNT 5
#define PARTICLE_INDEX(var, i) ((var >> (i * 3)) & 0x7)
#define PARTICLE_SET(var, i, new) (var & ~(0x7 << (i * 3))) | ((new & 0x7) << (i * 3))

#define OPTION_X 142

class DifficultyScene : public Scene {
  public:
    DifficultyScene(TFT *screen) : Scene(screen) {}

    virtual void Bootstrap();
    virtual void HandleFrame(unsigned char frame);
    virtual SceneID HandleInput();

  private:
    const unsigned char _option_locations[3] = {52, 70, 88};

    char _option = 0;
    char _last_option = 1;

    unsigned short _x = 0;
    unsigned short _y = 0;

    JoystickDirection _last_direction = JS_None;

    void AnimateParticles(unsigned char frame);

};

#endif
