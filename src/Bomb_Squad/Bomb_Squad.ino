#include <Thread.h>
#include <ThreadController.h>

#include <SPI.h>
#include <SD.h>
#include <TFT.h>

#include "Colors.h"
#include "Debugger.h"
#include "Display.h"
#include "Globals.h"
#include "Image.h"
#include "Pins.h"
#include "Scene.h"
#include "Scene_Factory.h"
#include "Scene_ID.h"
#include "Transition.h"

#define INPUT_READ_RATE 10
#define BOOT_SCENE SceneID_Splash

uint8_t g_difficulty = 0;
int16_t g_time_left = 0;

TFT screen = TFT(TFT_CS, TFT_DC, TFT_RST);

ThreadController thread_pool;

Thread gui_thread;
Thread input_thread;
Thread timer_thread;

Scene *current_scene;
SceneID current_scene_id;

void setup() {

  DEBUG_START(9600);

  uint32_t seed = abs((analogRead(A0) + 1) *
                      (analogRead(A1) + 1) *
                      (analogRead(A2) + 1) *
                      (analogRead(A3) + 1) *
                      (analogRead(A4) + 1) *
                      (analogRead(A5) + 1) *
                      (analogRead(0) + 1) *
                      (analogRead(1) + 1));

  randomSeed(seed);

  setup_pins();
  setup_screen();
  if(!setup_sd())
    return;

  gui_thread.onRun(gui_render);
  gui_thread.setInterval(FRAME_DURATION);

  input_thread.onRun(handle_input);
  input_thread.setInterval(INPUT_READ_RATE);

  timer_thread.onRun(handle_timer);
  timer_thread.setInterval(1000);

  thread_pool.add(&gui_thread);
  thread_pool.add(&input_thread);
  thread_pool.add(&timer_thread);

  current_scene_id = BOOT_SCENE;
  load_scene();
}

void loop() {

  thread_pool.run();

#ifdef DEBUG_MEMORY
  extern int __heap_start, *__brkval;
  int v;
  DEBUG((int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval));
#endif
}

void load_scene() {

  current_scene = SceneFactory::Create(current_scene_id, &screen);

  if(current_scene == NULL) {
    screen.setTextColor(COLOR_TEXT);
    screen.setCursor(4, 4);
    return;
  }

  current_scene->Bootstrap();
}

void handle_timer() {

  if(current_scene != NULL)
    current_scene->HandleTimer();
}

void handle_input() {

  if(current_scene != NULL) {
    SceneID next = current_scene->HandleInput();

    // Change scene only if neccesarry
    if(next != NULL && next != current_scene_id) {
      delete current_scene;
      current_scene = NULL;

      current_scene_id = next;

      Transition::ThatsAllFolks(&screen, COLOR_TEXT, COLOR_BG);

      load_scene();
    }
  }
}

void gui_render() {

  static unsigned char frame = 0;

  if(current_scene != NULL)
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
    screen.println(F("SD"));
    return false;
  }

  return true;
}

void setup_pins() {

  pinMode(X_PIN, INPUT);
  pinMode(Y_PIN, INPUT);

  pinMode(JOY_X_PIN, INPUT);
  pinMode(JOY_Y_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  pinMode(BLUE_PIN, INPUT);
  pinMode(ORANGE_PIN, INPUT);
  pinMode(GREEN_PIN, INPUT);
  pinMode(YELLOW_PIN, INPUT);

  pinMode(AUDIO_PIN, OUTPUT);

  pinMode(KNOB_PIN, INPUT);
}
