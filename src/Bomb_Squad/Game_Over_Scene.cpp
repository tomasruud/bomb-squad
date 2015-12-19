#include "Game_Over_Scene.h"
#include "Image.h"
#include "Pins.h"

void GameOverScene::Bootstrap() {
  _screen->println(_win ? F("You win!") : F("Game over!"));
}

void GameOverScene::HandleFrame(unsigned char frame) {
}

SceneID GameOverScene::HandleInput() {

  if(BUTTON_IS_DOWN)
    return SceneID_Difficulty;

  return _win ? SceneID_GameWin : SceneID_GameOver;
}
