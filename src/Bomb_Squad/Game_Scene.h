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
    void LoadWireLevel();

    Level *BuildLevel(LevelID id);

    void WriteTime();

    uint32_t _time;

    struct {
      uint8_t wire:1;
      uint8_t level:1;
    } _done = {0, 0};

    struct {
      uint16_t did_draw:1;
      uint16_t minute0:2;
      uint16_t minute1:4;
      uint16_t second0:4;
      uint16_t second1:4;
    } _printed_time;

    struct {
      uint8_t level:4;
      uint8_t wire_level:4;
    } _indexes = {0, 0};

    Level *_current_level;

    LevelID _levels[1] = {
      LevelID_HighLow
    };

    LevelID _wire_levels[4] = {
      LevelID_WireBlue,
      LevelID_WireOrange,
      LevelID_WireGreen,
      LevelID_WireYellow
    };

    const struct {
      uint8_t level:4;
      uint8_t wire_level:4;
    } _count = { .level = 1, .wire_level = 4 };
};

#endif
