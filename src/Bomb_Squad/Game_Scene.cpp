#include "Game_Scene.h"

#include "Pitches.h"
#include "Display.h"
#include "Colors.h"
#include "Pins.h"
#include "Image.h"

#include "High_Low_Level.h"

#define CLOCK_X 120
#define CLOCK_Y 100

void GameScene::Bootstrap() {

  // Shuffle level order
  // for(uint8_t i = 0; i < _level_count - 1; i++) {
  //
  //   uint8_t j = random(1, _level_count - i);
  //
  //   LevelID temp = _levels[0];
  //   _levels[0] = _levels[j];
  //   _levels[j] = temp;
  // }

  _time = 320;
  _printed_time.did_draw = 0;

  draw_image(_screen, "0.bmp", CLOCK_X - 5, CLOCK_Y - 3);

  LoadLevel();
}

void GameScene::LoadLevel() {

  if(_level_index >= _level_count) {
    _current_level = NULL;
    return;
  }

  _current_level = BuildLevel(_levels[_level_index++]);

  if(_current_level != NULL)
    _current_level->Bootstrap();
}

Level *GameScene::BuildLevel(LevelID id) {

  switch(id) {
    case LevelID_HighLow:
      return new HighLowLevel(_screen);
  }

  return NULL;
}

void GameScene::HandleFrame(unsigned char frame) {

  if(_current_level != NULL)
    _current_level->HandleFrame(frame);

  // Play annoying bomb-beep
  if(frame % FPS == 1) {
    tone(AUDIO_PIN, NOTE_G2, 250);

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
  if(_current_level == NULL)
    return SceneID_Splash;

  LevelAction action = _current_level->HandleLevelInput();

  switch(action) {

    case NEXT:
      delete _current_level;
      LoadLevel();
    break;

    case GAME_OVER:
      // TODO
      return SceneID_Difficulty;
    break;
  }

  return SceneID_Game;
}
