#ifndef WIRE_LEVEL_H_
#define WIRE_LEVEL_H_

#include "Level.h"
#include "Bomb_Wires.h"
#include "Game_Scene.h";

class WireLevel : public Level {

  public:
    WireLevel(TFT *screen, WireColor color, WireArray *removed, GameScene *container) : Level(screen) {
      _color = color;
      _removed = removed;
      _container = container;
    }

    virtual void Bootstrap();
    virtual void HandleFrame(unsigned char frame);
    virtual LevelAction HandleLevelInput();

  private:
    void Draw();
    bool AlreadyDefused(WireColor color);

    WireArray *_removed;
    WireColor _color;
    GameScene *_container;
};

#endif
