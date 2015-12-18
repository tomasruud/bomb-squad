#ifndef GAME_SCENE
#define GAME_SCENE

#include "Arduino.h"
#include "Scene.h"
#include "Level.h"
#include "Level_ID.h"

class GameScene : public Scene {
  public:
    GameScene(TFT *screen) : Scene(screen) {}

    virtual void Bootstrap();
    virtual void HandleFrame(unsigned char frame);
    virtual SceneID HandleInput();

  private:
    void LoadLevel();
    Level *BuildLevel(LevelID id);

    void WriteTime();

    uint32_t _time;

    struct {
      uint16_t did_draw:1;
      uint16_t minute0:2;
      uint16_t minute1:4;
      uint16_t second0:4;
      uint16_t second1:4;
    } _printed_time;

    uint8_t _level_index = 0;
    Level *_current_level;

    LevelID _levels[1] = {
      LevelID_HighLow
    };

    const uint8_t _level_count = 1;
};

#endif
