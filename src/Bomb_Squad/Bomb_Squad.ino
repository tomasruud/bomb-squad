#include <Thread.h>
#include <ThreadController.h>

#include <SPI.h>
#include <SD.h>
#include <TFT.h>

#define USE_DEBUG
#include "Debugger.h"

#include "Pins.h"
#include "Display.h"
#include "Color.h"
#include "Scenes.h"
#include "Strings.h"
#include "Splash.h"

TFT screen = TFT(TFT_CS, TFT_DC, TFT_RST);
PImage bitmap_buffer;

ThreadController thread_pool;
Thread gui_thread;

uint8_t frame = 0;
void (*current_frame_renderer)();

void setup() {

  DEBUG_START(9600);

  randomSeed(analogRead(0));

  prepare_pins();

  setup_screen();

  if(!setup_sd())
    return;

  gui_thread.onRun(render);
  gui_thread.setInterval(FRAME_DURATION);

  thread_pool.add(&gui_thread);

  display_intro_screen();
}

void loop() {

  thread_pool.run();
}

void render() {

  current_frame_renderer();

  if(frame >= FPS)
    frame = 0;
  else
    frame++;
}

void display_intro_screen() {

  bitmap_buffer = screen.loadImage(SPLASH);
  screen.image(bitmap_buffer, 0, 0);
  current_frame_renderer = &animate_intro_screen;
}

void animate_intro_screen() {

  animate_flame_particles(frame);
  animate_start_text(frame);
}

void animate_flame_particles(uint8_t frame) {

  static uint8_t x[PARTICLE_COUNT] = {
    RANDOM_FLAME_X, RANDOM_FLAME_X, RANDOM_FLAME_X
  };

  static uint8_t y[PARTICLE_COUNT] = {
    RANDOM_FLAME_Y, RANDOM_FLAME_Y, RANDOM_FLAME_Y
  };

  if(frame % 4 == 0) {
    for(uint8_t i = 0; i < PARTICLE_COUNT; i++) {
      screen.drawRect(x[i], y[i], 1, 1, COLOR_BG);

      x[i] = random(FLAME_MIN_X, FLAME_MAX_X);
      y[i] = random(FLAME_MIN_Y, FLAME_MAX_Y);

      screen.drawRect(x[i], y[i], 1, 1, RGB(242, 50, 18));
    }
  }
}

void animate_start_text(uint8_t frame) {

 static bool show = true;

 if(frame == 0) {
   screen.setTextColor(show ? COLOR_TEXT : COLOR_BG);
   show = !show;

   screen.setTextSize(FONT_SIZE_SMALL);
   screen.setCursor(TFT_W2 - (FONT_SIZE_SMALL * FONT_WIDTH *
                              strlen(splash_press_button)) / 2, 100);

   screen.print(splash_press_button);
 }
}

void setup_screen() {

  screen.initR(INITR_BLACKTAB);
  screen.setRotation(1);
  screen.fillScreen(COLOR_BG);
}

bool setup_sd() {

  if(!SD.begin(SD_CS)) {
    screen.println("No SD-card");
    return false;
  }

  return true;
}

void prepare_pins() {

  pinMode(X_PIN, INPUT);
  pinMode(Y_PIN, INPUT);

  pinMode(JOY_X_PIN, INPUT);
  pinMode(JOY_Y_PIN, INPUT);
  pinMode(JOY_SW_PIN, INPUT);

  pinMode(AUDIO_PIN, OUTPUT);

  pinMode(BUTTON_PIN, INPUT);
}
