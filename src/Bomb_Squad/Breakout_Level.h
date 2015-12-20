#ifndef LOCK_LEVEL_H_
#define LOCK_LEVEL_H_

#include "Level.h"

#include "Arduino.h"
#include "Globals.h"
#include "Display.h"

#define BLOCKS (2 + g_difficulty)
#define BLOCK_HEIGHT 8
#define BLOCK_WIDTH 16

class BreakoutLevel: public Level {
  public:
    BreakoutLevel(TFT *screen) : Level(screen) {}

    virtual void Bootstrap();
    virtual void HandleFrame(unsigned char frame);
    virtual LevelAction HandleLevelInput();

  private:
    void FlipAndIncrementX();
    void FlipAndIncrementY();

    void DrawBlocks();
    void UndrawBlockAt(uint8_t i);

    void CheckWallCollision();
    void CheckPadCollision();
    void CheckBlockCollision();

    struct {
      uint8_t x:5;
      uint8_t y:2;
      uint8_t active:1;
    } _blocks[4];

    int16_t _ball_x;
    int16_t _ball_y;

    int8_t _ball_inc_x = -1;
    int8_t _ball_inc_y = -1;

    uint8_t _pad_position;
    uint8_t _last_pad_position = TFT_W;

    struct {
      uint8_t game_over:1;
      uint8_t blocks_left:3;
    } _status = {
      .game_over = 0,
      .blocks_left = BLOCKS
    };
};

#endif
