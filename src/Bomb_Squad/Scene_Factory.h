#ifndef SCENE_FACTORY_H_
#define SCENE_FACTORY_H_

#include <TFT.h>

#include "Scene_ID.h"
#include "Scene.h"

class SceneFactory {

  public:
    static Scene *Create(SceneID id, TFT *screen);
};

#endif
