#ifndef TRANSITION_H_
#define TRANSITION_H_

#include <TFT.h>

class Transition {
  private:
    TFT *_screen;

  public:
    Transition(TFT *screen) { _screen = screen; }

    void Interlace();
    void ThatsAllFolks();
};

#endif
