#include "Scene_Factory.h"

#include "Splash_Scene.h"

Scene *SceneFactory::Create(SceneID id, TFT *screen) {

  switch(id) {
    case SceneID_Splash:
      return new SplashScene(screen);
  }

  return NULL;
}
