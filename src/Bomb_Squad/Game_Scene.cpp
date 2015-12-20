#include "Game_Scene.h"

#include "Pitches.h"
#include "Display.h"
#include "Colors.h"
#include "Pins.h"
#include "Image.h"
#include "Transition.h"

#include "Debugger.h"
#include "Globals.h"

#include "High_Low_Level.h"
#include "Marble_Maze_Level.h"
#include "Wire_Level.h"
#include "Lock_Level.h"

#define CLOCK_X 124
#define CLOCK_Y 109

#define TIME_EASY 70

void GameScene::PrepareLevels() {

  LevelID game_levels[] = {
    LevelID_Lock,
    LevelID_MarbleMaze,
    LevelID_HighLow
  };

  LevelID wire_levels[] = {
    LevelID_WireBlue,
    LevelID_WireOrange,
    LevelID_WireGreen,
    LevelID_WireYellow
  };

  // Shuffle level order
  for(uint8_t i = 0; i < LEVELS - 1; i++) {
    uint8_t j = random(1, LEVELS - i);

    LevelID temp = game_levels[0];
    game_levels[0] = game_levels[j];
    game_levels[j] = temp;
  }

  // Shuffle wire order
  for(uint8_t i = 0; i < WIRE_LEVELS - 1; i++) {
    uint8_t j = random(1, WIRE_LEVELS - i);

    LevelID temp = wire_levels[0];
    wire_levels[0] = wire_levels[j];
    wire_levels[j] = temp;
  }

  // Splice levels and wires
  for(uint8_t i = 0, wire = 0, game = 0; i < _level_count; i++) {
    if(i % 2 == 1)
      _levels[i] = game_levels[game++];
    else
      _levels[i] = wire_levels[wire++];
  }
}

bool GameScene::MissingWires() {

  for(EACH_WIRE) {
    if(BombWire::IsRemoved((WireColor) wire)) {
      _screen->setCursor(20, 20);
      _screen->setTextSize(FONT_SIZE_SMALL);
      _screen->setTextColor(COLOR_TEXT);

      _screen->println(F("Wires are missing!"));

      return true;
    }
  }

  return false;
}

void GameScene::ShowIntro() {

  _screen->fillScreen(COLOR_BG);

  delay(500);

  _screen->setCursor(TFT_W2 - (4 * FONT_WIDTH), TFT_H2 - (FONT_HEIGHT / 2));
  _screen->setTextSize(FONT_SIZE_SMALL);
  _screen->setTextColor(COLOR_TEXT);

  _screen->println(F("Get ready"));

  delay(1500);

  _screen->fillScreen(COLOR_BG);

  delay(500);
}

void GameScene::Bootstrap() {

  PrepareLevels();
  while(MissingWires());

  _time = TIME_EASY - (g_difficulty * 20);
  _printed_time.did_draw = 0;

  ShowIntro();

  LoadLevel();
}

void GameScene::LoadLevel() {

  _current_level = BuildLevel(_levels[_level_index]);

  if(_current_level != NULL)
    _current_level->Bootstrap();
}

void GameScene::HandleTimer() {

  tone(AUDIO_PIN, NOTE_C4, 250); // C4 hehe

  _time--;
  g_time_left = _time;

  WriteTime();
}

Level *GameScene::BuildLevel(LevelID id) {

  switch(id) {
    case LevelID_HighLow:
      return new HighLowLevel(_screen);

    case LevelID_Lock:
      return new LockLevel(_screen);

    case LevelID_MarbleMaze:
      return new MarbleMazeLevel(_screen);

    case LevelID_WireBlue:
      return new WireLevel(_screen, W_BLUE, &_defused_wires);

    case LevelID_WireOrange:
      return new WireLevel(_screen, W_ORANGE, &_defused_wires);

    case LevelID_WireGreen:
      return new WireLevel(_screen, W_GREEN, &_defused_wires);

    case LevelID_WireYellow:
      return new WireLevel(_screen, W_YELLOW, &_defused_wires);
  }

  return NULL;
}

void GameScene::HandleFrame(unsigned char frame) {

  if(_current_level != NULL)
    _current_level->HandleFrame(frame);
}

void GameScene::WriteTime() {

  uint8_t cursor = 0;

  if(_printed_time.did_draw == 0)
    ImageUtil::Draw(_screen, 12, CLOCK_X - 9, CLOCK_Y - 21);

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

  if(_current_level == NULL)
    return SceneID_Instructions;

  LevelAction action = _current_level->HandleLevelInput();

  if(_time < 0)
    action = GAME_OVER;

  switch(action) {

    case NEXT:
      delete _current_level;
      _current_level = NULL;

      _level_index++;

      if(_level_index >= _level_count)
        return SceneID_GameWin;

      _screen->fillScreen(COLOR_BG);
      _printed_time.did_draw = 0;

      LoadLevel();
    break;

    case GAME_OVER:
      delete _current_level;
      return SceneID_GameOver;
    break;
  }

  return SceneID_Game;
}
