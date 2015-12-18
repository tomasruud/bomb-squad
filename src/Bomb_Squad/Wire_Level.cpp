#include "Wire_Level.h"

#include "Display.h"
#include "Colors.h"

void WireLevel::Bootstrap() {

  Draw();
}

void WireLevel::HandleFrame(unsigned char frame) {

  
}

LevelAction WireLevel::HandleLevelInput() {

  return STAY;
};

void WireLevel::Draw() {

  const char top_text[] = "REMOVE THE";
  const char bottom_text[] = " WIRE!";
  char color[7];

  switch(_color) {
    case W_BLUE:
      strcpy(color, "BLUE");
    break;

    case W_ORANGE:
      strcpy(color, "ORANGE");
    break;

    case W_GREEN:
      strcpy(color, "GREEN");
    break;

    case W_YELLOW:
      strcpy(color, "YELLOW");
    break;
  }

  _screen->fillRect(0, 0, TFT_W, 95, COLOR_BG);
  _screen->setTextSize(FONT_SIZE_LARGE);

  _screen->setTextColor(COLOR_TEXT);
  _screen->setCursor(TFT_W2 - (strlen(top_text) * FONT_SIZE_LARGE * FONT_WIDTH / 2),
                    TFT_H2 - (FONT_SIZE_LARGE * FONT_HEIGHT));

  _screen->println(top_text);

  _screen->setTextColor(COLOR_GREEN);
  _screen->setCursor(TFT_W2 - ((strlen(bottom_text) + strlen(color)) *
                     FONT_SIZE_LARGE * FONT_WIDTH / 2), TFT_H2);

  _screen->print(color);

  _screen->setTextColor(COLOR_TEXT);
  _screen->println(bottom_text);
}
