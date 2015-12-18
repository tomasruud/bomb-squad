#include "High_Low_Level.h"
#include "Display.h"
#include "Colors.h"
#include "Joystick.h"

#define HIGH 10
#define MAX_ROUNDS 4

void HighLowLevel::Bootstrap() {

  _data.round = 0;
  _data.last_round = 0;

  _data.finished = 0;

  _data.next_number = random(0, HIGH);
  _data.number = random(0, HIGH);
  _data.last_number = _data.number;

  DrawNumber();
  DrawRound();
}

void HighLowLevel::HandleFrame(unsigned char frame) {

  if(_data.round > MAX_ROUNDS) {
    _data.finished = 1;

    const char text[] = "PULL OUT THE ORANGE WIRE!";

    _screen->fillScreen(COLOR_BG);
    _screen->setTextColor(COLOR_TEXT);
    _screen->setTextSize(FONT_SIZE_LARGE);
    _screen->setCursor(TFT_W2 - (strlen(text) * FONT_SIZE_LARGE / 2),
                      TFT_H2 - (FONT_SIZE_LARGE * FONT_HEIGHT) / 2);

    _screen->print(text);
    return;
  }

  if(_data.last_number != _data.number) {

    DrawNumber();
    _data.last_number = _data.number;
  }

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

  _screen->drawChar(10, 10, '0' + _data.last_round,
                    COLOR_BG, COLOR_BG, FONT_SIZE_HUGE);

  _screen->drawChar(50, 10, '0' + _data.round,
                    COLOR_TEXT, COLOR_BG, FONT_SIZE_HUGE);
}

LevelAction HighLowLevel::HandleLevelInput() {



  return STAY;
}
