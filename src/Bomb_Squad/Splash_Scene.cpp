#include "Splash_Scene.h"
#include "Display.h"
#include "Colors.h"
#include "Button.h"
#include "Arduino.h"
#include "Image.h"

void SplashScene::Bootstrap() {

  draw_image(_screen, "0/0.bmp", 7, 13);
  draw_image(_screen, "0/1.bmp", 21, 117);
}

void SplashScene::HandleFrame(unsigned char frame) {

  AnimateParticles(frame);
  AnimateText(frame);
}

SceneID SplashScene::HandleInput() {

  if(BUTTON_IS_DOWN)
    return SceneID_Difficulty;

  return SceneID_Splash;
}

void SplashScene::AnimateText(unsigned char frame) {

  const char splash_press_button[] = "[PRESS BUTTON]";

  if(frame == 0) {
    _screen->setTextColor(_show ? COLOR_TEXT : COLOR_BG);
    _show = !_show;

    _screen->setTextSize(FONT_SIZE_SMALL);
    _screen->setCursor(TFT_W2 - (FONT_SIZE_SMALL * FONT_WIDTH *
                       strlen(splash_press_button)) / 2, 100);

    _screen->print(splash_press_button);
  }
}

void SplashScene::AnimateParticles(unsigned char frame) {

  if(frame % 4 == 0) {
    for(unsigned char i = 0; i < PARTICLE_COUNT; i++) {
      _screen->drawPixel(FLAME_X + PARTICLE_INDEX(_x, i),
                         FLAME_Y + PARTICLE_INDEX(_y, i), COLOR_BG);

      _x = PARTICLE_SET(_x, i, random(FLAME_MAX_X));
      _y = PARTICLE_SET(_y, i, random(FLAME_MAX_Y));

      _screen->drawPixel(FLAME_X + PARTICLE_INDEX(_x, i),
                         FLAME_Y + PARTICLE_INDEX(_y, i), RGB(242, 50, 18));
    }
  }
}
