#include "Marble_Maze_Level.h"

#include "Accelerometer.h"
#include "Colors.h"
#include "Debugger.h"
#include "Display.h"
#include "Pins.h"
#include "Transition.h"

#define THRESHOLD 1
#define BOUNDS 50
#define MAX_SPEED 12

#define BALL_SIZE 8

#define MIN_X 0
#define MIN_Y 0

#define MAX_X TFT_W - BALL_SIZE
#define MAX_Y TFT_H - BALL_SIZE

#define WALL_THIKNESS 8
#define BACKGROUND RGB(243, 156, 18)

void MarbleMazeLevel::Bootstrap() {

  memset(_x_samples, 0, sizeof(_x_samples)); // Y U NO INITIALIZE MY ARRAYS
  memset(_y_samples, 0, sizeof(_y_samples)); // ;_;

  _ball_position_x = 0;
  _ball_position_y = MAX_Y;

  _last_ball_position_x = _ball_position_x;
  _last_ball_position_y = _ball_position_y;

  Transition::Expand(_screen, BACKGROUND);

  DrawWalls();
  _container->NotifyRedrawTimer();

  for(uint8_t i = 0; i < SAMPLES; i++)
    ReadAccelerometer();

  delay(100); // Coooldown
}

void MarbleMazeLevel::ReadAccelerometer() {

  _x_total -= _x_samples[_read_index];
  _y_total -= _y_samples[_read_index];

  _x_samples[_read_index] = analogRead(X_PIN);
  _y_samples[_read_index] = analogRead(Y_PIN);

  _x_total += _x_samples[_read_index];
  _y_total += _y_samples[_read_index];

  _read_index++;

  if(_read_index >= SAMPLES)
    _read_index = 0;
}

void MarbleMazeLevel::DrawWalls() {

  _screen->fillScreen(BACKGROUND);

  for(uint8_t i = 0; i < WALLS; i++) {
    Wall *wall = walls + i;

    if(wall->horizontal == 0x1)
      _screen->fillRect(wall->x * 8, wall->y * 8, wall->length * 8, WALL_THIKNESS, COLOR_GRAY);
    else
      _screen->fillRect(wall->x * 8, wall->y * 8, WALL_THIKNESS, wall->length * 8, COLOR_GRAY);
  }
}

void MarbleMazeLevel::HandleBounds() {

  if(_ball_position_x > MAX_X)
    _ball_position_x = MAX_X;

  if(_ball_position_x < MIN_X)
    _ball_position_x = MIN_X;

  if(_ball_position_y > MAX_Y)
    _ball_position_y = MAX_Y;

  if(_ball_position_y < MIN_Y)
    _ball_position_y = MIN_Y;
}

bool MarbleMazeLevel::CheckCollision() {

  for(uint8_t i = 0; i < WALLS; i++) {
    Wall *wall = walls + i;

    uint8_t wall_height = wall->horizontal ? WALL_THIKNESS : wall->length * 8;
    uint8_t wall_width  = wall->horizontal ? wall->length * 8 : WALL_THIKNESS;

    struct {
      uint8_t left:1;
      uint8_t right:1;
      uint8_t top:1;
      uint8_t bottom:1;
    } hit = {
      .left   = _ball_position_x <= wall->x * 8 + wall_width && _ball_position_x >= wall->x * 8,
      .right  = _ball_position_x + BALL_SIZE >= wall->x * 8 && _ball_position_x + BALL_SIZE <= wall->x * 8 + wall_width,
      .top    = _ball_position_y <= wall->y * 8 + wall_height && _ball_position_y >= wall->y * 8,
      .bottom = _ball_position_y + BALL_SIZE <= wall->y * 8 + wall_height && _ball_position_y + BALL_SIZE >= wall->y * 8
    };

    if(hit.left || hit.right)
      if(hit.top || hit.bottom)
        return true;
  }

  return false;
}

void MarbleMazeLevel::HandleFrame(unsigned char frame) {

    HandleBounds();

    // Redraws only parts of the image that needs it
    if(_last_ball_position_x != _ball_position_x) {
      if(_last_ball_position_x > _ball_position_x) // Moving right
        for(uint8_t i = 0; i <= _last_ball_position_x - _ball_position_x; i++)
          _screen->drawFastVLine(_last_ball_position_x + BALL_SIZE - i, _last_ball_position_y, BALL_SIZE, BACKGROUND);

      else // Moving left
        for(uint8_t i = 0; i <= _ball_position_x - _last_ball_position_x; i++)
          _screen->drawFastVLine(_last_ball_position_x + i, _last_ball_position_y, BALL_SIZE, BACKGROUND);
    }

    if(_last_ball_position_y != _ball_position_y) {
      if(_last_ball_position_y > _ball_position_y) // Moving up
        for(uint8_t i = 0; i <= _last_ball_position_y - _ball_position_y; i++)
          _screen->drawFastHLine(_last_ball_position_x, _last_ball_position_y + BALL_SIZE - i, BALL_SIZE, BACKGROUND);

      else // Moving down
        for(uint8_t i = 0; i <= _ball_position_y - _last_ball_position_y; i++)
          _screen->drawFastHLine(_last_ball_position_x, _last_ball_position_y + i, BALL_SIZE, BACKGROUND);
    }

    _screen->fillRect(_ball_position_x, _ball_position_y, BALL_SIZE, BALL_SIZE, COLOR_TEXT);

    _last_ball_position_x = _ball_position_x;
    _last_ball_position_y = _ball_position_y;

    // Check collision after drawing
    if(CheckCollision()) {
      _game.over = 1;
      _screen->drawLine(_ball_position_x - 2, _ball_position_y - 2,
                       _ball_position_x + BALL_SIZE + 2, _ball_position_y + BALL_SIZE + 2, COLOR_RED);

      _screen->drawLine(_ball_position_x - 2, _ball_position_y + BALL_SIZE + 2,
                       _ball_position_x + BALL_SIZE + 2, _ball_position_y - 2, COLOR_RED);
    }
}

LevelAction MarbleMazeLevel::HandleLevelInput() {

  if(_game.over) {
    delay(500);
    return GAME_OVER;
  }

  if(_game.won) {
    delay(500);
    return NEXT;
  }

  ReadAccelerometer();

  int8_t move_x = 0;
  int8_t move_y = 0;

  int8_t speed_x = map(GetAverageX(), X_NORMAL - BOUNDS, X_NORMAL + BOUNDS, 0, MAX_SPEED) - (MAX_SPEED / 2);
  int8_t speed_y = map(GetAverageY(), Y_NORMAL - BOUNDS, Y_NORMAL + BOUNDS, 0, MAX_SPEED) - (MAX_SPEED / 2);

  if(abs(GetAverageX() - X_NORMAL) > THRESHOLD)
    move_x = -speed_x;

  if(abs(GetAverageY() - Y_NORMAL) > THRESHOLD)
    move_y = -speed_y;

  // Smoooothing
  if(move_x == 0 && _last_move_x != 0)
    move_x = _last_move_x / 2;

  if(move_y == 0 && _last_move_y != 0)
    move_y = _last_move_y / 2;

  _last_move_x = move_x;
  _last_move_y = move_y;

  _ball_position_x += move_x;
  _ball_position_y += move_y;

  return STAY;
}
