#include "Transition.h"
#include "Display.h"
#include "Colors.h"

#define STEP_SIZE 4
#define TRANSITION_MS 500
#define WORM_SIZE 8

void Transition::Interlace(TFT *_screen) {

  for(uint8_t loop = 0; loop < 2; loop++)
    for(uint8_t i = loop * STEP_SIZE; i < TFT_H; i++) {

      _screen->drawFastHLine(0, i, TFT_W, COLOR_BG);

      if((loop * STEP_SIZE + i + 1) % STEP_SIZE == 0)
        i += STEP_SIZE;

      delay(TRANSITION_MS / TFT_H);
    }
}

void Transition::Explode(TFT *_screen) {

  for(uint8_t i = 0; i < ((TFT_H * TFT_W) / WORM_SIZE); i += (WORM_SIZE * WORM_SIZE)) {

  }
}

void Transition::ThatsAllFolks(TFT *_screen) {

  for(uint8_t i = 0; i < TFT_H2; i++) {

    _screen->drawFastHLine(0, i, TFT_W, COLOR_TEXT);
    _screen->drawFastHLine(0, TFT_H - 1 - i, TFT_W, COLOR_TEXT);

    delay((TRANSITION_MS / 2) / TFT_H);
  }

  for(int16_t i = TFT_H2; i >= 0; i--) {

    _screen->drawFastHLine(0, i, TFT_W, COLOR_BG);
    _screen->drawFastHLine(0, TFT_H - 1 - i, TFT_W, COLOR_BG);

    delay((TRANSITION_MS / 2) / TFT_H);
  }

  delay(10);
}
