#ifndef DIFFICULTY_SCENE_H_
#define DIFFICULTY_SCENE_H_

#include "Scene.h"
#include "Joystick.h"

#define DIFFICULTY_FILE "diffclty.bmp"

#define OPTION_X 142

class DifficultyScene : public Scene {
  public:
    DifficultyScene(TFT *screen) : Scene(screen) {}

    virtual char *Bootstrap();
    virtual void HandleFrame(unsigned char frame);
    virtual SceneID HandleInput();

  private:
    const unsigned char _option_locations[3] = {52, 70, 88};

    char _option = 0;
    char _last_option = 1;

    JoystickDirection _last_direction = JS_None;

};

#endif
