#include "Scene_Factory.h"

#include "Splash_Scene.h"
#include "Difficulty_Scene.h"

Scene *SceneFactory::Create(SceneID id, TFT *screen) {

  switch(id) {
    case SceneID_Splash:
      return new SplashScene(screen);

    case SceneID_Difficulty:
      return new DifficultyScene(screen);
  }

  return NULL;
}
