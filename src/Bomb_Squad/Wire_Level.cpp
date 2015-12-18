#include "Wire_Level.h"

#include "Display.h"
#include "Colors.h"
#include "Debugger.h"

void WireLevel::Bootstrap() {

  Draw();
}

void WireLevel::HandleFrame(unsigned char frame) {


}

LevelAction WireLevel::HandleLevelInput() {

  for(EACH_WIRE) {
    WireColor the_wire = (WireColor) wire;

    if(AlreadyDefused(the_wire))
      continue;

    if(_color != the_wire && BombWire::IsRemoved(the_wire))
      return GAME_OVER;

    else if(_color == the_wire && BombWire::IsRemoved(the_wire))
      return NEXT;
  }

  return STAY;
};

bool WireLevel::AlreadyDefused(WireColor color) {

  for(uint8_t i = 0; i < _removed->count; i++)
    if(_removed->wires[i] == color)
      return true;

  return false;
}

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
