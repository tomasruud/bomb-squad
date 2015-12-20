#include "Breakout_Level.h"

#include "Pins.h"
#include "Colors.h"

#define PAD_Y 80

void BreakoutLevel::Bootstrap() {

  HandleLevelInput();

  _ball_x = _pad_position + BLOCK_WIDTH / 2;
  _ball_y = PAD_Y - BLOCK_HEIGHT;

  for(uint8_t i = 0; i < BLOCKS; i++) {

    _blocks[i].active = 1;

    bool unique = false;

    while(!unique) {
      unique = true;

      _blocks[i].x = random(10);
      _blocks[i].y = random(4);

      for(uint8_t j = 0; j < BLOCKS; j++) {
        if(j == i)
          continue;

        if(_blocks[i].x == _blocks[j].x && _blocks[i].y == _blocks[j].y) {
          unique = false;
          break;
        }
      }
    }
  }

  DrawBlocks();
}

void BreakoutLevel::DrawBlocks() {

  for(uint8_t i = 0; i < BLOCKS; i++)
    _screen->fillRect(_blocks[i].x * BLOCK_WIDTH, _blocks[i].y * BLOCK_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT, COLOR_GREEN);
}

void BreakoutLevel::UndrawBlockAt(uint8_t i) {

  _blocks[i].active = 0;
  _status.blocks_left--;
  _screen->fillRect(_blocks[i].x * BLOCK_WIDTH, _blocks[i].y * BLOCK_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT, COLOR_BG);
}

void BreakoutLevel::CheckWallCollision() {

  // Check collision with side walls
  if(_ball_x + BLOCK_HEIGHT >= TFT_W || _ball_x < 0)
     FlipAndIncrementX();

  // Check collision with roof and ceiling
  if(_ball_y + BLOCK_HEIGHT >= TFT_H || _ball_y < 0)
     FlipAndIncrementY();
}

void BreakoutLevel::CheckPadCollision() {

  if(_ball_inc_y < 0)
    return;

  // Pad top collision
  if(_ball_y + BLOCK_HEIGHT >= PAD_Y &&
     _ball_x < _pad_position + BLOCK_WIDTH &&
     _ball_x + BLOCK_HEIGHT > _pad_position)
     FlipAndIncrementY();

  // Check collision with pad sides
  if(_ball_y + BLOCK_HEIGHT > PAD_Y &&
     _ball_x <= _pad_position + BLOCK_WIDTH &&
     _ball_x + BLOCK_HEIGHT >= _pad_position)
    if(_ball_x + BLOCK_HEIGHT >= _pad_position ||
       _ball_x <= _pad_position + BLOCK_WIDTH) {

      FlipAndIncrementX();
      FlipAndIncrementY();
    }

  // Failsafe stuff if we are inside the pad
  if(_ball_x + BLOCK_HEIGHT >= _pad_position && _ball_x <= _pad_position + BLOCK_WIDTH)
    if(_ball_y >= PAD_Y && _ball_y <= PAD_Y + BLOCK_HEIGHT)
      if(_ball_inc_y > 0)
        FlipAndIncrementY();

  if(_ball_y >= PAD_Y + BLOCK_HEIGHT * 2)
    _status.game_over = 1;
}

void BreakoutLevel::CheckBlockCollision() {

  for(uint8_t i = 0; i < BLOCKS; i++) {

    if(!_blocks[i].active)
      continue;

    bool horizontal_bounds = _ball_x <= _blocks[i].x * BLOCK_WIDTH + BLOCK_WIDTH &&
                             _ball_x + BLOCK_HEIGHT >= _blocks[i].x * BLOCK_WIDTH;

    // Check bottom
    if(_ball_y <= _blocks[i].y * BLOCK_HEIGHT + BLOCK_HEIGHT &&
       _ball_y >= _blocks[i].y * BLOCK_HEIGHT &&
       horizontal_bounds) {

      FlipAndIncrementY();
      UndrawBlockAt(i);
      return;
    }

    // Check top
    if(_ball_y + BLOCK_HEIGHT >= _blocks[i].y * BLOCK_HEIGHT &&
       _ball_y + BLOCK_HEIGHT <= _blocks[i].y * BLOCK_HEIGHT + BLOCK_HEIGHT &&
       horizontal_bounds) {

      FlipAndIncrementY();
      UndrawBlockAt(i);
      return;
    }

    bool vertical_bounds = _ball_y <= _blocks[i].y * BLOCK_HEIGHT + BLOCK_HEIGHT &&
                           _ball_y + BLOCK_HEIGHT >= _blocks[i].y * BLOCK_HEIGHT;

    // Check Left
    if(_ball_x <= _blocks[i].x * BLOCK_WIDTH + BLOCK_WIDTH &&
       _ball_x >= _blocks[i].x * BLOCK_WIDTH &&
       vertical_bounds) {

      FlipAndIncrementX();
      UndrawBlockAt(i);
      return;
    }

    // Check Right
    if(_ball_x + BLOCK_HEIGHT >= _blocks[i].x * BLOCK_WIDTH &&
       _ball_x + BLOCK_HEIGHT <= _blocks[i].x * BLOCK_WIDTH + BLOCK_WIDTH &&
       vertical_bounds) {

      FlipAndIncrementX();
      UndrawBlockAt(i);
      return;
    }
  }
}

void BreakoutLevel::HandleFrame(unsigned char frame) {

  // Move ball
  _screen->fillRect(_ball_x, _ball_y, BLOCK_HEIGHT, BLOCK_HEIGHT, COLOR_BG);

  _ball_x += _ball_inc_x;
  _ball_y += _ball_inc_y;

  CheckWallCollision();
  CheckPadCollision();
  CheckBlockCollision();

  _screen->fillRect(_ball_x, _ball_y, BLOCK_HEIGHT, BLOCK_HEIGHT, COLOR_RED);

  // Move pad
  if(_last_pad_position != _pad_position) {
    if(_last_pad_position < _pad_position) // Moving right
      _screen->fillRect(_last_pad_position, PAD_Y, _pad_position - _last_pad_position, BLOCK_HEIGHT, COLOR_BG);
    else
      _screen->fillRect(_pad_position + BLOCK_WIDTH, PAD_Y, _last_pad_position - _pad_position, BLOCK_HEIGHT, COLOR_BG);

    _last_pad_position = _pad_position;

    _screen->fillRect(_last_pad_position, PAD_Y, BLOCK_WIDTH, BLOCK_HEIGHT, COLOR_TEXT);
  }
}

void BreakoutLevel::FlipAndIncrementX() {

  _ball_inc_x = -_ball_inc_x;
  _ball_x += _ball_inc_x;
}

void BreakoutLevel::FlipAndIncrementY() {

  _ball_inc_y = -_ball_inc_y;
  _ball_y += _ball_inc_y;
}

LevelAction BreakoutLevel::HandleLevelInput() {

  if(_status.blocks_left == 0) {
    delay(200);
    return NEXT;
  }

  if(_status.game_over)
    return GAME_OVER;

  _pad_position = map(analogRead(KNOB_PIN), 0, 1023, TFT_W - BLOCK_WIDTH, 0);

  return STAY;
}
