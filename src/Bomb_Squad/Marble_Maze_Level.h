#ifndef MARBLE_MAZE_LEVEL_H_
#define MARBLE_MAZE_LEVEL_H_

#include "Level.h"
#include "Game_Scene.h"

#define SAMPLES 10
#define WALLS 2

// X, Y and Length should be multiplied by 8
struct Wall {
  uint16_t horizontal:1;
  uint16_t x:5;
  uint16_t y:4;
  uint16_t length:5;
};

// WALL_X      0 - 19
// WALL_Y      0 - 15
// WALL_LENGTH 0 - 15 or 0 - 19

class MarbleMazeLevel : public Level {
  public:
    MarbleMazeLevel(TFT *screen) : Level(screen) {}

    virtual void Bootstrap();
    virtual void HandleFrame(unsigned char frame);
    virtual LevelAction HandleLevelInput();

    void SetContainer(GameScene *scene) {
      _container = scene;
    };

  private:
    void ReadAccelerometer();
    void HandleBounds();
    bool CheckCollision();
    void DrawWalls();

    Wall walls[WALLS] = {
      { .horizontal = 0, .x = 2, .y = 2, .length = 8 },
      { .horizontal = 1, .x = 2, .y = 10, .length = 8 }
    };

    uint16_t GetAverageX() {
      return _x_total / SAMPLES;
    };

    uint16_t GetAverageY() {
      return _y_total / SAMPLES;
    };

    GameScene *_container;

    uint16_t _x_samples[SAMPLES];
    uint16_t _y_samples[SAMPLES];

    uint16_t _x_total = 0;
    uint16_t _y_total = 0;

    int8_t _last_move_x = 0;
    int8_t _last_move_y = 0;

    int16_t _ball_position_x = 0;
    int16_t _ball_position_y = 0;

    int16_t _last_ball_position_x = 0;
    int16_t _last_ball_position_y = 0;

    uint8_t _read_index = 0;

    struct {
      uint8_t over:1;
      uint8_t won:1;
    } _game = {.over = 0, .won = 0};
};

#endif
