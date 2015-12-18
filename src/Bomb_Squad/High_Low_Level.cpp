#include "High_Low_Level.h"
#include "Display.h"
#include "Colors.h"

#define HIGH 10
#define MAX_ROUNDS 4

void HighLowLevel::Bootstrap() {

  _data.round = 1;
  _data.last_round = 0;

  _data.next_number = random(0, HIGH);
  _data.number = random(0, HIGH);
  _data.last_number = _data.number;

  DrawNumber();
  DrawRound();
}

void HighLowLevel::HandleFrame(unsigned char frame) {

  // Draw number if needed
  if(_data.last_number != _data.number) {

    DrawNumber();
    _data.last_number = _data.number;
  }

  // Draw round if needed
  if(_data.last_round != _data.round) {

    DrawRound();
    _data.last_round = _data.round;
  }
}

void HighLowLevel::DrawNumber() {

  _screen->drawChar(10, 10, '0' + _data.last_number,
                    COLOR_BG, COLOR_BG, FONT_SIZE_HUGE);

  _screen->drawChar(10, 10, '0' + _data.number,
                    COLOR_TEXT, COLOR_BG, FONT_SIZE_HUGE);
}

void HighLowLevel::DrawRound() {

  _screen->drawChar(50, 10, '0' + _data.last_round,
                    COLOR_BG, COLOR_BG, FONT_SIZE_HUGE);

  _screen->drawChar(50, 10, '0' + _data.round,
                    COLOR_TEXT, COLOR_BG, FONT_SIZE_HUGE);
}

bool HighLowLevel::CheckInput(bool higher) {

  if(( higher && _data.next_number >= _data.number) ||
     (!higher && _data.next_number <= _data.number)) {

    _data.number = _data.next_number;
    _data.next_number = random(0, HIGH);

    return true;
  } else {
    return false;
  }
}

LevelAction HighLowLevel::HandleLevelInput() {

  JoystickDirection one_direction = get_joystick_vertical_direction();

  if(one_direction != _last_direction) {
    if(one_direction == JS_Up || one_direction == JS_Down)
      if(CheckInput(one_direction == JS_Up) == false) {

        return GAME_OVER;
      } else {
        _data.round++;

        if(_data.round > MAX_ROUNDS)
          return WIRE;
      }

    _last_direction = one_direction;
  }

  return STAY;
}
