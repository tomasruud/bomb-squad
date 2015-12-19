#include "Transition.h"
#include "Display.h"
#include "Colors.h"

#define STEP_SIZE 4
#define TRANSITION_MS 500
#define BLOCK_SIZE 32

void Transition::Interlace(TFT *screen) {

  for(uint8_t loop = 0; loop < 2; loop++)
    for(uint8_t i = loop * STEP_SIZE; i < TFT_H; i++) {

      screen->drawFastHLine(0, i, TFT_W, COLOR_BG);

      if((loop * STEP_SIZE + i + 1) % STEP_SIZE == 0)
        i += STEP_SIZE;

      delay(TRANSITION_MS / TFT_H);
    }
}

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

void Transition::Circle(TFT *screen, uint16_t color) {

  uint8_t cols = TFT_W / BLOCK_SIZE;
  uint8_t rows = TFT_H / BLOCK_SIZE;

  for(int16_t x = 0, y = 0, i = 0; i < cols * rows; i++) {


    screen->fillRect(x, y, BLOCK_SIZE, BLOCK_SIZE, color);

    delay((TRANSITION_MS * 2) / (cols * rows));
  }
}
