#define USE_DEBUG
#include "Debugger.h"

#include <Thread.h>
#include <ThreadController.h>

#include <SPI.h>
#include <SD.h>
#include <TFT.h>

#include "Colors.h"
#include "Display.h"
#include "Pins.h"
#include "Scene.h"

#include "Splash_Scene.h"

TFT screen = TFT(TFT_CS, TFT_DC, TFT_RST);

Scene *scenes[] = {
  new SplashScene(&screen)
};

ThreadController thread_pool;
Thread gui_thread;

Scene *current_scene;
PImage buffer_image;

void setup() {

  DEBUG_START(9600);

  randomSeed(analogRead(5));

  setup_pins();
  setup_screen();
  if(!setup_sd())
    return;

  gui_thread.onRun(gui_render);
  gui_thread.setInterval(FRAME_DURATION);

  thread_pool.add(&gui_thread);

  load_scene(0);
}

void loop() {

  thread_pool.run();
}

void load_scene(unsigned char scene) {

  current_scene = scenes[scene];

  char *image = current_scene->Bootstrap();

  DEBUGP("Loading: ");
  DEBUG(image);

  if(image != NULL) {
    buffer_image = screen.loadImage(image);
    screen.image(buffer_image, 0, 0);
  }
}

void gui_render() {

  static unsigned char frame = 0;

  current_scene->HandleFrame(frame);

  if(frame >= FPS)
    frame = 0;
  else
    frame++;
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

void setup_pins() {

  pinMode(X_PIN, INPUT);
  pinMode(Y_PIN, INPUT);

  pinMode(JOY_X_PIN, INPUT);
  pinMode(JOY_Y_PIN, INPUT);
  pinMode(JOY_SW_PIN, INPUT);

  pinMode(AUDIO_PIN, OUTPUT);

  pinMode(BUTTON_PIN, INPUT);
}
