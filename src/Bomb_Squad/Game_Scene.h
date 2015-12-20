#ifndef GAME_SCENE
#define GAME_SCENE

#include "Arduino.h"

#include "Scene.h"
#include "Level.h"
#include "Level_ID.h"
#include "Bomb_Wires.h"

#define LEVELS 3
#define WIRE_LEVELS 4
#define BEEP_RATE 1

class GameScene : public Scene {
  public:
    GameScene(TFT *screen) : Scene(screen) {}

    virtual void Bootstrap();
    virtual void HandleFrame(unsigned char frame);
    virtual SceneID HandleInput();
    virtual void HandleTimer();

  private:
    void LoadLevel();

    Level *BuildLevel(LevelID id);

    void WriteTime();
    void ShowIntro();

    void PrepareLevels();
    bool MissingWires();

    int16_t _time;

    struct {
      uint16_t did_draw:1;
      uint16_t minute0:2;
      uint16_t minute1:4;
      uint16_t second0:4;
      uint16_t second1:4;
    } _printed_time;

    uint8_t _level_index = 0;
    const uint8_t _level_count = WIRE_LEVELS + LEVELS;

    Level *_current_level;

    LevelID _levels[WIRE_LEVELS + LEVELS];

    WireArray _defused_wires;
};

#endif
