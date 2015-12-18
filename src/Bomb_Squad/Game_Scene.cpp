#include "Game_Scene.h"

#include "Pitches.h"
#include "Display.h"
#include "Colors.h"
#include "Pins.h"
#include "Image.h"

#include "High_Low_Level.h"
#include "Wire_Level.h"
#include "Bomb_Wires.h"

#define CLOCK_X 120
#define CLOCK_Y 100

void GameScene::Bootstrap() {

  // Shuffle level order
  for(uint8_t i = 0; i < _count.level - 1; i++) {
    uint8_t j = random(1, _count.level - i);

    LevelID temp = _levels[0];
    _levels[0] = _levels[j];
    _levels[j] = temp;
  }

  // Shuffle wire order
  for(uint8_t i = 0; i < _count.wire_level - 1; i++) {
    uint8_t j = random(1, _count.wire_level - i);

    LevelID temp = _wire_levels[0];
    _wire_levels[0] = _wire_levels[j];
    _wire_levels[j] = temp;
  }

  _time = 320;
  _printed_time.did_draw = 0;

  bool wires_are_present = false;

  while(wires_are_present == false) {
    wires_are_present = true;

    for(EACH_WIRE) {
      if(wire_removed((WireColor) wire)) {
        _screen->setCursor(20, 20);
        _screen->setTextSize(FONT_SIZE_SMALL);
        _screen->setTextColor(COLOR_TEXT);

        _screen->println("Wires are missing!");

        wires_are_present = false;
      }
    }
  }

  _screen->fillScreen(COLOR_BG);

  delay(500); // Just for prettyness

  draw_image(_screen, "0.bmp", CLOCK_X - 5, CLOCK_Y - 3);

  LoadLevel();
}

void GameScene::LoadLevel() {

  if(_indexes.level >= _count.level) {
    _done.level = 1;
    return;
  }

  _current_level = BuildLevel(_levels[_indexes.level++]);

  if(_current_level != NULL)
    _current_level->Bootstrap();
}

void GameScene::LoadWireLevel() {

  if(_indexes.wire_level >= _count.wire_level) {
    _done.wire = 1;
    return;
  }

  _current_level = BuildLevel(_wire_levels[_indexes.wire_level++]);

  if(_current_level != NULL)
    _current_level->Bootstrap();
}

Level *GameScene::BuildLevel(LevelID id) {

  switch(id) {
    case LevelID_HighLow:
      return new HighLowLevel(_screen);

    case LevelID_WireBlue:
      return new WireLevel(_screen, W_BLUE);

    case LevelID_WireOrange:
      return new WireLevel(_screen, W_ORANGE);

    case LevelID_WireGreen:
      return new WireLevel(_screen, W_GREEN);

    case LevelID_WireYellow:
      return new WireLevel(_screen, W_YELLOW);
  }

  return NULL;
}

void GameScene::HandleFrame(unsigned char frame) {

  if(_current_level != NULL)
    _current_level->HandleFrame(frame);

  if(frame % FPS == 1) {
    static bool odd = true;

    tone(AUDIO_PIN, odd ? NOTE_C3 : NOTE_F2, 250);
    odd = !odd;

    _time--;
    WriteTime();
  }
}

void GameScene::WriteTime() {

  uint8_t cursor = 0;

  if(_printed_time.did_draw == 0 || ((_time / 60) / 10) != _printed_time.minute0) {
    _screen->drawChar(CLOCK_X + cursor, CLOCK_Y, '0' + _printed_time.minute0,
                      COLOR_GRAY, COLOR_GRAY, FONT_SIZE_SMALL);

    _printed_time.minute0 = (_time / 60) / 10;

    _screen->drawChar(CLOCK_X + cursor, CLOCK_Y, '0' + _printed_time.minute0,
                      COLOR_RED, COLOR_GRAY, FONT_SIZE_SMALL);
  }

  cursor += FONT_WIDTH;

  if(_printed_time.did_draw == 0 || ((_time / 60) % 10) != _printed_time.minute1) {
    _screen->drawChar(CLOCK_X + cursor, CLOCK_Y, '0' + _printed_time.minute1,
                      COLOR_GRAY, COLOR_GRAY, FONT_SIZE_SMALL);

    _printed_time.minute1 = (_time / 60) % 10;

    _screen->drawChar(CLOCK_X + cursor, CLOCK_Y, '0' + _printed_time.minute1,
                      COLOR_RED, COLOR_GRAY, FONT_SIZE_SMALL);
  }

  cursor += FONT_WIDTH;

  if(_printed_time.did_draw == 0) {
    _screen->drawChar(CLOCK_X + cursor, CLOCK_Y, ':',
                      COLOR_RED, COLOR_GRAY, FONT_SIZE_SMALL);
  }

  cursor += FONT_WIDTH;

  if(_printed_time.did_draw == 0 || ((_time % 60) / 10) != _printed_time.second0) {
    _screen->drawChar(CLOCK_X + cursor, CLOCK_Y, '0' + _printed_time.second0,
                      COLOR_GRAY, COLOR_GRAY, FONT_SIZE_SMALL);

    _printed_time.second0 = (_time % 60) / 10;

    _screen->drawChar(CLOCK_X + cursor, CLOCK_Y, '0' + _printed_time.second0,
                      COLOR_RED, COLOR_GRAY, FONT_SIZE_SMALL);
  }

  cursor += FONT_WIDTH;

  if(_printed_time.did_draw == 0 || ((_time % 60) % 10) != _printed_time.second1) {
    _screen->drawChar(CLOCK_X + cursor, CLOCK_Y, '0' + _printed_time.second1,
                      COLOR_GRAY, COLOR_GRAY, FONT_SIZE_SMALL);

    _printed_time.second1 = (_time % 60) % 10;

    _screen->drawChar(CLOCK_X + cursor, CLOCK_Y, '0' + _printed_time.second1,
                      COLOR_RED, COLOR_GRAY, FONT_SIZE_SMALL);
  }

  _printed_time.did_draw = 1;
}

SceneID GameScene::HandleInput() {

  // TODO
  if(_done.wire && _done.level)
    return SceneID_Splash;

  LevelAction action = _current_level->HandleLevelInput();

  switch(action) {

    case NEXT:
      delete _current_level;
      LoadLevel();
    break;

    case WIRE:
      delete _current_level;
      LoadWireLevel();
    break;

    case GAME_OVER:
      // TODO
      return SceneID_Difficulty;
    break;
  }

  return SceneID_Game;
}
