#include "Game_Over_Scene.h"
#include "Image.h"
#include "Pins.h"
#include "Globals.h"
#include "Display.h"

void GameOverScene::Bootstrap() {

  ImageUtil::Draw(_screen, "3/0.bmp", 39, 20);

  _screen->setTextSize(FONT_SIZE_SMALL);

  if(_win) {
    ImageUtil::Draw(_screen, "3/2.bmp", 0, 44);

    _screen->setCursor(70, 60);
    _screen->println(F("Great success"));

    return;
  }

  _screen->setCursor(40, 50);
  _screen->println((g_time_left < 0) ? F("No more time") : F("You messed up"));

  ImageUtil::Draw(_screen, "3/1.bmp", 18, 64);
}

void GameOverScene::HandleFrame(unsigned char frame) {
}

SceneID GameOverScene::HandleInput() {

  if(BUTTON_IS_DOWN)
    return SceneID_Difficulty;

  return _win ? SceneID_GameWin : SceneID_GameOver;
}
