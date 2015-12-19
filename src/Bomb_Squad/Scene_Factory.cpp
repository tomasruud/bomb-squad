#include "Scene_Factory.h"

#include "Splash_Scene.h"
#include "Difficulty_Scene.h"
#include "Instruction_Scene.h"
#include "Game_Scene.h"
#include "Game_Over_Scene.h"

Scene *SceneFactory::Create(SceneID id, TFT *screen) {

  switch(id) {
    case SceneID_Splash:
      return new SplashScene(screen);

    case SceneID_Difficulty:
      return new DifficultyScene(screen);

    case SceneID_Instructions:
      return new InstructionScene(screen);

    case SceneID_Game:
      return new GameScene(screen);

    case SceneID_GameOver:
      return new GameOverScene(screen, false);

    case SceneID_GameWin:
      return new GameOverScene(screen, true);
  }

  return NULL;
}
