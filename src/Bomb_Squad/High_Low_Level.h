#ifndef HIGH_LOW_LEVEL_H_
#define HIGH_LOW_LEVEL_H_

#include "Level.h"
#include "Joystick.h"

class HighLowLevel : public Level {
  public:
    HighLowLevel(TFT *screen) : Level(screen) {}

    virtual void Bootstrap();
    virtual void HandleFrame(unsigned char frame);
    virtual LevelAction HandleLevelInput();

  private:
    void DrawNumber();
    void DrawRound();
    bool CheckInput(bool higher);

    JoystickDirection _last_direction = JS_None;

    struct {
      uint32_t last_number:4;
      uint32_t next_number:4;
      uint32_t number:4;
      uint32_t round:4;
      uint32_t last_round:4;
    } _data;
};

#endif
