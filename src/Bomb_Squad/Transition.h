#ifndef TRANSITION_H_
#define TRANSITION_H_

#include <TFT.h>

class Transition {
  public:
    static void Interlace(TFT *screen);
    static void ThatsAllFolks(TFT *screen, uint16_t from, uint16_t to);
    static void Expand(TFT *screen, uint16_t to);
    static void Close(TFT *screen, uint16_t to);
    static void Explode(TFT *screen);
    static void Circle(TFT *screen, uint16_t color);
};

#endif
