#include <avr/pgmspace.h>

// #define SAVE_SPACE

#include "Game_Over_Scene.h"
#include "Image.h"
#include "Pins.h"
#include "Globals.h"
#include "Display.h"
#include "Pitches.h"

void GameOverScene::Bootstrap() {

  ImageUtil::Draw(_screen, 7, 39, 20);

  _screen->setTextSize(FONT_SIZE_SMALL);

  if(_win) {
    ImageUtil::Draw(_screen, 9, 0, 44);

    _screen->setCursor(70, 60);
    _screen->print(F("Bomb disarmed."));

    _screen->setCursor(70, 60 + FONT_HEIGHT);
    _screen->print(F("Great success!"));

    tone(AUDIO_PIN, NOTE_C6, 150);
    delay(200);
    tone(AUDIO_PIN, NOTE_C3, 100);
    delay(150);
    tone(AUDIO_PIN, NOTE_C6, 400);
    delay(400);

    return;
  }

  _screen->setCursor(40, 50);
  _screen->println((g_time_left < 0) ? F("No more time") : F("You messed up"));

#ifndef SAVE_SPACE
  for(uint8_t i = 0; i < 25; i++) {
    tone(AUDIO_PIN, NOTE_C6 - i * 40, 20);
    delay(40);
  }
#endif

  ImageUtil::Draw(_screen, 8, 18, 64);
}

void GameOverScene::HandleFrame(unsigned char frame) {
}

SceneID GameOverScene::HandleInput() {

  if(BUTTON_IS_DOWN)
    return SceneID_Difficulty;

  return _win ? SceneID_GameWin : SceneID_GameOver;
}
