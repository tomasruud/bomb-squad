#include "Transition.h"
#include "Display.h"
#include "Colors.h"

#define STEP_SIZE 4
#define TRANSITION_MS 500

void Transition::Interlace() {

  for(unsigned char loop = 0; loop < 2; loop++)
    for(unsigned char i = loop * STEP_SIZE; i < TFT_H; i++) {

      _screen->drawFastHLine(0, i, TFT_W, COLOR_BG);

      if((loop * STEP_SIZE + i + 1) % STEP_SIZE == 0)
        i += STEP_SIZE;

      delay(TRANSITION_MS / TFT_H);
    }
}

void Transition::ThatsAllFolks() {

  for(unsigned char i = 0; i <= TFT_H2; i++) {

    _screen->drawFastHLine(0, i, TFT_W, COLOR_BG);
    _screen->drawFastHLine(0, TFT_H - i, TFT_W, COLOR_BG);

    delay(TRANSITION_MS / TFT_H);
  }

  delay(50);
}
