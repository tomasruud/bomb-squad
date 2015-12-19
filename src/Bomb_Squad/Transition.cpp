#include "Transition.h"
#include "Display.h"
#include "Colors.h"

#define STEP_SIZE 4
#define TRANSITION_MS 500
#define BLOCK_SIZE 32

void Transition::ThatsAllFolks(TFT *screen, uint16_t from, uint16_t to) {

  Close(screen, from);
  Expand(screen, to);

  delay(10);
}

void Transition::Close(TFT *screen, uint16_t to) {

  for(uint8_t i = 0; i < TFT_H2; i++) {

    screen->drawFastHLine(0, i, TFT_W, to);
    screen->drawFastHLine(0, TFT_H - 1 - i, TFT_W, to);

    delay((TRANSITION_MS / 2) / TFT_H);
  }
}

void Transition::Expand(TFT *screen, uint16_t to) {

  for(int8_t i = TFT_H2; i >= 0; i--) {

    screen->drawFastHLine(0, i, TFT_W, to);
    screen->drawFastHLine(0, TFT_H - 1 - i, TFT_W, to);

    delay((TRANSITION_MS / 2) / TFT_H);
  }
}
