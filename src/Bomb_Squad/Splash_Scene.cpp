#include "Splash_Scene.h"
#include "Display.h"
#include "Strings.h"
#include "Color.h"

char *SplashScene::Bootstrap() {

  return SPLASH_FILE;
}

void SplashScene::HandleFrame(unsigned char frame) {

  AnimateParticles(frame);
  AnimateText(frame);
}

void SplashScene::AnimateText(unsigned char frame) {

  static bool show = true;
  const char splash_press_button[] = "[PRESS BUTTON]";

  if(frame == 0) {
    _screen->setTextColor(show ? COLOR_TEXT : COLOR_BG);
    show = !show;

    _screen->setTextSize(FONT_SIZE_SMALL);
    _screen->setCursor(TFT_W2 - (FONT_SIZE_SMALL * FONT_WIDTH *
                       strlen(splash_press_button)) / 2, 100);

    _screen->print(splash_press_button);
  }
}

void SplashScene::AnimateParticles(unsigned char frame) {

  static unsigned short x = 0;
  static unsigned short y = 0;

  if(frame % 4 == 0) {
    for(unsigned char i = 0; i < PARTICLE_COUNT; i++) {
      _screen->drawPixel(FLAME_X + PARTICLE_INDEX(x, i),
                         FLAME_Y + PARTICLE_INDEX(y, i),
                         COLOR_BG);

      x = PARTICLE_SET(x, i, random(FLAME_MAX_X));
      y = PARTICLE_SET(y, i, random(FLAME_MAX_Y));

      _screen->drawPixel(FLAME_X + PARTICLE_INDEX(x, i),
                         FLAME_Y + PARTICLE_INDEX(y, i),
                         RGB(242, 50, 18));
    }
  }
}
